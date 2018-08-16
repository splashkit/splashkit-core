//
// SplashKit Generated Graphics C++ Code
// DO NOT MODIFY
//

#ifndef __graphics_h
#define __graphics_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void clear_screen();
void clear_screen(color clr);
display display_details(unsigned int index);
int display_height(display disp);
string display_name(display disp);
int display_width(display disp);
int display_x(display disp);
int display_y(display disp);
int number_of_displays();
void refresh_screen();
void refresh_screen(unsigned int target_fps);
void save_bitmap(bitmap bmp, const string &basename);
int screen_height();
int screen_width();
void take_screenshot(const string &basename);
void take_screenshot(window wind, const string &basename);

#endif /* __graphics_h */
