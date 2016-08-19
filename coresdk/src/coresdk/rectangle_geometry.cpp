//
//  rectangle_geometry.cpp
//  splashkit
//
//  Created by Jacob on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

// Include class header
#include "rectangle_geometry.h"
#include "utility_functions.h"

#include <sstream>

rectangle rectangle_from(float x, float y, float width, float height)
{
    rectangle result;
    result.x = x;
    result.y = y;
    result.width = width;
    result.height = height;
    
    return result;
}

string rectangle_to_string(const rectangle &rect)
{
    ostringstream result;
    
    result << "Rect @" << rect.x << "," << rect.y << " " << rect.width << "x" << rect.height;
    
    return result.str();
}

rectangle intersection(const rectangle &rect1, const rectangle &rect2)
{
    float r, l, b, t;
    
    b = MIN(rectangle_bottom(rect1), rectangle_bottom(rect2));
    t = MAX(rectangle_top(rect1), rectangle_top(rect2));
    r = MIN(rectangle_right(rect1), rectangle_right(rect2));
    l = MAX(rectangle_left(rect1), rectangle_left(rect2));
    
    if ((r < l) or (b < t))
        return rectangle_from(0, 0, 0, 0);
    else
        return rectangle_from(l, t, r - l, b - t);
}

float rectangle_top(const rectangle &rect)
{
    if ( rect.height >= 0) return rect.y;
    else return rect.y + rect.height;
}

float rectangle_bottom(const rectangle &rect)
{
    if ( rect.height >= 0) return rect.y + rect.height;
    else return rect.y;
}

float rectangle_left(const rectangle &rect)
{
    if ( rect.width >= 0) return rect.x;
    else return rect.x + rect.width;
}

float rectangle_right(const rectangle &rect)
{
    if ( rect.width >= 0) return rect.x + rect.width;
    else return rect.x;
}
