//
// SplashKit Generated Point Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __point_drawing_h
#define __point_drawing_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_pixel(color clr, const point_2d &pt);
void draw_pixel(color clr, const point_2d &pt, drawing_options opts);
void draw_pixel(color clr, float x, float y);
void draw_pixel(color clr, float x, float y, drawing_options opts);
color get_pixel(bitmap bmp, const point_2d &pt);
color get_pixel(bitmap bmp, float x, float y);
color get_pixel(const point_2d &pt);
color get_pixel(float x, float y);
color get_pixel(window wnd, const point_2d &pt);
color get_pixel(window wnd, float x, float y);

#endif /* __point_drawing_h */
