//
//  vector_2d.cpp
//  splashkit
//
//  Created by Andrew Cain on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "vector_2d.h"

#include "point_geometry.h"

#include <cmath>

vector_2d vector_to_point(const point_2d &p1)
{
    vector_2d result;
    result.x = p1.x;
    result.y = p1.y;
    return result;
}

vector_2d vector_point_to_point(const point_2d &start, const point_2d &end)
{
    vector_2d result;
    result.x = end.x - start.x;
    result.y = end.y - start.y;
    return result;
}

vector_2d vector_subtract(const vector_2d &v1, const vector_2d &v2)
{
    return vector_point_to_point(v2, v1);
}

float dot_product(const vector_2d &v1, const vector_2d &v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

float vector_magnitude_sqared(const vector_2d &v)
{
    return (v.x * v.x) + (v.y * v.y);
}

float vector_magnitude(const vector_2d &v)
{
    return sqrt(vector_magnitude_sqared(v));
}

