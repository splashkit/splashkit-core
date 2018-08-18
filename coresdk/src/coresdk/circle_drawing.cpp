//
//  circle_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "circle_drawing.h"

#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "drawing_options.h"
#include "camera.h"

#include "utility_functions.h"

#include "graphics_driver.h"

#include <cmath>

using std::abs;

namespace splashkit_lib
{

    void draw_circle(color clr, double x, double y, double radius, drawing_options opts)
    {
        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        xy_from_opts(opts, x, y);

        if (surface)
        {
            sk_draw_circle(surface, clr, x, y, abs(radius));
        }
    }

    void draw_circle(color clr, double x, double y, double radius)
    {
        draw_circle(clr, x, y, radius, option_defaults());
    }

    void draw_circle(color clr, const circle &c, drawing_options opts)
    {
        draw_circle(clr, c.center.x, c.center.y, c.radius, opts);
    }

    void draw_circle(color clr, const circle &c)
    {
        draw_circle(clr, c.center.x, c.center.y, c.radius, option_defaults());
    }

    void fill_circle(color clr, double x, double y, double radius, drawing_options opts)
    {
        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        xy_from_opts(opts, x, y);

        if (surface)
            sk_fill_circle(surface, clr, x, y, abs(radius));
    }

    void fill_circle(color clr, double x, double y, double radius)
    {
        fill_circle(clr, x, y, radius, option_defaults());
    }

    void fill_circle(color clr, const circle &c, drawing_options opts)
    {
        fill_circle(clr, c.center.x, c.center.y, c.radius, opts);
    }

    void fill_circle(color clr, const circle &c)
    {
        fill_circle(clr, c.center.x, c.center.y, c.radius, option_defaults());
    }
    
    void draw_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts)
    {
        draw_circle(clr, x, y, radius, option_draw_to(destination, opts));
    }
    
    void draw_circle_on_window(window destination, color clr, double x, double y, double radius)
    {
        draw_circle(clr, x, y, radius, option_draw_to(destination));
    }
    
    void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts)
    {
        draw_circle(clr, x, y, radius, option_draw_to(destination, opts));
    }
    
    void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius)
    {
        draw_circle(clr, x, y, radius, option_draw_to(destination));
    }
    
    void fill_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts)
    {
        fill_circle(clr, x, y, radius, option_draw_to(destination, opts));
    }
    
    void fill_circle_on_window(window destination, color clr, double x, double y, double radius)
    {
        fill_circle(clr, x, y, radius, option_draw_to(destination));
    }
    
    void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts)
    {
        fill_circle(clr, x, y, radius, option_draw_to(destination, opts));
    }
    
    void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius)
    {
        fill_circle(clr, x, y, radius, option_draw_to(destination));
    }
}
