//
//  test_input.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_input.hpp"

#include "input.h"
#include "graphics.h"
#include "text.h"

void run_input_test()
{
    rectangle rect = { 30.0f, 50.0f, 200.0f, 30.0f };
    
    open_window("Test Input", 600, 600);
    
    start_reading_text(rect);
    
    while (! quit_requested())
    {
        process_events();
        
        refresh_screen();
    }
    
    close_window("Test Input");
}