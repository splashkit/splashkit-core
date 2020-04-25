//
//  AudioDriver.cpp
//
//  Created by Andrew Cain on 28/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#else
#include <SDL.h>
#include <SDL_mixer.h>
#endif

#include <iostream>
#include <sstream>
#include <AL/al.h>
#include <AL/alc.h>
#include <thread>

extern "C"{
    #include <libavutil/frame.h>
    #include <libavutil/mem.h>
    #include <libavcodec/avcodec.h>
    #include <libavformat/avformat.h>
    #include <libavutil/avutil.h>
    #include <libavutil/channel_layout.h>
    #include <libavutil/samplefmt.h>
    #include <libavutil/opt.h>
    #include <libswresample/swresample.h>
}

#include "audio_driver.h"
#include "core_driver.h"

using std::cerr;
using std::endl;

#define SG_MAX_CHANNELS 64
namespace splashkit_lib
{
    static void* _sk_sound_channels[SG_MAX_CHANNELS];
    static sk_sound_data * _current_music  = nullptr;

    // Any error bits that get set by libraries
    static int audio_last_error = 0;

    // access system data from core driver
    extern sk_system_data _sk_system_data;

    static bool _sk_audio_open = false;

    // OpenAL devices
    static ALCdevice *device = nullptr;
    static ALCcontext *openal_ctx = nullptr;

    int sk_audio_get_last_error(){
        return audio_last_error;
    }

    void set_error_from_al_error(){
        ALenum error = alGetError();
        if(error != AL_NO_ERROR){
            audio_last_error = -1;
        }
    }

    void sk_init_audio()
    {
        /* Open and initialize a device */
        if(_sk_audio_open){
            return;
        }
        device = nullptr;
        device = alcOpenDevice(nullptr);
        if (!device){
            set_error_from_al_error();
            return;
        }

        openal_ctx = alcCreateContext(device, NULL);
        if (openal_ctx == nullptr || alcMakeContextCurrent(openal_ctx) == ALC_FALSE)
        {
            if (openal_ctx != nullptr)
                alcDestroyContext(openal_ctx);
            alcCloseDevice(device);
            set_error_from_al_error();
            return;
        }

        

        const ALCchar *name;
        if (alcIsExtensionPresent(device, "ALC_ENUMERATE_ALL_EXT"))
            name = alcGetString(device, ALC_ALL_DEVICES_SPECIFIER);
        if (!name || alcGetError(device) != AL_NO_ERROR)
            name = alcGetString(device, ALC_DEVICE_SPECIFIER);
    }

    int* sk_get_device_attributes(int* size){
        alcGetIntegerv(device, ALC_ATTRIBUTES_SIZE, 1, size);
        ALCint* attrs = new ALCint[*size];
        alcGetIntegerv(device, ALC_ALL_ATTRIBUTES, *size, &attrs[0]);
        return attrs;
    }

    bool sk_audio_is_open()
    {
        internal_sk_init();
        return _sk_audio_open;
    }

    void sk_open_audio()
    {
        if(_sk_audio_open == false){
            sk_init_audio();
        }
        _sk_audio_open = true;
    }

    void sk_close_audio()
    {
        ALCdevice *device;
        ALCcontext *ctx;

        ctx = alcGetCurrentContext();
        if (ctx == NULL)
            return;

        device = alcGetContextsDevice(ctx);

        alcMakeContextCurrent(NULL);
        alcDestroyContext(ctx);
        alcCloseDevice(device);

        _sk_audio_open = false;
    }

    void format_av_error(const int ret)
    {
        // Only want to trigger this on unhandable errors
        if (ret < 0 && ret != AVERROR(EAGAIN) && ret != AVERROR_EOF)
        {
            char errbuff[1028];
            av_strerror(ret, errbuff, 1028);
            cerr << "Audio decoding error " << ret << "; message: " << errbuff << "n";
        }
    }

    void format_av_error(const void *pointer, const char *error_msg)
    {
        if (pointer == nullptr)
        {
            cerr << error_msg << "\n";
        }
    }

