//
//  rectangle_geometry.h
//  splashkit
//
//  Created by Jacob Milligan on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef rectangle_geometry_H
#define rectangle_geometry_H

#include "types.h"
#include <string>

using namespace std;

/**
 * Returns a rectangle from a given x,y location with the specified width
 * and height.
 */
rectangle rectangle_from(float x, float y, float width, float height);

/**
 * Returns a rectangle with pt1 and pt2 defining the two distant edge points.
 */
rectangle rectangle_from(const point_2d pt1, const point_2d pt2);

/**
 * Returns a rectangle at the specified point with a given width and height
 */
rectangle rectangle_from(const point_2d pt, const float width, const float height);

/**
 *  Returns a rectangle that is moved by the provided vector.
 */
rectangle rectangle_offset_by(const rectangle &rect, const vector_2d &offset);

/**
 * Returns the center point of a given rectangle
 */
point_2d rectangle_center(const rectangle &rect);

/**
 * Returns a rectangle that surrounds a given line segment
 */
rectangle rectangle_around(const line &l);

/**
 * Returns a rectangle that surrounds a given circle
 */
rectangle rectangle_around(const circle &c);

/**
 * Returns a rectangle that surrounds a given triangle
 */
rectangle rectangle_around(const triangle &t);

/**
 * Returns a rectangle that represents the intersection of two rectangles.
 *
 * @param rect1     The first rectangle
 * @param rect2     The second rectangle
 * @returns         The intersection of rect1 and rect2.
 */
rectangle intersection(const rectangle &rect1, const rectangle &rect2);


/**
 * Returns true if the two rectangles intersect.
 *
 * @param rect1     The first rectangle
 * @param rect2     The second rectangle
 * @returns         True when rect1 and rect2 intersect.
 */
bool rectangles_intersect(const rectangle &rect1, const rectangle &rect2);

float rectangle_top(const rectangle &rect);
float rectangle_bottom(const rectangle &rect);
float rectangle_left(const rectangle &rect);
float rectangle_right(const rectangle &rect);

/**
 *  Get a text representation of the passed in rectangle.
 */
string rectangle_to_string(const rectangle &rect);



#endif /* rectangle_geometry_H */
