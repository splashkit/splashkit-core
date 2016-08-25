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
#include "rectangle_geometry.h"
#include "line_geometry.h"
#include "circle_geometry.h"
#include "quad_geometry.h"
/**
 *  Returns the cosine of the supplied angle (in degrees).
 */
float cosine(float degrees);

/**
 *  Returns the sine of the supplied angle (in degrees).
 */
float sine(float degrees);

/**
 *  Returns the tangent of the supplied angle (in degrees).
 */
float tangent(float degrees);



triangle triangle_from(float x1, float y1, float x2, float y2, float x3, float y3);

triangle triangle_from(point_2d p1, point_2d p2, point_2d p3);




#endif /* geometry_hpp */
