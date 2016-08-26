//
//  music.cpp
//  splashkit
//
//  Created by Jon Meyers on 15/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "audio_driver.h"
#include "audio.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"
#include "music.h"

#include <map>

static map<string, music> _music;

// While this is the same as sound data..
// we want the compiler to make them different!
struct _music_data
{
    pointer_identifier id;
    sk_sound_data audio;
    string filename, name;
};

music load_music(string name, string filename)
{
    if (has_music(name)) return music_named(name);
    
    string file_path = path_to_resource(filename, AUDIO_RESOURCE);
    
    if ( ! file_exists(file_path) )
    {
        raise_warning(cat({ "Unable to locate file for ", name, " (", file_path, ")"}));
        return nullptr;
    }
    
    music result = new _music_data();
    
    result->id = MUSIC_PTR;
    result->filename = file_path;
    result->name = name;
    result->audio = sk_load_sound_data(file_path, SGSD_MUSIC);
    
    // Unable to load sound effect
    if ( ! result->audio._data )
    {
        result->id = NONE_PTR;
        delete result;
        raise_warning ( cat({ "Error loading sound data for ", name, " (", file_path, ")"}) );
        return nullptr;
    }
    
    _music[name] = result;
    return result;
}

void free_music(music effect)
{
    if ( VALID_PTR(effect, MUSIC_PTR) )
    {
        _music.erase(effect->name);
        sk_close_sound_data(&effect->audio);
        effect->id = NONE_PTR;  // ensure future use of this pointer will fail...
        delete(effect);
    }
    else
    {
        raise_warning("Delete music called without valid music");
    }
}

void free_all_music()
{
    string name;
    
    size_t sz = _music.size();
    
    for(size_t i = 0; i < sz; i++)
    {
        music effect = _music.begin()->second;
        if (VALID_PTR(effect, MUSIC_PTR))
        {
            free_music(effect);
        }
        else
        {
            raise_warning("Music contained an invalid pointer");
            _music.erase(_music.begin());
        }
    }
}

bool has_music(string name)
{
    return _music.count(name) > 0;
}

music music_named(string name)
{
    if (has_music(name))
        return _music[name];
    else
        return nullptr;
}

void play_music(music data, int times, float volume)
{
    if ( !audio_ready() )
        return;
    
    if ( INVALID_PTR(data, MUSIC_PTR) )
    {
        raise_warning("Attempting to play music with invalid data");
        return;
    }
    
    sk_play_sound(&data->audio, times, volume);
}

void play_music(music data)
{
    play_music(data, 1, 1.0f);
}

void play_music(music data, int times)
{
    play_music(data, times, 1.0f);
}

void play_music(string name, int times)
{
    play_music(music_named(name), times, 1.0f);
}

void play_music(string name)
{
    play_music(music_named(name), 1, 1.0f);
}

void fade_music_in(music data, int times, int ms)
{
    if ( !audio_ready() )
        return;
    
    if ( INVALID_PTR(data, MUSIC_PTR) )
    {
        raise_warning("Attempting to play music with invalid data");
        return;
    }
    
    sk_fade_in(&data->audio, times, ms);
}

void fade_music_in(music data, int ms)
{
    fade_music_in(data, 1, ms);
}

void fade_music_in(string name, int times, int ms)
{
    fade_music_in(music_named(name), times, ms);
}

void fade_music_in(string name, int ms)
{
    fade_music_in(music_named(name), 1, ms);
}

void fade_music_out(int ms)
{
    sk_fade_music_out(ms);
}

void pause_music()
{
    sk_pause_music();
}

void resume_music()
{
    sk_resume_music();
}

void stop_music()
{
    sk_stop_music();
}

bool music_playing()
{
    return sk_music_playing();
}

void set_music_volume(float volume)
{
    sk_set_music_vol(volume);
}

float music_volume()
{
    return sk_music_vol();
}

string music_name(music data)
{
    if (INVALID_PTR(data, MUSIC_PTR)) return "";
    return data->name;
}

string music_filename(music data)
{
    if (INVALID_PTR(data, MUSIC_PTR)) return "";
    return data->filename;
}