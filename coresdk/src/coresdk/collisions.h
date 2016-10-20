/**
 * @header  collisions
 * @author  Andrew Cain
 * @brief   SplashKit Collisions library allow you to perform tests between
 *          bitmaps, sprites and shapes to determin if a collision has occured.
 *
 * @attribute group  physics
 * @attribute static collisions
 */

#ifndef collisions_h
#define collisions_h

#include "images.h"
#include "matrix_2d.h"
#include "sprites.h"
#include "types.h"
namespace splashkit_lib
{
    /**
     * Tests if a bitmap drawn using the passed in translation matrix would draw a pixel
     * at the passed in point. Use to check collisions between a point and a bitmap.
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
     * Tests if a bitmap drawn at the `bmp_pt` point would draw a pixel
     * at the passed in point. Use to check collisions between a point and a bitmap.
     *
     * @param bmp           The bitmap to test.
     * @param pt            The point in the resulting drawing that is being tested.
     * @param bmp_pt        The point where the bitmap is drawn.
     * @returns             True if drawing the bitmap, at `bmp_pt`,
     *                      will draw a pixel at the indicated point (`pt`).
     */
    bool bitmap_point_collision(bitmap bmp, const point_2d &bmp_pt, const point_2d& pt);

    /**
     * Tests if a bitmap drawn at x,y would draw a pixel at the passed in point. Use 
     * to check collisions between a point and a bitmap.
     *
     * @param bmp   The bitmap to test.
     * @param bmp_x The x location where the bitmap is drawn
     * @param bmp_y The y location where the bitmap is drawn
     * @param  x    The x location of the point to test
     * @param  y    The y location of the point to test
     * @returns     True if drawing the bitmap, at `bmp_pt`,
     *              will draw a pixel at the indicated point (`pt`).
     */
    bool bitmap_point_collision(bitmap bmp, float bmp_x, float bmp_y, float x, float y);

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

    /**
     * Tests if a bitmap cell drawn using a passed in translation, will
     * intersect with a rectangle. You can use this to detect collisions between
     * bitmaps and rectangles.
     *
     * @param  bmp         The bitmap to test
     * @param  cell        The cell of the bitmap to check
     * @param  translation The matrix used to transfrom the bitmap when drawing
     * @param  rect        The rectangle to test
     * @return             True if a drawn pixel in the cell of the bitmap will
     *                     intersect with `rect` when drawn.
     */
    bool bitmap_rectangle_collision(bitmap bmp, int cell, const matrix_2d& translation, const rectangle& rect);

    /**
     * Tests if a bitmap cell drawn at `pt` would intersect with a rectangle.
     *
     * @param  bmp  The bitmap to test
     * @param  cell The cell of the bitmap to check
     * @param  pt   The location where the bitmap is drawn
     * @param  rect The rectangle to test
     * @return      True if a drawn pixel in the cell of the bitmap will
     *              intersect with `rect` when drawn.
     */
    bool bitmap_rectangle_collision(bitmap bmp, int cell, const point_2d& pt, const rectangle& rect);

