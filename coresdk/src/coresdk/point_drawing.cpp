//
//  point_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "point_drawing.h"

#include "graphics_driver.h"
#include "utility_functions.h"

namespace splashkit_lib
{
    void draw_pixel(color clr, double x, double y)
    {
        draw_pixel(clr, x, y, option_defaults());
    }

    void draw_pixel(color clr, double x, double y, drawing_options opts)
    {
        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        xy_from_opts(opts, x, y);

        if (surface)
        {
            sk_draw_pixel(surface, clr, x, y);
        }
    }

    void draw_pixel(color clr, const point_2d &pt)
    {
        draw_pixel(clr, pt.x, pt.y, option_defaults());
    }

    void draw_pixel(color clr, const point_2d &pt, drawing_options opts)
    {
        draw_pixel(clr, pt.x, pt.y, opts);
    }

    color get_pixel(bitmap bmp, double x, double y)
    {
        if ( INVALID_PTR(bmp, BITMAP_PTR) )
        {
            LOG(WARNING) << "Attempting to get pixel from invalid bitmap";
            return COLOR_WHITE;
        }

        return sk_read_pixel(&bmp->image.surface, static_cast<int>(x), static_cast<int>(y));
    }

    color get_pixel(bitmap bmp, const point_2d &pt)
    {
        return get_pixel(bmp, pt.x, pt.y);
    }

    color get_pixel(window wnd, double x, double y)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR) )
        {
            LOG(WARNING) << "Attempting to get pixel from invalid window";
            return COLOR_WHITE;
        }

        return sk_read_pixel(&wnd->image.surface, static_cast<int>(x), static_cast<int>(y));
    }

    color get_pixel(window wnd, const point_2d &pt)
    {
        return get_pixel(wnd, pt.x, pt.y);
    }
    
    color get_pixel(double x, double y)
    {
        return get_pixel(current_window(), x, y);
    }
    
    color get_pixel(const point_2d &pt)
    {
        return get_pixel(current_window(), pt.x, pt.y);
    }
    
    void draw_pixel_on_window(window destination, color clr, double x, double y)
    {
        draw_pixel(clr, x, y, option_draw_to(destination));
    }
    
    void draw_pixel_on_window(window destination, color clr, double x, double y, drawing_options opts)
    {
        draw_pixel(clr, x, y, option_draw_to(destination, opts));
    }
    
    void draw_pixel_on_window(window destination, color clr, const point_2d &pt)
    {
        draw_pixel(clr, pt, option_draw_to(destination));
    }
    
    void draw_pixel_on_window(window destination, color clr, const point_2d &pt, drawing_options opts)
    {
        draw_pixel(clr, pt, option_draw_to(destination, opts));
    }
    
    void draw_pixel_on_bitmap(bitmap destination, color clr, double x, double y)
    {
        draw_pixel(clr, x, y, option_draw_to(destination));
    }
    
    void draw_pixel_on_bitmap(bitmap destination, color clr, double x, double y, drawing_options opts)
    {
        draw_pixel(clr, x, y, option_draw_to(destination, opts));
    }
    
    void draw_pixel_on_bitmap(bitmap destination, color clr, const point_2d &pt)
    {
        draw_pixel(clr, pt, option_draw_to(destination));
    }
    
    void draw_pixel_on_bitmap(bitmap destination, color clr, const point_2d &pt, drawing_options opts)
    {
        draw_pixel(clr, pt, option_draw_to(destination, opts));
    }
    
    color get_pixel_from_window(window destination, double x, double y)
    {
        return get_pixel(destination, x, y);
    }
    
    color get_pixel_from_window(window destination, const point_2d &pt)
    {
        return get_pixel(destination, pt.x, pt.y);
    }
}
