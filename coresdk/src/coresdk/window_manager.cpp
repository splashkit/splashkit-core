
//
//  window_manager.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "window_manager.h"
#include "graphics_driver.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"
#include "input_driver.h"
#include "input.h"

#include <map>

using std::map;

namespace splashkit_lib
{
    static window _primary_window = nullptr;
    window _current_window = nullptr;
    map<string, window> _windows;

    unsigned int number_open_windows()
    {
        return static_cast<unsigned int>(_windows.size());
    }

    window open_window(string caption, int width, int height)
    {
        sk_color clr;
        string real_caption;
        int idx;
        window result;

        _sk_quit = false;
        
        real_caption = caption;
        idx = 0;

        while ( has_window(real_caption) )
        {
            real_caption = caption + ": " + std::to_string(idx);
            idx++;
        }

        result = new _window_data();

        result->id = WINDOW_PTR;
        result->caption = real_caption;

        result->image.surface = sk_open_window(caption.c_str(), width, height);

        sk_window_position(&result->image.surface, &result->x, &result->y);

        result->open = true;
        result->fullscreen = false;
        result->border = true;

        result->screen_rect = { 0, 0, float(width), float(height) };

        result->temp_string = "";
        result->max_string_len = 0;

        //    result->text_bitmap = nullptr;
        //    result->cursor_bitmap = nullptr;
        //    result->font = nullptr;
        //    result->foreColor := RGBAColor(0, 0, 0, 255);
        //    result->background_color := RGBAColor(255, 255, 255, 255);
        //    result->input_area := RectangleFrom(0,0,0,0);

        //    result^.readingString := false;
        //    result^.textCancelled := false;

        clr = { 1.0f, 1.0f, 1.0f, 1.0f };
        sk_clear_drawing_surface(&result->image.surface, clr);

        clr = { 0.5f, 0.5f, 0.5f, 1.0f };
        //    _sg_functions^.text.draw_text( @result^.image.surface, nil, screenWidth div 2 - 60, screenHeight div 2, 'Getting ready to make a Splash!', clr);

        refresh_window(result);

        _windows[real_caption] = result;

        if ( ! _primary_window)
        {
            _primary_window = result;
            _current_window = result;
        }

        return result;
    }

