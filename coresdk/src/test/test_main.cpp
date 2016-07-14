//
//  test_main.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <stdio.h>

#include "audio_test.hpp"
#include "resources_tests.h"

int main()
{
    run_resources_tests();
    run_audio_tests();
    
    return 0;
}