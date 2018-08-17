//
//  SGSDK2Audio.h
//  sgsdl2
//
//  Created by Andrew Cain on 28/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifndef sk_AudioDriver_h
#define sk_AudioDriver_h

#include <string>
using std::string;

namespace splashkit_lib
{
    typedef enum sk_sound_kind
    {
        SGSD_UNKNOWN = 0,
        SGSD_SOUND_EFFECT = 1,
        SGSD_MUSIC = 2
    } sk_sound_kind;

    //
    // Sound data is an audio chunk the user can play.
    //
    typedef struct sk_sound_data
    {
        sk_sound_kind kind;

        // private data used by backend
        void * _data;
    } sk_sound_data;


    void sk_init_audio();
    void sk_open_audio();
    void sk_close_audio();
    bool sk_audio_is_open();

    int sk_get_channel(sk_sound_data *sound);

    sk_sound_data sk_load_sound_data(string filename, sk_sound_kind kind);

    void sk_close_sound_data(sk_sound_data * sound );

    void sk_play_sound(sk_sound_data * sound, int loops, float volume);

    float sk_sound_playing(sk_sound_data * sound);

    void sk_fade_in(sk_sound_data *sound, int loops, int ms);

    void sk_fade_out(sk_sound_data *sound, int ms);

    void sk_fade_all_sound_effects_out(int ms);

    void sk_fade_music_out(int ms);

    void sk_set_music_vol(float vol);

    float sk_music_vol();

    float sk_sound_volume(sk_sound_data *sound);

    void sk_set_sound_volume(sk_sound_data *sound, float vol);

    void sk_pause_music();
    
    void sk_resume_music();
    
    void sk_stop_music();
    
    void sk_stop_sound(sk_sound_data *sound);
    
    bool sk_music_playing();
    
    sk_sound_data * sk_current_music();
    
    
}
#endif /* defined(__sk__SGSDK2Audio__) */
