//
//  test_main.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <stdio.h>

#include "input.h"

#include "test_main.h"

int main()
{
    run_shape_drawing_test();
    reset_quit();
    
    run_animation_test();
    reset_quit();
    
    run_text_test();
    reset_quit();
    
    run_audio_tests();
    reset_quit();
    
    run_resources_tests();
    reset_quit();
    
    run_windows_tests();
    reset_quit();
    
    run_graphics_test();
    reset_quit();
    
    run_database_tests();
    reset_quit();
    
    run_timer_test();
    reset_quit();
    
    run_input_test();
    reset_quit();
    
    return 0;
}
