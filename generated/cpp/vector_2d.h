//
// SplashKit Generated Vector 2 D C++ Code
// DO NOT MODIFY
//

#ifndef __vector_2d_h
#define __vector_2d_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

double angle_between(const vector_2d &v1, const vector_2d &v2);
double dot_product(const vector_2d &v1, const vector_2d &v2);
bool is_zero_vector(const vector_2d &v);
bool ray_intersection_point(const point_2d &from_pt, const vector_2d &heading, const line &l, point_2d &pt);
vector_2d unit_vector(const vector_2d &v);
vector_2d vector_add(const vector_2d &v1, const vector_2d &v2);
double vector_angle(const vector_2d v);
vector_2d vector_from_angle(double angle, double magnitude);
vector_2d vector_from_line(const line &l);
vector_2d vector_from_point_to_rect(const point_2d &pt, const rectangle &rect);
bool vector_in_rect(const vector_2d &v, const rectangle &rect);
vector_2d vector_invert(const vector_2d &v);
vector_2d vector_limit(const vector_2d &v, double limit);
double vector_magnitude(const vector_2d &v);
double vector_magnitude_sqared(const vector_2d &v);
vector_2d vector_multiply(const vector_2d &v1, double s);
vector_2d vector_normal(const vector_2d &v);
vector_2d vector_out_of_circle_from_circle(const circle &src, const circle &bounds, const vector_2d &velocity);
vector_2d vector_out_of_circle_from_point(const point_2d &pt, const circle &c, const vector_2d &velocity);
vector_2d vector_out_of_rect_from_circle(const circle &c, const rectangle &rect, const vector_2d &velocity);
vector_2d vector_out_of_rect_from_point(const point_2d &pt, const rectangle &rect, const vector_2d &velocity);
vector_2d vector_out_of_rect_from_rect(const rectangle &src, const rectangle &bounds, const vector_2d &velocity);
vector_2d vector_point_to_point(const point_2d &start, const point_2d &end_pt);
vector_2d vector_subtract(const vector_2d &v1, const vector_2d &v2);
vector_2d vector_to(const point_2d &p1);
vector_2d vector_to(double x, double y);
string vector_to_string(const vector_2d &v);
bool vectors_equal(const vector_2d &v1, const vector_2d v2);
bool vectors_not_equal(const vector_2d &v1, const vector_2d v2);

#endif /* __vector_2d_h */
