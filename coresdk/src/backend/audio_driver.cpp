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

#include "audio_driver.h"
#include "core_driver.h"

using std::cerr;
using std::endl;

#define SG_MAX_CHANNELS 64
namespace splashkit_lib
{
    static Mix_Chunk * _sk_sound_channels[SG_MAX_CHANNELS];
    static sk_sound_data * _current_music  = NULL;

    // access system data from core driver
    extern sk_system_data _sk_system_data;

    static bool _sk_audio_open = false;

    void sk_init_audio()
    {
        Mix_Init(~0);
    }

    bool sk_audio_is_open()
    {
        internal_sk_init();
        return _sk_audio_open;
    }

    void sk_open_audio()
    {
        internal_sk_init();
        if ( Mix_OpenAudio(MIX_DEFAULT_FREQUENCY, MIX_DEFAULT_FORMAT, 2, 4096 ) < 0 )
        {
            //        set_error_state("Unable to load audio. Mix_OpenAudio failed.");
            return;
        }

        Uint16 format;
        Mix_QuerySpec(&_sk_system_data.audio_specs.audio_rate, &format, &_sk_system_data.audio_specs.audio_channels);
        _sk_system_data.audio_specs.times_opened++;
        _sk_system_data.audio_specs.audio_format = format;

        Mix_AllocateChannels(SG_MAX_CHANNELS);

        _sk_audio_open = true;
    }

    void sk_close_audio()
    {
        Mix_CloseAudio();
        _sk_system_data.audio_specs.times_opened--;
        if ( 0 == _sk_system_data.audio_specs.times_opened )
        {
            sk_audiospec empty = { 0, 0, 0, 0 };
            _sk_system_data.audio_specs = empty;
            _sk_audio_open = false;
        }
    }

    int sk_get_channel(sk_sound_data *sound)
    {
        if ( (!sound) || (!sound->_data) ) return -1;

        for (int i = 0; i < SG_MAX_CHANNELS; i++)
        {
            if ( _sk_sound_channels[i] == sound->_data && Mix_Playing(i) )
            {
                return i;
            }
        }
        return -1;
    }



    sk_sound_data sk_load_sound_data(string filename, sk_sound_kind kind)
    {
        internal_sk_init();
        sk_sound_data result = { SGSD_UNKNOWN, NULL } ;

        result.kind = kind;

        switch (kind)
        {
            case SGSD_SOUND_EFFECT:
            {
                result._data = Mix_LoadWAV(filename.c_str());
                break;
            }
            case SGSD_MUSIC:
            {
                result._data = Mix_LoadMUS(filename.c_str());
                break;
            }

            case SGSD_UNKNOWN:
            default:
                return result;
        }

        if(result._data == nullptr)
        {
            cerr << Mix_GetError() << endl;
        }

        return result;
    }

    void sk_close_sound_data(sk_sound_data * sound )
    {
        if ( (!sound) || (!sound->_data) ) return;

        switch (sound->kind)
        {
            case SGSD_MUSIC:
                Mix_FreeMusic(static_cast<Mix_Music *>(sound->_data));
                break;

            case SGSD_SOUND_EFFECT:
                if (_current_music == sound)
                {
                    _current_music = NULL;
                }
                Mix_FreeChunk(static_cast<Mix_Chunk *>(sound->_data));
                break;

            case SGSD_UNKNOWN:
                break;
        }

        sound->kind = SGSD_UNKNOWN;
        sound->_data = NULL;
    }

    void sk_play_sound(sk_sound_data * sound, int loops, float volume)
    {
        if ( (!sound) || (!sound->_data) ) return;

        switch (sound->kind)
        {
            case SGSD_SOUND_EFFECT:
            {
                Mix_Chunk *effect = static_cast<Mix_Chunk *>(sound->_data);
                int channel = Mix_PlayChannel( -1, effect, loops);
                if (channel >= 0 && channel < SG_MAX_CHANNELS)
                {
                    Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
                    _sk_sound_channels[channel] = effect;   // record which channel is playing the effect
                }
                break;
            }
            case SGSD_MUSIC:
            {
                Mix_PlayMusic(static_cast<Mix_Music *>(sound->_data), loops);
                Mix_VolumeMusic(static_cast<int>(MIX_MAX_VOLUME * volume));
                _current_music = sound;
                break;
            }
            case SGSD_UNKNOWN:
                break;
        }
    }

