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

circle circle_at(const point_2d &pt, float radius);

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
 */
point_2d center_point(const circle &c);

void widest_points(const circle &c, const vector_2d &along, point_2d &pt1, point_2d &pt2);

bool distant_point_on_circle_heading(const point_2d &pt, const circle &c, const vector_2d &heading, point_2d &opposite_pt);

float ray_circle_intersect_distance(const point_2d &ray_origin, const vector_2d &ray_heading, const circle &c);

#endif /* circle_geometry_hpp */
