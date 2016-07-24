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
#include "utils_driver.h"

#include "graphics.h"

void run_windows_tests()
{
    open_window("Hello World", 800, 600);
    
    sk_delay(2500);
    
    while ( ! quit_requested() )
    {
        process_events();
        
        draw_circle(COLOR_RED, 10, 10, 10);
        fill_circle(COLOR_GREEN, 50, 10, 10);
        
        refresh_screen();
    }
    
    close_window(window_named("Hello World"));
    
    sk_delay(500);
}