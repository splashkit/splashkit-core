//
//  line_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 20/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef line_geometry_hpp
#define line_geometry_hpp

#include "types.h"

line line_from(const point_2d &start, const point_2d &end);
line line_from(float x1, float y1, float x2, float y2);
line line_from_vector(const point_2d &start, const vector_2d &offset);

float line_length_squared(const line &l);

line line_from(const vector_2d &v);
line line_from(const point_2d pt, const vector_2d &v);

bool line_intersection_point(const line &line1, const line &line2, point_2d &pt);

point_2d closest_point_on_line(const point_2d from_pt, const line &l);

#endif /* line_geometry_hpp */
