//
// SplashKit Generated Line Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __line_drawing_h
#define __line_drawing_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* Draws a line onto the current window.
* @param clr The color of the line
* @param l The line's details
*
*/
void draw_line(color clr, const line &l);
/**
* Draws a line.
* @param clr The color of the line
* @param l The line's details
* @param opts The drawing options
*
*/
void draw_line(color clr, const line &l, drawing_options opts);
/**
* Draw a line from one point to another on the current window.
* @param clr The color of the line
* @param from_pt The start of the line
* @param to_pt The end of the line
*
*/
void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt);
/**
* Draw a line from one point to another on the current window.
* @param clr The color of the line
* @param from_pt The start of the line
* @param to_pt The end of the line
* @param opts The drawing options
*
*/
void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
/**
* Draw a line from one point to another on the current window.
* @param clr The color of the line
* @param x1 The distance from the left of the window/bitmap to the first
* point
* @param y1 The distance from the top of the window/bitmap to the first
* point
* @param x2 The distance from the left of the window/bitmap to the second
* point
* @param y2 The distance from the top of the window/bitmap to the second
* point
*
*/
void draw_line(color clr, double x1, double y1, double x2, double y2);
/**
* Draw a line from one point to another
* @param clr The color of the line
* @param x1 The distance from the left of the window/bitmap to the first
* point
* @param y1 The distance from the top of the window/bitmap to the first
* point
* @param x2 The distance from the left of the window/bitmap to the second
* point
* @param y2 The distance from the top of the window/bitmap to the second
* point
* @param opts The drawing options
*
*/
void draw_line(color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);
/**
* Draws a line onto the given bitmap.
* @param destination The destination bitmap
* @param clr The color of the line
* @param l The line's details
*
*/
void draw_line_on_bitmap(bitmap destination, color clr, const line &l);
/**
* Draws a line on the given bitmap.
* @param destination The destination bitmap
* @param clr The color of the line
* @param l The line's details
* @param opts The drawing options
*
*/
void draw_line_on_bitmap(bitmap destination, color clr, const line &l, drawing_options opts);
/**
* Draw a line from one point to another on the given bitmap.
* @param destination The destination bitmap
* @param clr The color of the line
* @param from_pt The start of the line
* @param to_pt The end of the line
*
*/
void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt);
/**
* Draw a line from one point to another on the given bitmap.
* @param destination The destination bitmap
* @param clr The color of the line
* @param from_pt The start of the line
* @param to_pt The end of the line
* @param opts The drawing options
*
*/
void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
/**
* Draw a line from one point to another on the given bitmap.
* @param destination The destination bitmap
* @param clr The color of the line
* @param x1 The distance from the left of the bitmap/bitmap to the first
* point
* @param y1 The distance from the top of the bitmap/bitmap to the first
* point
* @param x2 The distance from the left of the bitmap/bitmap to the second
* point
* @param y2 The distance from the top of the bitmap/bitmap to the second
* point
*
*/
void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2);
/**
* Draw a line from one point to another
* @param destination The destination bitmap
* @param clr The color of the line
* @param x1 The distance from the left of the bitmap/bitmap to the first
* point
* @param y1 The distance from the top of the bitmap/bitmap to the first
* point
* @param x2 The distance from the left of the bitmap/bitmap to the second
* point
* @param y2 The distance from the top of the bitmap/bitmap to the second
* point
* @param opts The drawing options
*
*/
void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);
/**
* Draws a line onto the given window.
* @param destination The destination bitmap
* @param clr The color of the line
* @param l The line's details
*
*/
void draw_line_on_window(window destination, color clr, const line &l);
/**
* Draws a line on the given window.
* @param destination The destination bitmap
* @param clr The color of the line
* @param l The line's details
* @param opts The drawing options
*
*/
void draw_line_on_window(window destination, color clr, const line &l, drawing_options opts);
/**
* Draw a line from one point to another on the given window.
* @param destination The destination bitmap
* @param clr The color of the line
* @param from_pt The start of the line
* @param to_pt The end of the line
*
*/
void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt);
/**
* Draw a line from one point to another on the given window.
* @param destination The destination bitmap
* @param clr The color of the line
* @param from_pt The start of the line
* @param to_pt The end of the line
* @param opts The drawing options
*
*/
void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
/**
* Draw a line from one point to another on the given window.
* @param destination The destination bitmap
* @param clr The color of the line
* @param x1 The distance from the left of the window/bitmap to the first
* point
* @param y1 The distance from the top of the window/bitmap to the first
* point
* @param x2 The distance from the left of the window/bitmap to the second
* point
* @param y2 The distance from the top of the window/bitmap to the second
* point
*
*/
void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2);
/**
* Draw a line from one point to another
* @param destination The destination bitmap
* @param clr The color of the line
* @param x1 The distance from the left of the window/bitmap to the first
* point
* @param y1 The distance from the top of the window/bitmap to the first
* point
* @param x2 The distance from the left of the window/bitmap to the second
* point
* @param y2 The distance from the top of the window/bitmap to the second
* point
* @param opts The drawing options
*
*/
void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);

#endif /* __line_drawing_h */
