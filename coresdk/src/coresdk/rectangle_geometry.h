//
//  rectangle_geometry.h
//  splashkit
//
//  Created by Jacob on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef rectangle_geometry_H
#define rectangle_geometry_H

#include "types.h"
#include <string>
using namespace std;

rectangle rectangle_from(float x, float y, float width, float height);

rectangle rectangle_around(const line &l);

rectangle intersection(const rectangle &rect1, const rectangle &rect2);

float rectangle_top(const rectangle &rect);
float rectangle_bottom(const rectangle &rect);
float rectangle_left(const rectangle &rect);
float rectangle_right(const rectangle &rect);

/**
 *  Get a text representation of the passed in rectangle.
 */
string rectangle_to_string(const rectangle &rect);



#endif /* rectangle_geometry_H */
