//
//  geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef geometry_hpp
#define geometry_hpp

#include "types.h"
#include "window_manager.h"


rectangle rectangle_from(float x, float y, float width, float height);

vector_2d vector_to(float x, float y);

point_2d point_at(float x, float y);

circle circle_at(const point_2d &pt, float radius);

circle circle_at(float x, float y, float radius);

triangle triangle_from(float x1, float y1, float x2, float y2, float x3, float y3);

triangle triangle_from(point_2d p1, point_2d p2, point_2d p3);

quad quad_from(point_2d p1, point_2d p2, point_2d p3, point_2d p4);

point_2d random_screen_point();

point_2d random_window_point(window wind);

#endif /* geometry_hpp */
