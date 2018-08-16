//
// SplashKit Generated Text Input C++ Code
// DO NOT MODIFY
//

#ifndef __text_input_h
#define __text_input_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_collected_text(color clr, font fnt, int font_size, const drawing_options &opts);
void end_reading_text();
void end_reading_text(window wind);
bool reading_text();
bool reading_text(window wind);
void start_reading_text(rectangle rect);
void start_reading_text(rectangle rect, string initial_text);
void start_reading_text(window wind, rectangle rect);
void start_reading_text(window wind, rectangle rect, string initial_text);
bool text_entry_cancelled();
bool text_entry_cancelled(window wind);
string text_input();
string text_input(window wind);

#endif /* __text_input_h */
