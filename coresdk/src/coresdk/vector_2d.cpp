//
//  vector_2d.cpp
//  splashkit
//
//  Created by Andrew Cain on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "vector_2d.h"

#include "point_geometry.h"
#include "line_geometry.h"
#include "utility_functions.h"

#include <cmath>

string vector_to_string(const vector_2d &v)
{
    return "Vec -> " + to_string(v.x) + ":" + to_string(v.y);
}

vector_2d vector_to(float x, float y)
{
    return { x, y };
}

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

vector_2d vector_invert(const vector_2d &v)
{
    return { -v.x, -v.y };
}

vector_2d vector_from_angle(float angle, float magnitude)
{
    return vector_to(magnitude * cosine(angle), magnitude * sine(angle));
}

vector_2d vector_from_line(const line &l)
{
    return vector_point_to_point(l.start_point, l.end_point);
}

vector_2d vector_add(const vector_2d &v1, const vector_2d &v2)
{
    return { v1.x +  v2.x, v1.y + v2.y };
}

vector_2d vector_subtract(const vector_2d &v1, const vector_2d &v2)
{
    return { v2.x - v1.x, v2.y - v1.y };
}

vector_2d vector_multiply(const vector_2d &v1, float s)
{
    return { v1.x * s, v1.y * s };
}

bool vectors_equal(const vector_2d &v1, const vector_2d v2)
{
    return abs(v1.x - v2.x) < EPSEPS and abs(v1.y - v2.y) < EPSEPS;
}

float dot_product(const vector_2d &v1, const vector_2d &v2)
{
    return (v1.x * v2.x) + (v1.y * v2.y);
}

float vector_angle(const vector_2d v)
{
    if (v.x == 0)
    {
        if (v.y < 0) return -90;
        else return 90; //Default to down screen if x and y are both 0
    }
    else if (v.y == 0)
    {
        if (v.x < 0) return 180;
        else return 0;
    }
    else
    {
        float result = rad_to_deg(atan(v.y / v.x));
    
        if (v.x < 0)
        {
            if (v.y < 0) result -= 180;
            else result += 180;
        }
        return result;
    }
}

vector_2d vector_normal(const vector_2d &v)
{
    float magnitude = vector_magnitude(v);
    
    if (magnitude == 0)
    {
        raise_warning("Attempting to get normal of null/zero vector");
        return { 0,0 };
    }
    
    return { -v.y / magnitude, v.x / magnitude };
}

float vector_magnitude_sqared(const vector_2d &v)
{
    return (v.x * v.x) + (v.y * v.y);
}

float vector_magnitude(const vector_2d &v)
{
    return sqrt(vector_magnitude_sqared(v));
}

vector_2d vector_limit(const vector_2d &v, float limit)
{
    if ( abs(vector_magnitude(v)) > abs(limit) )
    {
        return vector_multiply(unit_vector(v), limit);
    }
    return v;
}

vector_2d unit_vector(const vector_2d &v)
{
    float tmp;
    float mag = vector_magnitude(v);
    
    if ( mag == 0 )
        tmp = 0;
    else
        tmp = 1 / mag;
    
    return { tmp * v.x, tmp * v.y };
}

bool is_zero_vector(const vector_2d &v)
{
    return (v.x == 0) && (v.y == 0);
}

bool ray_intersection_point(const point_2d &from_pt, const vector_2d &heading, const line &l, point_2d &pt)
{
    line ray_line;
    float comb_mag;
    
    ray_line = line_from(from_pt, heading);

    // Get where the line intersect
    if (not line_intersection_point(ray_line, l, pt)) return false;
    //DrawLine(ColorWhite, fromPt, pt);

    comb_mag = vector_magnitude(vector_add(unit_vector(vector_point_to_point(from_pt, pt)), unit_vector(heading)));
    // WriteLn(combMag:4:2);
    // Test that pt is forward of fromPt (given heading)
    if ( comb_mag < 1 ) return false; //behind point

    return true;
}

