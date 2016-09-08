//
//  geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "geometry.h"
#include "window_manager.h"
#include "graphics.h"
#include "random.h"
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

    triangle triangle_from(float x1, float y1, float x2, float y2, float x3, float y3)
    {
        triangle result;
        result.points[0] = point_at(x1, y1);
        result.points[1] = point_at(x2, y2);
        result.points[2] = point_at(x3, y3);
        return result;
    }

    triangle triangle_from(point_2d p1, point_2d p2, point_2d p3)
    {
        triangle result;
        result.points[0] = p1;
        result.points[1] = p2;
        result.points[2] = p3;
        return result;
    }
    
}