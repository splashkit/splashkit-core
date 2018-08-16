//
// SplashKit Generated Point Geometry C++ Code
// DO NOT MODIFY
//

#ifndef __point_geometry_h
#define __point_geometry_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

point_2d point_at(double x, double y);
point_2d point_at_origin();
bool point_in_circle(const point_2d &pt, const circle &c);
bool point_in_quad(const point_2d &pt, const quad &q);
bool point_in_rectangle(const point_2d &pt, const rectangle &rect);
bool point_in_triangle(const point_2d &pt, const triangle &tri);
float point_line_distance(const point_2d &pt, const line &l);
point_2d point_offset_by(const point_2d &start_point, const vector_2d &offset);
point_2d point_offset_from_origin(const vector_2d &offset);
bool point_on_line(const point_2d &pt, const line &l);
bool point_on_line(const point_2d &pt, const line &l, float proximity);
float point_point_angle(const point_2d &pt1, const point_2d &pt2);
float point_point_distance(const point_2d &pt1, const point_2d &pt2);
string point_to_string(const point_2d &pt);
point_2d random_bitmap_point(bitmap bmp);
point_2d random_screen_point();
point_2d random_window_point(window wind);
bool same_point(const point_2d &pt1, const point_2d &pt2);

#endif /* __point_geometry_h */
