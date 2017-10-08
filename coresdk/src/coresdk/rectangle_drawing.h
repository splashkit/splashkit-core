//
//  rectangle_drawing.hpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef rectangle_drawing_hpp
#define rectangle_drawing_hpp

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"


/// Draw a rectangle using the supplied drawing options.
///
/// @lib DrawRectangleOpts
/// @sn drawRectangleColor:%s atX:%s y:%s width:%s height:%s opts:%s
void draw_rectangle(color clr, float x, float y, float width, float height, drawing_options opts);

/// Draw a rectangle onto the current window.
///
/// @lib DrawRectangle
/// @sn drawRectangleColor:%s atX:%s y:%s width:%s height:%s
void draw_rectangle(color clr, float x, float y, float width, float height);

void draw_rectangle(color clr, const rectangle rect, drawing_options opts);

void draw_rectangle(color clr, const rectangle rect);

/// Fill a rectangle using the supplied drawing options.
///
/// @lib FillRectangleOpts
/// @sn fillRectangleColor:%s atX:%s y:%s width:%s height:%s opts:%s
void fill_rectangle(color clr, float x, float y, float width, float height, drawing_options opts);

/// Fill a rectangle onto the current window.
///
void fill_rectangle(color clr, float x, float y, float width, float height);

void fill_rectangle(color clr, const rectangle rect, drawing_options opts);

void fill_rectangle(color clr, const rectangle rect);

void draw_quad(color clr, const quad &q);
void draw_quad(color clr, const quad &q, drawing_options opts);

void fill_quad(color clr, const quad &q);
void fill_quad(color clr, const quad &q, drawing_options opts);


#endif /* rectangle_drawing_hpp */
