//
//  line_geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 20/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "line_geometry.h"
#include "point_geometry.h"
#include "utility_functions.h"

#include <cmath>

namespace splashkit_lib
{
    line line_from(const point_2d &start, const point_2d &end)
    {
        return {start, end};
    }

    line line_from(float x1, float y1, float x2, float y2)
    {
        return line_from(point_at(x1, y1), point_at(x2, y2));
    }

    line line_from_vector(const point_2d &start, const vector_2d &offset)
    {
        return line_from(start, point_offset_by(start, offset) );
    }

    float line_length_squared(const line &l)
    {
        return (l.end_point.x - l.start_point.x) * (l.end_point.x - l.start_point.x) +
        (l.end_point.y - l.start_point.y) * (l.end_point.y - l.start_point.y);
    }

    line line_from(const vector_2d &v)
    {
        return { {0,0}, {static_cast<float>(v.x), static_cast<float>(v.y)} };
    }

    line line_from(const point_2d pt, const vector_2d &v)
    {
        return { {pt.x, pt.y}, {static_cast<float>(pt.x + v.x), static_cast<float>(pt.y + v.y)} };
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

    point_2d closest_point_on_line(const point_2d from_pt, const line &l)
    {
        float sq_line_mag, u;

        // see Paul Bourke's original article(s)
        // square of line's magnitude (see note in function LineMagnitude)
        sq_line_mag = line_length_squared(l);
        if ( sq_line_mag < EPSEPS)
        {
            LOG(WARNING) << "Cannot determine intersection point on line, line is too short";
            return point_at(0,0);
        }

        u = ( (from_pt.x - l.start_point.x)*(l.end_point.x - l.start_point.x) + (from_pt.y - l.start_point.y) * (l.end_point.y - l.start_point.y) ) / sq_line_mag;

        if ((u < EPS) or (u > 1))
        {
            //  Closest point does not fall within the line segment,
            //    take the shorter distance to an endpoint
            if (line_length_squared(line_from(from_pt.x, from_pt.y, l.start_point.x, l.start_point.y)) < line_length_squared(line_from(from_pt.x, from_pt.y, l.end_point.x, l.end_point.y)))
                return l.start_point;
            else
                return l.end_point;
        } //  if (u < EPS) or (u > 1)
        else
        {
            //  Intersecting point is on the line, use the formula
            return point_at(
                            l.start_point.x + u * (l.end_point.x - l.start_point.x),
                            l.start_point.y + u * (l.end_point.y - l.start_point.y));
            
        } //  else NOT (u < EPS) or (u > 1)
    }

    vector<line> lines_from(const triangle &t)
    {
        vector<line> result;

        result.push_back(line_from(t.points[0], t.points[1]));
        result.push_back(line_from(t.points[1], t.points[2]));
        result.push_back(line_from(t.points[2], t.points[0]));

        return result;
    }

    float line_length(const line &l)
    {
        return sqrt(line_length_squared(l));
    }

    bool lines_intersect(const line &l1, const line &l2)
    {
        if ( line_length(l1) == 0 || line_length(l2) == 0 ) return false;

        point_2d pt;
        return line_intersection_point(l1, l2, pt) and point_on_line(pt, l1) and point_on_line(pt, l2);
    }
}