/**
 * @header audio
 * @author Andrew Cain
 * @brief SplashKit Audio allows you to load and play music and sound effects.
 *
 * SplashKit's audio library allows you to easily load and play music and
 * sound effects within your programs. To get started with audio the first
 * thing you need to do is load a sound effect or music file. You can do this
 * by calling the `load_sound_effect(string name)` function to the
 * `load_music(string name)` function.
 *
 * @attribute group  audio
 * @attribute static audio
 */

#ifndef sk_audio
#define sk_audio
namespace splashkit_lib
{
    /**
     * Starts the SplashKit audio system working.
     */
    void open_audio();

    /**
     * Turns off audio, stopping all current sounds effects and music.
     */
    void close_audio();

    /**
     * Checks if SplashKit audio currently ready to be used.
     *
     * Should this return `false`, you may want to use `open_audio`
     * to enable audio.
     *
     * @returns Returns `true` if the audio has been initalised.
     *
     * @attribute getter is_ready
     */
    bool audio_ready();
}
#include "sound.h"
#include "music.h"

#endif
