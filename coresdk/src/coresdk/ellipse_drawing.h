//
//  ellipse_drawing.hpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef ellipse_drawing_h
#define ellipse_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"

void draw_ellipse(color clr, float x, float y, float width, float height, drawing_options opts);

void draw_ellipse(color clr, float x, float y, float width, float height);

void draw_ellipse(color clr, const rectangle rect, drawing_options opts);

void draw_ellipse(color clr, const rectangle rect);

void fill_ellipse(color clr, float x, float y, float width, float height, drawing_options opts);

void fill_ellipse(color clr, float x, float y, float width, float height);

void fill_ellipse(color clr, const rectangle rect, drawing_options opts);

void fill_ellipse(color clr, const rectangle rect);

#endif /* ellipse_drawing_h */