    const uint8_t* decode(AVCodecContext *dec_ctx,
                 AVFormatContext *form_ctx,
                 SwrContext *swr,
                 size_t* out_mem_size)
    {
        /*
        In this context of reading a file, decoding it, resampling it, and reading it memory
        the following words have the following meanings.

        Packet: a set of data read from a file/IO stream
        Frame: Encoded/Decoded data from the library
        Format: How the data is stored in the file
        Codec: The kind of compression/decompression used on the file
        Stream: One kind of data set in the file (audio, video, subtitles)

        */

        int ret = 0;

        AVPacket *pkt = av_packet_alloc();
        AVFrame *frame = av_frame_alloc();
        /* 
        Grab our first packet from the file
        */
        ret = av_read_frame(form_ctx, pkt);
        format_av_error(ret);

        ret = avcodec_send_packet(dec_ctx, pkt);
        format_av_error(ret);

        // Pointers for our data buffers for the converter to write into
        uint8_t *outData;
        int lineSize;

        // Keeping track if the amount of frames decoded changes
        int last_nb_samples = 0;

        /* read all the output frames (in general there may be any number of them */
        // We use a string stream because we just want a memory backed allocation
        std::basic_stringstream<uint8_t> stream;
        bool is_eof = false;

        ret = 0; // Clear the error number so it's not confused
        while (ret >= 0 && !is_eof)
        {
            do
            {
                if (ret == AVERROR(EAGAIN))
                {
                    // We need more data from the file to decode
                    // So grab another packet and then read it into a frame
                    ret = av_read_frame(form_ctx, pkt);
                    format_av_error(ret);
                    if (ret == AVERROR_EOF)
                    {
                        // This should probably be fixed.
                        // This loop needs to be elevated out
                        is_eof = true;
                        break;
                    }
                    ret = avcodec_send_packet(dec_ctx, pkt);
                    // needs to flush
                    if(ret == AVERROR(EINVAL)){
                        ret = avcodec_send_packet(dec_ctx, nullptr);
                        is_eof = true;
                    }
                    format_av_error(ret);
                }
                // This spits out EAGAIN when it needs another frame from the packet stream
                ret = avcodec_receive_frame(dec_ctx, frame);
            } while (ret == AVERROR(EAGAIN));

            if (is_eof)
            {
                break;
            }

            // If the frame amount has changed, we need to re-allocate our buffer
            if (frame->nb_samples != last_nb_samples)
            {
                ret = av_samples_alloc(
                    &outData,
                    &lineSize,
                    // As we are only doing alignment conversion keep we can cheat here
                    // by using the de-coded frame settings. Normally you have to figure this out
                    // by using the format changes. E.G Upsampling sample rate
                    frame->channels,
                    swr_get_out_samples(swr, frame->nb_samples),
                    AV_SAMPLE_FMT_S16,
                    0);
                last_nb_samples = frame->nb_samples;
                format_av_error(ret);
            }

            // Convert our frame to what we want through SWR
            const uint8_t **inBuf = (const uint8_t **)(frame->extended_data);
            format_av_error(ret);
            // Convert the audio to correct PCM format
            ret = swr_convert(
                swr,
                &outData,
                // Again cheating the samples because we keep the same sample rate when converting
                frame->nb_samples,
                inBuf,
                frame->nb_samples);
            format_av_error(ret);

            if (ret == AVERROR(EAGAIN) || ret == AVERROR_EOF)
                break;
            else if (ret < 0)
            {
                format_av_error(ret);
            }

            // We only care about the first channel because the data is converted to packed
            size_t size = lineSize;
            stream.write(outData, size);
            ret = 0;
        }

        stream.flush();

        uint8_t* buf = new uint8_t[stream.tellp()];
        stream.read(buf, stream.tellp());
        *out_mem_size = stream.tellp();

        return buf;
    }

    /* 
    LoadBuffer loads the named audio file into an OpenAL buffer object, and
    returns the new buffer ID.
    */
    ALuint openal_load_sound(const uint8_t *membuf, size_t buf_size, size_t sample_rate)
    {

        ALenum err = AL_NO_ERROR;
        ALuint buffer;
        ALsizei num_bytes;

        buffer = 0;
        alGenBuffers(1, &buffer);
        err = alGetError();
        if (err != AL_NO_ERROR)
        {
            cerr << "OpenAL Error: " << alGetString(err) << "\n";
            if (buffer && alIsBuffer(buffer))
                alDeleteBuffers(1, &buffer);
            return 0;
        }

        alBufferData(
            buffer,
            AL_FORMAT_STEREO16,
            membuf,
            buf_size,
            sample_rate);

        /* Check if an error occured, and clean up if so. */
        err = alGetError();
        if (err != AL_NO_ERROR)
        {
            cerr << "OpenAL Error: " << alGetString(err) << "\n";
            if (buffer && alIsBuffer(buffer))
                alDeleteBuffers(1, &buffer);
            return 0;
        }

        return buffer;
    }

    ALint openal_get_source_state(ALuint source){
        if (source > 0)
        {
            ALint sourceState;
            alGetSourcei(source, AL_SOURCE_STATE, &sourceState);
            return sourceState;
        }else{
            return -1;
        }
    }

    ALuint openal_open_sound(ALuint buffer)
    {
        ALuint source = 0;
        ALenum state;
        alGenSources(1, &source);
        alSourcei(source, AL_BUFFER, (ALint)buffer);
        auto err = alGetError();
        if(err != AL_NO_ERROR){
            cerr << "OpenAL Error: " << alGetString(err) << "\n";
        }


        return source;
    }

