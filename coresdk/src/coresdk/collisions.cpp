//
//  collisions.cpp
//  splashkit
//
//  Created by Andrew Cain on 25/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "collisions.h"
#include "physics.h"
#include "sprites.h"
#include "utility_functions.h"

#include <cmath>
#include <functional>

#include "graphics.h"
#include "utils.h"

// Step over pixels in the two areas based on the supplied matrix
//
// See http://www.austincc.edu/cchrist1/GAME1343/TransformedCollision/TransformedCollision.htm
bool _step_through_pixels (
    float w1, float h1,
    const matrix_2d &matrix1,
    float w2, float h2,
    const matrix_2d &matrix2,
    function<bool(int, int, int, int)> end_fn )
{
    bool a_is_1;
    float h_a, w_a;
    float h_b, w_b;
    matrix_2d transform_a_to_b;
    
    if ( w1 * h1 <= w2 * h2 ) // use bitmap 1 as the one to scan
    {
        a_is_1 = true;
        h_a = h1;
        w_a = w1;

        h_b = h2;
        w_b = w2;

        // Calculate a matrix which transforms from 1's local space into
        // world space and then into 2's local space
        transform_a_to_b = matrix_multiply(matrix1, matrix_inverse(matrix2));
    }
    else // use bitmap 2
    {
        a_is_1 = false;
        h_a = h2;
        w_a = w2;

        h_b = h1;
        w_b = w1;

        // Calculate a matrix which transforms from 1's local space into
        // world space and then into 2's local space
        transform_a_to_b = matrix_multiply(matrix2, matrix_inverse(matrix1));
    }

    vector_2d step_x, step_y, y_pos_in_b, pos_in_b;
    
    // Calculate the top left corner of A in B's local space
    // This variable will be reused to keep track of the start of each row
    y_pos_in_b = matrix_multiply(transform_a_to_b, vector_to(0,0));
    
	// draw_rectangle(COLOR_BLUE, y_pos_in_b.x + 300, y_pos_in_b.y + 300, w1, h1);

    // When a point moves in A's local space, it moves in B's local space with a
    // fixed direction and distance proportional to the movement in A.
    // This algorithm steps through A one pixel at a time along A's X and Y axes
    // Calculate the analogous steps in B:
    step_x = vector_subtract(matrix_multiply(transform_a_to_b, vector_to(1, 0)), y_pos_in_b);
    step_y = vector_subtract(matrix_multiply(transform_a_to_b, vector_to(0, -1)), y_pos_in_b); // y inverted for drawing

    int x_b, y_b;
    
    // have to check all pixels of one bitmap
    // For each row of pixels in A (the smaller)
    for (int y_a = 0; y_a < h_a; y_a++)
    {
        pos_in_b = y_pos_in_b;

        // For each pixel in this row
        for (int x_a = 0; x_a < w_a; x_a++)
        {
            // Calculate this pixel's location in B
            // positionInB = transform_a_to_b * vector_to(xA, yA);

            // Round to the nearest pixel
            x_b = round(pos_in_b.x);
            y_b = round(pos_in_b.y);

            fill_circle(COLOR_MAGENTA, x_b + 300, y_b + 300, 2);
            refresh_screen();
            // delay(10);

            // If the pixel lies within the bounds of B
            if  ( (0 <= x_b) and (x_b < w_b) and (0 <= y_b) and (y_b < h_b) )
            {
                if ( ( a_is_1 and end_fn(x_a, y_a, x_b, y_b) )
                    or ( (not a_is_1) and end_fn(x_b, y_b, x_a, y_a)) )
                {
                    return true;
                }
            }
            
            // Move to the next pixel in the row
            pos_in_b = vector_add(pos_in_b, step_x);
        }

        // Move to the next row
        y_pos_in_b = vector_add(y_pos_in_b, step_y);
    }

    // No intersection found
    return false;
}

bool _collision_within_bitmap_images_with_translation(bitmap bmp1, int c1, const matrix_2d& matrix1, bitmap bmp2, int c2, const matrix_2d& matrix2)
{
	return _step_through_pixels(bitmap_cell_width(bmp1), bitmap_cell_height(bmp1), matrix1,
								bitmap_cell_width(bmp2), bitmap_cell_height(bmp2), matrix2,
								[&] (int ax, int ay, int bx, int by)
								{
									return pixel_drawn_at_point(bmp1, c1, ax, ay) and pixel_drawn_at_point(bmp2, c2, bx, by);
								});
}

bool bitmap_point_collision(bitmap bmp, int cell, const matrix_2d& translation, const point_2d& pt )
{
    if (INVALID_PTR(bmp, BITMAP_PTR))
    {
        return false;
    }
    
    return _step_through_pixels(1, 1, translation_matrix(pt.x, pt.y), bmp->cell_w, bmp->cell_h, translation, [&] (int ax, int ay, int bx, int by)
    {
        return pixel_drawn_at_point(bmp, cell, bx, by);
    });
}

bool bitmap_point_collision(bitmap bmp, const matrix_2d& translation, const point_2d& pt)
{
    return bitmap_point_collision(bmp, 0, translation, pt);
}

bool bitmap_rect_collision(bitmap bmp, int cell, const matrix_2d& translation, const rectangle& rect)
{
	if (INVALID_PTR(bmp, BITMAP_PTR))
	{
		return false;
	}

	return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&] (int ax, int ay, int bx, int by)
								{
									return pixel_drawn_at_point(bmp, cell, bx, by);
								});
}

bool bitmap_rect_collision(bitmap bmp, int cell, const point_2d& pt, const rectangle& rect)
{
	return bitmap_rect_collision(bmp, cell, translation_matrix(pt), rect);
}

bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, float x, float y)
{
	if (!rectangles_intersect(sprite_collision_rectangle(s), bitmap_cell_rectangle(bmp, point_at(x, y))))
	{
		return false;
	}

	if (sprite_collision_kind(s) == AABB_COLLISIONS)
	{
		return bitmap_rect_collision(bmp, cell, point_at(x, y), sprite_collision_rectangle(s));
	}

	return _collision_within_bitmap_images_with_translation(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s),
															bmp, cell, translation_matrix(x, y));
}

bool sprite_bitmap_collision(sprite s, bitmap bmp, float x, float y)
{
	return sprite_bitmap_collision(s, bmp, 0, x, y);
}

bool sprite_rect_collision(sprite s, const rectangle& rect)
{
	// TODO: Implement

	return false;
}
