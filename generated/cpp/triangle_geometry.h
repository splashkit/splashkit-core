//
// SplashKit Generated Triangle Geometry C++ Code
// DO NOT MODIFY
//

#ifndef __triangle_geometry_h
#define __triangle_geometry_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

point_2d triangle_barycenter(const triangle &tri);
triangle triangle_from(const point_2d &p1, const point_2d &p2, const point_2d &p3);
triangle triangle_from(float x1, float y1, float x2, float y2, float x3, float y3);
bool triangle_rectangle_intersect(const triangle &tri, const rectangle &rect);
string triangle_to_string(const triangle &tri);
bool triangles_intersect(const triangle &t1, const triangle &t2);

#endif /* __triangle_geometry_h */
