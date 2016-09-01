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

#include <string>
using namespace std;

/**
 *  Get a text description of the `vector`.
 */
string vector_to_string(const vector_2d &v);

/**
 *  Returns a vector to the indicated point.
 */
vector_2d vector_to(float x, float y);

/**
 *  Returns a new `vector_2d` using the x and y value of a `point_2d` parameter.
 *  This is a vector from the origin to that point.
 */
vector_2d vector_to(const point_2d &p1);

/**
 *  Returns a `vector_2d` created from the difference from the `p1` to
 *  the second `p2` points (`Point2D`).
 */
vector_2d vector_point_to_point(const point_2d &start, const point_2d &end);

/**
 *  Returns a `vector_2d` from the supplied angle and distance.
 */
vector_2d vector_from_angle(float angle, float magnitude);

/**
 *  Returns a vector that points from the start to the end of a line.
 */
vector_2d vector_from_line(const line &l);

/**
 *  Adds the two passed in vectors returns the result as new `vector_2d`.
 */
vector_2d vector_add(const vector_2d &v1, const vector_2d &v2);

/**
 *  Subtracts the second vector parameter (`v2`) from the first vector
 *  (`v1`) and returns the result as new `vector_2d`.
 */
vector_2d vector_subtract(const vector_2d &v1, const vector_2d &v2);

/**
 *  Multiplies the vector by the passed in value.
 */
vector_2d vector_multiply(const vector_2d &v1, float s);

/**
 *  Determines if two vectors are the same.
 */
bool vectors_equal(const vector_2d &v1, const vector_2d v2);

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
 *  Returns a new `vector_2d` that is perpendicular ("normal") to the parameter
 *  vector `v` provided. The concept of a "normal" vector is usually
 *  extracted from (or associated with) a line.
 *
 *  Note: when passed a zero or null vector (a vector with no
 *  magnitude or direction) then this function returns a zero/null vector.
 */
vector_2d vector_normal(const vector_2d &v);

/**
 *  Returns a new Vector that is an inverted version of the parameter
 *  vector (v). In other words, the -/+ sign of the x and y values are changed.
 */
vector_2d vector_invert(const vector_2d &v);

/**
 * Returns the squared magnitude (or "length") of the vector.
 */
float vector_magnitude_sqared(const vector_2d &v);

/**
 * Returns the magnitude (or "length") of the vector.
 */
float vector_magnitude(const vector_2d &v);

/**
 *  Returns a scaled vector that ensures the new vector points
 *  in the same direction as v, but has a magnitude that is 
 *  limited to the length specified in the limit prameter.
 */
vector_2d vector_limit(const vector_2d &v, float limit);

/**
 *  Returns the unit vector of the parameter vector (v). The unit vector has a
 *  magnitude of 1, resulting in a vector that indicates the direction of
 *  the original vector.
 */
vector_2d unit_vector(const vector_2d &v);

/**
 *  Returns if the vector is a null/zero vector -- having no size or direction.
 */
bool is_zero_vector(const vector_2d &v);

/**
 *  Calculates the angle of a vector.
 */
float vector_angle(const vector_2d v);

/**
 *  Determines the vector needed to move back from point `pt` out of rectangle `rect` given
 *  the point was moving at the velocity specified.
 */
vector_2d vector_out_of_rect_from_point(const point_2d &pt, const rectangle &rect, const vector_2d &velocity);

/**
 *  Returns the vector needed to move rectangle `src` back out of rectangle `bounds`
 *  assuming the rectangle was moving at the velocity specified.
 */
vector_2d vector_out_of_rect_from_rect(const rectangle &src, const rectangle &bounds, const vector_2d &velocity);

/**
 *  Returns the vector out to move a point back out of a circle, 
 *  given the point was moving at the specified velocity.
 */
vector_2d vector_out_of_circle_from_point(const point_2d &pt, const circle &c, const vector_2d &velocity);

/**
 *  Returns a vector to back one circle out of another, assuming the first circle was
 *  moving at a specified velocity.
 */
vector_2d vector_out_of_circle_from_circle(const circle &src, const circle &bounds, const vector_2d &velocity);

/**
 *  Returns a vector that can be used to move a circle back out of a rectangle,
 *  given that the circle is moving at the specified velocity.
 */
vector_2d vector_out_of_rect_from_circle(const circle &c, const rectangle &rect, const vector_2d &velocity);

#endif /* vector_2d_h */
