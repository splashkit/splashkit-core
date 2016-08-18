//
//  line_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "line_drawing.h"

#include "utility_functions.h"

#include "graphics_driver.h"

void draw_line(color clr, float x1, float y1, float x2, float y2)
{
    draw_line(clr, x1, y1, x2, y2, option_defaults());
}

void draw_line(color clr, float x1, float y1, float x2, float y2, drawing_options opts)
{
    sk_drawing_surface *surface;
    
    surface = to_surface_ptr(opts.dest);
    
    if (surface)
    {
        xy_from_opts(opts, x1, y1);
        xy_from_opts(opts, x2, y2);
        
        sk_draw_line(surface, clr, x1, y1, x2, y2, opts.line_width);
    }
}

void draw_line(color clr, point_2d pt1, point_2d pt2)
{
    draw_line(clr, pt1.x, pt1.y, pt2.x, pt2.y, option_defaults());
}

void draw_line(color clr, point_2d pt1, point_2d pt2, drawing_options opts)
{
    draw_line(clr, pt1.x, pt1.y, pt2.x, pt2.y, opts);
}