    void *read_audio_into_buffer(const char *filename, int *out_openal_id)
    {

        AVFormatContext *avFormatContext = NULL;
        // Return code for calls
        int ret = 0;

        // Auto figure out the codec and audio settings
        ret = avformat_open_input(&avFormatContext, filename, NULL, NULL);
        format_av_error(ret);

        // Ensure the codecs are actually decoded by reading the headers
        ret = avformat_find_stream_info(avFormatContext, NULL);
        format_av_error(ret);

        // We assume the first stream is the audio stream
        // This can be replaced with a call to find_best_stream
        AVCodecParameters *codec_context = avFormatContext->streams[0]->codecpar;
        format_av_error(codec_context, "Could not find stream 0");

        // Grab the codec ID for the stream
        AVCodec *codec = avcodec_find_decoder(codec_context->codec_id);
        format_av_error(codec, "Could not find codec");

        // AVCodecParserContext *parser = av_parser_init(codec->id);
        // format_av_error(parser, "Could not create parser");

        AVCodecContext *c = avcodec_alloc_context3(codec);
        format_av_error(c, "Could not alloc codec");

        avcodec_parameters_to_context(c, codec_context);

        ret = avcodec_open2(c, codec, NULL);
        format_av_error(ret);

        /*
        Set the audio conversion options so it can be pushed into OpenAL
        OpenAL needs PCM (packed) mono or stero, 8 or 16 bit
        we just sample to stero for simplicity and keep all the incoming audio settings.
        If you wish to change the settings for sample rate changes, or layout changes,
        then changes to the decode method need to account for this
        See https://ffmpeg.org/doxygen/trunk/group__lswr.html for all the options
        */
        SwrContext *swr = swr_alloc_set_opts(
            NULL,
            AV_CH_LAYOUT_STEREO,
            AV_SAMPLE_FMT_S16,
            codec_context->sample_rate,
            codec_context->channel_layout,
            (AVSampleFormat)codec_context->format,
            codec_context->sample_rate,
            0,
            NULL);
        swr_init(swr);
        format_av_error(swr, "Something went wrong with allocating resample context");
        // dump_av_opt(swr);

        // Heap create this so we can return it out
        size_t mem_size = 0;
        const uint8_t *stream = decode(c, avFormatContext, swr, &mem_size);
        int buf_id = openal_load_sound(stream, mem_size, codec_context->sample_rate);
        *out_openal_id = buf_id;

        // Create a struct so we can return out some information
        // in a format neutral way
        // We allocate on the heap so it doesn't get deleted when we return

        swr_close(swr);
        avcodec_free_context(&c);
        avformat_free_context(avFormatContext);

        return (void*)stream;
    };



    sk_sound_data sk_load_sound_data(string filename, sk_sound_kind kind)
    {
        internal_sk_init();
        sk_sound_data result;

        result.kind = kind;
        result._data = nullptr;
        result.openal_id = -1;
        result.openal_source_id = -1;

        result._data = read_audio_into_buffer(
            filename.c_str(),
            &(result.openal_id)
        );

        if(result._data == nullptr)
        {
            cerr << Mix_GetError() << endl;
        }

        return result;
    }

    int sk_get_channel(sk_sound_data *sound)
    {
        if ( (!sound) || (!sound->_data) ) return -1;


        return sound->openal_source_id;
    }

    void sk_close_sound_data(sk_sound_data * sound )
    {
        if ( (!sound) || (!sound->_data) ) return;

        delete (const uint8_t *)sound->_data;
        sound->_data = nullptr;

        if (sound->openal_source_id > 0)
        {
            alSourcei(sound->openal_source_id, AL_BUFFER, 0);
            alDeleteSources(1, (const ALuint *)&sound->openal_source_id);
        }
        if(sound->openal_id > 0){
            alDeleteBuffers(1, (const ALuint *)&sound->openal_id);
        }
        sound->openal_id = 0;
        sound->openal_source_id = 0;

        sound->kind = SGSD_UNKNOWN;
        sound->_data = nullptr;
    }



    void sk_play_sound(sk_sound_data * sound, int loops, float volume)
    {
        if ( (!sound) || (!sound->_data) ) return;

        if(sound->openal_source_id < 1){
            sound->openal_source_id = openal_open_sound(
                sound->openal_id);
        }
        alSourcePlay(sound->openal_source_id);
        if(sound->kind == SGSD_MUSIC){
            _current_music = sound;
        }
        sk_set_music_vol(volume);
    }

