//
// SplashKit Generated Line Geometry C++ Code
// DO NOT MODIFY
//

#ifndef __line_geometry_h
#define __line_geometry_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

point_2d closest_point_on_line(const point_2d from_pt, const line &l);
point_2d closest_point_on_lines(const point_2d from_pt, const vector<line> &lines, int &line_idx);
line line_from(const point_2d &start, const point_2d &end_pt);
line line_from(const point_2d &start, const vector_2d &offset);
line line_from(const vector_2d &v);
line line_from(double x1, double y1, double x2, double y2);
bool line_intersection_point(const line &line1, const line &line2, point_2d &pt);
bool line_intersects_circle(const line &l, const circle &c);
bool line_intersects_lines(const line &l, const vector<line> &lines);
bool line_intersects_rect(const line &l, const rectangle &rect);
float line_length(const line &l);
float line_length_squared(const line &l);
point_2d line_mid_point(const line &l);
vector_2d line_normal(const line &l);
string line_to_string(const line &ln);
vector<line> lines_from(const rectangle &rect);
vector<line> lines_from(const triangle &t);
bool lines_intersect(const line &l1, const line &l2);

#endif /* __line_geometry_h */
