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
#include "point_geometry.h"

rectangle rectangle_from(float x, float y, float width, float height);

vector_2d vector_to(float x, float y);


circle circle_at(const point_2d &pt, float radius);

circle circle_at(float x, float y, float radius);

triangle triangle_from(float x1, float y1, float x2, float y2, float x3, float y3);

triangle triangle_from(point_2d p1, point_2d p2, point_2d p3);

quad quad_from(point_2d p1, point_2d p2, point_2d p3, point_2d p4);


rectangle intersection(const rectangle &rect1, const rectangle &rect2);

float rectangle_top(const rectangle &rect);
float rectangle_bottom(const rectangle &rect);
float rectangle_left(const rectangle &rect);
float rectangle_right(const rectangle &rect);

#endif /* geometry_hpp */