    void window_set_icon(window wind, bitmap bmp)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to set icon for an invalid window!";
            return;
        }
        if ( INVALID_PTR(bmp, BITMAP_PTR))
        {
            LOG(WARNING) << "Attempting to set icon with an invalid bitmap!";
            return;
        }

        sk_set_icon(&wind->image.surface, &bmp->image.surface);
    }
    
    //TODO: From graphics... need to rework...
    void delay_for_target_fps(unsigned int target_fps);

    void refresh_window(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to refresh an invalid window!";
            return;
        }

        sk_refresh_window(&wind->image.surface);
    }
    
    void refresh_window(window wind, unsigned int target_fps)
    {
        refresh_window(wind);
        delay_for_target_fps(60);
    }

    void clear_window(window wind, color clr)
    {
        if ( not VALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to clear an invalid window!";
            return;
        }

        sk_clear_drawing_surface(&wind->image.surface, clr);
    }

    void close_window(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR) )
        {
            LOG(WARNING) << "Close window called without valid window parameter";
            return;
        }

        notify_of_free(wind);

        if ( wind == _current_window )
            _current_window = _primary_window;

        if ( wind == _primary_window )
        {
            _sk_quit = true;
            _primary_window = nullptr;

            if ( wind == _current_window ) // in case they ignore the quit!
                _current_window = nullptr;
        }

        sk_close_drawing_surface(&wind->image.surface);
        wind->id = NONE_PTR;
        _windows.erase(wind->caption);
        delete(wind);
    }

    void close_window(const string &name)
    {
        close_window(window_named(name));
    }

    void close_current_window()
    {
        close_window(_current_window);
    }

    void close_all_windows()
    {
        FREE_ALL_FROM_MAP(_windows, WINDOW_PTR, close_window);
    }

    bool has_window(string caption)
    {
        return _windows.count(caption) > 0;
    }

    window window_named(string caption)
    {
        if (has_window(caption))
            return _windows[caption];
        else
            return nullptr;
    }

    window window_with_focus()
    {
        for (auto win_itr: _windows)
        {
            if (sk_get_window_event_data(&win_itr.second->image.surface).has_focus)
            {
                return win_itr.second;
            }
        }

        return current_window();
    }
    
    bool window_has_focus(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to check window focus for an invalid window value";
            return false;
        }
        
        return sk_get_window_event_data(&wind->image.surface).has_focus;
    }

    window current_window()
    {
        return _current_window;
    }

    void set_current_window(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to set active window to an invalid window value";
            return;
        }

        _current_window = wind;
    }

    void set_current_window(const string &name)
    {
        set_current_window(window_named(name));
    }
    
    bool is_current_window(window wind)
    {
        return wind == _current_window;
    }

    bool window_close_requested(window wind)
    {
        if ( quit_requested() ) return true;
        
        if (INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to check if invalid window closed";
            return true;
        }

        return sk_get_window_event_data(&wind->image.surface).close_requested;
    }

    bool window_close_requested(const string &name)
    {
        return window_close_requested(window_named(name));
    }

    int window_width(window wind)
    {
        if (INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to get width of invalid window";
            return 0;
        }

        return wind->image.surface.width;
    }

    int window_width(const string &name)
    {
        return window_width(window_named(name));
    }

    int current_window_width()
    {
        return window_width(_current_window);
    }

    int window_height(window wind)
    {
        if (INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to get height of invalid window";
            return 0;
        }

        return wind->image.surface.height;
    }

    int window_height(const string &name)
    {
        return window_height(window_named(name));
    }

    int current_window_height()
    {
        return window_height(_current_window);
    }

    void resize_window(window wnd, int width, int height)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to change size of invalid window";
            return;
        }

        sk_resize(&wnd->image.surface, width, height);
    }

    void resize_current_window(int width, int height)
    {
        resize_window(_current_window, width, height);
    }

    void move_window_to(window wind, int x, int y)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to move invalid window";
            return;
        }

        sk_move_window(&wind->image.surface, x, y);
    }

    void move_window_to(const string &name, int x, int y)
    {
        move_window_to(window_named(name), x, y);
    }

    void move_current_window_to(int x, int y)
    {
        move_window_to(_current_window, x, y);
    }

    bool window_is_fullscreen(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to get fullscreen from invalid window";
            return false;
        }

        return wnd->fullscreen;
    }

    bool window_is_fullscreen(const string &name)
    {
        return window_is_fullscreen(window_named(name));
    }

    bool current_window_is_fullscreen()
    {
        return window_is_fullscreen(_current_window);
    }

    void window_toggle_fullscreen(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to toggle fullscreen of invalid window";
            return;
        }

        wnd->fullscreen = not wnd->fullscreen;
        sk_show_fullscreen(&wnd->image.surface, wnd->fullscreen);

        if ( not wnd->fullscreen )
        {
            resize_window(wnd, wnd->image.surface.width, wnd->image.surface.height);
        }
    }

    void window_toggle_fullscreen(const string &name)
    {
        window_toggle_fullscreen(window_named(name));
    }

    void current_window_toggle_fullscreen()
    {
        window_toggle_fullscreen(_current_window);
    }

    bool window_has_border(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to access border of invalid window";
            return false;
        }

        return wnd->border;
    }

    bool window_has_border(const string &name)
    {
        return window_has_border(window_named(name));
    }

    bool current_window_has_border()
    {
        return window_has_border(_current_window);
    }

    void window_toggle_border(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to toggle border of invalid window";
            return;
        }

        wnd->border = not wnd->border;
        sk_show_border(&wnd->image.surface, wnd->border);
    }

    void window_toggle_border(const string &name)
    {
        window_toggle_border(window_named(name));
    }

    void current_window_toggle_border()
    {
        window_toggle_border(_current_window);
    }

    int window_x(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to get position of invalid window";
            return 0;
        }

        int x, y;

        sk_window_position(&wnd->image.surface, &x, &y);

        return x;
    }

    int window_x(const string &name)
    {
        return window_x(window_named(name));
    }

    int current_window_x()
    {
        return window_x(_current_window);
    }

    int window_y(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to get position of invalid window";
            return 0;
        }

        int x, y;

        sk_window_position(&wnd->image.surface, &x, &y);

        return y;
    }

    int window_y(const string &name)
    {
        return window_y(window_named(name));
    }

    int current_window_y()
    {
        return window_y(_current_window);
    }

    point_2d window_position(window wnd)
    {
        if ( INVALID_PTR(wnd, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to get position of invalid window";
            return point_at_origin();
        }

        int x, y;

        sk_window_position(&wnd->image.surface, &x, &y);

        return point_at(x, y);
    }

    point_2d window_position(const string &name)
    {
        return window_position(window_named(name));
    }

    point_2d current_window_position()
    {
        return window_position(_current_window);
    }

    string window_caption(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to get caption of invalid window";
            return "";
        }
        
        return wind->caption;
    }
    
}
