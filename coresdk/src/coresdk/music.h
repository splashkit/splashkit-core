//
//  music.hpp
//  splashkit
//
//  Created by Jon Meyers on 15/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef music_h
#define music_h

/**
 * The Music type is used to refer to music that can be
 * played by the SwinGame audio code. Music files are loaded with
 * `LoadMusic`, played using `PlayMusic`, and must be
 * released using `FreeMusic`.
 *
 * Unlike `SoundEffect`s, there can only be one Music track
 * playing at a time. Playing an new track will stop the currently
 * playing music and switch to the new track.
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

void free_music(music effect);
void free_all_music();

bool has_music(string name);

music music_named(string name);

void play_music(music data, int loops, float pct);

#endif /* music_hpp */
