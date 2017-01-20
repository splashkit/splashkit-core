//
//  ellipse_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "ellipse_drawing.h"

#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "drawing_options.h"
#include "camera.h"

#include "utility_functions.h"

#include "graphics_driver.h"
namespace splashkit_lib
{
    void draw_ellipse(color clr, double x, double y, double width, double height, drawing_options opts)
    {
        if ( width == 0 || height == 0 ) return;

        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        if (surface)
        {
            if (width < 0)
            {
                x = x + width; //move back by width
                width = -width;
            }

            if (height < 0)
            {
                y = y + height; //move up by height
                height = -height;
            }

            xy_from_opts(opts, x, y);
            sk_draw_ellipse(surface, clr, x, y, width, height);
        }
    }

    void draw_ellipse(color clr, double x, double y, double width, double height)
    {
        draw_ellipse(clr, x, y, width, height, option_defaults());
    }

    void draw_ellipse(color clr, const rectangle rect, drawing_options opts)
    {
        draw_ellipse(clr, rect.x, rect.y, rect.width, rect.height, opts);
    }

    void draw_ellipse(color clr, const rectangle rect)
    {
        draw_ellipse(clr, rect.x, rect.y, rect.width, rect.height, option_defaults());
    }

    void fill_ellipse(color clr, double x, double y, double width, double height, drawing_options opts)
    {
        if ( width == 0 || height == 0 ) return;

        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        if (surface)
        {
            if (width < 0)
            {
                x = x + width; //move back by width
                width = -width;
            }

            if (height < 0)
            {
                y = y + height; //move up by height
                height = -height;
            }

            xy_from_opts(opts, x, y);
            sk_fill_ellipse(surface, clr, x, y, width, height);
        }
    }

    void fill_ellipse(color clr, double x, double y, double width, double height)
    {
        fill_ellipse(clr, x, y, width, height, option_defaults());
    }
    
    void fill_ellipse(color clr, const rectangle rect, drawing_options opts)
    {
        fill_ellipse(clr, rect.x, rect.y, rect.width, rect.height, opts);
    }
    
    void fill_ellipse(color clr, const rectangle rect)
    {
        fill_ellipse(clr, rect.x, rect.y, rect.width, rect.height, option_defaults());
    }
    
    void draw_ellipse_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts)
    {
        draw_ellipse(clr, x, y, width, height, option_draw_to(destination, opts));
    }
    
    void draw_ellipse_on_window(window destination, color clr, double x, double y, double width, double height)
    {
        draw_ellipse(clr, x, y, width, height, option_draw_to(destination));
    }
    
    void draw_ellipse_on_window(window destination, color clr, const rectangle rect, drawing_options opts)
    {
        draw_ellipse(clr, rect, option_draw_to(destination, opts));
    }
    
    void draw_ellipse_on_window(window destination, color clr, const rectangle rect)
    {
        draw_ellipse(clr, rect, option_draw_to(destination));
    }
    
    void fill_ellipse_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts)
    {
        fill_ellipse(clr, x, y, width, height, option_draw_to(destination, opts));
    }
    
    void fill_ellipse_on_window(window destination, color clr, double x, double y, double width, double height)
    {
        fill_ellipse(clr, x, y, width, height, option_draw_to(destination));
    }
    
    void fill_ellipse_on_window(window destination, color clr, const rectangle rect, drawing_options opts)
    {
        fill_ellipse(clr, rect, option_draw_to(destination, opts));
    }
    
    void fill_ellipse_on_window(window destination, color clr, const rectangle rect)
    {
        fill_ellipse(clr, rect, option_draw_to(destination));
    }

    void draw_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts)
    {
        draw_ellipse(clr, x, y, width, height, option_draw_to(destination, opts));
    }
    
    void draw_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height)
    {
        draw_ellipse(clr, x, y, width, height, option_draw_to(destination));
    }
    
    void draw_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect, drawing_options opts)
    {
        draw_ellipse(clr, rect, option_draw_to(destination, opts));
    }
    
    void draw_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect)
    {
        draw_ellipse(clr, rect, option_draw_to(destination));
    }
    
    void fill_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts)
    {
        fill_ellipse(clr, x, y, width, height, option_draw_to(destination, opts));
    }
    
    void fill_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height)
    {
        fill_ellipse(clr, x, y, width, height, option_draw_to(destination));
    }
    
    void fill_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect, drawing_options opts)
    {
        fill_ellipse(clr, rect, option_draw_to(destination, opts));
    }
    
    void fill_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect)
    {
        fill_ellipse(clr, rect, option_draw_to(destination));
    }
}
