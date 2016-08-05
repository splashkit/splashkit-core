//
//  test_main.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <stdio.h>

#include "input.h"

#include "test_windows.hpp"
#include "audio_test.hpp"
#include "resources_tests.h"
#include "test_graphics.hpp"
#include "test_database.hpp"

int main()
{
    run_graphics_test();
    reset_quit();
    
    run_windows_tests();
    reset_quit();
    
    run_resources_tests();
    reset_quit();
    
    run_audio_tests();
    run_database_tests();
    
    return 0;
}