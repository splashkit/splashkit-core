//
//  text_input.hpp
//  splashkit
//
//  Created by Andrew Cain on 16/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef text_input_hpp
#define text_input_hpp

#include "geometry.h"
#include "window_manager.h"

/**
 *
 */
void start_reading_text(rectangle rect);

void start_reading_text(window wind, rectangle rect);

void start_reading_text(rectangle rect, string initial_text);

void start_reading_text(window wind, rectangle rect, string initial_text);

void draw_collected_text(color clr, font fnt, int font_size, float x, float y, drawing_options opts);

bool reading_text();

bool reading_text(window wind);

void end_reading_text();

void end_reading_text(window wind);

bool text_entry_cancelled();

bool text_entry_cancelled(window wind);

string text_input();

string text_input(window wind);

#endif /* text_input_hpp */
