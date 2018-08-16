//
// SplashKit Generated Ellipse Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __ellipse_drawing_h
#define __ellipse_drawing_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_ellipse(color clr, const rectangle rect);
void draw_ellipse(color clr, const rectangle rect, drawing_options opts);
void draw_ellipse(color clr, double x, double y, double width, double height);
void draw_ellipse(color clr, double x, double y, double width, double height, drawing_options opts);
void draw_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect);
void draw_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect, drawing_options opts);
void draw_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
void draw_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts);
void draw_ellipse_on_window(window destination, color clr, const rectangle rect);
void draw_ellipse_on_window(window destination, color clr, const rectangle rect, drawing_options opts);
void draw_ellipse_on_window(window destination, color clr, double x, double y, double width, double height);
void draw_ellipse_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts);
void fill_ellipse(color clr, const rectangle rect);
void fill_ellipse(color clr, const rectangle rect, drawing_options opts);
void fill_ellipse(color clr, double x, double y, double width, double height);
void fill_ellipse(color clr, double x, double y, double width, double height, drawing_options opts);
void fill_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect);
void fill_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect, drawing_options opts);
void fill_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
void fill_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts);
void fill_ellipse_on_window(window destination, color clr, const rectangle rect);
void fill_ellipse_on_window(window destination, color clr, const rectangle rect, drawing_options opts);
void fill_ellipse_on_window(window destination, color clr, double x, double y, double width, double height);
void fill_ellipse_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts);

#endif /* __ellipse_drawing_h */
