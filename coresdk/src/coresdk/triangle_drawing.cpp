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
namespace splashkit_lib
{
    void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts)
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

    void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        draw_triangle(clr, x1, y1, x2, y2, x3, y3, option_defaults());
    }

    void draw_triangle(color clr, const triangle &tri, drawing_options opts)
    {
        draw_triangle(clr,
                      tri.points[0].x, tri.points[0].y,
                      tri.points[1].x, tri.points[1].y,
                      tri.points[2].x, tri.points[2].y,
                      opts);
    }

    void draw_triangle(color clr, const triangle &tri)
    {
        draw_triangle(clr,
                      tri.points[0].x, tri.points[0].y,
                      tri.points[1].x, tri.points[1].y,
                      tri.points[2].x, tri.points[2].y,
                      option_defaults());
    }

    void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts)
    {
        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        if (surface)
        {
            xy_from_opts(opts, x1, y1);
            xy_from_opts(opts, x2, y2);
            xy_from_opts(opts, x3, y3);

            sk_fill_triangle(surface, clr, x1, y1, x2, y2, x3, y3);
        }
    }

    void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        fill_triangle(clr, x1, y1, x2, y2, x3, y3, option_defaults());
    }

    void fill_triangle(color clr, const triangle &tri, drawing_options opts)
    {
        fill_triangle(clr,
                      tri.points[0].x, tri.points[0].y,
                      tri.points[1].x, tri.points[1].y,
                      tri.points[2].x, tri.points[2].y,
                      opts);
    }

    void fill_triangle(color clr, const triangle &tri)
    {
        fill_triangle(clr,
                      tri.points[0].x, tri.points[0].y,
                      tri.points[1].x, tri.points[1].y,
                      tri.points[2].x, tri.points[2].y,
                      option_defaults());
    }

    void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts)
    {
        draw_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination, opts));
    }

    void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        draw_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination));
    }

    void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts)
    {
        draw_triangle(clr, tri, option_draw_to(destination, opts));
    }

    void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri)
    {
        draw_triangle(clr, tri, option_draw_to(destination));
    }

    void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts)
    {
        fill_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination, opts));
    }

    void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        fill_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination));
    }

    void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts)
    {
        fill_triangle(clr, tri, option_draw_to(destination, opts));
    }

    void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri)
    {
        fill_triangle(clr, tri, option_draw_to(destination));
    }
    
    void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts)
    {
        draw_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination, opts));
    }
    
    void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        draw_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination));
    }
    
    void draw_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts)
    {
        draw_triangle(clr, tri, option_draw_to(destination, opts));
    }
    
    void draw_triangle_on_window(window destination, color clr, const triangle &tri)
    {
        draw_triangle(clr, tri, option_draw_to(destination));
    }
    
    void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts)
    {
        fill_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination, opts));
    }
    
    void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        fill_triangle(clr, x1, y1, x2, y2, x3, y3, option_draw_to(destination));
    }
    
    void fill_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts)
    {
        fill_triangle(clr, tri, option_draw_to(destination, opts));
    }
    
    void fill_triangle_on_window(window destination, color clr, const triangle &tri)
    {
        fill_triangle(clr, tri, option_draw_to(destination));
    }

}
