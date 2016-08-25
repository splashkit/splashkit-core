//
//  collisions.hpp
//  splashkit
//
//  Created by Andrew Cain on 25/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef collisions_h
#define collisions_h

#include "types.h"
#include "images.h"
#include "matrix_2d.h"

/**
 * Tests if a bitmap drawn using the passed in translation matrix would draw a pixel
 * at the passed in point.
 *
 * @param bmp           The bitmap to test.
 * @param translation   The translation matrix that represents the position, scale,
 *                      and rotation of the bitmap when it is drawn.
 * @param pt            The point in the resulting drawing that is being tested.
 * @returns             True if drawing the bitmap, using the passed in translation, 
 *                      will draw a pixel at the indicated point.
 */
bool bitmap_point_collision( bitmap bmp, const matrix_2d &translation, const point_2d &pt );

/**
 * Tests if a bitmap cell drawn using the passed in translation matrix would draw a pixel
 * at the passed in point.
 *
 * @param bmp           The bitmap to test.
 * @param cell          The cell of the bitmap to check.
 * @param translation   The translation matrix that represents the position, scale,
 *                      and rotation of the bitmap when it is drawn.
 * @param pt            The point in the resulting drawing that is being tested.
 * @returns             True if drawing the bitmap, using the passed in translation,
 *                      will draw a pixel at the indicated point.
 */
bool bitmap_point_collision( bitmap bmp, int cell, const matrix_2d &translation, const point_2d &pt );


#endif /* collisions_h */
