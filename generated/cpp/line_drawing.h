/*
 * SplashKit Line Drawing
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __line_drawing_h
#define __line_drawing_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_line(color clr, const line &l);
void draw_line(color clr, const line &l, drawing_options opts);
void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt);
void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
void draw_line(color clr, float x1, float y1, float x2, float y2);
void draw_line(color clr, float x1, float y1, float x2, float y2, const drawing_options &opts);

#endif /* __line_drawing_h */
