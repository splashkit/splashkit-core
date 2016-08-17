//
//  circle_drawing.hpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef circle_drawing_h
#define circle_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"

/**
 *  Draw a circle using the supplied drawing options. The circle is centred on its x, y
 *  coordinates, and has the provided radius. This will use `drawing_options` to determine
 *  the destination.
 */
void draw_circle(color clr, float x, float y, float radius, drawing_options opts);

/**
 *  Draw a circle onto the current window. The circle is centred on its x, y
 *  coordinates, and has the provided radius.
 */
void draw_circle(color clr, float x, float y, float radius);

/**
 *  Draw a circle with the provided drawing options, which may include options related to
 *  the drawing destination.
 */
void draw_circle(color clr, const circle &c, drawing_options opts);

/**
 *  Draw a circle on the current window. The circle is centred on its x, y
 *  coordinates, and has the provided radius.
 */
void draw_circle(color clr, const circle &c);

/**
 *  Fill a circle using the supplied drawing options. The circle is centred on its x, y
 *  coordinates, and has the provided radius. This will use `drawing_options` to determine
 *  the destination.
 */
void fill_circle(color clr, float x, float y, float radius, drawing_options opts);

/**
 *  Fill a circle onto the current window. The circle is centred on its x, y
 *  coordinates, and has the provided radius.
 */
void fill_circle(color clr, float x, float y, float radius);

/**
 *  Fill a circle with the provided drawing options, which may include options related to
 *  the drawing destination.
 */
void fill_circle(color clr, const circle &c, drawing_options opts);

/**
 *  Draw a circle on the current window. The circle is centred on its x, y
 *  coordinates, and has the provided radius.
 */
void fill_circle(color clr, const circle &c);

#endif /* circle_drawing_hpp */
