//
// SplashKit Generated Circle Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __circle_drawing_h
#define __circle_drawing_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_circle(color clr, const circle &c);
void draw_circle(color clr, const circle &c, drawing_options opts);
void draw_circle(color clr, double x, double y, double radius);
void draw_circle(color clr, double x, double y, double radius, drawing_options opts);
void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius);
void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts);
void draw_circle_on_window(window destination, color clr, double x, double y, double radius);
void draw_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts);
void fill_circle(color clr, const circle &c);
void fill_circle(color clr, const circle &c, drawing_options opts);
void fill_circle(color clr, double x, double y, double radius);
void fill_circle(color clr, double x, double y, double radius, drawing_options opts);
void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius);
void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts);
void fill_circle_on_window(window destination, color clr, double x, double y, double radius);
void fill_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts);

#endif /* __circle_drawing_h */
