
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
namespace splashkit_lib
{
    static bool _do_seed = true;

    float rnd()
    {
        return rnd(RAND_MAX) / static_cast<float>(RAND_MAX);
    }

    int rnd(int ubound)
    {
        if (_do_seed)
        {
            _do_seed = false;
            srand((unsigned)time(0));
        }
        
        return rand() % ubound;
    }
    
    int rnd(int min, int max)
    {
        if (_do_seed)
        {
            _do_seed = false;
            srand((unsigned)time(0));
        }
        
        return min + rand() % (max - min);
    }
}
