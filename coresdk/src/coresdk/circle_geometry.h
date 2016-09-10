//
//  circle_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 22/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef circle_geometry_hpp
#define circle_geometry_hpp

#include "types.h"
namespace splashkit_lib
{
    /**
     * Returns a circle at the indicated point and radius.
     *
     * @param  pt     The location of the center of the circle
     * @param  radius The radius of the circle
     * @return        A circle at the indicatd point and radius
     */
    circle circle_at(const point_2d &pt, float radius);

    /**
     * Returns a circle at the indicated point and radius.
     *
     * @param  x      The x location of the circle
     * @param  y      The y location of the circle
     * @param  radius The radius of the circle
     * @return        A circle at the indicatd point and radius
     * 
     * @attribute suffic from_points
     */
    circle circle_at(float x, float y, float radius);

    /**
     * Detects if two circles intersect. This can be used to detect collisions between
     * bounding circles.
     *
     * @param c1    The circle to test if intersects with c2
     * @param c2    The circle to test if intersects with c1
     * @returns     True if the two circles do intersect
     */
    bool circles_intersect(circle c1, circle c2);

    /**
     *  Returns the center point of the circle.
     *
     * @param c   The circle to get the center point
     * @returns   The center point of the circle
     */
    point_2d center_point(const circle &c);

    /**
     * Calculates the two points on a circles radius that lie along the given
     * vector. This represents the points on the circle when the vector is
     * placed at the circle's center point.
     *
     * @param c     The circle
     * @param along The vector representing the line along which the points lie.
     * @param pt1   After the call, this is set to one of the widest points
     * @param pt2   After the call, this is set to one of the widest points
     */
    void widest_points(const circle &c, const vector_2d &along, point_2d &pt1, point_2d &pt2);

    /**
     * Determines the opposite side of a circle given a collision point and a
     * heading.
     *
     * @param  pt          The point from which the test is being made
     * @param  c           The circle
     * @param  heading     The direction the point is heading
     * @param  opposite_pt After the call, this is set to the point on the
     *                     opposite side of the circle from pt when it is
     *                     heading in the given direction.
     * @return             True when the `opposite_pt` is calculated, false when
     *                     the point would not collide with the circle when
     *                     heading as indicated.
     */
    bool distant_point_on_circle_heading(const point_2d &pt, const circle &c, const vector_2d &heading, point_2d &opposite_pt);

    /**
     * Calculates the distance from a ray cast from a point to a given circle.
     *
     * @param  ray_origin  The origin of the ray
     * @param  ray_heading The direction of the ray
     * @param  c           The circle being tested
     * @return             -1 if the ray does not hit the circle, otherwise the
     *                     distance from the origin to the circle bounds.
     */
    float ray_circle_intersect_distance(const point_2d &ray_origin, const vector_2d &ray_heading, const circle &c);

    /**
     *  Returns the circle radius.
     *
     * @param  c The circle
     * @return   The radius of the circle
     */
    float circle_radius(const circle c);

    /**
     *  Returns the circle x value.
     *
     * @param  c The circle
     * @return   The x location of the center of the circle
     */
    float circle_x(const circle &c);

    /**
     *  Returns the circle y value.
     *
     * @param  c The circle
     * @return   The y location of the center of the circle
     */
    float circle_y(const circle &c);

}
#endif /* circle_geometry_hpp */
