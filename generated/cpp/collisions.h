//
// SplashKit Generated Collisions C++ Code
// DO NOT MODIFY
//

#ifndef __collisions_h
#define __collisions_h

#include "matrix_2d.h"
#include "sprites.h"
#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

bool bitmap_circle_collision(bitmap bmp, const point_2d &pt, const circle &circ);
bool bitmap_circle_collision(bitmap bmp, double x, double y, const circle &circ);
bool bitmap_circle_collision(bitmap bmp, int cell, const matrix_2d &translation, const circle &circ);
bool bitmap_circle_collision(bitmap bmp, int cell, const point_2d &pt, const circle &circ);
bool bitmap_circle_collision(bitmap bmp, int cell, double x, double y, const circle &circ);
bool bitmap_collision(bitmap bmp1, double x1, double y1, bitmap bmp2, double x2, double y2);
bool bitmap_collision(bitmap bmp1, const point_2d &pt1, bitmap bmp2, const point_2d &pt2);
bool bitmap_collision(bitmap bmp1, int cell1, const matrix_2d &matrix1, bitmap bmp2, int cell2, const matrix_2d &matrix2);
bool bitmap_collision(bitmap bmp1, int cell1, const point_2d &pt1, bitmap bmp2, int cell2, const point_2d &pt2);
bool bitmap_collision(bitmap bmp1, int cell1, double x1, double y1, bitmap bmp2, int cell2, double x2, double y2);
bool bitmap_point_collision(bitmap bmp, const matrix_2d &translation, const point_2d &pt);
bool bitmap_point_collision(bitmap bmp, const point_2d &bmp_pt, const point_2d &pt);
bool bitmap_point_collision(bitmap bmp, double bmp_x, double bmp_y, double x, double y);
bool bitmap_point_collision(bitmap bmp, int cell, const matrix_2d &translation, const point_2d &pt);
bool bitmap_point_collision(bitmap bmp, int cell, const point_2d &bmp_pt, const point_2d &pt);
bool bitmap_point_collision(bitmap bmp, int cell, double bmp_x, double bmp_y, double x, double y);
bool bitmap_quad_collision(bitmap bmp, const point_2d &pt, const quad &q);
bool bitmap_quad_collision(bitmap bmp, double x, double y, const quad &q);
bool bitmap_quad_collision(bitmap bmp, int cell, const matrix_2d &translation, const quad &q);
bool bitmap_quad_collision(bitmap bmp, int cell, const point_2d &pt, const quad &q);
bool bitmap_quad_collision(bitmap bmp, int cell, double x, double y, const quad &q);
bool bitmap_ray_collision(bitmap bmp, const point_2d &pt, const point_2d &origin, const vector_2d &heading);
bool bitmap_ray_collision(bitmap bmp, double x, double y, const point_2d &origin, const vector_2d &heading);
bool bitmap_ray_collision(bitmap bmp, int cell, const matrix_2d &translation, const point_2d &origin, const vector_2d &heading);
bool bitmap_ray_collision(bitmap bmp, int cell, const point_2d &pt, const point_2d &origin, const vector_2d &heading);
bool bitmap_ray_collision(bitmap bmp, int cell, double x, double y, const point_2d &origin, const vector_2d &heading);
bool bitmap_rectangle_collision(bitmap bmp, const point_2d &pt, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, double x, double y, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, int cell, const matrix_2d &translation, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, int cell, const point_2d &pt, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, int cell, double x, double y, const rectangle &rect);
bool bitmap_triangle_collision(bitmap bmp, const point_2d &pt, const triangle &tri);
bool bitmap_triangle_collision(bitmap bmp, double x, double y, const triangle &tri);
bool bitmap_triangle_collision(bitmap bmp, int cell, const matrix_2d &translation, const triangle &tri);
bool bitmap_triangle_collision(bitmap bmp, int cell, const point_2d &pt, const triangle &tri);
bool bitmap_triangle_collision(bitmap bmp, int cell, double x, double y, const triangle &tri);
vector_2d calculate_collision_direction(const quad &collider, const quad &collidee);
vector_2d calculate_collision_direction(const circle &collider, const circle &collidee);
vector_2d calculate_collision_direction(const circle &collider, const quad &collidee);
vector_2d calculate_collision_direction(const circle &collider, const rectangle &collidee);
vector_2d calculate_collision_direction(const circle &collider, const sprite collidee);
vector_2d calculate_collision_direction(const circle &collider, const triangle &collidee);
vector_2d calculate_collision_direction(const quad &collider, const circle &collidee);
vector_2d calculate_collision_direction(const quad &collider, const rectangle &collidee);
vector_2d calculate_collision_direction(const quad &collider, const sprite collidee);
vector_2d calculate_collision_direction(const quad &collider, const triangle &collidee);
vector_2d calculate_collision_direction(const rectangle &collider, const circle &collidee);
vector_2d calculate_collision_direction(const rectangle &collider, const quad &collidee);
vector_2d calculate_collision_direction(const rectangle &collider, const rectangle &collidee);
vector_2d calculate_collision_direction(const rectangle &collider, const sprite collidee);
vector_2d calculate_collision_direction(const rectangle &collider, const triangle &collidee);
vector_2d calculate_collision_direction(const sprite collider, const circle &collidee);
vector_2d calculate_collision_direction(const sprite collider, const quad &collidee);
vector_2d calculate_collision_direction(const sprite collider, const rectangle &collidee);
vector_2d calculate_collision_direction(const sprite collider, const sprite collidee);
vector_2d calculate_collision_direction(const sprite collider, const triangle &collidee);
vector_2d calculate_collision_direction(const triangle &collider, const circle &collidee);
vector_2d calculate_collision_direction(const triangle &collider, const quad &collidee);
vector_2d calculate_collision_direction(const triangle &collider, const rectangle &collidee);
vector_2d calculate_collision_direction(const triangle &collider, const sprite collidee);
vector_2d calculate_collision_direction(const triangle &collider, const triangle &collidee);
bool resolve_collision(quad &collider, const quad &collidee, const vector_2d &direction);
bool resolve_collision(circle &collider, const circle &collidee, const vector_2d &direction);
bool resolve_collision(circle &collider, const quad &collidee, const vector_2d &direction);
bool resolve_collision(circle &collider, const rectangle &collidee, const vector_2d &direction);
bool resolve_collision(circle &collider, const sprite collidee, const vector_2d &direction);
bool resolve_collision(circle &collider, const triangle &collidee, const vector_2d &direction);
bool resolve_collision(quad &collider, const circle &collidee, const vector_2d &direction);
bool resolve_collision(quad &collider, const rectangle &collidee, const vector_2d &direction);
bool resolve_collision(quad &collider, const sprite collidee, const vector_2d &direction);
bool resolve_collision(quad &collider, const triangle &collidee, const vector_2d &direction);
bool resolve_collision(rectangle &collider, const circle &collidee, const vector_2d &direction);
bool resolve_collision(rectangle &collider, const quad &collidee, const vector_2d &direction);
bool resolve_collision(rectangle &collider, const rectangle &collidee, const vector_2d &direction);
bool resolve_collision(rectangle &collider, const sprite collidee, const vector_2d &direction);
bool resolve_collision(rectangle &collider, const triangle &collidee, const vector_2d &direction);
bool resolve_collision(sprite collider, const circle &collidee, const vector_2d &direction);
bool resolve_collision(sprite collider, const quad &collidee, const vector_2d &direction);
bool resolve_collision(sprite collider, const rectangle &collidee, const vector_2d &direction);
bool resolve_collision(sprite collider, const sprite collidee, const vector_2d &direction);
bool resolve_collision(sprite collider, const triangle &collidee, const vector_2d &direction);
bool resolve_collision(triangle &collider, const circle &collidee, const vector_2d &direction);
bool resolve_collision(triangle &collider, const quad &collidee, const vector_2d &direction);
bool resolve_collision(triangle &collider, const rectangle &collidee, const vector_2d &direction);
bool resolve_collision(triangle &collider, const sprite collidee, const vector_2d &direction);
bool resolve_collision(triangle &collider, const triangle &collidee, const vector_2d &direction);
bool sprite_bitmap_collision(sprite s, bitmap bmp, double x, double y);
bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, const point_2d &pt);
bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, double x, double y);
bool sprite_circle_collision(sprite s, const circle &c);
bool sprite_collision(sprite s1, sprite s2);
bool sprite_point_collision(sprite s, const point_2d &pt);
bool sprite_quad_collision(sprite s, const quad &q);
bool sprite_ray_collision(sprite s, const point_2d &origin, const vector_2d &heading);
bool sprite_rectangle_collision(sprite s, const rectangle &rect);
bool sprite_triangle_collision(sprite s, const triangle &t);

#endif /* __collisions_h */
