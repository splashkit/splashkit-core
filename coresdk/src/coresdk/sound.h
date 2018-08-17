/**
 * @header sound
 * @author Andrew Cain
 * @attribute group  audio
 * @attribute static audio
 */

#ifndef sound_h
#define sound_h

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     * The `sound_effect` type is used to refer to sound effects that can be
     * played by the SplashKit audio code. Sound effects are:
     *
     *
     *   - loaded with `load_sound_effect`,
     *
     *   - played using `play_sound_effect`,
     *
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
     * Use `music` for background music for your games.
     *
     * @attribute class sound_effect
     */
    typedef struct _sound_data *sound_effect;

    /**
     * @brief Loads and returns a sound effect.
     *
     * The supplied `filename` is used to locate the sound effect to load. The
     * supplied `name` indicates the name to use to refer to this `sound_effect`.
     * The `sound_effect` can then be retrieved by passing this `name` to
     * the `sound_effect_named` function.
     *
     * @param name      The name used to refer to the sound effect.
     * @param filename  The filename used to locate the sound effect to use.
     *
     * @returns A new `sound_effect` with the initialised values provided.
     *
     * @attribute class         sound_effect
     * @attribute constructor   true
     */
    sound_effect load_sound_effect(const string &name, const string &filename);

    /**
     * Determines if SplashKit has a sound effect loaded for the supplied name.
     * This checks against all sounds loaded, those loaded without a name
     * are assigned the filename as a default. If this returns `false`, you may
     * want to use `load_sound_effect` to load in a specific sound effect and give
     * it the desired name.
     *
     * @param name The name to check if a sound effect is loaded.
     *
     * @returns Returns `true` if there is a sound effect with the given `name` has
     *          has been loaded.
     */
    bool has_sound_effect(const string &name);

    /**
     * Retrieves a `sound_effect` that has been loaded into SplashKit. If the
     * sound effect has not been loaded, this will attempt to use the name to
     * locate the file for you. If a file can be found, the sound effect is loaded
     * and returned.
     *
     * @param name The name of the sound effect to return.
     *
     * @returns Returns the `sound_effect` that has been loaded with the specified
     *          `name` using `load_sound_effect`.
     */
    sound_effect sound_effect_named(const string &name);

    /**
     * Returns the name of the `sound_effect` that has been loaded by SplashKit
     *
     * @param effect The `sound_effect` to check
     *
     * @returns Returns the name of the `sound_effect` that has been loaded
     *
     * @attribute class     sound_effect
     * @attribute getter    name
     * @attribute self      effect
     */
    string sound_effect_name(sound_effect effect);

    /**
     * Returns the filename of the `sound_effect` that has been loaded by SplashKit
     *
     * @param effect The `sound_effect` to check
     *
     * @returns Returns the filename of the `sound_effect` that has been loaded
     *
     * @attribute class     sound_effect
     * @attribute getter    filename
     * @attribute self      effect
     */
    string sound_effect_filename(sound_effect effect);

    /**
     * Checks whether the `sound_effect` is currently playing
     *
     * @param effect The `sound_effect` to be tested.
     *
     * @returns Returns whether the "sound_effect" is currently playing or not
     *
     * @attribute class     sound_effect
     * @attribute getter    is_playing
     * @attribute self      effect
     */
    bool sound_effect_playing(sound_effect effect);

    /**
     * Checks whether the `sound_effect` that matches the name is currently playing
     *
     * @param name The name of the `sound_effect`
     *
     * @returns Returns whether the "sound_effect" that matches the name is currently playing or not
     *
     * @attribute suffix  named
     */
    bool sound_effect_playing(const string &name);

    /**
     * Releases the SplashKit resources associated with the sound effect.
     *
     * @param effect The `sound_effect` whose resources should be released.
     *
     * @attribute class       sound_effect
     * @attribute destructor  true
     * @attribute self        effect
     * @attribute method      close
     */
    void free_sound_effect(sound_effect effect);

    /**
     * Releases all of the sound effects that have been loaded.
     *
     */
    void free_all_sound_effects();

    /**
     * This version of `play_sound_effect` allows you to control both the number
     * of times the `sound_effect` is repeated and its playback volume.
     *
     * @param effect   The effect indicates which sound effect to start playing.
     * @param times    Controls the number of times the sound effect is played.
     * @param volume   Indicates the percentage of the original volume to play the
     *                 `sound_effect` at. This must be between `0` and `1`.
     *
     * @attribute class   sound_effect
     * @attribute method  play
     * @attribute suffix  with_times_and_volume
     * @attribute self    effect
     */
    void play_sound_effect(sound_effect effect, int times, float volume);

    /**
     * Plays a sound effect once at full volume.
     *
     * @param effect   The effect indicates which sound effect to start playing.
     *
     * @attribute class   sound_effect
     * @attribute method  play
     * @attribute self    effect
     */
    void play_sound_effect(sound_effect effect);

    /**
     * Plays a sound effect once at full volume.
     *
     * @param effect    The effect indicates which sound effect to start playing.
     * @param times     Controls the number of times the sound effect is played.
     *
     * @attribute class   sound_effect
     * @attribute method  play
     * @attribute self    effect
     *
     * @attribute suffix  with_times
     */
    void play_sound_effect(sound_effect effect, int times);

    /**
     * Plays a sound effect once at playback volume.
     *
     * @param effect    The effect indicates which sound effect to start playing.
     * @param volume    Indicates the percentage of the original volume to play the
     *                 `sound_effect` at. This must be between `0` and `1`.
     *
     * @attribute class   sound_effect
     * @attribute method  play
     * @attribute self    effect
     *
     * @attribute suffix  with_volume
     */
    void play_sound_effect(sound_effect effect, float volume);

    /**
     * Plays a sound effect for a specified number of times and playback volume.
     *
     * @param name      The name of the effect to play.
     * @param times     Controls the number of times the sound effect is played.
     * @param volume    Indicates the percentage of the original volume to play the
     *                 `sound_effect` at. This must be between `0` and `1`.
     *
     * @attribute suffix  named_with_times_and_volume
     */
    void play_sound_effect(const string &name, int times, float volume);

    /**
     * Plays a sound effect for a specified number of times at full volume.
     *
     * @param name      The name of the effect to play.
     * @param times     Controls the number of times the sound effect is played.
     *
     * @attribute suffix  named_with_times
     */
    void play_sound_effect(const string &name, int times);

    /**
     * Plays a sound effect once at full volume.
     *
     * @param name      The name of the effect to play.
     *
     * @attribute suffix  named
     */
    void play_sound_effect(const string &name);

    /**
     * Plays a sound effect once at full volume.
     *
     * @param name      The name of the effect to play.
     * @param volume    The volume to play the `sound_effect`
     *
     * @attribute suffix  named_with_volume
     */
    void play_sound_effect(const string &name, float volume);

    /**
     * Stops the `sound_effect` if it is currently playing
     *
     * @param effect      The `sound_effect` to stop.
     *
     * @attribute class   sound_effect
     * @attribute method  stop
     * @attribute self    effect
     */
    void stop_sound_effect(sound_effect effect);

    /**
     * Stops the `sound_effect` that matches the name, if it is currently playing.
     *
     * @param name      The name of the `sound_effect` to stop.
     *
     * @attribute suffix  named
     */
    void stop_sound_effect(const string &name);

    /**
     * Fades out the `sound_effect` over the specified milliseconds.
     *
     * @param effect      The `sound_effect` to fade out.
     * @param ms          The number of milliseconds to fade out the `sound_effect`.
     *
     * @attribute class   sound_effect
     * @attribute method  fade_out
     * @attribute self    effect
     */
    void fade_sound_effect_out(sound_effect effect, int ms);

    /**
     * Fades out all `sound_effect`s over the specified milliseconds.
     *
     * @param ms The number of milliseconds to fade out all sound effects.
     */
    void fade_all_sound_effects_out(int ms);
}

#endif /* sound_h */
