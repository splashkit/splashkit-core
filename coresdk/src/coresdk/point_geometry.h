//
//  point_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef point_geometry_h
#define point_geometry_h

#include "types.h"
#include "window_manager.h"
#include "images.h"


point_2d point_at(float x, float y);

/**
 *  Returns a point representing the origin.
 */
point_2d point_at_origin();

/**
 *  Calculate the `point_2d` that is offset from the `start_point` by the `offset`
 */
point_2d point_offset_by(const point_2d &start_point, const vector_2d &offset);

/**
 *  Get a text description of the `point_2d`.
 */
string point_to_string(const point_2d &pt);

point_2d random_screen_point();

point_2d random_window_point(window wind);

point_2d random_bitmap_point(bitmap bmp);

/**
 *  Returns true if the point `pt` is in the Triangle `tri`.
 */
bool point_in_triangle(const point_2d &pt, const triangle &tri);

/**
 *  Returns true if point `pt` is in the Rectangle `rect`.
 */
bool point_in_rect(const point_2d &pt, const rectangle &rect);

/**
 *  Returns true if the point `pt` is in the circle `c`.
 */
bool point_in_circle(const point_2d pt, const circle &c);

/**
 *  Returns true if point `pt` is on the line `l`.
 */
bool point_on_line(const point_2d &pt, const line &l);

/**
 *  Returns True of `pt1` is at the same point as `pt2`.
 */
bool same_point(const point_2d &pt1, const point_2d &pt2);

/**
 *  Returns the angle between two points in degrees.
 */
float calculate_angle_between(const point_2d &pt1, const point_2d &pt2);

/**
 *  Returns the distance between two points.
 */
float point_point_distance(const point_2d &pt1, const point_2d pt2);



#endif /* point_geometry_h */
