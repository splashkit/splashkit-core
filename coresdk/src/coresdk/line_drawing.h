//
//  line_drawing.hpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef line_drawing_h
#define line_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"

void draw_line(color clr, float x1, float y1, float x2, float y2);
void draw_line(color clr, float x1, float y1, float x2, float y2, drawing_options opts);

void draw_line(color clr, const line &l);
void draw_line(color clr, const line &l, drawing_options opts);

#endif /* line_drawing_h */
