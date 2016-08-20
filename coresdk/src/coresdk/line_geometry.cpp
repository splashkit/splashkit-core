//
//  line_geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 20/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "line_geometry.h"


line line_from(const point_2d &start, const point_2d &end)
{
    return {start, end};
}

float line_length_squared(const line &l)
{
    return (l.end_point.x - l.start_point.x) * (l.end_point.x - l.start_point.x) +
    (l.end_point.y - l.start_point.y) * (l.end_point.y - l.start_point.y);
}