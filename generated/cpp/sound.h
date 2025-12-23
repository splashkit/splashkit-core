//
// SplashKit Generated Sound C++ Code
// DO NOT MODIFY
//

#ifndef __sound_h
#define __sound_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _sound_effect_data;
typedef struct _sound_effect_data *sound_effect;
/**
* Fades out all `sound_effect`s over the specified milliseconds.
* @param ms The number of milliseconds to fade out all sound effects.
*
*/;
void fade_all_sound_effects_out(int ms);
/**
* Fades out the `sound_effect` over the specified milliseconds.
* @param effect The `sound_effect` to fade out.
* @param ms The number of milliseconds to fade out the `sound_effect`.
*
*/;
void fade_sound_effect_out(sound_effect effect, int ms);
/**
* Releases all of the sound effects that have been loaded.

*
*/;
void free_all_sound_effects();
/**
* Releases the SplashKit resources associated with the sound effect.
* @param effect The `sound_effect` whose resources should be released.
*
*/;
void free_sound_effect(sound_effect effect);
/**
* Determines if SplashKit has a sound effect loaded for the supplied name.
* This checks against all sounds loaded, those loaded without a name
* are assigned the filename as a default. If this returns `false`, you may
* want to use `load_sound_effect` to load in a specific sound effect and give
* it the desired name.
* @param name The name to check if a sound effect is loaded.
* @return Returns `true` if there is a sound effect with the given `name` has
has been loaded.
*/;
bool has_sound_effect(const string &name);
/**
* The supplied `filename` is used to locate the sound effect to load. The
* supplied `name` indicates the name to use to refer to this `sound_effect`.
* The `sound_effect` can then be retrieved by passing this `name` to
* the `sound_effect_named` function.
* @param name The name used to refer to the sound effect.
* @param filename The filename used to locate the sound effect to use.
* @return A new `sound_effect` with the initialised values provided.
*/;
sound_effect load_sound_effect(const string &name, const string &filename);
/**
* Plays a sound effect once at full volume.
* @param name The name of the effect to play.
*
*/;
void play_sound_effect(const string &name);
/**
* Plays a sound effect once at full volume.
* @param name The name of the effect to play.
* @param volume The volume to play the `sound_effect`
*
*/;
void play_sound_effect(const string &name, double volume);
/**
* Plays a sound effect for a specified number of times at full volume.
* @param name The name of the effect to play.
* @param times Controls the number of times the sound effect is played.
*
*/;
void play_sound_effect(const string &name, int times);
/**
* Plays a sound effect for a specified number of times and playback volume.
* @param name The name of the effect to play.
* @param times Controls the number of times the sound effect is played.
* @param volume Indicates the percentage of the original volume to play the
* `sound_effect` at. This must be between `0` and `1`.
*
*/;
void play_sound_effect(const string &name, int times, double volume);
/**
* Plays a sound effect once at full volume.
* @param effect The effect indicates which sound effect to start playing.
*
*/;
void play_sound_effect(sound_effect effect);
/**
* Plays a sound effect once at playback volume.
* @param effect The effect indicates which sound effect to start playing.
* @param volume Indicates the percentage of the original volume to play the
* `sound_effect` at. This must be between `0` and `1`.
*
*/;
void play_sound_effect(sound_effect effect, double volume);
/**
* Plays a sound effect once at full volume.
* @param effect The effect indicates which sound effect to start playing.
* @param times Controls the number of times the sound effect is played.
*
*/;
void play_sound_effect(sound_effect effect, int times);
/**
* This version of `play_sound_effect` allows you to control both the number
* of times the `sound_effect` is repeated and its playback volume.
* @param effect The effect indicates which sound effect to start playing.
* @param times Controls the number of times the sound effect is played.
* @param volume Indicates the percentage of the original volume to play the
* `sound_effect` at. This must be between `0` and `1`.
*
*/;
void play_sound_effect(sound_effect effect, int times, double volume);
/**
* Returns the filename of the `sound_effect` that has been loaded by SplashKit
* @param effect The `sound_effect` to check
* @return Returns the filename of the `sound_effect` that has been loaded
*/;
string sound_effect_filename(sound_effect effect);
/**
* Returns the name of the `sound_effect` that has been loaded by SplashKit
* @param effect The `sound_effect` to check
* @return Returns the name of the `sound_effect` that has been loaded
*/;
string sound_effect_name(sound_effect effect);
/**
* Retrieves a `sound_effect` that has been loaded into SplashKit. If the
* sound effect has not been loaded, this will attempt to use the name to
* locate the file for you. If a file can be found, the sound effect is loaded
* and returned.
* @param name The name of the sound effect to return.
* @return Returns the `sound_effect` that has been loaded with the specified
`name` using `load_sound_effect`.
*/;
sound_effect sound_effect_named(const string &name);
/**
* Checks whether the `sound_effect` that matches the name is currently playing
* @param name The name of the `sound_effect`
* @return Returns whether the "sound_effect" that matches the name is currently playing or not
*/;
bool sound_effect_playing(const string &name);
/**
* Checks whether the `sound_effect` is currently playing
* @param effect The `sound_effect` to be tested.
* @return Returns whether the "sound_effect" is currently playing or not
*/;
bool sound_effect_playing(sound_effect effect);
/**
* Lets you test if a sound effect is valid. This will return true when it is a valid sound effect.
* @param effect the effect to test
* @return true when the sound effect is valid.
*/;
bool sound_effect_valid(sound_effect effect);
/**
* Stops the `sound_effect` that matches the name, if it is currently playing.
* @param name The name of the `sound_effect` to stop.
*
*/;
void stop_sound_effect(const string &name);
/**
* Stops the `sound_effect` if it is currently playing
* @param effect The `sound_effect` to stop.
*
*/;
void stop_sound_effect(sound_effect effect);

#endif /* __sound_h */
