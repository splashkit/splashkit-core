//
// SplashKit Generated Utils C++ Code
// DO NOT MODIFY
//

#ifndef __utils_h
#define __utils_h

#include "resources.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

unsigned int current_ticks();
void delay(unsigned int milliseconds);
void display_dialog(const string &title, const string &msg, font output_font, int font_size);
string file_as_string(string filename, resource_kind kind);

#endif /* __utils_h */
