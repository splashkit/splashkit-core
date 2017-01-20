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
namespace splashkit_lib
{
    void draw_line(color clr, double x1, double y1, double x2, double y2)
    {
        draw_line(clr, x1, y1, x2, y2, option_defaults());
    }

    void draw_line(color clr, double x1, double y1, double x2, double y2, const drawing_options &opts)
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

    void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt)
    {
        draw_line(clr, from_pt.x, from_pt.y, to_pt.x, to_pt.y, option_defaults());
    }

    void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts)
    {
        draw_line(clr, from_pt.x, from_pt.y, to_pt.x, to_pt.y, opts);
    }

    void draw_line(color clr, const line &l)
    {
        draw_line(clr, l.start_point.x, l.start_point.y, l.end_point.x, l.end_point.y, option_defaults());
    }

    void draw_line(color clr, const line &l, drawing_options opts)
    {
        draw_line(clr, l.start_point.x, l.start_point.y, l.end_point.x, l.end_point.y, opts);
    }
    
    void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2)
    {
        draw_line(clr, x1, y1, x2, y2, option_draw_to(destination));
    }
    
    void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts)
    {
        draw_line(clr, x1, y1, x2, y2, option_draw_to(destination, opts));
    }
    
    void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt)
    {
        draw_line(clr, from_pt, to_pt, option_draw_to(destination));
    }
    
    void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts)
    {
        draw_line(clr, from_pt, to_pt, option_draw_to(destination, opts));
    }
    
    void draw_line_on_window(window destination, color clr, const line &l)
    {
        draw_line(clr, l, option_draw_to(destination));
    }
    
    void draw_line_on_window(window destination, color clr, const line &l, drawing_options opts)
    {
        draw_line(clr, l, option_draw_to(destination, opts));
    }
    
    void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2)
    {
        draw_line(clr, x1, y1, x2, y2, option_draw_to(destination));
    }
    
    void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts)
    {
        draw_line(clr, x1, y1, x2, y2, option_draw_to(destination, opts));
    }
    
    void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt)
    {
        draw_line(clr, from_pt, to_pt, option_draw_to(destination));
    }
    
    void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts)
    {
        draw_line(clr, from_pt, to_pt, option_draw_to(destination, opts));
    }
    
    void draw_line_on_bitmap(bitmap destination, color clr, const line &l)
    {
        draw_line(clr, l, option_draw_to(destination));
    }
    
    void draw_line_on_bitmap(bitmap destination, color clr, const line &l, drawing_options opts)
    {
        draw_line(clr, l, option_draw_to(destination, opts));
    }
}
