//
// SplashKit Generated Line Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __line_drawing_h
#define __line_drawing_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_line(color clr, const line &l);
void draw_line(color clr, const line &l, drawing_options opts);
void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt);
void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
void draw_line(color clr, double x1, double y1, double x2, double y2);
void draw_line(color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);
void draw_line_on_bitmap(bitmap destination, color clr, const line &l);
void draw_line_on_bitmap(bitmap destination, color clr, const line &l, drawing_options opts);
void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt);
void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2);
void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);
void draw_line_on_window(window destination, color clr, const line &l);
void draw_line_on_window(window destination, color clr, const line &l, drawing_options opts);
void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt);
void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2);
void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);

#endif /* __line_drawing_h */
