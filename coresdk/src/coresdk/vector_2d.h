//
//  vector_2d.hpp
//  splashkit
//
//  Created by Andrew Cain on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef vector_2d_h
#define vector_2d_h

#include "types.h"


/**
 *  Returns a new `vector_2d` using the x and y value of a `point_2d` parameter.
 *  This is a vector from the origin to that point.
 */
vector_2d vector_to_point(const point_2d &p1);

/**
 *  Returns a `Vector` created from the difference from the ``p1`` to
 *  the second ``p2`` points (`Point2D`).
 */
vector_2d vector_point_to_point(const point_2d &start, const point_2d &end);

vector_2d vector_subtract(const vector_2d &v1, const vector_2d &v2);

/**
 *  Calculates the dot product (scalar product) between the two vector
 *  parameters provided (`v1` and `v2`). It returns the result as a
 *  scalar value.
 *
 *  If the result is 0.0 it means that the vectors are orthogonal (at right
 *  angles to each other). If `v1` and `v2` are unit vectors (length of
 *  1.0) and the dot product is 1.0, it means that `v1` and `v2` vectors
 *  are parallel.
 */
float dot_product(const vector_2d &v1, const vector_2d &v2);

/**
 * Returns the squared magnitude (or "length") of the vector.
 */
float vector_magnitude_sqared(const vector_2d &v);

/**
 * Returns the magnitude (or "length") of the vector.
 */
float vector_magnitude(const vector_2d &v);

#endif /* vector_2d_h */
