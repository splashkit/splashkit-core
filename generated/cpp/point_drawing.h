//
// SplashKit Generated Point Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __point_drawing_h
#define __point_drawing_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_pixel(color clr, const point_2d &pt);
void draw_pixel(color clr, const point_2d &pt, drawing_options opts);
void draw_pixel(color clr, double x, double y);
void draw_pixel(color clr, double x, double y, drawing_options opts);
void draw_pixel_on_bitmap(bitmap destination, color clr, const point_2d &pt);
void draw_pixel_on_bitmap(bitmap destination, color clr, const point_2d &pt, drawing_options opts);
void draw_pixel_on_bitmap(bitmap destination, color clr, double x, double y);
void draw_pixel_on_bitmap(bitmap destination, color clr, double x, double y, drawing_options opts);
void draw_pixel_on_window(window destination, color clr, const point_2d &pt);
void draw_pixel_on_window(window destination, color clr, const point_2d &pt, drawing_options opts);
void draw_pixel_on_window(window destination, color clr, double x, double y);
void draw_pixel_on_window(window destination, color clr, double x, double y, drawing_options opts);
color get_pixel(bitmap bmp, const point_2d &pt);
color get_pixel(bitmap bmp, double x, double y);
color get_pixel(const point_2d &pt);
color get_pixel(double x, double y);
color get_pixel(window wnd, const point_2d &pt);
color get_pixel(window wnd, double x, double y);
color get_pixel_from_window(window destination, const point_2d &pt);
color get_pixel_from_window(window destination, double x, double y);

#endif /* __point_drawing_h */
