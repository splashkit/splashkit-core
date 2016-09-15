//
//  rectangle_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "rectangle_drawing.h"

#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "drawing_options.h"
#include "camera.h"

#include "utility_functions.h"

#include "graphics_driver.h"

namespace splashkit_lib
{
    void draw_rectangle(color clr, float x, float y, float width, float height, const drawing_options &opts)
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
            sk_draw_aa_rect(surface, clr, x, y, width, height);
        }
    }

    void draw_rectangle(color clr, float x, float y, float width, float height)
    {
        draw_rectangle(clr, x, y, width, height, option_defaults());
    }

    void draw_rectangle(color clr, const rectangle &rect, const drawing_options &opts)
    {
        draw_rectangle(clr, rect.x, rect.y, rect.width, rect.height, opts);
    }

    void draw_rectangle(color clr, const rectangle &rect)
    {
        draw_rectangle(clr, rect.x, rect.y, rect.width, rect.height, option_defaults());
    }

    void fill_rectangle(color clr, float x, float y, float width, float height, const drawing_options &opts)
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
            sk_fill_aa_rect(surface, clr, x, y, width, height);
        }
    }

    void fill_rectangle(color clr, float x, float y, float width, float height)
    {
        fill_rectangle(clr, x, y, width, height, option_defaults());
    }

    void fill_rectangle(color clr, const rectangle &rect, const drawing_options &opts)
    {
        fill_rectangle(clr, rect.x, rect.y, rect.width, rect.height, opts);
    }

    void fill_rectangle(color clr, const rectangle &rect)
    {
        fill_rectangle(clr, rect.x, rect.y, rect.width, rect.height, option_defaults());
    }

    void draw_quad(color clr, const quad &q)
    {
        draw_quad(clr, q, option_defaults());
    }

    void draw_quad(color clr, const quad &q, const drawing_options &opts)
    {
        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        if (surface)
        {
            float pts[8];
            for(int i = 0; i < 4; i++)
            {
                pts[i * 2] = q.points[i].x;
                pts[i * 2 + 1] = q.points[i].y;
                xy_from_opts(opts, pts[i * 2], pts[i * 2 + 1]);
            }
            sk_draw_rect(surface, clr, pts, 8);
        }
    }

    void fill_quad(color clr, const quad &q)
    {
        fill_quad(clr, q, option_defaults());
    }
    
    void fill_quad(color clr, const quad &q, const drawing_options &opts)
    {
        sk_drawing_surface *surface;
        
        surface = to_surface_ptr(opts.dest);
        
        if (surface)
        {
            float pts[8];
            for(int i = 0; i < 4; i++)
            {
                pts[i * 2] = q.points[i].x;
                pts[i * 2 + 1] = q.points[i].y;
                xy_from_opts(opts, pts[i * 2], pts[i * 2 + 1]);
            }
            sk_fill_rect(surface, clr, pts, 8);
        }
    }
    
}