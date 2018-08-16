//
// SplashKit Generated Triangle Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __triangle_drawing_h
#define __triangle_drawing_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_triangle(color clr, const triangle &tri);
void draw_triangle(color clr, const triangle &tri, drawing_options opts);
void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3);
void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri);
void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts);
void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
void draw_triangle_on_window(window destination, color clr, const triangle &tri);
void draw_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts);
void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
void fill_triangle(color clr, const triangle &tri);
void fill_triangle(color clr, const triangle &tri, drawing_options opts);
void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3);
void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri);
void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts);
void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
void fill_triangle_on_window(window destination, color clr, const triangle &tri);
void fill_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts);
void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

#endif /* __triangle_drawing_h */
