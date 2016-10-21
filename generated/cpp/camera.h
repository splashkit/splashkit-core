/*
 * SplashKit Camera
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __camera_h
#define __camera_h

#include "sprites.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

point_2d camera_position();
float camera_x();
float camera_y();
void center_camera_on(sprite s, const vector_2d &offset);
void center_camera_on(sprite s, float offset_x, float offset_y);
void move_camera_by(const vector_2d &offset);
void move_camera_by(float dx, float dy);
void move_camera_to(const point_2d &pt);
void move_camera_to(float x, float y);
bool point_on_screen(const point_2d &pt);
bool rect_on_screen(const rectangle &rect);
point_2d screen_center();
rectangle screen_rectangle();
void set_camera_position(point_2d pos);
void set_camera_y(float y);
point_2d to_screen(const point_2d &pt);
rectangle to_screen(const rectangle &rect);
float to_screen_x(float world_x);
float to_screen_y(float world_y);
point_2d to_world(const point_2d &pt);
float to_world_x(float screen_x);
float to_world_y(float screen_y);
vector_2d vector_world_to_screen();

#endif /* __camera_h */
