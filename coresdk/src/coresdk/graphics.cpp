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
#include "camera.h"

#include "utility_functions.h"

#include "graphics_driver.h"

#include <map>

using namespace std;

extern map<string, window> _windows;
extern window _current_window;

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

void clear_screen(color clr)
{
    clear_window(_current_window, clr);
}

int screen_width()
{
    return window_width(current_window());
}

int screen_height()
{
    return window_height(current_window());
}

void _save_surface(image_data &image, string basename)
{
    string path = path_from( {path_to_user_home(), "Desktop"} );
    
    if (not directory_exists(path))
    {
        path = path_to_user_home();
    }
    
    string filename = basename + ".png";
    
    int i = 1;
    
    while (file_exists( path_from({path}, filename)))
    {
        filename = basename + to_string(i) + ".png";
        i = i + 1;
    }
    
    path = path_from( { path }, filename);
    
    sk_save_png(&image.surface, path.c_str());
}

void take_screenshot(const string &basename)
{
    take_screenshot(current_window(), basename);
}

void take_screenshot(window wind, const string &basename)
{
    if ( INVALID_PTR(wind, WINDOW_PTR))
    {
        raise_warning("Attempting to save screenshot of invalid window");
        return;
    }
    
    _save_surface(wind->image, basename);
}

void save_bitmap(bitmap bmp, const string &basename)
{
    if ( INVALID_PTR(bmp, BITMAP_PTR))
    {
        raise_warning("Attempting to save image of invalid bitmap");
        return;
    }
    
    _save_surface(bmp->image, basename);
}