    /**
     * Tests if a sprite will collide with a bitmap drawn at the indicated
     * location.
     *
     * @param  s    The sprite to test
     * @param  bmp  The bitmap to test
     * @param  cell The cell of the bitmap to check
     * @param  x    The x location where the bitmap is drawn
     * @param  y    The y location where the bitmap is drawn
     * @return      True if the sprite collides with the bitmap cell when drawn
     *              at the indicated location.
     */
    bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, float x, float y);

    /**
     * Tests if a sprite will collide with a bitmap drawn at the indicated
     * location.
     *
     * @param  s    The sprite to test
     * @param  bmp  The bitmap to test
     * @param  cell The cell of the bitmap to check
     * @param  pt   The point where the bitmap is drawn
     * @return      True if the sprite collides with the bitmap cell when drawn
     *              at the indicated location.
     */
    bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, const point_2d &pt);

    /**
     * Tests if a sprite will collide with a bitmap drawn at the indicated
     * location.
     *
     * @param  s    The sprite to test
     * @param  bmp  The bitmap to test
     * @param  x    The x location where the bitmap is drawn
     * @param  y    The y location where the bitmap is drawn
     * @return      True if the sprite collides with the bitmap when drawn
     *              at the indicated location.
     */
    bool sprite_bitmap_collision(sprite s, bitmap bmp, float x, float y);

    /**
     * Tests if a sprite is drawn at a given point.
     *
     * @param  s  The sprite to test
     * @param  pt The point to check
     * @return    True if the sprite it drawn at the indicated point
     */
    bool sprite_point_collision(sprite s, const point_2d& pt);

    /**
     * Tests if a sprite is drawn within an given area (rectangle).
     *
     * @param  s    The sprite to test
     * @param  rect The rectangle to check
     * @return      True if the sprite it drawn in the rectangle area
     */
    bool sprite_rectangle_collision(sprite s, const rectangle& rect);

    /**
     * Tests if two given sprites `s1` and `s2` are collided
     * @param  s1 the first `sprite` to test
     * @param  s2 the second `sprite` to test
     *
     * @returns return `true` if both `s1` and `s2` are colliding, false otherwise.
     *
     * @attribute class   sprite
     * @attribute method  collide_with_sprite
     * @attribute self    s1
     */
    bool sprite_collision(sprite s1, sprite s2);

    /**
     * Check if two bitmaps collide, based on their cell and transform
     * matricies.
     *
     * @param  bmp1    The first bitmap
     * @param  cell1   The cell of the first bitmap.
     * @param  matrix1 The transformation for the first matrix
     * @param  bmp2    The second bitmap
     * @param  cell2   The cell of the second bitmap.
     * @param  matrix2 The transformation for the second matrix
     * @return         True if pixels in the two bitmaps would collide/overlap
     */
    bool bitmap_collision(bitmap bmp1, int cell1, const matrix_2d &matrix1, bitmap bmp2, int cell2, const matrix_2d &matrix2);

    /**
     * Check if two bitmaps collide.
     *
     * @param  bmp1   The first bitmap
     * @param  cell1  The cell of the first bitmap.
     * @param  pt1    The point where bitmap 1 is drawn
     * @param  bmp2   The second bitmap
     * @param  cell2  The cell of the second bitmap.
     * @param  pt2    The point where bitmap 2 is drawn
     * @return        True if pixels in the two bitmaps would collide/overlap
     */
    bool bitmap_collision(bitmap bmp1, int cell1, const point_2d &pt1, bitmap bmp2, int cell2, const point_2d &pt2);

    /**
     * Check if two bitmaps collide.
     *
     * @param  bmp1   The first bitmap
     * @param  cell1  The cell of the first bitmap.
     * @param  x1     The x location where the first bitmap is drawn
     * @param  y1     The y location where the first bitmap is drawn
     * @param  bmp2   The second bitmap
     * @param  cell2  The cell of the second bitmap.
     * @param  x2     The x location where the second bitmap is drawn
     * @param  y2     The y location where the second bitmap is drawn
     * @return        True if pixels in the two bitmaps would collide/overlap
     */
    bool bitmap_collision(bitmap bmp1, int cell1, float x1, float y1, bitmap bmp2, int cell2, float x2, float y2);

    /**
     * Check if two bitmaps collide.
     *
     * @param  bmp1   The first bitmap
     * @param  pt1    The point where bitmap 1 is drawn
     * @param  bmp2   The second bitmap
     * @param  pt2    The point where bitmap 2 is drawn
     * @return        True if pixels in the two bitmaps would collide/overlap
     */
    bool bitmap_collision(bitmap bmp1, const point_2d &pt1, bitmap bmp2, const point_2d &pt2);

    /**
     * Check if two bitmaps collide.
     *
     * @param  bmp1   The first bitmap
     * @param  x1     The x location where the first bitmap is drawn
     * @param  y1     The y location where the first bitmap is drawn
     * @param  bmp2   The second bitmap
     * @param  x2     The x location where the second bitmap is drawn
     * @param  y2     The y location where the second bitmap is drawn
     * @return        True if pixels in the two bitmaps would collide/overlap
     */
    bool bitmap_collision(bitmap bmp1, float x1, float y1, bitmap bmp2, float x2, float y2);

}
#endif /* collisions_h */
