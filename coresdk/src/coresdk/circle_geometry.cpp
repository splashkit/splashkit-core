//
//  circle_geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 22/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "circle_geometry.h"

#include "geometry.h"
#include "vector_2d.h"

#include <cmath>
namespace splashkit_lib
{
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

    point_2d center_point(const circle &c)
    {
        return c.center;
    }

    void widest_points(const circle &c, const vector_2d &along, point_2d &pt1, point_2d &pt2)
    {
        pt1 = point_offset_by(c.center, vector_multiply(unit_vector(along), c.radius));
        pt2 = point_offset_by(c.center, vector_multiply(unit_vector(along), -c.radius));
    }

    bool distant_point_on_circle_heading(const point_2d &pt, const circle &c, const vector_2d &heading, point_2d &opposite_pt)
    {
        float dist, dot_prod;
        point_2d pt_on_circle, chk_pt;
        vector_2d to_center, head;

        head = unit_vector(heading);

        //Move pt back 2 * radius to ensure it is outside of the circle...
        //  but still on same alignment
        chk_pt = point_offset_by(pt, vector_multiply(vector_invert(head), 2 * c.radius));
        //DrawCircle(ColorBlue, chk_pt, 1);

        dist = ray_circle_intersect_distance(chk_pt, head, c);
        if (dist < 0) return false;

        // Get point on circle by moving from chk_pt dist distance in heading direction
        pt_on_circle = point_offset_by(chk_pt, vector_multiply(head, dist));
        //DrawLine(ColorMagenta, chk_pt, pt_on_circle);
        //DrawCircle(ColorMagenta, pt_on_circle, 2);

        //Project the ray to the other side of the circle
        to_center = vector_point_to_point(pt_on_circle, c.center);
        dot_prod = dot_product(to_center, head);
        //WriteLn(dot_prod:4:2);

        opposite_pt = point_offset_by(pt_on_circle, vector_multiply(head, 2 * dot_prod));
        //FillCircle(ColorRed, oppositePt, 2);
        return true;
    }

    float ray_circle_intersect_distance(const point_2d &ray_origin, const vector_2d &ray_heading, const circle &c)
    {
        vector_2d to_circle, unit_heading;
        float length, v, d;

        unit_heading = unit_vector(ray_heading);
        to_circle = vector_point_to_point(ray_origin, c.center);
        length = vector_magnitude(to_circle);

        v = dot_product(to_circle, unit_heading);
        d = c.radius*c.radius - (length*length - v*v);

        if (d < 0.0)
            // if there was no intersection, return -1
            return -1.0;
        else
            // return the distance to the (first) intersection point
            return (v - sqrt(d));
    }
    
    bool circles_intersect(circle c1, circle c2)
    {
        return point_point_distance(c1.center, c2.center) < c1.radius + c2.radius;
    }
}