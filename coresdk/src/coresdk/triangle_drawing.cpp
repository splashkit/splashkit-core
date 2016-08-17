//
//  triangle_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "triangle_drawing.h"

#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "drawing_options.h"
#include "camera.h"

#include "utility_functions.h"

#include "graphics_driver.h"

void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3, drawing_options opts)
{
    sk_drawing_surface *surface;
    
    surface = to_surface_ptr(opts.dest);
    
    if (surface)
    {
        xy_from_opts(opts, x1, y1);
        xy_from_opts(opts, x2, y2);
        xy_from_opts(opts, x3, y3);
        
        sk_draw_triangle(surface, clr, x1, y1, x2, y2, x3, y3);
    }
}

void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3)
{
    draw_triangle(clr, x1, y1, x2, y2, x3, y3, option_defaults());
}
