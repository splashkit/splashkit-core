
//
//  utils.cpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "utils.h"
#include "input.h"
#include "utils_driver.h"
#include <iostream>
namespace splashkit_lib
{

    void delay(unsigned int milliseconds)
    {
        if (milliseconds > 0)
        {
            if (milliseconds < 50)
                sk_delay(milliseconds);
            else
            {
                unsigned int t;
                for (t = 1; t < milliseconds / 50; t++)
                {
                    process_events();
                    if ( quit_requested() ) return;

                    sk_delay(50);
                }
                t = milliseconds % 50;

                if (t > 0) sk_delay(t);
            }
        }
    }
    
    unsigned int current_ticks()
    {
        return sk_get_ticks();
    }
}

