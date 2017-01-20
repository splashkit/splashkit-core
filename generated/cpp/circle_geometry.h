//
// SplashKit Generated Circle Geometry C++ Code
// DO NOT MODIFY
//

#ifndef __circle_geometry_h
#define __circle_geometry_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

point_2d center_point(const circle &c);
circle circle_at(const point_2d &pt, double radius);
circle circle_at(double x, double y, double radius);
float circle_radius(const circle c);
float circle_x(const circle &c);
float circle_y(const circle &c);
bool circles_intersect(circle c1, circle c2);
point_2d closest_point_on_circle(const point_2d &from_pt, const circle &c);
point_2d closest_point_on_line_from_circle(const circle &c, const line &l);
point_2d closest_point_on_rect_from_circle(const circle &c, const rectangle &rect);
point_2d distant_point_on_circle(const point_2d &pt, const circle &c);
bool distant_point_on_circle_heading(const point_2d &pt, const circle &c, const vector_2d &heading, point_2d &opposite_pt);
float ray_circle_intersect_distance(const point_2d &ray_origin, const vector_2d &ray_heading, const circle &c);
bool tangent_points(const point_2d &from_pt, const circle &c, point_2d &p1, point_2d &p2);
void widest_points(const circle &c, const vector_2d &along, point_2d &pt1, point_2d &pt2);

#endif /* __circle_geometry_h */
