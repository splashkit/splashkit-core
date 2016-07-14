/// \file audio.cpp
/// \brief SplashKit Audio allows you to load and play music and sound effects.
///
/// # SplashKit Audio
/// The SplashKit's audio library allows you to easily load and play music and
/// sound effects within your programs. To get started with audio the first
/// thing you need to do is load a sound effect or music file. You can do this
/// by calling the load_sound_effect(string name) function to the
/// load_music(string name) function.

#include "audio_driver.h"
#include "audio.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"

#include <iostream>
#include <map>

using namespace std;

static bool _sk_audio_open = false;
static map<string, sound_effect> _sound_effects;

struct _sound_data
{
    pointer_identifier id;
    sk_sound_data effect;
    string filename, name;
};

/// Start the SplashKit audio system working.
void open_audio()
{
    sk_open_audio();
    _sk_audio_open = true;
}

/// Shutdown audio, stopping all current sounds effects and music.
void close_audio()
{
    _sk_audio_open = false;
    sk_close_audio();
}

/// Is the audio currently ready to be used.
bool audio_ready()
{
    return _sk_audio_open;
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
    
    string filePath = path_to_resource(filename, AUDIO_RESOURCE);
    
    sound_effect result = new _sound_data();
    
    result->id = AUDIO_PTR;
    result->filename = filePath;
    result->name = name;
    result->effect = sk_load_sound_data(filePath, SGSD_SOUND_EFFECT);

    // Unable to load sound effect
    if ( ! result->effect._data )
    {
        result->id = NONE_PTR;
        delete result;
        raise_warning ( cat({ "Error loading sound data for ", name, " (", filePath, ")"}) );
        return nullptr;
    }
    
    _sound_effects[name] = result;
    return result;
}

void delete_sound_effect(sound_effect effect)
{
    if ( VALID_PTR(effect, AUDIO_PTR) )
    {
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

void delete_all_sound_effects()
{
    string name;
    
    size_t sz = _sound_effects.size();
    
    for(size_t i = 0; i < sz; i++)
    {
        sound_effect effect = _sound_effects.begin()->second;
        if (VALID_PTR(effect, AUDIO_PTR))
        {
            delete_sound_effect(effect);
        }
        else
        {
            raise_warning("Sound effects contained an invalid pointer");
            _sound_effects.erase(_sound_effects.begin());
        }
    }
}

void play_sound_effect(sound_effect effect, int times, float volume)
{
    if (not audio_ready()) return;

    if ( ! VALID_PTR(effect, AUDIO_PTR) )
    {
        raise_warning("Play Sound Effect called, but no valid sound effect supplied");
        return;
    }

    //dont play if loops = 0
    if (times <= 0) return;

    //correct volume to be between 0 and 1
    if (volume < 0) volume = 0;
    else if (volume > 1) volume = 1;

    //alter repeats for multiple loops
    int loops = times - 1;

    //play the effect, seaching for a channel
    sk_play_sound(&effect->effect, loops, volume);
}