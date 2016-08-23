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


/**
 *Returns a quad for the passed in x & y points.
 */
quad quad_from(float x_top_left, float y_top_left, float x_top_right, float y_top_right, float x_bottom_left, float y_bottom_left, float x_bottom_right, float y_bottom_right );

/**
 * Returns a quad from the x-y points of a given recatangle
 */
quad quad_from(const rectangle &rect);

/**
 * Use a matrix to transform all of the points in a quad.
 */
void apply_matrix(const matrix_2d m, quad _quad);

/**
 *  Multiplying matrix by point_2d and returning as point_2d.
 */

point_2d matrix_multiply(const matrix_2d &m, const point_2d &pts);


#endif /* quad_geometry_h */
