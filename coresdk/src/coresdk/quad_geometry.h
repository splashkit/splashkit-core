//
//  quad_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 23/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef quad_geometry_h
#define quad_geometry_h

#include "types.h"
#include "matrix_2d.h"

namespace splashkit_lib
{
    /**
     *Returns a quad for the passed in x & y points.
     */
    quad quad_from(float x_top_left, float y_top_left, float x_top_right, float y_top_right, float x_bottom_left, float y_bottom_left, float x_bottom_right, float y_bottom_right );

    /**
     * Returns a quad from the x-y points of a given recatangle
     */
    quad quad_from(const rectangle &rect);

    /**
     * Returns a quad from the rectangle, then applies the transformation to
     * the quads points.
     *
     * @param rect          The rectangle to transform to a quad.
     * @param transform     A transform to apply to the resulting quad.
     * @returns             A quad that represents the rectangle after the transformation.
     */
    quad quad_from(const rectangle &rect, const matrix_2d &transform);

    quad quad_from(point_2d p1, point_2d p2, point_2d p3, point_2d p4);
}
#endif /* quad_geometry_h */
