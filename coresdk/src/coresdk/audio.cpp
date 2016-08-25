#include "audio_driver.h"
#include "audio.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"

#include "resource_event_notifications.h"

#include <iostream>
#include <map>

using namespace std;

static map<string, sound_effect> _sound_effects;

struct _sound_data
{
    pointer_identifier id;
    sk_sound_data effect;
    string filename, name;
};

void open_audio()
{
    sk_open_audio();
}

void close_audio()
{
    sk_close_audio();
}

bool audio_ready()
{
    return sk_audio_is_open();
}

bool has_sound_effect(string name)
{
    return _sound_effects.count(name) > 0;
}

sound_effect sound_effect_named(string name)
{
    if (has_sound_effect(name))
        return _sound_effects[name];
    else
        return nullptr;
}

sound_effect load_sound_effect(string name, string filename)
{
    if (has_sound_effect(name)) return sound_effect_named(name);

    string file_path = path_to_resource(filename, AUDIO_RESOURCE);

    if ( ! file_exists(file_path) )
    {
        raise_warning(cat({ "Unable to locate file for ", name, " (", file_path, ")"}));
        return nullptr;
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
        raise_warning ( cat({ "Error loading sound data for ", name, " (", file_path, ")"}) );
        return nullptr;
    }

    _sound_effects[name] = result;
    return result;
}

void free_sound_effect(sound_effect effect)
{
    if ( VALID_PTR(effect, AUDIO_PTR) )
    {
        notify_handlers_of_free(effect);
        
        _sound_effects.erase(effect->name);
        sk_close_sound_data(&effect->effect);
        effect->id = NONE_PTR;  // ensure future use of this pointer will fail...
        delete(effect);
    }
    else
    {
        raise_warning("Delete sound effect called without valid sound effect");
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
        raise_warning("Play Sound Effect called, but no valid sound effect supplied");
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



