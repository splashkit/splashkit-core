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

point_2d point_at(float x, float y)
{
    point_2d result;
    result.x = x;
    result.y = y;
    return result;
}

circle circle_at(const point_2d &pt, float radius)
{
    circle result;
    result.center = pt;
    result.radius = radius;
    return result;
}

circle circle_at(float x, float y, float radius)
{
    return circle_at(point_at(x, y), radius);
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
