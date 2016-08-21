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

line line_from(const vector_2d &v)
{
    return { {0,0}, {v.x, v.y} };
}

line line_from(const point_2d pt, const vector_2d &v)
{
    return { {pt.x, pt.y}, {pt.x + v.x, pt.y + v.y} };
}

bool line_intersection_point(const line &line1, const line &line2, point_2d &pt)
{
    // convert lines to the eqn
    // c = ax + by
    float a1, b1, c1;
    float a2, b2, c2;
    float det;

    pt.x = 0;
    pt.y = 0;

    //Convert lines to eqn c = ax + by
    a1 = line1.end_point.y - line1.start_point.y; //y12 - y11;
    b1 = line1.start_point.x - line1.end_point.x; //x11 - x12;
    c1 = a1 * line1.start_point.x + b1 * line1.start_point.y; //a1 * x11 + b1 * y11;

    a2 = line2.end_point.y - line2.start_point.y; //y22 - y21;
    b2 = line2.start_point.x - line2.end_point.x; //x21 - x22;
    c2 = a2 * line2.start_point.x + b2 * line2.start_point.y; //a2 * x21 + b2 * y21;

    det = (a1 * b2) - (a2 * b1);

    if (det == 0)
        return false;
    else
    {
        pt.x = (b2*c1 - b1*c2) / det;
        pt.y = (a1*c2 - a2*c1) / det;
        return true;
    }
}