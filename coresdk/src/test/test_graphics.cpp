//
//  test_graphics.cpp
//  splashkit
//
//  Created by Kai Renshaw on 27/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_graphics.hpp"

#include "graphics.h"
#include "input.h"
#include "color.h"
#include "random.h"

void run_graphics_test()
{
    open_window("Test Graphics", 800, 600);
    
    while (! quit_requested())
    {
        process_events();
        
        fill_rectangle(random_rgb_color(128), rnd() * 800, rnd() * 600, rnd() * 100, rnd() * 50);
        
        refresh_screen();
    }
    
    close_window(window_named("Test Graphics"));
}