    float sk_sound_playing(sk_sound_data * sound)
    {
        if ( ! sound ) {
            return 0.0f;
        }

        switch (sound->kind)
        {
            case SGSD_SOUND_EFFECT:
            {
                int idx = sk_get_channel(sound);
                return ( idx >= 0 && idx < SG_MAX_CHANNELS ? 1.0f : 0.0f );
            }
            case SGSD_MUSIC:
            {
                if ( _current_music == sound && Mix_PlayingMusic() ) return 1.0f;
                break;
            }

            case SGSD_UNKNOWN:
                break;
        }

        return 0.0f;
    }

    void sk_fade_in(sk_sound_data *sound, int loops, int ms)
    {
        if ( !sound ) return;

        switch (sound->kind)
        {
            case SGSD_SOUND_EFFECT:
            {
                int channel;
                channel = Mix_FadeInChannel(-1, static_cast<Mix_Chunk *>(sound->_data), loops, ms);
                if ( channel >= 0 && channel < SG_MAX_CHANNELS )
                {
                    _sk_sound_channels[channel] = static_cast<Mix_Chunk *>(sound->_data);
                }
                break;
            }

            case SGSD_MUSIC:
            {
                Mix_FadeInMusic(static_cast<Mix_Music *>(sound->_data), loops, ms);
                _current_music = sound;
                break;
            }

            case SGSD_UNKNOWN:
                break;
        }
    }

    void sk_fade_out(sk_sound_data *sound, int ms)
    {
        if ( !sound ) return;

        switch (sound->kind)
        {
            case SGSD_SOUND_EFFECT:
            {
                int channel = sk_get_channel(sound);
                Mix_FadeOutChannel(channel, ms);
                break;
            }

            case SGSD_MUSIC:
            {
                if ( _current_music == sound )
                {
                    Mix_FadeOutMusic(ms);
                    _current_music = NULL;
                }
                break;
            }

            case SGSD_UNKNOWN:
                break;
        }
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
        _current_music = NULL;
    }

    void sk_set_music_vol(float vol)
    {
        internal_sk_init();
        Mix_VolumeMusic( static_cast<int>(MIX_MAX_VOLUME * vol) );
    }

    float sk_music_vol()
    {
        internal_sk_init();
        return Mix_VolumeMusic(-1) / static_cast<float>(MIX_MAX_VOLUME);
    }

    float sk_sound_volume(sk_sound_data *sound)
    {
        if ( ! sound ) return 0.0f;

        switch (sound->kind)
        {
            case SGSD_MUSIC:
                if ( _current_music == sound ) return sk_music_vol();
                break;
            case SGSD_SOUND_EFFECT:
                return Mix_VolumeChunk(static_cast<Mix_Chunk *>(sound->_data), -1) / static_cast<float>(MIX_MAX_VOLUME);
            case SGSD_UNKNOWN:
                break;
        }

        return 0.0f;
    }

    void sk_set_sound_volume(sk_sound_data *sound, float vol)
    {
        if ( !sound ) return;

        switch (sound->kind)
        {
            case SGSD_MUSIC:
                if ( _current_music == sound )
                    sk_set_music_vol(vol);
                break;
                
            case SGSD_SOUND_EFFECT:
                Mix_VolumeChunk(static_cast<Mix_Chunk *>(sound->_data), static_cast<int>(vol * MIX_MAX_VOLUME));
                break;
                
            case SGSD_UNKNOWN:
                break;
        }
    }
    
    void sk_pause_music()
    {
        internal_sk_init();
        Mix_PauseMusic();
    }
    
    void sk_resume_music()
    {
        internal_sk_init();
        if ( Mix_PausedMusic() )
        {
            Mix_ResumeMusic();
        }
    }
    
    void sk_stop_music()
    {
        internal_sk_init();
        Mix_HaltMusic();
    }
    
    void sk_stop_sound(sk_sound_data *sound)
    {
        if ( ! sound ) return;
        
        switch (sound->kind)
        {
            case SGSD_MUSIC:
                if ( _current_music == sound ) sk_stop_music();
                break;
                
            case SGSD_SOUND_EFFECT:
            {
                for (int i = 0; i < SG_MAX_CHANNELS; i++)
                {
                    if ( _sk_sound_channels[i] == sound->_data )
                    {
                        Mix_HaltChannel(i);
                    }
                }
                break;
            }
                
            case SGSD_UNKNOWN:
                break;
        }
    }
    
    bool sk_music_playing()
    {
        internal_sk_init();
        if ( Mix_PlayingMusic() ) {
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