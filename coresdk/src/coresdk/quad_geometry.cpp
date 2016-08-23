//
//  quad_geometry.cpp
//  splashkit
//
//  Created by Andrew Cain on 23/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "quad_geometry.h"
#include "types.h"
#include "rectangle_geometry.h"


 
quad quad_from(float x_top_left,float y_top_left,float x_top_right,float y_top_right, float x_bottom_left,float y_bottom_left,float x_bottom_right,float y_bottom_right)
{
    quad result;
    result.points[0].x = x_top_left;
    result.points[0].y = y_top_left;
    result.points[1].x = x_top_right;
    result.points[1].y = y_top_right;
    result.points[2].x = x_bottom_left;
    result.points[2].y = y_bottom_left;
    result.points[3].x = x_bottom_right;
    result.points[3].y = y_bottom_right;
    return result;
}



quad quad_from(const rectangle &rect)
{
    quad result;
    result = quad_from(
                       rectangle_left(rect), rectangle_top(rect),
                       rectangle_right(rect), rectangle_top(rect),
                       rectangle_left(rect), rectangle_bottom(rect),
                       rectangle_right(rect), rectangle_bottom(rect) );
    return result;
}


