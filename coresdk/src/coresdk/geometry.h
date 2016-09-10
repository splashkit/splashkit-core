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
#include "triangle_geometry.h"

namespace splashkit_lib
{
    /**
     *  Returns the cosine of the supplied angle (in degrees).
     *
     * @param  degrees The angle in degrees
     * @return         the cosine of the supplied angle (in degrees).
     */
    float cosine(float degrees);

    /**
     *  Returns the sine of the supplied angle (in degrees).
     *
     * @param  degrees The angle in degrees
     * @return         the sine of the supplied angle (in degrees).
     */
    float sine(float degrees);

    /**
     *  Returns the tangent of the supplied angle (in degrees).
     *
     * @param  degrees The angle in degrees
     * @return         the tangent of the supplied angle (in degrees).
     */
    float tangent(float degrees);

}
#endif /* geometry_hpp */
