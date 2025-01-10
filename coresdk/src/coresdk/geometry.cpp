//
//  geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "geometry.h"
#include "utility_functions.h"

#include <cmath>
namespace splashkit_lib
{
    float cosine(float angle)
    {
        return cos(deg_to_rad(angle));
    }

    float sine(float angle)
    {
        return sin(deg_to_rad(angle));
    }

    float tangent(float angle)
    {
        return tan(deg_to_rad(angle));
    }    
}