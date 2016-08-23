//
//  quad_geometry.hpp
//  splashkit
//
//  Created by Andrew Cain on 23/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef quad_geometry_h
#define quad_geometry_h

#include "types.h"

/**
 *Returns a quad for the passed in x & y points.
 */
quad quad_from(float x_top_left, float y_top_left, float x_top_right, float y_top_right, float x_bottom_left, float y_bottom_left, float x_bottom_right, float y_bottom_right );


/**
 * Returns a quad from x-y of given recatangle
 */
quad quad_from(const rectangle &rect);


#endif /* quad_geometry_h */
