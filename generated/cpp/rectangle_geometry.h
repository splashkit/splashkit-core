//
// SplashKit Generated Rectangle Geometry C++ Code
// DO NOT MODIFY
//

#ifndef __rectangle_geometry_h
#define __rectangle_geometry_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

rectangle inset_rectangle(const rectangle &rect, float inset_amount);
rectangle intersection(const rectangle &rect1, const rectangle &rect2);
rectangle rectangle_around(const circle &c);
rectangle rectangle_around(const line &l);
rectangle rectangle_around(const quad &q);
rectangle rectangle_around(const triangle &t);
float rectangle_bottom(const rectangle &rect);
point_2d rectangle_center(const rectangle &rect);
rectangle rectangle_from(const point_2d pt, const double width, const double height);
rectangle rectangle_from(const point_2d pt1, const point_2d pt2);
rectangle rectangle_from(double x, double y, double width, double height);
float rectangle_left(const rectangle &rect);
rectangle rectangle_offset_by(const rectangle &rect, const vector_2d &offset);
float rectangle_right(const rectangle &rect);
string rectangle_to_string(const rectangle &rect);
float rectangle_top(const rectangle &rect);
bool rectangles_intersect(const rectangle &rect1, const rectangle &rect2);

#endif /* __rectangle_geometry_h */
