//
// SplashKit Generated Triangle Geometry C++ Code
// DO NOT MODIFY
//

#ifndef __triangle_geometry_h
#define __triangle_geometry_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

point_2d triangle_barycenter(const triangle &tri);
triangle triangle_from(const point_2d &p1, const point_2d &p2, const point_2d &p3);
triangle triangle_from(double x1, double y1, double x2, double y2, double x3, double y3);
bool triangle_quad_intersect(const triangle &tri, const quad &q);
bool triangle_ray_intersection(const point_2d &origin, const vector_2d &heading, const triangle &tri);
bool triangle_ray_intersection(const point_2d &origin, const vector_2d &heading, const triangle &tri, point_2d &hit_point, double &hit_distance);
bool triangle_rectangle_intersect(const triangle &tri, const rectangle &rect);
string triangle_to_string(const triangle &tri);
bool triangles_intersect(const triangle &t1, const triangle &t2);

#endif /* __triangle_geometry_h */
