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
    
    run_audio_tests();
    run_database_tests();
    
    return 0;
}
