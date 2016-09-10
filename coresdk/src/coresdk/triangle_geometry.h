//
//  triangle_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 23/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef triangle_geometry_h
#define triangle_geometry_h

#include "types.h"

namespace splashkit_lib
{
    triangle triangle_from(float x1, float y1, float x2, float y2, float x3, float y3);

    triangle triangle_from(point_2d p1, point_2d p2, point_2d p3);
}

#endif /* triangle_geometry_h */
