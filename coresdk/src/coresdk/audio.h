#include <string>
using namespace std;

#ifndef sk_audio
#define sk_audio

/// The `SoundEffect` type is used to refer to sound effects that can be
/// played by the SwinGame audio code. Sound effects are loaded with
/// `LoadSoundEffect`, played using `PlaySoundEffect`, and must be
/// released using `FreeMusic`.
///
/// SwinGame will mix the audio from multiple sound effects, making it
/// possible to play multiple SoundEffects, or even to play the one
/// SoundEffect multiple times.
///
/// You can check if a SoundEffect is currently playing using
/// `SoundEffectPlaying`.
///
/// To stop a SoundEffect playing use `StopSoundEffect`. This will stop all
/// instances of this one sound effect from playing.
///
/// @note Use `Music` for background music for your games.
///
/// @class SoundEffect
/// @pointer_wrapper
/// @field pointer: pointer
typedef struct _sound_data *sound_effect;

/// Start the SplashKit audio system working.
///
/// @class Audio
/// @method Open
void open_audio();

/// Shutdown audio, stopping all current sounds effects and music.
///
/// @class Audio
/// @method Close
void close_audio();

/// Is the audio currently ready to be used.
///
/// @class Audio
/// @getter Ready
bool audio_ready();

/// Loads and returns a sound effect. The supplied ``filename`` is used to
/// locate the sound effect to load. The supplied ``name`` indicates the
/// name to use to refer to this SoundEffect. The `SoundEffect` can then be
/// retrieved by passing this ``name`` to the `SoundEffectNamed` function.
///
/// @class SoundEffect
/// @constructor
sound_effect load_sound_effect(string name, string filename);

/// Determines if SwinGame has a sound effect loaded for the supplied name.
/// This checks against all sounds loaded, those loaded without a name
/// are assigned the filename as a default
///
/// @class Audio
/// @method HasSoundEffect
bool has_sound_effect(string name);

/// Returns the `SoundEffect` that has been loaded with the specified name,
/// see `LoadSoundEffectNamed`.
///
/// @class Audio
/// @method SoundEffectNamed
sound_effect sound_effect_named(string name);

/// Releases the SplashKit resources associated with the sound effect.
///
/// @lib
///
/// @class SoundEffect
/// @destructor
void free_sound_effect(sound_effect effect);

/// Releases all of the sound effects that have been loaded.
///
/// @lib
///
/// @class Audio
/// @method DeleteAllSoundEffects
void free_all_sound_effects();

/// This version of PlaySoundEffect allows you to control both the number
/// of times the `SoundEffect` is repeated, and its playback volume.
///
/// @param effect   The effect indicates which sound effect to start playing.
/// @param times    Controls the number of times the sound effect is played.
/// @param vol      Indicates the percentage of the original volume to play the
///                      `SoundEffect` at. This must be between 0 and 1.
///
/// @lib
///
/// @class SoundEffect
/// @overload Play PlayWithLoopsAndVolume
///
/// @doc_details
void play_sound_effect(sound_effect effect, int times, float volume);

#endif
