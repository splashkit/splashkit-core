/*
 * SplashKit Triangle Drawing
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __triangle_drawing_h
#define __triangle_drawing_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_triangle(color clr, const triangle &tri);
void draw_triangle(color clr, const triangle &tri, drawing_options opts);
void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3);
void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3, drawing_options opts);
void fill_triangle(color clr, const triangle &tri);
void fill_triangle(color clr, const triangle &tri, drawing_options opts);
void fill_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3);
void fill_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3, drawing_options opts);

#endif /* __triangle_drawing_h */
