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

float line_length_squared(const line &l);

#endif /* line_geometry_hpp */
