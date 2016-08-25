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




animation_script load_animation_script(string name, string filename);

void free_animation_script(animation_script script_to_free);
void free_animation_script(string name);

void free_all_animation_scripts();


animation_script animation_script_named(string name);

bool has_animation_script(string name);


string animation_script_name(animation_script script);

bool has_animation_named(animation_script script, string name);

int animation_count(animation_script script);



animation create_animation(animation_script script, string name, bool with_sound);

animation create_animation(string script_name, string name, bool with_sound);

animation create_animation(animation_script script, string name);

animation create_animation(string script_name, string name);

animation create_animation(animation_script script, int idx, bool with_sound);

animation create_animation(string script_name, int idx);


void free_animation(animation ani);


void assign_animation(animation anim, animation_script script, string name);

void assign_animation(animation anim, animation_script script, string name, bool with_sound);

void assign_animation(animation anim, string script_name, string name);

void assign_animation(animation anim, string script_name, string name, bool with_sound);

void assign_animation(animation anim, animation_script script, int idx);

void assign_animation(animation anim, animation_script script, int idx, bool with_sound);


int animation_index(animation_script script, string name);

string animation_name(animation temp);

int animation_current_cell(animation anim);

bool animation_ended(animation anim);

bool animation_entered_frame(animation anim);

float animation_frame_time(animation anim);

vector_2d animation_current_vector(animation anim);

void restart_animation(animation anim);

void restart_animation(animation anim, bool with_sound);

void update_animation(animation anim);

void update_animation(animation anim, float pct);

void update_animation(animation anim, float pct, bool with_sound);


#endif /* animations_h */
