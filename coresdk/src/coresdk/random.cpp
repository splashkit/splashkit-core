
//
//  random.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "random.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <easylogging++.h>

namespace splashkit_lib
{
    static bool _do_seed = true;

    float rnd()
    {
        return rnd(RAND_MAX) / static_cast<float>(RAND_MAX);
    }

    int rnd(int ubound)
    {
        if (ubound <= 0) return 0;
        
        if (_do_seed)
        {
            _do_seed = false;
            srand((unsigned)time(0));
        }
        
        return rand() % ubound;
    }
    
    int rnd(int min, int max)
    {
        if (min > max)
        {
            LOG(WARNING) << "Min value is greater than max value when calling rnd.";
            return rnd(max, min);
        }

        if (min == max) return min;
        
        if (_do_seed)
        {
            _do_seed = false;
            srand((unsigned)time(0));
        }
        
        int range = abs(max - min) + 1;
        return min + (rand() % range);
    }
}
