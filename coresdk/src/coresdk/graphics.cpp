//
//  graphics.cpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "drawing_options.h"
#include "camera.h"

#include "utility_functions.h"

#include "graphics_driver.h"

#include <map>

using namespace std;

extern map<string, window> _windows;

static unsigned int _last_update_time = 0;

void refresh_screen()
{
    refresh_screen(60);
}

void refresh_screen(unsigned int target_fps)
{
    for (const auto& kv : _windows)
    {
        refresh_window(kv.second);
    }

    unsigned int now = current_ticks();
    unsigned int delta = now - _last_update_time;
    unsigned int delay_time;

    //dont sleep if 5ms remaining...
    while ((target_fps > 0) and ((delta + 8) * target_fps < 1000))
    {
        delay_time = (1000 / target_fps) - delta;
        delay(delay_time);
        now = current_ticks();
        delta = now - _last_update_time;
    }

    _last_update_time = now;
}

struct unknown_data {
    pointer_identifier id;
};

pointer_identifier ptr_kind(void *p)
{
    unknown_data *ptr;

    ptr = static_cast<unknown_data *>(p);
    
    if (ptr)
        return ptr->id;
    else
        return NONE_PTR;
}

_window_data *to_window_ptr(void *w)
{
    _window_data *result = static_cast<_window_data *>(w);
    
    if (result and (result->id != WINDOW_PTR) )
    {
        raise_warning("Attempted to access a Window that appears to be an invalid pointer\n");
        result = nullptr;
    }
    
    return result;
}

_bitmap_data *to_bitmap_ptr(void *b)
{
    _bitmap_data *result = static_cast<_bitmap_data *>(b);
    
    if (result and (result->id != BITMAP_PTR) )
    {
        raise_warning("Attempted to access a Bitmap that appears to be an invalid pointer\n");
        result = nullptr;
    }
    
    return result;
}

sk_drawing_surface *to_surface_ptr(void *p)
{
    pointer_identifier id;
    _window_data *w;
    _bitmap_data *b;
    
    id = ptr_kind(p);
    
    if (id == WINDOW_PTR)
    {
        w = to_window_ptr(p);
        return &w->image.surface;
    }
    else if (id == BITMAP_PTR)
    {
        b = to_bitmap_ptr(p);
        return &b->image.surface;
    }
    else
        return  nullptr;
}

void xy_from_opts(drawing_options &opts, float &x, float &y)
{
    // check cases where drawn without camera...
    switch (opts.camera)
    {
        case DRAW_TO_SCREEN:
            return;
        case DRAW_TO_WORLD:
            break;
        case DRAW_DEFAULT:
            pointer_identifier id = ptr_kind(opts.dest);
            if (id != WINDOW_PTR) return;
            break;
    }

    // update location using camera
    x = to_screen_x(x);
    y = to_screen_y(y);
}

//----------------------------------------------------------------------------
// Circle drawing
//----------------------------------------------------------------------------


void draw_circle(color clr, float x, float y, float radius, drawing_options opts)
{
    sk_drawing_surface *surface;
    
    surface = to_surface_ptr(opts.dest);
    
    xy_from_opts(opts, x, y);
    
    if (surface)
        sk_draw_circle(surface, clr, x, y, radius);
}

void draw_circle(color clr, float x, float y, float radius)
{
    draw_circle(clr, x, y, radius, option_defaults());
}

void draw_circle(color clr, circle &c, drawing_options opts)
{
    draw_circle(clr, c.center.x, c.center.y, c.radius, opts);
}

void draw_circle(color clr, circle &c)
{
    draw_circle(clr, c.center.x, c.center.y, c.radius, option_defaults());
}


void fill_circle(color clr, float x, float y, float radius, drawing_options opts)
{
    sk_drawing_surface *surface;
    
    surface = to_surface_ptr(opts.dest);
    
    xy_from_opts(opts, x, y);
    
    if (surface)
        sk_fill_circle(surface, clr, x, y, radius);
}

void fill_circle(color clr, float x, float y, float radius)
{
    fill_circle(clr, x, y, radius, option_defaults());
}

void fill_circle(color clr, circle &c,drawing_options opts)
{
    fill_circle(clr, c.center.x, c.center.y, c.radius, opts);
}

void fill_circle(color clr, circle &c)
{
    fill_circle(clr, c.center.x, c.center.y, c.radius, option_defaults());
}

