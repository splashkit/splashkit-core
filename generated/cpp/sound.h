//
// SplashKit Generated Sound C++ Code
// DO NOT MODIFY
//

#ifndef __sound_h
#define __sound_h

#include "sound.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _sound_effect_data;
typedef struct _sound_effect_data *sound_effect;
void fade_all_sound_effects_out(int ms);
void fade_sound_effect_out(sound_effect effect, int ms);
void free_all_sound_effects();
void free_sound_effect(sound_effect effect);
bool has_sound_effect(const string &name);
sound_effect load_sound_effect(const string &name, const string &filename);
void play_sound_effect(const string &name);
void play_sound_effect(const string &name, float volume);
void play_sound_effect(const string &name, int times);
void play_sound_effect(const string &name, int times, float volume);
void play_sound_effect(sound_effect effect);
void play_sound_effect(sound_effect effect, float volume);
void play_sound_effect(sound_effect effect, int times);
void play_sound_effect(sound_effect effect, int times, float volume);
string sound_effect_filename(sound_effect effect);
string sound_effect_name(sound_effect effect);
sound_effect sound_effect_named(const string &name);
bool sound_effect_playing(const string &name);
bool sound_effect_playing(sound_effect effect);
void stop_sound_effect(const string &name);
void stop_sound_effect(sound_effect effect);

#endif /* __sound_h */
