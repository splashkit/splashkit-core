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
#include "vector_2d.h"

point_2d point_at(float x, float y)
{
    point_2d result;
    result.x = x;
    result.y = y;
    return result;
}

point_2d point_at_origin()
{
    return point_at(0, 0);
}

point_2d point_offset_by(const point_2d &start_point, const vector_2d &offset)
{
    return point_at(start_point.x + offset.x, start_point.y + offset.y);
}

string point_to_string(const point_2d &pt)
{
    return "Pt @" + to_string(pt.x) + ":" + to_string(pt.y);
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

bool point_in_triangle(const point_2d &pt, const triangle &tri)
{
    vector_2d v0, v1, v2;
    vector_2d a, b, c, p;
    float dot00, dot01, dot02, dot11, dot12;
    float inv_denom, u, v;
    
    //Convert Points to vectors
    p = vector_to_point(pt);
    a = vector_to_point(tri.points[0]);
    b = vector_to_point(tri.points[1]);
    c = vector_to_point(tri.points[2]);
    
    // Compute vectors
    v0 = vector_subtract(c, a);
    v1 = vector_subtract(b, a);
    v2 = vector_subtract(p, a);
    
    // Compute dot products
    dot00 = dot_product(v0, v0);
    dot01 = dot_product(v0, v1);
    dot02 = dot_product(v0, v2);
    dot11 = dot_product(v1, v1);
    dot12 = dot_product(v1, v2);
    
    // Compute barycentric coordinates
    if (dot00 * dot11 - dot01 * dot01 == 0)
        return false;
    
    inv_denom = 1 / (dot00 * dot11 - dot01 * dot01);
    u = (dot11 * dot02 - dot01 * dot12) * inv_denom;
    v = (dot00 * dot12 - dot01 * dot02) * inv_denom;
    
    // Check if point is in triangle
    return ((u > 0) and (v > 0) and (u + v < 1));
}

bool point_in_rectangle(const point_2d &pt, const rectangle &rect)
{
    if (pt.x < rectangle_left(rect)) return false;
    else if (pt.x > rectangle_right(rect)) return false;
    else if (pt.y < rectangle_top(rect)) return false;
    else if (pt.y > rectangle_bottom(rect)) return false;
    else return true;
}

/**
 *  Returns true if the point `pt` is in the circle `c`.
 */
bool point_in_circle(const point_2d &pt, const circle &c);

/**
 *  Returns true if point `pt` is on the line `l`.
 */
bool point_on_line(const point_2d &pt, const line &l);

/**
 *  Returns True of `pt1` is at the same point as `pt2`.
 */
bool same_point(const point_2d &pt1, const point_2d &pt2);

/**
 *  Returns the angle between two points in degrees.
 */
float calculate_angle_between(const point_2d &pt1, const point_2d &pt2);

/**
 *  Returns the distance between two points.
 */
float point_point_distance(const point_2d &pt1, const point_2d pt2);

