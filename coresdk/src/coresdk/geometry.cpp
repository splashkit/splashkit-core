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

rectangle rectangle_from(float x, float y, float width, float height)
{
    rectangle result;
    result.x = x;
    result.y = y;
    result.width = width;
    result.height = height;
    
    return result;
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

vector_2d vector_to(float x, float y)
{
    vector_2d result;
    
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

quad quad_from(point_2d p1, point_2d p2, point_2d p3, point_2d p4)
{
    quad result;
    
    result.points[0] = p1;
    result.points[1] = p2;
    result.points[2] = p3;
    result.points[3] = p4;
    
    return result;
}

