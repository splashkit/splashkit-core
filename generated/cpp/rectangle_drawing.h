//
// SplashKit Generated Rectangle Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __rectangle_drawing_h
#define __rectangle_drawing_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_quad(color clr, const quad &q);
void draw_quad(color clr, const quad &q, const drawing_options &opts);
void draw_quad_on_bitmap(bitmap destination, color clr, const quad &q);
void draw_quad_on_bitmap(bitmap destination, color clr, const quad &q, const drawing_options &opts);
void draw_quad_on_window(window destination, color clr, const quad &q);
void draw_quad_on_window(window destination, color clr, const quad &q, const drawing_options &opts);
void draw_rectangle(color clr, const rectangle &rect);
void draw_rectangle(color clr, const rectangle &rect, const drawing_options &opts);
void draw_rectangle(color clr, double x, double y, double width, double height);
void draw_rectangle(color clr, double x, double y, double width, double height, const drawing_options &opts);
void draw_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect);
void draw_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect, const drawing_options &opts);
void draw_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
void draw_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts);
void draw_rectangle_on_window(window destination, color clr, const rectangle &rect);
void draw_rectangle_on_window(window destination, color clr, const rectangle &rect, const drawing_options &opts);
void draw_rectangle_on_window(window destination, color clr, double x, double y, double width, double height);
void draw_rectangle_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts);
void fill_quad(color clr, const quad &q);
void fill_quad(color clr, const quad &q, const drawing_options &opts);
void fill_quad_on_bitmap(bitmap destination, color clr, const quad &q);
void fill_quad_on_bitmap(bitmap destination, color clr, const quad &q, const drawing_options &opts);
void fill_quad_on_window(window destination, color clr, const quad &q);
void fill_quad_on_window(window destination, color clr, const quad &q, const drawing_options &opts);
void fill_rectangle(color clr, const rectangle &rect);
void fill_rectangle(color clr, const rectangle &rect, const drawing_options &opts);
void fill_rectangle(color clr, double x, double y, double width, double height);
void fill_rectangle(color clr, double x, double y, double width, double height, const drawing_options &opts);
void fill_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect);
void fill_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect, const drawing_options &opts);
void fill_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
void fill_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, const drawing_options &opts);
void fill_rectangle_on_window(window destination, color clr, const rectangle &rect);
void fill_rectangle_on_window(window destination, color clr, const rectangle &rect, const drawing_options &opts);
void fill_rectangle_on_window(window destination, color clr, double x, double y, double width, double height);
void fill_rectangle_on_window(window destination, color clr, double x, double y, double width, double height, const drawing_options &opts);

#endif /* __rectangle_drawing_h */
