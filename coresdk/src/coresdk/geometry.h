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


rectangle rectangle_from(float x, float y, float width, float height);

vector_2d vector_to(float x, float y);

point_2d point_at(float x, float y);

circle circle_at(const point_2d &pt, float radius);

circle circle_at(float x, float y, float radius);


#endif /* geometry_hpp */
