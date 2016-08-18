//
//  point_geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "point_geometry.h"

#include "random.h"
#include "graphics.h"

point_2d point_at(float x, float y)
{
    point_2d result;
    result.x = x;
    result.y = y;
    return result;
}

point_2d point_offset_by(const point_2d &start_point, const vector_2d &offset)
{
    return point_at(start_point.x + offset.x, start_point.y + offset.y);
}

string point_to_string(const point_2d &pt)
{
    return "@" + to_string(pt.x) + ":" + to_string(pt.y);
}

point_2d random_screen_point()
{
    return random_window_point(current_window());
}

point_2d random_window_point(window wind)
{
    point_2d result;
    result.x = rnd() * screen_width();
    result.y = rnd() * screen_height();
    return result;
}

point_2d random_bitmap_point(bitmap bmp)
{
    point_2d result;
    result.x = rnd() * bitmap_width(bmp);
    result.y = rnd() * bitmap_height(bmp);
    return result;
}
