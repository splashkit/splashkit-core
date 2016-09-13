//
//  line_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 20/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef line_geometry_hpp
#define line_geometry_hpp

#include "types.h"

#include <vector>
using std::vector;

namespace splashkit_lib
{
    line line_from(const point_2d &start, const point_2d &end);
    line line_from(float x1, float y1, float x2, float y2);
    line line_from_vector(const point_2d &start, const vector_2d &offset);

    float line_length_squared(const line &l);

    /**
     * Returns the length of a line.
     *
     * @param  l The line
     * @return   The length of the line
     */
    float line_length(const line &l);

    line line_from(const vector_2d &v);
    line line_from(const point_2d pt, const vector_2d &v);

    /**
     * Returns an array of lines from the details in the triangle.
     *
     * @param t The triangle
     * @return  The lines from the triangle
     */
    vector<line> lines_from(const triangle &t);

    /**
     * Returns an array of lines from a supplied rectangle.
     *
     * @param rect  The rectangle to get the lines from
     * @return      An array containing 4 lines
     */
    vector<line> lines_from(const rectangle &rect);

    bool line_intersection_point(const line &line1, const line &line2, point_2d &pt);

    point_2d closest_point_on_line(const point_2d from_pt, const line &l);

    /**
     * Returns true if the two lines intersect.
     *
     * @param  l1 The first line
     * @param  l2 The other line
     * @return    True if the two lines intersect (share a common point).
     */
    bool lines_intersect(const line &l1, const line &l2);
}
#endif /* line_geometry_hpp */
