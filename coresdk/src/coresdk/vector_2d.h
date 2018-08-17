/**
 * @header  vector_2d
 * @author  Andrew Cain
 * @brief   Provides vector functions to work on vectors.
 *
 * @attribute group  physics
 * @attribute static vector_2d
 */

#ifndef vector_2d_h
#define vector_2d_h

#include "types.h"

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     *  Get a text description of the `vector_2d`.
     *
     * @param  v The vector
     * @return   A string representation of the vector
     */
    string vector_to_string(const vector_2d &v);

    /**
     *  Returns a vector to the indicated point.
     *
     * @param  x The amount to move horizontally
     * @param  y The amount to move vertically
     * @return   A vector that will move things the indicated amount
     */
    vector_2d vector_to(double x, double y);

    /**
     *  Returns a new `vector_2d` using the x and y value of a `point_2d` parameter.
     *  This is a vector from the origin to that point.
     *
      * @param  p1 The point
      * @return    A vector from the origin to `p1`
      *
      * @attribute suffix  point
      */
    vector_2d vector_to(const point_2d &p1);

    /**
     *  Returns a `vector_2d` created from the difference from the `p1` to
     *  the second `p2` points (`Point2D`).
     *
     * @param  start The starting point
     * @param  end_pt   The ending point
     * @return       A vector that will move things from the starting point to
     *               the ending point
     */
    vector_2d vector_point_to_point(const point_2d &start, const point_2d &end_pt);

    /**
     *  Returns a `vector_2d` from the supplied angle and distance.
     *
     * @param  angle     The angle in degrees
     * @param  magnitude The length of the vector
     * @return           A vector that will move things at that angle and
     *                   magnitude
     */
    vector_2d vector_from_angle(double angle, double magnitude);

    /**
     *  Returns a vector that points from the start to the end of a line.
     *
     * @param  l The line
     * @return   A vector that will move things from the start to the end of the
     *           line
     */
    vector_2d vector_from_line(const line &l);

    /**
     *  Adds the two passed in vectors returns the result as new `vector_2d`.
     *
     * @param  v1 The first vector.
     * @param  v2 The other vector.
     * @return    The result of adding the movements of the two vectors
     *            together.
     */
    vector_2d vector_add(const vector_2d &v1, const vector_2d &v2);

    /**
     *  Subtracts the second vector parameter (`v2`) from the first vector
     *  (`v1`) and returns the result as new `vector_2d`.
     *
     * @param  v1 The first vector.
     * @param  v2 The other vector.
     * @return    The result of subtracting the movements of `v2` from `v1`.
     */
    vector_2d vector_subtract(const vector_2d &v1, const vector_2d &v2);

    /**
     *  Multiplies the vector by the passed in value.
     *
     * @param  v1 The original vector
     * @param  s  The amount to multiply by
     * @return    A new vector
     */
    vector_2d vector_multiply(const vector_2d &v1, double s);

    /**
     *  Determines if two vectors are the same.
     *
     * @param  v1 The first vector
     * @param  v2 The other vector
     * @return    True if the two vectors are equal.
     */
    bool vectors_equal(const vector_2d &v1, const vector_2d v2);

    /**
     *  Determines if two vectors are not the same.
     *
     * @param  v1 The first vector
     * @param  v2 The other vector
     * @return    True if the two vectors are different.
     */
    bool vectors_not_equal(const vector_2d &v1, const vector_2d v2);

    /**
     *  Calculates the dot product (scalar product) between the two vector
     *  parameters provided (`v1` and `v2`). It returns the result as a
     *  scalar value.
     *
     *  If the result is 0.0 it means that the vectors are orthogonal (at right
     *  angles to each other). If `v1` and `v2` are unit vectors (length of
     *  1.0) and the dot product is 1.0, it means that `v1` and `v2` vectors
     *  are parallel.
     *
     * @param  v1 The first vector
     * @param  v2 The other vector
     * @return    The dot product of `v1` . `v2`
     */
    double dot_product(const vector_2d &v1, const vector_2d &v2);

    /**
     *  Returns a new `vector_2d` that is perpendicular ("normal") to the parameter
     *  vector `v` provided. The concept of a "normal" vector is usually
     *  extracted from (or associated with) a line.
     *
     *  Note: when passed a zero or null vector (a vector with no
     *  magnitude or direction) then this function returns a zero/null vector.
     *
     * @param  v The vector
     * @return   The normal of `v`
     */
    vector_2d vector_normal(const vector_2d &v);

    /**
     *  Returns a new Vector that is an inverted version of the parameter
     *  vector (v). In other words, the -/+ sign of the x and y values are changed.
     *
     * @param  v The vector
     * @return   The inverse (reverse) of `v`
     */
    vector_2d vector_invert(const vector_2d &v);

    /**
     * Returns the squared magnitude (or "length") of the vector.
     *
     * @param  v The vector
     * @return   Its squared magnitude
     */
    double vector_magnitude_sqared(const vector_2d &v);

    /**
     * Returns the magnitude (or "length") of the vector.
     *
     * @param  v The vector
     * @return   Its magnitude
     */
    double vector_magnitude(const vector_2d &v);

    /**
     *  Returns a scaled vector that ensures the new vector points
     *  in the same direction as v, but has a magnitude that is
     *  limited to the length specified in the limit prameter.
     *
     * @param  v     The vector
     * @param  limit Its maximum magnitude
     * @return       A new vector in the same direction as v, but with a
     *               magnitude that is less than or equal to the limit.
     */
    vector_2d vector_limit(const vector_2d &v, double limit);

    /**
     *  Returns the unit vector of the parameter vector (v). The unit vector has a
     *  magnitude of 1, resulting in a vector that indicates the direction of
     *  the original vector.
     *
     * @param  v The vector
     * @return   The unit vector of `v`
     */
    vector_2d unit_vector(const vector_2d &v);

    /**
     *  Returns if the vector is a null/zero vector -- having no size or direction.
     *
     * @param  v The vector
     * @return   True if `v` has no magnitude.
     */
    bool is_zero_vector(const vector_2d &v);

    /**
     *  Calculates the angle of a vector
     *
     * @param  v The vector
     * @return   The angle of the vector in degrees
     */
    double vector_angle(const vector_2d v);

    /**
     * Calculates the angle from one vector to another.
     *
     * @param v1    The first vector
     * @param v2    The second vector
     * @returns     The angle of the line from the end of `v1` to the end of `v2`
     */
    double angle_between(const vector_2d &v1, const vector_2d &v2);

    /**
     *  Determines the vector needed to move back from point `pt` out of rectangle `rect` given
     *  the point was moving at the velocity specified.
     *
     * @param  pt       The point you want to move out of a rectangle
     * @param  rect     The rectangle to move out of
     * @param  velocity The velocity of the point. This is used to determine
     *                  where the point should return to.
     * @return          A vector that can move the point outside of the
     *                  rectangle.
     */
    vector_2d vector_out_of_rect_from_point(const point_2d &pt, const rectangle &rect, const vector_2d &velocity);

    /**
     *  Returns the vector needed to move rectangle `src` back out of rectangle `bounds`
     *  assuming the rectangle was moving at the velocity specified.
     *
     * @param  src      The rectangle you want to move.
     * @param  bounds   The area you want to move the rectangle out of
     * @param  velocity The velocity of the `src` rectangle
     * @return          A vector that can move the rectangle out of the bounds
     */
    vector_2d vector_out_of_rect_from_rect(const rectangle &src, const rectangle &bounds, const vector_2d &velocity);

    /**
     *  Returns the vector out to move a point back out of a circle,
     *  given the point was moving at the specified velocity.
     *
     * @param  pt       The point that is moving
     * @param  c        The circle you want to move the point out of
     * @param  velocity The point's velocity
     * @return          A vector that can move the point out of the circle
     */
    vector_2d vector_out_of_circle_from_point(const point_2d &pt, const circle &c, const vector_2d &velocity);

    /**
     *  Returns a vector to back one circle out of another, assuming the first circle was
     *  moving at a specified velocity.
     *
     * @param  src      The circle that is moving
     * @param  bounds   The area you want to move the circle out of
     * @param  velocity The circle's velocity
     * @return          A vector that can move the circle out of the bounds
     */
    vector_2d vector_out_of_circle_from_circle(const circle &src, const circle &bounds, const vector_2d &velocity);

    /**
     *  Returns a vector that can be used to move a circle back out of a rectangle,
     *  given that the circle is moving at the specified velocity.
     *
     * @param  c        The circle that is moving
     * @param  rect     The area you wan to move the circle out of
     * @param  velocity The circle's velocity
     * @return          A vector that will move the circle out of the rectangle
     */
    vector_2d vector_out_of_rect_from_circle(const circle &c, const rectangle &rect, const vector_2d &velocity);

    /**
     * Casts a ray in a heading and returns true is it intersects with a line
     *
     * @param  from_pt The origin of the ray
     * @param  heading The direction the ray is heading (as a `vector_2d`)
     * @param  l       The line to be checked
     * @param  pt      Outputs the point where the line and ray intersect
     * @return         True if the line and ray will intersect, in which case
     *                 the value of `pt` will be changed to be the point where
     *                 the intersection occurs.
     */
    bool ray_intersection_point(const point_2d &from_pt, const vector_2d &heading, const line &l, point_2d &pt);

    /**
     * Returns a vector from a point to a rectangle.
     *
     * @param  pt   The point
     * @param  rect The rectangle
     * @return      A vector representing the distance and direction from `pt`
     *                to `rect`
     */
    vector_2d vector_from_point_to_rect(const point_2d &pt, const rectangle &rect);

    /**
     * Returns true if the resulting vector would end in the rectangle if
     * placed at the origin.
     *
     * @param  v    The vector
     * @param  rect The rectangle
     * @return      True if the vector would end in the rectangle
     */
    bool vector_in_rect(const vector_2d &v, const rectangle &rect);

}

#endif /* vector_2d_h */
