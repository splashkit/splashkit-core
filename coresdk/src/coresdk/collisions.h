//
//  collisions.hpp
//  splashkit
//
//  Created by Andrew Cain on 25/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef collisions_h
#define collisions_h

#include "images.h"
#include "matrix_2d.h"
#include "sprites.h"
#include "types.h"

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
bool bitmap_point_collision(bitmap bmp, const matrix_2d& translation, const point_2d& pt);

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
bool bitmap_point_collision(bitmap bmp, int cell, const matrix_2d& translation, const point_2d& pt);

bool bitmap_rect_collision(bitmap bmp, int cell, const matrix_2d& translation, const rectangle& rect);

bool bitmap_rect_collision(bitmap bmp, int cell, const point_2d& pt, const rectangle& rect);

bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, float x, float y);

bool sprite_bitmap_collision(sprite s, bitmap bmp, float x, float y);

bool sprite_point_collision(sprite s, const point_2d& pt);

bool sprite_rect_collision(sprite s, const rectangle& rect);

bool sprite_collision(sprite s1, sprite s2);

#endif /* collisions_h */
