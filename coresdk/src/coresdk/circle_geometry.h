//
//  circle_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 22/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef circle_geometry_hpp
#define circle_geometry_hpp

#include "types.h"

circle circle_at(const point_2d &pt, float radius);

circle circle_at(float x, float y, float radius);


/**
 *  Returns the center point of the circle.
 */
point_2d center_point(const circle &c);

#endif /* circle_geometry_hpp */
