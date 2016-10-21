/*
 * SplashKit Quad Geometry
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __quad_geometry_h
#define __quad_geometry_h

#include "matrix_2d.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

quad quad_from(const point_2d &p1, const point_2d &p2, const point_2d &p3, const point_2d &p4);
quad quad_from(const rectangle &rect);
quad quad_from(const rectangle &rect, const matrix_2d &transform);
quad quad_from(float x_top_left, float y_top_left, float x_top_right, float y_top_right, float x_bottom_left, float y_bottom_left, float x_bottom_right, float y_bottom_right);
bool quads_intersect(const quad &q1, const quad &q2);
void set_quad_point(quad &q, int idx, const point_2d &value);
vector<triangle> triangles_from(const quad &q);

#endif /* __quad_geometry_h */
