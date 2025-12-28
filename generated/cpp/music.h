//
// SplashKit Generated Music C++ Code
// DO NOT MODIFY
//

#ifndef __music_h
#define __music_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _music_data;
typedef struct _music_data *music;
/**
* Fades music file matching the name to full volume over a specified number of milliseconds
* @param name The name of the `music` file to play.
* @param ms How many milliseconds it takes to fade the `music` to full volume
*
*/
void fade_music_in(const string &name, int ms);
/**
* Fades music file matching the name to full volume over a specified number of milliseconds
* and loops a specified number of times
* @param name The name of the `music` file to play.
* @param times Controls the number of times the music is played.
* @param ms How many milliseconds it takes to fade the `music` to full volume
*
*/
void fade_music_in(const string &name, int times, int ms);
/**
* Fades music up to full volume over a specified number of milliseconds.
* @param data The name of the `music` to play.
* @param ms How many milliseconds it takes to fade the `music` to full volume
*
*/
void fade_music_in(music data, int ms);
/**
* Fades music up to full volume over a specified number of milliseconds
* for a specified number of times.
* @param data The name of the `music` to play.
* @param times Controls the number of times the music is played.
* @param ms How many milliseconds it takes to fade the `music` to full volume
*
*/
void fade_music_in(music data, int times, int ms);
/**
* Fades music outover a specified number of milliseconds
* @param ms How many milliseconds it takes to fade the `music` out
*
*/
void fade_music_out(int ms);
/**
* Releases all of the music files that have been loaded.

*
*/
void free_all_music();
/**
* Releases the SplashKit resources associated with music.
* @param effect The music file whose resources should be released.
*
*/
void free_music(music effect);
/**
* Determines if SplashKit has a music file loaded for the supplied name.
* This checks against all music files loaded, those loaded without a name
* are assigned the filename as a default. If this returns `false`, you may
* want to use `load_music` to load in a specific sound effect and give
* it the desired name.
* @param name The name to check if a music file is loaded.
* @return Returns `true` if there is a music file with the given `name` has
has been loaded.
*/
bool has_music(const string &name);
/**
* Loads and returns a music value. The supplied `filename` is used to
* locate the music file to load. The supplied `name` indicates the
* name to use to refer to this Music value. The `music` can then be
* retrieved by passing this `name` to the `music_named` function.
* @param name The name of the resource for SplashKit
* @param filename The filename to load
* @return A new music resource
*/
music load_music(const string &name, const string &filename);
/**
* Returns the filename the of the music data
* @param data The music resource
* @return Returns a string with the filename of the `music` file.
*/
string music_filename(music data);
/**
* Returns the name that SplashKit uses to refer to this music data
* @param data The music resource
* @return Returns a string with the name of the `music` that SplashKit refers to.
*/
string music_name(music data);
/**
* Retrieves a `music` that has been loaded into SplashKit.
* @param name The name of the music file to return.
* @return Returns the `music` that has been loaded with the specified
`name` using `load_music`.
*/
music music_named(const string &name);
/**
* Checks whether music is currently paused.

* @return Returns true or false value representing whether music is currently paused.
*/
bool music_paused();
/**
* Checks whether music is currently playing.

* @return Returns true or false value representing whether music is currently playing.
*/
bool music_playing();
/**
* Lets you test if music value is valid. This will return true when it is a valid music.
* @param m the music source to test
* @return true when the music is valid.
*/
bool music_valid(music m);
/**
* Returns the volume of the currently playing `music`.

* @return Returns the percentage of the currently playing `music`.
*/
double music_volume();
/**
* Pauses currently playing music - see resume_music to continue playing.

*
*/
void pause_music();
/**
* Plays the music file that matches the name once at full volume.
* @param name The name of the `music` to play.
*
*/
void play_music(const string &name);
/**
* Plays the music file that matches the name a specified number of times at full volume.
* @param name The name of the `music` to play.
* @param times Controls the number of times the music is played.
*
*/
void play_music(const string &name, int times);
/**
* Plays a music file once at full volume.
* @param data The name of the `music` to play.
*
*/
void play_music(music data);
/**
* Plays a music file a specified number of times at full volume.
* @param data The name of the `music` to play.
* @param times Controls the number of times the music is played.
*
*/
void play_music(music data, int times);
/**
* Plays a music file for a specified number of times and playback volume.
* @param data The name of the `music` to play.
* @param times Controls the number of times the music is played.
* @param volume Indicates the percentage of the original volume to play the
* `music` at. This must be between `0` and `1`.
*
*/
void play_music(music data, int times, double volume);
/**
* Resumes currently paused music - see pause_music to pause playing music.

*
*/
void resume_music();
/**
* Sets the volume of the currently playing `music`. Must be between 0 and 1, e.g. 0.1 is 10%.
* @param volume Indicates the percentage of the original volume to play the
* `music` at. This must be between `0` and `1`.
*
*/
void set_music_volume(double volume);
/**
* Stops currently playing music.

*
*/
void stop_music();

#endif /* __music_h */
