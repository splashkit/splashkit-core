//
//  clipping.cpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "clipping.h"

#include "backend_types.h"
#include "graphics_driver.h"
#include "utility_functions.h"
namespace splashkit_lib
{
    void push_clip(const rectangle &r)
    {
        push_clip(current_window(), r);
    }

    void _push_clip(image_data &img, const rectangle &r)
    {
        rectangle clip_rect;
        if (img.clip_stack.size() > 0)
        {
            clip_rect = intersection(r, img.clip_stack.back());
        }
        else
        {
            clip_rect = r;
        }

        img.clip_stack.push_back(clip_rect);

        sk_set_clip_rect(&img.surface, clip_rect.x, clip_rect.y, clip_rect.width, clip_rect.height);
    }

    void push_clip(bitmap bmp, const rectangle &r)
    {
        if ( INVALID_PTR(bmp, BITMAP_PTR) )
        {
            LOG(WARNING) << "Attempting to push clip rect to invalid bitmap";
            return;
        }

        _push_clip(bmp->image, r);
    }

    void push_clip(window wnd, const rectangle &r)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR) )
        {
            LOG(WARNING) << "Attempting to push clip rect to invalid window";
            return;
        }

        _push_clip(wnd->image, r);
    }

    void reset_clip()
    {
        reset_clip(current_window());
    }

    void _reset_clip(image_data &img)
    {
        img.clip_stack.clear();
        sk_clear_clip_rect(&img.surface);
    }

    void reset_clip(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR) )
        {
            LOG(WARNING) << "Attempting to reset clip rect of invalid window";
            return;
        }

        _reset_clip(wnd->image);
    }

    void reset_clip(bitmap bmp)
    {
        if ( INVALID_PTR(bmp, BITMAP_PTR) )
        {
            LOG(WARNING) << "Attempting to reset clip rect of invalid bitmap";
            return;
        }

        _reset_clip(bmp->image);
    }

    void set_clip(bitmap bmp, const rectangle &r)
    {
        reset_clip(bmp);
        push_clip(bmp, r);
    }

    void set_clip(window wnd, const rectangle &r)
    {
        reset_clip(wnd);
        push_clip(wnd, r);
    }

    void set_clip(const rectangle &r)
    {
        set_clip(current_window(), r);
    }

    void _pop_clip(image_data &img)
    {
        if ( img.clip_stack.size() == 0 )
        {
            LOG(WARNING) << "Attempting to pop clip from bitmap or window where clipping is not set";
            return;
        }

        img.clip_stack.pop_back();

        if ( img.clip_stack.size() > 0 )
        {
            rectangle clip_rect = *img.clip_stack.end();
            sk_set_clip_rect(&img.surface, clip_rect.x, clip_rect.y, clip_rect.width, clip_rect.height);
        }
        else
        {
            sk_clear_clip_rect(&img.surface);
        }
    }

    void pop_clip()
    {
        pop_clip(current_window());
    }

    void pop_clip(bitmap bmp)
    {
        if ( INVALID_PTR(bmp, BITMAP_PTR) )
        {
            LOG(WARNING) << "Attempting to pop clip rect of invalid bitmap";
            return;
        }

        _pop_clip(bmp->image);
    }

    void pop_clip(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR) )
        {
            LOG(WARNING) << "Attempting to pop clip rect of invalid window";
            return;
        }

        _pop_clip(wnd->image);
    }

    rectangle _current_clip(const image_data &img)
    {
        if (img.clip_stack.size() > 0)
            return *img.clip_stack.end();
        else
            return rectangle_from(0, 0, img.surface.width, img.surface.height);
    }

    rectangle current_clip(bitmap bmp)
    {
        if ( INVALID_PTR(bmp, BITMAP_PTR) )
        {
            LOG(WARNING) << "Attempting to read clip rect of invalid bitmap";
            return rectangle_from(0, 0, 0, 0);
        }
        
        return _current_clip(bmp->image);
    }
    
    rectangle current_clip(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR) )
        {
            LOG(WARNING) << "Attempting to read clip rect of invalid window";
            return rectangle_from(0, 0, 0, 0);
        }
        
        return _current_clip(wnd->image);
    }
    
    /// Returns the rectangle of the clip area of the current window
    rectangle current_clip()
    {
        return current_clip(current_window());
    }
}