//
// SplashKit Generated Music C++ Code
// DO NOT MODIFY
//

#ifndef __music_h
#define __music_h

#include "music.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _music_data;
typedef struct _music_data *music;
void fade_music_in(const string &name, int ms);
void fade_music_in(const string &name, int times, int ms);
void fade_music_in(music data, int ms);
void fade_music_in(music data, int times, int ms);
void fade_music_out(int ms);
void free_all_music();
void free_music(music effect);
bool has_music(const string &name);
music load_music(const string &name, const string &filename);
string music_filename(music data);
string music_name(music data);
music music_named(const string &name);
bool music_playing();
float music_volume();
void pause_music();
void play_music(const string &name);
void play_music(const string &name, int times);
void play_music(music data);
void play_music(music data, int times);
void play_music(music data, int times, float volume);
void resume_music();
void set_music_volume(float volume);
void stop_music();

#endif /* __music_h */
