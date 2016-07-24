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

