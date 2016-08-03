/**
 * \headerfile audio.h
 * \brief SplashKit Audio allows you to load and play music and sound effects.
 *
 * # SplashKit Audio
 * The SplashKit's audio library allows you to easily load and play music and
 * sound effects within your programs. To get started with audio the first
 * thing you need to do is load a sound effect or music file. You can do this
 * by calling the `load_sound_effect(string name)` function to the
 * `load_music(string name)` function.
 */
#include <string>
using namespace std;

#ifndef sk_audio
#define sk_audio

/**
 * The `sound_effect` type is used to refer to sound effects that can be
 * played by the SplashKit audio code. Sound effects are:
 *
 *   - loaded with `load_sound_effect`,
 *   - played using `play_sound_effect`,
 *   - and must be released using `delete_sound_effect` (to release a specific
 *     sound effect) or `delete_all_sound_effects` (to release all loaded
 *     sound effects).
 *
 * SplashKit will mix the audio from multiple sound effects, making it
 * possible to play multiple `sound_effect`s, or even to play the one
 * `sound_effect` multiple times.
 *
 * You can check if a `sound_effect` is currently playing using
 * `sound_effect_playing`.
 *
 * To stop a `sound_effect` playing use `stop_sound_effect`. This will stop all
 * instances of this one sound effect from playing.
 *
 * \note Use `music` for background music for your games.
 *
 * \internal
 *   [class] SoundEffect
 *   [pointer_wrapper]
 *   [field] pointer: pointer
 * \endintenral
 */
typedef struct _sound_data *sound_effect;

/**
 * Starts the SplashKit audio system working.
 *
 * \internal
 *   [class] Audio
 *   [method] Open
 * \endintenral
 */
void open_audio();

/**
 * Turns off audio, stopping all current sounds effects and music.
 *
 * \internal
 *   [class]  Audio
 *   [method] Close
 * \endintenral
 */
void close_audio();

/**
 * Checks if SplashKit audio currently ready to be used.
 *
 * \returns Returns `true` if the audio has been initalised.
 *
 * \note Should this return `false`, you may want to use `open_audio` to enable
 *       audio.
 *
 * \internal
 *   [class]  Audio
 *   [getter] Ready
 * \endintenral
 */
bool audio_ready();

/**
 * Loads and returns a sound effect. The supplied `filename` is used to
 * locate the sound effect to load. The supplied `name` indicates the
 * name to use to refer to this `sound_effect`. The `sound_effect` can then be
 * retrieved by passing this `name` to the `sound_effect_named` function.
 *
 * \param name      The name used to refer to the sound effect.
 * \param filename  The filename used to locate the sound effect to use.
 *
 * \returns A new `sound_effect` with the initialised values provided.
 *
 * \internal
 *   [class] SoundEffect
 *   [constructor]
 * \endintenral
 */
sound_effect load_sound_effect(string name, string filename);

/**
 * Determines if SplashKit has a sound effect loaded for the supplied name.
 * This checks against all sounds loaded, those loaded without a name
 * are assigned the filename as a default.
 *
 * \param name The name to check if a sound effect is loaded.
 *
 * \returns Returns `true` if there is a sound effect with the given `name` has
 *          has been loaded.
 *
 * \note If this returns `false`, you may want to use `load_sound_effect` to
 *       load in a specific sound effect and give it the desired name.
 *
 * \internal
 *   [class]  Audio
 *   [method] HasSoundEffect
 * \endintenral
 */
bool has_sound_effect(string name);

/**
 * Retrieves a `sound_effect` that has been loaded into SplashKit.
 *
 * \param name The name of the sound effect to return.
 *
 * \returns Returns the `sound_effect` that has been loaded with the specified
 *          `name` using `load_sound_effect`.
 *
 * \internal
 *   [class]  Audio
 *   [method] SoundEffectNamed
 * \endintenral
 */
sound_effect sound_effect_named(string name);

/**
 * Releases the SplashKit resources associated with the sound effect.
 *
 * \param effect The `sound_effect` whose resources should be released.
 *
 * \internal
 *   [lib]
 *   [class] SoundEffect
 *   [destructor]
 * \endintenral
 */
void free_sound_effect(sound_effect effect);

/**
 * Releases all of the sound effects that have been loaded.
 *
 * \internal
 *   [lib]
 *   [class] Audio
 *   [method] FreeAllSoundEffects
 * \endintenral
 */
void free_all_sound_effects();

/**
 * This version of `play_sound_effect` allows you to control both the number
 * of times the `sound_effect` is repeated and its playback volume.
 *
 * \param effect   The effect indicates which sound effect to start playing.
 * \param times    Controls the number of times the sound effect is played.
 * \param volume   Indicates the percentage of the original volume to play the
 *                 `sound_effect` at. This must be between `0` and `1`.
 *
 * \internal
 *   [lib]
 *   [class]    SoundEffect
 *   [overload] Play PlayWithLoopsAndVolume
 * \endintenral
 */
void play_sound_effect(sound_effect effect, int times, float volume);

void play_sound_effect(sound_effect effect);

#endif
