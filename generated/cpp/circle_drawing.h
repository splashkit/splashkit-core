/*
 * SplashKit Circle Drawing
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __circle_drawing_h
#define __circle_drawing_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_circle(color clr, const circle &c);
void draw_circle(color clr, const circle &c, drawing_options opts);
void draw_circle(color clr, float x, float y, float radius);
void draw_circle(color clr, float x, float y, float radius, drawing_options opts);
void fill_circle(color clr, const circle &c);
void fill_circle(color clr, const circle &c, drawing_options opts);
void fill_circle(color clr, float x, float y, float radius);
void fill_circle(color clr, float x, float y, float radius, drawing_options opts);

#endif /* __circle_drawing_h */
