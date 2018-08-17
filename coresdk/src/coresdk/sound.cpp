//
//  sound.cpp
//  splashkit
//
//  Created by Andrew Cain on 29/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//
#include "audio_driver.h"
#include "audio.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"

#include <iostream>
#include <map>

using std::map;

namespace splashkit_lib
{
    static map<string, sound_effect> _sound_effects;

    struct _sound_data
    {
        pointer_identifier id;
        sk_sound_data effect;
        string filename, name;
    };
#include "sound.h"

    bool has_sound_effect(const string &name)
    {
        return _sound_effects.count(name) > 0;
    }

    sound_effect sound_effect_named(const string &name)
    {
        if (has_sound_effect(name))
            return _sound_effects[name];
        else
        {
            string filename = path_to_resource(name, SOUND_RESOURCE);

            if ( file_exists(filename) or file_exists(name))
                return load_sound_effect(name, name);
            return nullptr;
        }
    }

    string sound_effect_name(sound_effect effect)
    {
        if (INVALID_PTR(effect, AUDIO_PTR)) return "";
        return effect->name;
    }

    string sound_effect_filename(sound_effect effect)
    {
        if (INVALID_PTR(effect, AUDIO_PTR)) return "";
        return effect->filename;
    }

    sound_effect load_sound_effect(const string &name, const string &filename)
    {
        if ( ! audio_ready() )
        {
            LOG(ERROR) << "Attempting to load sound effect when audio is closed.";
            return nullptr;
        }
        if (has_sound_effect(name)) return sound_effect_named(name);

        string file_path = filename;

        if ( ! file_exists(file_path) )
        {
            file_path = path_to_resource(filename, SOUND_RESOURCE);

            if ( ! file_exists(file_path) )
            {
                LOG(WARNING) << cat({ "Unable to locate file for ", name, " (", file_path, ")"});
                return nullptr;
            }
        }

        sound_effect result = new _sound_data();

        result->id = AUDIO_PTR;
        result->filename = file_path;
        result->name = name;
        result->effect = sk_load_sound_data(file_path, SGSD_SOUND_EFFECT);

        // Unable to load sound effect
        if ( ! result->effect._data )
        {
            result->id = NONE_PTR;
            delete result;
            LOG(WARNING) <<  cat({ "Error loading sound data for ", name, " (", file_path, ")"}) ;
            return nullptr;
        }

        _sound_effects[name] = result;
        return result;
    }

    void free_sound_effect(sound_effect effect)
    {
        if ( VALID_PTR(effect, AUDIO_PTR) )
        {
            notify_of_free(effect);

            _sound_effects.erase(effect->name);
            sk_close_sound_data(&effect->effect);
            effect->id = NONE_PTR;  // ensure future use of this pointer will fail...
            delete(effect);
        }
        else
        {
            LOG(WARNING) << "Delete sound effect called without valid sound effect";
        }
    }

    void free_all_sound_effects()
    {
        FREE_ALL_FROM_MAP(_sound_effects, AUDIO_PTR, free_sound_effect);
    }

    void play_sound_effect(sound_effect effect, int times, float volume)
    {
        if (not audio_ready()) return;

        if ( ! VALID_PTR(effect, AUDIO_PTR) )
        {
            LOG(WARNING) << "Play Sound Effect called, but no valid sound effect supplied";
            return;
        }

        // dont play if loops = 0
        if (times <= 0) return;

        // correct volume to be between 0 and 1
        if (volume < 0) volume = 0;
        else if (volume > 1) volume = 1;

        // alter repeats for multiple loops
        int loops = times - 1;

        // play the effect, seaching for a channel
        sk_play_sound(&effect->effect, loops, volume);
    }

    void play_sound_effect(sound_effect effect)
    {
        play_sound_effect(effect, 1, 1.0f);
    }

    void play_sound_effect(sound_effect effect, int times)
    {
        play_sound_effect(effect, times, 1.0f);
    }

    void play_sound_effect(sound_effect effect, float volume)
    {
        play_sound_effect(effect, 1, volume);
    }

    void play_sound_effect(const string &name, int times, float volume)
    {
        play_sound_effect(sound_effect_named(name), times, volume);
    }

    void play_sound_effect(const string &name, int times)
    {
        play_sound_effect(sound_effect_named(name), times, 1.0f);
    }

    void play_sound_effect(const string &name)
    {
        play_sound_effect(sound_effect_named(name), 1, 1.0f);
    }

    void play_sound_effect(const string &name, float volume)
    {
        play_sound_effect(sound_effect_named(name), 1, volume);
    }

    bool sound_effect_playing(sound_effect effect)
    {
        if ( INVALID_PTR(effect, AUDIO_PTR) ) return false;

        return sk_sound_playing(&effect->effect);
    }

    bool sound_effect_playing(const string &name)
    {
        return sound_effect_playing(sound_effect_named(name));
    }

    void stop_sound_effect(sound_effect effect)
    {
        if (VALID_PTR(effect, AUDIO_PTR))
            sk_stop_sound(&effect->effect);
    }

    void stop_sound_effect(const string &name)
    {
        stop_sound_effect(sound_effect_named(name));
    }

    void fade_sound_effect_out(sound_effect effect, int ms)
    {
        if (VALID_PTR(effect, AUDIO_PTR))
            sk_fade_out(&effect->effect, ms);
    }

    void fade_all_sound_effects_out(int ms)
    {
        sk_fade_all_sound_effects_out(ms);
    }
}
