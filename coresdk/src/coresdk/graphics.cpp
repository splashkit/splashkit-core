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
#include "core_driver.h"

#include <map>

using std::map;
using std::to_string;

namespace splashkit_lib
{
    extern map<string, window> _windows;
    extern window _current_window;

    static unsigned int _last_update_time = 0;

    void refresh_screen()
    {
        for (const auto& kv : _windows)
        {
            refresh_window(kv.second);
        }
    }

    void delay_for_target_fps(unsigned int target_fps)
    {
        if ( target_fps == 0 ) return;
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
    
    void refresh_screen(unsigned int target_fps)
    {
        refresh_screen();
        delay_for_target_fps(target_fps);
    }

    void clear_screen(color clr)
    {
        clear_window(_current_window, clr);
    }

    void clear_screen()
    {
        clear_window(_current_window, COLOR_WHITE);
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
            LOG(WARNING) << "Attempting to save screenshot of invalid window";
            return;
        }

        _save_surface(wind->image, basename);
    }

    void save_bitmap(bitmap bmp, const string &basename)
    {
        if ( INVALID_PTR(bmp, BITMAP_PTR))
        {
            LOG(WARNING) << "Attempting to save image of invalid bitmap";
            return;
        }

        _save_surface(bmp->image, basename);
    }

    int number_of_displays()
    {
        sk_system_data *data = sk_read_system_data();

        if ( not data )
        {
            LOG(WARNING) << "Failed to load system data";
            return 0;
        }

        return data->num_displays;
    }

    display display_details(unsigned int index)
    {
        sk_system_data *data = sk_read_system_data();

        if ( not data )
        {
            LOG(WARNING) << "Failed to load system data";
            return 0;
        }

        if ( index < data->num_displays )
            return &data->displays[index];
        else
            return nullptr;
    }

    string display_name(display disp)
    {
        if ( INVALID_PTR(disp, DISPLAY_PTR) )
        {
            LOG(WARNING) << "Attempting to get name of invalid display";
            return "";
        }

        return string(disp->name);
    }

    int display_width(display disp)
    {
        if ( INVALID_PTR(disp, DISPLAY_PTR) )
        {
            LOG(WARNING) << "Attempting to get width of invalid display";
            return 0;
        }

        return disp->width;
    }
    
    int display_height(display disp)
    {
        if ( INVALID_PTR(disp, DISPLAY_PTR) )
        {
            LOG(WARNING) << "Attempting to get height of invalid display";
            return 0;
        }
        
        return disp->height;
    }
    
    int display_x(display disp)
    {
        if ( INVALID_PTR(disp, DISPLAY_PTR) )
        {
            LOG(WARNING) << "Attempting to get x of invalid display";
            return 0;
        }
        
        return disp->x;
    }
    
    int display_y(display disp)
    {
        if ( INVALID_PTR(disp, DISPLAY_PTR) )
        {
            LOG(WARNING) << "Attempting to get y of invalid display";
            return 0;
        }
        
        return disp->y;
    }
}
