//
// SplashKit Generated Camera C++ Code
// DO NOT MODIFY
//

#ifndef __camera_h
#define __camera_h

#include "window_manager.h"
#include "types.h"
#include "sprites.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

point_2d camera_position();
double camera_x();
double camera_y();
void center_camera_on(sprite s, const vector_2d &offset);
void center_camera_on(sprite s, double offset_x, double offset_y);
void move_camera_by(const vector_2d &offset);
void move_camera_by(double dx, double dy);
void move_camera_to(const point_2d &pt);
void move_camera_to(double x, double y);
bool point_in_window(window wind, const point_2d &pt);
bool point_on_screen(const point_2d &pt);
bool rect_in_window(window wind, const rectangle &rect);
bool rect_on_screen(const rectangle &rect);
point_2d screen_center();
rectangle screen_rectangle();
void set_camera_position(point_2d pos);
void set_camera_x(double x);
void set_camera_y(double y);
point_2d to_screen(const point_2d &pt);
rectangle to_screen(const rectangle &rect);
double to_screen_x(double world_x);
double to_screen_y(double world_y);
point_2d to_world(const point_2d &pt);
double to_world_x(double screen_x);
double to_world_y(double screen_y);
vector_2d vector_world_to_screen();
rectangle window_area(window wind);

#endif /* __camera_h */
