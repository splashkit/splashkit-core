/*
 * SplashKit Ellipse Drawing
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __ellipse_drawing_h
#define __ellipse_drawing_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_ellipse(color clr, const rectangle rect);
void draw_ellipse(color clr, const rectangle rect, drawing_options opts);
void draw_ellipse(color clr, float x, float y, float width, float height);
void draw_ellipse(color clr, float x, float y, float width, float height, drawing_options opts);
void fill_ellipse(color clr, const rectangle rect);
void fill_ellipse(color clr, const rectangle rect, drawing_options opts);
void fill_ellipse(color clr, float x, float y, float width, float height);
void fill_ellipse(color clr, float x, float y, float width, float height, drawing_options opts);

#endif /* __ellipse_drawing_h */