vector_2d vector_out_of_rect_from_point(const point_2d &pt, const rectangle &rect, const vector_2d &velocity)
{
    point_2d pt_on_line;
    vector_2d ray, v_out;
    int i;
    float dist, max_dist;
    
    // Cast ray searching back from pts... looking for the impact point
    ray = vector_invert(velocity);  // the ray
    v_out = vector_to(0,0);          // the vector out (from the point to over the line, i.e. moving the point along this vector moves it back over the line)
    
    line lines[4] = {
        { {rect.x, rect.y}, {rect.x + rect.width, rect.y} },
        { {rect.x, rect.y}, {rect.x, rect.y + rect.height} },
        { {rect.x + rect.width, rect.y}, {rect.x + rect.width, rect.y + rect.height} },
        { {rect.x, rect.y + rect.height}, {rect.x + rect.width, rect.y + rect.height} }
    };
    
    // Indicate no find so far....
    int max_idx = -1;
    max_dist = -1;
    
    //Search all lines for hit points
    for (i = 0; i < 4; i++)
    {
        //DrawCircle(ColorWhite, pts[j], 2);
        
        // Cast a ray back from this point to find line pts... out on ptOnLine
        // ptOnLine is then the point that the ray intersects with the line
        if ( ray_intersection_point(pt, ray, lines[i], pt_on_line) )
        {
            //DrawCircle(ColorRed, ptOnLine, 1);
            //DrawLine(ColorRed, pts[j], ptOnLine);
            
            if (not point_on_line(pt_on_line, lines[i])) continue; //this points ray misses the line
    
            // Calculate the distance from the point on the line to the point being tested
            dist = point_point_distance(pt_on_line, pt);
            
            // Check if the distance is the new max distance
            if ((dist > max_dist) or (max_idx == -1))
            {
                max_dist = dist;
                max_idx = i;
                v_out = vector_point_to_point(pt, pt_on_line);
                v_out = vector_multiply(unit_vector(v_out), vector_magnitude(v_out) + 1.4);
            }
        }
    }
    
    return v_out;
}

//vector_2d vector_out_of_rect_from_rect(const rectangle &src, const rectangle &bounds, const vector_2d &velocity)
//{
//    
//}

vector_2d vector_out_of_circle_from_point(const point_2d &pt, const circle &c, const vector_2d &velocity)
{
    float dx, dy, cx, cy;
    float a, b, c1, det, t, mv_out;
    point_2d ipt2;
    
    // If the point is not in the radius of the circle, return a zero vector
    if (point_point_distance(pt, center_point(c)) > c.radius)
    {
        return vector_to(0, 0);
    }
    
    // Calculate the determinant (and components) from the center circle and
    // the point+velocity details
    cx = c.center.x;
    cy = c.center.y;
    dx = velocity.x;
    dy = velocity.y;
    
    a = dx * dx + dy * dy;
    b = 2 * (dx * (pt.x - cx) + dy * (pt.y - cy));
    c1 = (pt.x - cx) * (pt.x - cx) + (pt.y - cy) * (pt.y - cy) - c.radius * c.radius;
    
    det = b * b - 4 * a * c1;
    
    // If the determinate is very small, return a zero vector
    if ((det <= 0) or (a == 0))
        return vector_to(0, 0);
    else
    {
        // Calculate the vector required to "push" the vector out of the circle
        t = (-b - sqrt(det)) / (2 * a);
        ipt2.x = pt.x + t * dx;
        ipt2.y = pt.y + t * dy;
        
        mv_out = point_point_distance(pt, ipt2) + 1.42; // sqrt 2
        return vector_multiply(unit_vector(vector_invert(velocity)), mv_out);
    }
}

vector_2d vector_out_of_circle_from_circle(const circle &src, const circle &bounds, const vector_2d &velocity)
{
    circle c = circle_at(center_point(bounds), bounds.radius + src.radius);
    return vector_out_of_circle_from_point(center_point(src), c, velocity);
}

//vector_2d vector_out_of_rect_from_circle(const circle &c, const rectangle &rect, const vector_2d &velocity)
//{
//    
//}