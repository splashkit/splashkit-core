//
// SplashKit Generated Triangle Drawing C++ Code
// DO NOT MODIFY
//

#ifndef __triangle_drawing_h
#define __triangle_drawing_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

/**
* Draw a triangle onto the current window.
* @param clr The color for the triangle
* @param tri The triangles details
*
*/
void draw_triangle(color clr, const triangle &tri);
/**
* Draw a triangle using the supplied drawing options.
* @param clr The color for the triangle
* @param tri The triangles details
* @param opts The drawing options
*
*/
void draw_triangle(color clr, const triangle &tri, drawing_options opts);
/**
* Draw a triangle to the current window.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the window to the
* first point of the triangle
* @param y1 The distance from the top of the window to the
* first point of the triangle
* @param x2 The distance from the left side of the window to the
* second point of the triangle
* @param y2 The distance from the top of the window to the
* second point of the triangle
* @param x3 The distance from the left side of the window to the
* third point of the triangle
* @param y3 The distance from the top of the window to the
* third point of the triangle
*
*/
void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3);
/**
* Draw a triangle using the supplied drawing options.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap/window to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap/window to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap/window to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap/window to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap/window to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap/window to the
* third point of the triangle
* @param opts The drawing options
*
*/
void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
/**
* Draw a triangle on a given bitmap, using the supplied drawing options.
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
*
*/
void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri);
/**
* Draw a triangle on a given bitmap, using the supplied drawing options.
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
* @param opts The drawing options
*
*/
void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts);
/**
* Draw a triangle to the given bitmap.
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap to the
* third point of the triangle
*
*/
void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
/**
* Draw a triangle to the given bitmap, using the supplied drawing options.
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap/bitmap to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap/bitmap to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap/bitmap to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap/bitmap to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap/bitmap to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap/bitmap to the
* third point of the triangle
* @param opts The drawing options
*
*/
void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
/**
* Draw a triangle on a given window, using the supplied drawing options.
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
*
*/
void draw_triangle_on_window(window destination, color clr, const triangle &tri);
/**
* Draw a triangle on a given window, using the supplied drawing options.
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
* @param opts The drawing options
*
*/
void draw_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts);
/**
* Draw a triangle to the given window.
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the window to the
* first point of the triangle
* @param y1 The distance from the top of the window to the
* first point of the triangle
* @param x2 The distance from the left side of the window to the
* second point of the triangle
* @param y2 The distance from the top of the window to the
* second point of the triangle
* @param x3 The distance from the left side of the window to the
* third point of the triangle
* @param y3 The distance from the top of the window to the
* third point of the triangle
*
*/
void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
/**
* Draw a triangle to the given window, using the supplied drawing options.
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap/window to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap/window to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap/window to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap/window to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap/window to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap/window to the
* third point of the triangle
* @param opts The drawing options
*
*/
void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
/**
* Draw a triangle onto the current window.
* @param clr The color for the triangle
* @param tri The triangles details
*
*/
void fill_triangle(color clr, const triangle &tri);
/**
* Fill a triangle using the supplied drawing options.
* @param clr The color for the triangle
* @param tri The triangles details
* @param opts The drawing options
*
*/
void fill_triangle(color clr, const triangle &tri, drawing_options opts);
/**
* Fills a triangle on the current window.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the window to the
* first point of the triangle
* @param y1 The distance from the top of the window to the
* first point of the triangle
* @param x2 The distance from the left side of the window to the
* second point of the triangle
* @param y2 The distance from the top of the window to the
* second point of the triangle
* @param x3 The distance from the left side of the window to the
* third point of the triangle
* @param y3 The distance from the top of the window to the
* third point of the triangle
*
*/
void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3);
/**
* Fills a triangle using the supplied drawing options.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap/window to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap/window to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap/window to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap/window to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap/window to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap/window to the
* third point of the triangle
* @param opts The drawing options
*
*/
void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
/**
* Fill a triangle on a given bitmap
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
*
*/
void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri);
/**
* Fill a triangle on a given bitmap, using given drawing options
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
* @param opts The drawing options
*
*/
void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts);
/**
* Fill a triangle on a given bitmap
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap to the
* third point of the triangle
*
*/
void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
/**
* Fill a triangle on a given bitmap, using the supplied drawing options.
* @param destination The bitmap which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap/bitmap to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap/bitmap to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap/bitmap to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap/bitmap to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap/bitmap to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap/bitmap to the
* third point of the triangle
* @param opts The drawing options
*
*/
void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);
/**
* Fill a triangle on a given window
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
*
*/
void fill_triangle_on_window(window destination, color clr, const triangle &tri);
/**
* Fill a triangle on a given window, using given drawing options
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param tri The triangles details
* @param opts The drawing options
*
*/
void fill_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts);
/**
* Fill a triangle on a given window
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the window to the
* first point of the triangle
* @param y1 The distance from the top of the window to the
* first point of the triangle
* @param x2 The distance from the left side of the window to the
* second point of the triangle
* @param y2 The distance from the top of the window to the
* second point of the triangle
* @param x3 The distance from the left side of the window to the
* third point of the triangle
* @param y3 The distance from the top of the window to the
* third point of the triangle
*
*/
void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);
/**
* Fill a triangle on a given window, using the supplied drawing options.
* @param destination The window which the triangle will be drawn on.
* @param clr The color for the triangle
* @param x1 The distance from the left side of the bitmap/window to the
* first point of the triangle
* @param y1 The distance from the top of the bitmap/window to the
* first point of the triangle
* @param x2 The distance from the left side of the bitmap/window to the
* second point of the triangle
* @param y2 The distance from the top of the bitmap/window to the
* second point of the triangle
* @param x3 The distance from the left side of the bitmap/window to the
* third point of the triangle
* @param y3 The distance from the top of the bitmap/window to the
* third point of the triangle
* @param opts The drawing options
*
*/
void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

#endif /* __triangle_drawing_h */
