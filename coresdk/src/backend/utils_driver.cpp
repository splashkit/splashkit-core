//
//  SGDL2Utils.cpp
//  sgsdl2
//
//  Created by Andrew Cain on 20/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#include "core_driver.h"
#include "utils_driver.h"

#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif
namespace splashkit_lib
{
    void sk_delay(unsigned int ms)
    {
        SDL_Delay(ms);
    }

    unsigned int sk_get_ticks()
    {
        //ok without SDL init... and called on load
        return SDL_GetTicks();
    }
}