    float sk_sound_playing(sk_sound_data *sound)
    {
        if (!sound)
        {
            return 0.0f;
        }
        if (sound->openal_source_id > 0 && openal_get_source_state(sound->openal_source_id) == AL_PLAYING)
            return 1.0f;

        return 0.0f;
    }

    /**
     * @brief Fades the sound data by volume
     * 
     * @param sound sound to fade
     * @param ms time to take in milliseconds
     * @param direction 1 for fade in, else for fade out
     */
    void fade(sk_sound_data &sound, int ms, int direction)
    {
        int source = sound.openal_source_id;

        int running_ms = 0;
        // 1 for fade in (start at 0), otherwise 1 (start at 1)
        float volume = direction == 1 ? 0.0f : 1.0f;
        float volume_step = 1.0f/(ms/16.0f);
        // We want to step the volume position or negative
        // direction 1 is fade in so we want to add
        // otherwise step the volume back (negative add)
        volume_step *= (direction == 1) ? 1 : -1;
        while(running_ms < ms){
            alSourcef(source, AL_GAIN, volume);
            volume += volume_step;
            // Clip the volume to zero
            volume = (volume < 0) ? 0 : volume;
            running_ms += 16;

            std::this_thread::sleep_for(std::chrono::milliseconds(16));
        }

    }

    void sk_fade_in(sk_sound_data *sound, int loops, int ms)
    {
        if ( !sound && sound->openal_id > 0) return;
        sk_play_sound(sound, 1, 0.0f);
        std::thread *t = new std::thread(fade, std::ref(*sound), ms, 1);
        // This ensures the resources will be freed when they are done
        t->detach();
    }

    void sk_fade_out(sk_sound_data *sound, int ms)
    {
        if ( !sound && sound->openal_id > 0) return;
        sk_play_sound(sound, 1, 1.0f);
        std::thread *t = new std::thread(fade, std::ref(*sound), ms, -1);
        // This ensures the resources will be freed when they are done
        t->detach();
    }

    void sk_fade_all_sound_effects_out(int ms)
    {
        internal_sk_init();
        Mix_FadeOutChannel(-1, ms);
    }

    void sk_fade_music_out(int ms)
    {
        internal_sk_init();
        Mix_FadeOutMusic(ms);
        _current_music = nullptr;
    }

    void sk_set_music_vol(float vol)
    {
        internal_sk_init();
        sk_sound_data *sound = _current_music;
        sk_set_sound_volume(sound, vol);
    }

    float sk_music_vol()
    {
        internal_sk_init();
        sk_sound_data *sound = _current_music;
        
        return sk_sound_volume(sound);
    }

    float sk_sound_volume(sk_sound_data *sound)
    {
        if ( ! sound ) return 0.0f;
        ALfloat vol = 0;
        if (
            sound != nullptr &&
            sound->openal_source_id > 0)
        {
            alGetSourcef(sound->openal_source_id, AL_GAIN, &vol);
        }
        return 0.0f;
    }

    void sk_set_sound_volume(sk_sound_data *sound, float vol)
    {
        if ( !sound ) return;
        if (
            sound != nullptr &&
            sound->openal_source_id > 0)
        {
            ALfloat max_gain;
            alGetSourcef(sound->openal_source_id, AL_MAX_GAIN, &max_gain);
            alSourcef(sound->openal_source_id, AL_GAIN, vol*max_gain);
        }

    }

    
    void sk_pause_music()
    {
        internal_sk_init();
        sk_sound_data *sound = _current_music;
        if (
            sound != nullptr &&
            sound->openal_source_id > 0 &&
            openal_get_source_state(sound->openal_source_id) == AL_PLAYING)
        {
            alSourcePause(sound->openal_source_id);
        }
    }
    
    void sk_resume_music()
    {
        internal_sk_init();
        sk_sound_data *sound = _current_music;
        // Check if we are paused before we try to resume
        if (
            sound != nullptr &&
            sound->openal_source_id > 0 &&
            openal_get_source_state(sound->openal_source_id) == AL_PAUSED)
        {
            alSourcePlay(sound->openal_source_id);
        }
    }
    
    void sk_stop_music()
    {
        internal_sk_init();
        sk_sound_data *sound = _current_music;
        sk_stop_sound(sound);
        
    }
    
    void sk_stop_sound(sk_sound_data *sound)
    {
        if ( ! sound ) return;
        if (sound != nullptr && sound->openal_source_id > 0)
        {
            alSourceStop(sound->openal_source_id);
        }
    }
    
    bool sk_music_playing()
    {
        internal_sk_init();
        if (_current_music != nullptr && _current_music->openal_source_id > 0 && openal_get_source_state(_current_music->openal_source_id) == AL_PLAYING) {
            return true;
        }
        else
        {
            return false;
        }
    }
    
    sk_sound_data * sk_current_music()
    {
        return _current_music;
    }
}