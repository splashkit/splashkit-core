//
// SplashKit Generated Collisions C++ Code
// DO NOT MODIFY
//

#ifndef __collisions_h
#define __collisions_h

#include "types.h"
#include "matrix_2d.h"
#include "sprites.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

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
bool bitmap_rectangle_collision(bitmap bmp, const point_2d &pt, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, double x, double y, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, int cell, const matrix_2d &translation, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, int cell, const point_2d &pt, const rectangle &rect);
bool bitmap_rectangle_collision(bitmap bmp, int cell, double x, double y, const rectangle &rect);
bool sprite_bitmap_collision(sprite s, bitmap bmp, double x, double y);
bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, const point_2d &pt);
bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, double x, double y);
bool sprite_collision(sprite s1, sprite s2);
bool sprite_point_collision(sprite s, const point_2d &pt);
bool sprite_rectangle_collision(sprite s, const rectangle &rect);

#endif /* __collisions_h */
