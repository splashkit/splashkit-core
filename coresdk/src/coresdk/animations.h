//
//  animations.hpp
//  splashkit
//
//  Created by Andrew Cain on 10/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef animations_h
#define animations_h

#include "types.h"
#include "drawing_options.h"

#include <string>
using namespace std;



animation_script animation_script_named(string name);

animation_script load_animation_script(string name, string filename);

void free_animation_script(animation_script script_to_free);
void free_animation_script(string name);

bool has_animation_script(string name);

void free_all_animation_scripts();

void free_animation(animation ani);



int animation_count(animation_script script);

int animation_current_cell(animation anim);

vector_2d animation_current_vector(animation anim);

bool animation_ended(animation anim);

bool animation_entered_frame(animation anim);

float animation_frame_time(animation anim);

int animation_index(animation_script temp, string name);

string animation_name(animation temp);

string animation_name(animation_script temp, int idx);

string animation_script_name(animation_script script);

bool has_animation_named(animation_script script, string name);

void assign_animation(animation anim, animation_script script, int idx);

void assign_animation(animation anim, animation_script script, string name);

void assign_animation(animation anim, animation_script script, string name, bool with_sound);

void assign_animation(animation anim, animation_script script, int idx, bool with_sound);

animation create_animation(animation_script script, int idx);
animation create_animation(animation_script script, int idx, bool with_sound);
animation create_animation(animation_script script, string name, bool with_sound);
animation create_animation(animation_script script, string name);

void restart_animation(animation anim);
void restart_animation(animation anim, bool with_sound);

void update_animation(animation anim);
void update_animation(animation anim, float pct);
void update_animation(animation anim, float pct, bool with_sound);


#endif /* animations_h */
