//
//  geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "geometry.h"

rectangle rectangle_from(float x, float y, float width, float height)
{
    rectangle result;
    result.x = x;
    result.y = y;
    result.width = width;
    result.height = height;
    
    return result;
}

vector_2d vector_to(float x, float y)
{
    vector_2d result;
    
    result.x = x;
    result.y = y;
    
    return result;
}