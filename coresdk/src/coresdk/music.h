/**
 * @header Music
 * @author Jon Meyers
 * @brief SplashKit Audio allows you to load and play music and sound effects.
 *
 * The SplashKit's audio library allows you to easily load and play music and
 * sound effects within your programs. To get started with audio the first
 * thing you need to do is load a sound effect or music file. You can do this
 * by calling the `load_sound_effect(string name)` function to the
 * `load_music(string name)` function.
 *
 * @attribute static audio
 */

#ifndef music_h
#define music_h

/**
 * The Music type is used to refer to music that can be
 * played by SplashKit. Music files are loaded with
 * `LoadMusic`, played using `PlayMusic`, and must be
 * released using `FreeMusic`.
 *
 * Unlike `SoundEffect`s, there can only be one Music track
 * playing at a time. Playing an new track will stop the currently
 * playing music and switch to the new track.
 *
 * @attribute class music
 *
 */
typedef struct _music_data *music;

/**
 * Loads and returns a music value. The supplied `filename` is used to
 * locate the music file to load. The supplied `name` indicates the
 * name to use to refer to this Music value. The `music` can then be
 * retrieved by passing this `name` to the `music_named` function.
 *
 * @attribute class         music
 * @attribute constructor   true
 */
music load_music(string name, string filename);

/**
 * Releases the SplashKit resources associated with music.
 *
 * @param music    The music file whose resources should be released.
 *
 * @attribute class       music
 * @attribute destructor  true
 * @attribute self        music
 */
void free_music(music effect);

/**
 * Releases all of the music files that have been loaded.
 *
 * @attribute class   music
 * @attribute method  free_all_music
 * @attribute self    music
 *
 */
void free_all_music();

/**
 * Determines if SplashKit has a music file loaded for the supplied name.
 * This checks against all music files loaded, those loaded without a name
 * are assigned the filename as a default. If this returns `false`, you may
 * want to use `load_music` to load in a specific sound effect and give
 * it the desired name.
 *
 * @param name The name to check if a music file is loaded.
 *
 * @returns Returns `true` if there is a music file with the given `name` has
 *          has been loaded.
 *
 */
bool has_music(string name);

/**
 * Retrieves a 'music' that has been loaded into SplashKit.
 *
 * @param name The name of the music file to return.
 *
 * @returns Returns the `music` that has been loaded with the specified
 *          `name` using `load_music`.
 *
 */
music music_named(string name);

/**
 * Plays a music file for a specified number of times and playback volume.
 *
 * @param data      The name of the 'music' to play.
 * @param times     Controls the number of times the music is played.
 * @param volume    Indicates the percentage of the original volume to play the
 *                 `music` at. This must be between `0` and `1`.
 *
 * @attribute class   music
 * @attribute method  play
 * @attribute self    data
 *
 */
void play_music(music data, int times, float volume);

/**
 * Plays a music file once at full volume.
 *
 * @param data      The name of the 'music' to play.
 *
 * @attribute class   music
 * @attribute method  play
 * @attribute self    data
 *
 */
void play_music(music data);

/**
 * Plays a music file a specified number of times at full volume.
 *
 * @param data      The name of the 'music' to play.
 * @param times     Controls the number of times the music is played.
 *
 * @attribute class   music
 * @attribute method  play
 * @attribute self    data
 *
 */
void play_music(music data, int times);

/**
 * Plays the music file that matches the name a specified number of times at full volume.
 *
 * @param name      The name of the 'music' to play.
 * @param times     Controls the number of times the music is played.
 *
 */
void play_music(string name, int times);

/**
 * Plays the music file that matches the name once at full volume.
 *
 * @param name      The name of the 'music' to play.
 *
 */
void play_music(string name);

/**
 * Fades music up to full volume over a specified number of milliseconds 
 * for a specified number of times.
 *
 * @param data      The name of the 'music' to play.
 * @param times     Controls the number of times the music is played.
 * @param ms        How many milliseconds it takes to fade the 'music' to full volume
 *
 * @attribute class   music
 * @attribute method  fade_in
 * @attribute self    data
 *
 */
void fade_music_in(music data, int times, int ms);

/**
 * Fades music up to full volume over a specified number of milliseconds.
 *
 * @param data      The name of the 'music' to play.
 * @param ms        How many milliseconds it takes to fade the 'music' to full volume
 *
 * @attribute class   music
 * @attribute method  fade_in
 * @attribute self    data
 *
 */
void fade_music_in(music data, int ms);

/**
 * Fades music file matching the name to full volume over a specified number of milliseconds
 * and loops a specified number of times
 *
 * @param name      The name of the 'music' file to play.
 * @param times     Controls the number of times the music is played.
 * @param ms        How many milliseconds it takes to fade the 'music' to full volume
 *
 * @attribute class   music
 * @attribute method  fade_in
 * @attribute self    music
 *
 */
void fade_music_in(string name, int times, int ms);

/**
 * Fades music file matching the name to full volume over a specified number of milliseconds
 *
 * @param name      The name of the 'music' file to play.
 * @param ms        How many milliseconds it takes to fade the 'music' to full volume
 *
 * @attribute class   music
 * @attribute method  fade_in
 * @attribute self    music
 *
 */
void fade_music_in(string name, int ms);

/**
 * Fades music outover a specified number of milliseconds
 *
 * @param ms        How many milliseconds it takes to fade the 'music' out
 *
 */
void fade_music_out(int ms);

/**
 * Pauses currently playing music - see resume_music to continue playing.
 *
 */
void pause_music();

/**
 * Resumes currently paused music - see pause_music to pause playing music.
 *
 */
void resume_music();

/**
 * Stops currently playing music.
 *
 */
void stop_music();

/**
 * Checks whether music is currently playing.
 * @returns Returns true or false value representing whether music is currently playing.
 *
 */
bool music_playing();

/**
 * Sets the volume of the currently playing 'music'. Must be between 0 and 1, e.g. 0.1 is 10%.
 *
 * @param volume    Indicates the percentage of the original volume to play the
 *                 `music` at. This must be between `0` and `1`.
 *
 */
void set_music_volume(float volume);

/**
 * Returns the volume of the currently playing 'music'.
 *
 * @returns Returns the percentage of the currently playing 'music'.
 *
 */
float music_volume();

/**
 * Returns the name that SplashKit uses to refer to this music data
 *
 * @returns Returns a string with the name of the 'music' that SplashKit refers to.
 *
 * @attribute class   music
 * @attribute getter  name 
 * @attribute self    data
 *
 */
string music_name(music data);

/**
 * Returns the filename the of the music data
 *
 * @returns Returns a string with the filename of the 'music' file.
 *
 * @attribute class   music
 * @attribute getter  filename
 * @attribute self    data
 *
 */
string music_filename(music data);

#endif /* music_hpp */
