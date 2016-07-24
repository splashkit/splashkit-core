//
//  test_windows.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_windows.hpp"

#include "window_manager.h"
#include "input.h"
#include "images.h"
#include "graphics.h"
#include "utils.h"

void run_windows_tests()
{
    open_window("Hello World", 800, 600);
    
    bitmap light = load_bitmap("light", "on_med.png");
    
    while ( ! quit_requested() )
    {
        process_events();
        
        draw_circle(COLOR_RED, 10, 10, 10);
        fill_circle(COLOR_GREEN, 50, 10, 10);
        
        draw_bitmap(light, 10, 100);
        draw_bitmap("light", 75, 100);
        draw_bitmap("fred", 75, 100);
        
        refresh_screen();
    }
    
    delete_bitmap(light);
    close_window(window_named("Hello World"));
    
    delay(500);
}