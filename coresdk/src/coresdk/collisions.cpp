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

constexpr int DEFAULT_BRACKET_ITERATIONS = 50;
constexpr double ITERATION_POWER = 1.5;

using std::function;

namespace splashkit_lib
{
    enum class _sprite_movement_direction
    {
        UP,
        DOWN,
        LEFT,
        RIGHT,
        UP_LEFT,
        UP_RIGHT,
        DOWN_LEFT,
        DOWN_RIGHT,
        NONE,
    };
    
    //#define DEBUG_STEP

    // Step over pixels in the two areas based on the supplied matrix
    //
    // See http://www.austincc.edu/cchrist1/GAME1343/TransformedCollision/TransformedCollision.htm
    bool _step_through_pixels (
                               double w1, double h1,
                               const matrix_2d &matrix1,
                               double w2, double h2,
                               const matrix_2d &matrix2,
                               function<bool(int, int, int, int)> end_fn )
    {
        bool a_is_1;
        double h_a, w_a;
        double h_b, w_b;
        matrix_2d transform_a_to_b;

        // Determine the smaller area to step through.
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

        // When a point moves in A's local space, it moves in B's local space with a
        // fixed direction and distance proportional to the movement in A.
        // This algorithm steps through A one pixel at a time along A's X and Y axes
        // Calculate the analogous steps in B:
        step_x = vector_subtract(matrix_multiply(transform_a_to_b, vector_to(1, 0)), y_pos_in_b);
        step_y = vector_subtract(matrix_multiply(transform_a_to_b, vector_to(0, 1)), y_pos_in_b); // y inverted for drawing

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
                x_b = trunc(pos_in_b.x);
                y_b = trunc(pos_in_b.y);

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
#if DEBUG_STEP
                                        point_2d apt, bpt;
                                        apt = matrix_multiply(matrix1, point_at(ax,ay));
                                        if ( pixel_drawn_at_point(bmp1, c1, ax, ay) )
                                            draw_circle(COLOR_RED, apt.x, apt.y, 3);
                                        bpt = matrix_multiply(matrix2, point_at(bx,by));
                                        if ( pixel_drawn_at_point(bmp2, c2, bx, by) )
                                            draw_circle(COLOR_PINK, bpt.x, bpt.y, 2);

                                        if ( pixel_drawn_at_point(bmp1, c1, ax, ay) and pixel_drawn_at_point(bmp2, c2, bx, by) )
                                        {
                                            fill_circle(COLOR_GREEN, apt.x, apt.y, 1);
                                            fill_circle(COLOR_YELLOW, bpt.x, bpt.y, 3);
                                        }
#endif
                                        return pixel_drawn_at_point(bmp1, c1, ax, ay) and pixel_drawn_at_point(bmp2, c2, bx, by);
                                    });
    }

    bool bitmap_point_collision(bitmap bmp, int cell, const matrix_2d& translation, const point_2d& pt )
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        if ( not point_in_quad(pt, quad_from(bitmap_cell_rectangle(bmp), translation)) )
        {
            return false;
        }

        return _step_through_pixels(1, 1, translation_matrix(pt.x, pt.y), bmp->cell_w, bmp->cell_h, translation, [&] (int ax, int ay, int bx, int by)
                                    {
#if DEBUG_STEP
                                        point_2d bpt;
                                        bpt = matrix_multiply(translation, point_at(bx,by));
                                        if ( pixel_drawn_at_point(bmp, cell, bx, by) )
                                            fill_rectangle(COLOR_PINK, bpt.x, bpt.y, translation.elements[0][0], translation.elements[1][1] );
#endif
                                        return pixel_drawn_at_point(bmp, cell, bx, by);
                                    });
    }

    bool bitmap_point_collision(bitmap bmp, const matrix_2d& translation, const point_2d& pt)
    {
        return bitmap_point_collision(bmp, 0, translation, pt);
    }

    bool bitmap_point_collision(bitmap bmp, const point_2d &bmp_pt, const point_2d& pt)
    {
        return bitmap_point_collision(bmp, translation_matrix(bmp_pt), pt);
    }

    bool bitmap_point_collision(bitmap bmp, double bmp_x, double bmp_y, double x, double y)
    {
        return bitmap_point_collision(bmp, 0, translation_matrix(bmp_x, bmp_y), point_at(x, y));
    }
    
    bool bitmap_point_collision(bitmap bmp, int cell, const point_2d &bmp_pt, const point_2d& pt)
    {
        return bitmap_point_collision(bmp, cell, translation_matrix(bmp_pt), pt);
    }
    
    bool bitmap_point_collision(bitmap bmp, int cell, double bmp_x, double bmp_y, double x, double y)
    {
        return bitmap_point_collision(bmp, cell, translation_matrix(bmp_x, bmp_y), point_at(x, y));
    }

    bool bitmap_rectangle_collision(bitmap bmp, int cell, const matrix_2d& translation, const rectangle& rect)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        quad q1, q2;

        q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        q2 = quad_from(rect);

        if ( not quads_intersect(q1, q2) ) return false;

        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&] (int ax, int ay, int bx, int by)
                                    {
                                        return pixel_drawn_at_point(bmp, cell, bx, by);
                                    });
    }

    bool bitmap_rectangle_collision(bitmap bmp, int cell, const point_2d& pt, const rectangle& rect)
    {
        return bitmap_rectangle_collision(bmp, cell, translation_matrix(pt), rect);
    }
    
    bool bitmap_rectangle_collision(bitmap bmp, const point_2d& pt, const rectangle& rect)
    {
        return bitmap_rectangle_collision(bmp, 0, translation_matrix(pt), rect);
    }
    
    bool bitmap_rectangle_collision(bitmap bmp, double x, double y, const rectangle& rect)
    {
        return bitmap_rectangle_collision(bmp, 0, translation_matrix(x, y), rect);
    }
    
    bool bitmap_rectangle_collision(bitmap bmp, int cell, double x, double y, const rectangle& rect)
    {
        return bitmap_rectangle_collision(bmp, cell, translation_matrix(x, y), rect);
    }
    
    bool bitmap_circle_collision(bitmap bmp, int cell, const matrix_2d& translation, const circle& circ)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }
        
        quad q1, q2;
        
        q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        rectangle rect = rectangle_around(circ);
        q2 = quad_from(rect);
        
        if ( not quads_intersect(q1, q2) ) return false;
        
        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&] (int ax, int ay, int bx, int by)
                                    {
                                        return pixel_drawn_at_point(bmp, cell, bx, by) && point_in_circle(point_at(rect.x + ax, rect.y + ay), circ);
                                    });
    }
    
    bool bitmap_circle_collision(bitmap bmp, int cell, const point_2d& pt, const circle& circ)
    {
        return bitmap_circle_collision(bmp, cell, translation_matrix(pt), circ);
    }

    bool bitmap_circle_collision(bitmap bmp, const point_2d& pt, const circle& circ)
    {
        return bitmap_circle_collision(bmp, 0, translation_matrix(pt), circ);
    }
    
    bool bitmap_circle_collision(bitmap bmp, double x, double y, const circle& circ)
    {
        return bitmap_circle_collision(bmp, 0, translation_matrix(x, y), circ);
    }
    
    bool bitmap_circle_collision(bitmap bmp, int cell, double x, double y, const circle& circ)
    {
        return bitmap_circle_collision(bmp, cell, translation_matrix(x, y), circ);
    }

    bool bitmap_triangle_collision(bitmap bmp, int cell, const matrix_2d &translation, const triangle &tri)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }
        
        quad q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        rectangle rect = rectangle_around(tri);

        if (! triangle_quad_intersect(tri, q1))
        {
            return false;
        }
        
        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&] (int ax, int ay, int bx, int by)
                                    {
                                        return pixel_drawn_at_point(bmp, cell, bx, by) && point_in_triangle(point_at(rect.x + ax, rect.y + ay), tri);
                                    }); 
    }

    bool bitmap_triangle_collision(bitmap bmp, int cell, const point_2d& pt, const triangle &tri)
    {
        return bitmap_triangle_collision(bmp, cell, translation_matrix(pt), tri);
    }

    bool bitmap_triangle_collision(bitmap bmp, int cell, double x, double y, const triangle &tri)
    {
        return bitmap_triangle_collision(bmp, cell, translation_matrix(x, y), tri);
    }

    bool bitmap_triangle_collision(bitmap bmp, double x, double y, const triangle &tri)
    {
        return bitmap_triangle_collision(bmp, 0, translation_matrix(x, y), tri);
    }

    bool bitmap_triangle_collision(bitmap bmp, const point_2d& pt, const triangle &tri)
    {
        return bitmap_triangle_collision(bmp, 0, translation_matrix(pt), tri);
    }

    bool bitmap_quad_collision(bitmap bmp, int cell, const matrix_2d &translation, const quad &q)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }
        
        quad q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        rectangle rect = rectangle_around(q);
        
        if ( not quads_intersect(q1, q) ) return false;
        
        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&] (int ax, int ay, int bx, int by)
                                    {
                                        return pixel_drawn_at_point(bmp, cell, bx, by) && point_in_quad(point_at(rect.x + ax, rect.y + ay), q);
                                    });
    }

    bool bitmap_quad_collision(bitmap bmp, int cell, const point_2d& pt, const quad &q)
    {
        return bitmap_quad_collision(bmp, cell, translation_matrix(pt), q);
    }

    bool bitmap_quad_collision(bitmap bmp, int cell, double x, double y, const quad &q)
    {
        return bitmap_quad_collision(bmp, cell, translation_matrix(x, y), q);
    }

    bool bitmap_quad_collision(bitmap bmp, double x, double y, const quad &q)
    {
        return bitmap_quad_collision(bmp, 0, translation_matrix(x, y), q);
    }

    bool bitmap_quad_collision(bitmap bmp, const point_2d& pt, const quad &q)
    {
        return bitmap_quad_collision(bmp, 0, translation_matrix(pt), q);
    }

    bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, double x, double y)
    {
        if (!rectangles_intersect(sprite_collision_rectangle(s), bitmap_cell_rectangle(bmp, point_at(x, y))))
        {
            return false;
        }

        if (sprite_collision_kind(s) == AABB_COLLISIONS)
        {
            return bitmap_rectangle_collision(bmp, cell, point_at(x, y), sprite_collision_rectangle(s));
        }

        return _collision_within_bitmap_images_with_translation(
                    sprite_collision_bitmap(s), sprite_current_cell(s),
                    sprite_location_matrix(s),
                    bmp,
                    cell,
                    translation_matrix(x, y));
    }

    bool sprite_bitmap_collision(sprite s, bitmap bmp, int cell, const point_2d &pt)
    {
        return sprite_bitmap_collision(s, bmp, cell, pt.x, pt.y);
    }

    bool sprite_bitmap_collision(sprite s, bitmap bmp, double x, double y)
    {
        return sprite_bitmap_collision(s, bmp, 0, x, y);
    }
    
    bool sprite_point_collision(sprite s, const point_2d &pt)
    {
        if (!point_in_circle(pt, sprite_collision_circle(s)))
        {
            return false;
        }
        else if (bitmap_cell_count(sprite_collision_bitmap(s)) > 1)
        {
            return bitmap_point_collision(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s), pt);
        }
        else
        {
            return bitmap_point_collision(sprite_collision_bitmap(s), sprite_location_matrix(s), pt);
        }
    }
    
    bool sprite_rectangle_collision(sprite s, const rectangle& rect)
    {
        if (!rectangles_intersect(sprite_collision_rectangle(s), rect))
        {
            return false;
        }
        
        return bitmap_rectangle_collision(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s), rect);
    }

    bool sprite_circle_collision(sprite s, const circle &c)
    {
        if (!circles_intersect(sprite_collision_circle(s), c))
        {
            return false;
        }
        
        return bitmap_circle_collision(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s), c);
    }

    bool sprite_triangle_collision(sprite s, const triangle &t)
    {
        if (!triangle_rectangle_intersect(t, sprite_collision_rectangle(s)))
        {
            return false;
        }
        
        return bitmap_triangle_collision(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s), t);
    }

    bool sprite_quad_collision(sprite s, const quad &q)
    {
        if (!rectangles_intersect(sprite_collision_rectangle(s), rectangle_around(q)))
        {
            return false;
        }
        
        return bitmap_quad_collision(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s), q);
    }
    
    bool sprite_collision(sprite s1, sprite s2)
    {
        if (!rectangles_intersect(sprite_collision_rectangle(s1), sprite_collision_rectangle(s2)))
        {
            return false;
        }
        
        if (sprite_collision_kind(s1) == AABB_COLLISIONS)
        {
            return sprite_rectangle_collision(s2, sprite_collision_rectangle(s1));
        }
        
        if (sprite_collision_kind(s2) == AABB_COLLISIONS)
        {
            return sprite_rectangle_collision(s1, sprite_collision_rectangle(s2));
        }
        
        return _collision_within_bitmap_images_with_translation (
                                                                 sprite_collision_bitmap(s1), sprite_current_cell(s1), sprite_location_matrix(s1),
                                                                 sprite_collision_bitmap(s2), sprite_current_cell(s2), sprite_location_matrix(s2) );
    }

    bool bitmap_collision(bitmap bmp1, int cell1, const matrix_2d &matrix1, bitmap bmp2, int cell2, const matrix_2d &matrix2)
    {
        quad q1 = quad_from(bitmap_cell_rectangle(bmp1), matrix1);
        quad q2 = quad_from(bitmap_cell_rectangle(bmp2), matrix2);

        if ( not quads_intersect(q1, q2) )
        {
            return false;
        }

        return _collision_within_bitmap_images_with_translation(bmp1, cell1, matrix1,
                                                                bmp2, cell2, matrix2);
    }

    bool bitmap_collision(bitmap bmp1, int cell1, const point_2d &pt1, bitmap bmp2, int cell2, const point_2d &pt2)
    {
        return bitmap_collision(bmp1, cell1, translation_matrix(pt1), bmp2, cell2, translation_matrix(pt2));
    }

    bool bitmap_collision(bitmap bmp1, int cell1, double x1, double y1, bitmap bmp2, int cell2, double x2, double y2)
    {
        return bitmap_collision(bmp1, cell1, translation_matrix(x1, y1), bmp2, cell2, translation_matrix(x2, y2));
    }

    bool bitmap_collision(bitmap bmp1, const point_2d &pt1, bitmap bmp2, const point_2d &pt2)
    {
        return bitmap_collision(bmp1, 0, pt1.x, pt1.y, bmp2, 0, pt2.x, pt2.y);
    }

    bool bitmap_collision(bitmap bmp1, double x1, double y1, bitmap bmp2, double x2, double y2)
    {
        return bitmap_collision(bmp1, 0, translation_matrix(x1, y1), bmp2, 0, translation_matrix(x2, y2));
    }

    _sprite_movement_direction _opposite_direction(_sprite_movement_direction direction)
    {
        switch (direction)
        {
        case _sprite_movement_direction::UP:
            return _sprite_movement_direction::DOWN;
        case _sprite_movement_direction::DOWN:
            return _sprite_movement_direction::UP;
        case _sprite_movement_direction::LEFT:
            return _sprite_movement_direction::RIGHT;
        case _sprite_movement_direction::RIGHT:
            return _sprite_movement_direction::LEFT;
        case _sprite_movement_direction::UP_LEFT:
            return _sprite_movement_direction::DOWN_RIGHT;
        case _sprite_movement_direction::UP_RIGHT:
            return _sprite_movement_direction::DOWN_LEFT;
        case _sprite_movement_direction::DOWN_LEFT:
            return _sprite_movement_direction::UP_RIGHT;
        case _sprite_movement_direction::DOWN_RIGHT:
            return _sprite_movement_direction::UP_LEFT;
        };
        return _sprite_movement_direction::NONE;
    }

    _sprite_movement_direction _direction_from_collision(collision_direction direction)
    {
        switch (direction)
        {
        case collision_direction::TOP:
            return _sprite_movement_direction::DOWN;
        case collision_direction::BOTTOM:
            return _sprite_movement_direction::UP;
        case collision_direction::LEFT:
            return _sprite_movement_direction::RIGHT;
        case collision_direction::RIGHT:
            return _sprite_movement_direction::LEFT;
        case collision_direction::TOP_LEFT:
            return _sprite_movement_direction::DOWN_RIGHT;
        case collision_direction::TOP_RIGHT:
            return _sprite_movement_direction::DOWN_LEFT;
        case collision_direction::BOTTOM_LEFT:
            return _sprite_movement_direction::UP_RIGHT;
        case collision_direction::BOTTOM_RIGHT:
            return _sprite_movement_direction::UP_LEFT;
        };
        return _sprite_movement_direction::NONE;
    }

    // _sprite_movement_direction _direction_from_velocity(const vector_2d& velocity)
    // {
    //     double angle = vector_angle(velocity);

    //     // split the angle into 8 directions (using atan2 in degrees)
    //     if (angle >= 67.5 && angle < 112.5)
    //     {
    //         return _sprite_movement_direction::UP;
    //     }
    //     else if (angle >= 112.5 && angle < 157.5)
    //     {
    //         return _sprite_movement_direction::UP_LEFT;
    //     }
    //     else if (angle >= 157.5 || angle < -157.5)
    //     {
    //         return _sprite_movement_direction::LEFT;
    //     }
    //     else if (angle >= -157.5 && angle < -112.5)
    //     {
    //         return _sprite_movement_direction::DOWN_LEFT;
    //     }
    //     else if (angle >= -112.5 && angle < -67.5)
    //     {
    //         return _sprite_movement_direction::DOWN;
    //     }
    //     else if (angle >= -67.5 && angle < -22.5)
    //     {
    //         return _sprite_movement_direction::DOWN_RIGHT;
    //     }
    //     else if (angle >= -22.5 && angle < 22.5)
    //     {
    //         return _sprite_movement_direction::RIGHT;
    //     }
    //     else if (angle >= 22.5 && angle < 67.5)
    //     {
    //         return _sprite_movement_direction::UP_RIGHT;
    //     }
    //     return _sprite_movement_direction::NONE;
    // }

    void _move_sprite_by_direction(sprite sprt, _sprite_movement_direction direction, const vector_2d& amount)
    {
        if (amount.x == 0.0 && amount.y == 0.0)
        {
            return;
        }
        
        switch (direction)
        {
        case _sprite_movement_direction::UP:
            sprite_set_y(sprt, sprite_y(sprt) - amount.y);
            break;
        case _sprite_movement_direction::DOWN:
            sprite_set_y(sprt, sprite_y(sprt) + amount.y);
            break;
        case _sprite_movement_direction::LEFT:
            sprite_set_x(sprt, sprite_x(sprt) - amount.x);
            break;
        case _sprite_movement_direction::RIGHT:
            sprite_set_x(sprt, sprite_x(sprt) + amount.x);
            break;
        case _sprite_movement_direction::UP_LEFT:
            sprite_set_x(sprt, sprite_x(sprt) - amount.x);
            sprite_set_y(sprt, sprite_y(sprt) - amount.y);
            break;
        case _sprite_movement_direction::UP_RIGHT:
            sprite_set_x(sprt, sprite_x(sprt) + amount.x);
            sprite_set_y(sprt, sprite_y(sprt) - amount.y);
            break;
        case _sprite_movement_direction::DOWN_LEFT:
            sprite_set_x(sprt, sprite_x(sprt) - amount.x);
            sprite_set_y(sprt, sprite_y(sprt) + amount.y);
            break;
        default: // _sprite_movement_direction::DOWN_RIGHT:
            sprite_set_x(sprt, sprite_x(sprt) + amount.x);
            sprite_set_y(sprt, sprite_y(sprt) + amount.y);
            break;
        };
    }

    void _move_sprite_by_direction_relative_to_size(sprite sprt, _sprite_movement_direction direction, double relative_amount = 1.0)
    {
        rectangle col_rect = sprite_collision_rectangle(sprt);

        double width = col_rect.width;
        double height = col_rect.height;

        double relative_width = width * relative_amount;
        double relative_height = height * relative_amount;

        // vector_2d vel = sprite_velocity(sprt);

        // _sprite_movement_direction vel_direction = _direction_from_velocity(vel);

        // bool up = vel_direction == _sprite_movement_direction::UP;
        // bool down = vel_direction == _sprite_movement_direction::DOWN;
        // bool left = vel_direction == _sprite_movement_direction::LEFT;
        // bool right = vel_direction == _sprite_movement_direction::RIGHT;

        switch (direction)
        {
        case _sprite_movement_direction::UP:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::UP, vector_to(0.0, relative_height));
            break;
        case _sprite_movement_direction::DOWN:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::DOWN, vector_to(0.0, relative_height));
            break;
        case _sprite_movement_direction::LEFT:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::LEFT, vector_to(relative_width, 0.0));
            break;
        case _sprite_movement_direction::RIGHT:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::RIGHT, vector_to(relative_width, 0.0));
            break;
        case _sprite_movement_direction::UP_LEFT:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::UP_LEFT, vector_to(relative_width, relative_height));
            break;
        case _sprite_movement_direction::UP_RIGHT:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::UP_RIGHT, vector_to(relative_width, relative_height));
            break;
        case _sprite_movement_direction::DOWN_LEFT:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::DOWN_LEFT, vector_to(relative_width, relative_height));
            break;
        default: // _sprite_movement_direction::DOWN_RIGHT:
            _move_sprite_by_direction(sprt, _sprite_movement_direction::DOWN_RIGHT, vector_to(relative_width, relative_height));
            break;
        };
    }

    bool _bracket_sprite_collision(bool colliding, int i, sprite collider, _sprite_movement_direction collider_direction)
    {
        if (colliding)
        {
            _move_sprite_by_direction_relative_to_size(collider, collider_direction,
                                                        1.0 / pow(ITERATION_POWER, static_cast<double>(i)));
        }
        else if (i == 1) // no collision in the first iteration
        {
            return false;
        }
        else
        {
            _move_sprite_by_direction_relative_to_size(collider, _opposite_direction(collider_direction),
                                                        1.0 / pow(ITERATION_POWER, static_cast<double>(i)));
        }
        return true;
    }

    bool _bracket_sprite_sprite_collision(sprite collider, sprite collidee,
        _sprite_movement_direction collider_direction, int iterations = DEFAULT_BRACKET_ITERATIONS)
    {
        for (int i = 1; i <= iterations; i++)
        {
            if (!_bracket_sprite_collision(sprite_collision(collider, collidee), i, collider, collider_direction))
            {
                return false;
            }
            {
                return false;
            }
        }
        return true;
    }

    bool _bracket_sprite_rectangle_collision(sprite collider, const rectangle& collidee,
        _sprite_movement_direction collider_direction, int iterations = DEFAULT_BRACKET_ITERATIONS)
    {
        for (int i = 1; i <= iterations; i++)
        {
            if (!_bracket_sprite_collision(sprite_rectangle_collision(collider, collidee), i, collider,
                                                                                    collider_direction))
            {
                return false;
            }
        }
        return true;
    }

    bool _bracket_sprite_circle_collision(sprite collider, const circle& collidee,
        _sprite_movement_direction collider_direction, int iterations = DEFAULT_BRACKET_ITERATIONS)
    {
        for (int i = 1; i <= iterations; i++)
        {
            if (!_bracket_sprite_collision(sprite_circle_collision(collider, collidee), i, collider,
                                                                                collider_direction))
            {
                return false;
            }
        }
        return true;
    }

    bool _bracket_sprite_triangle_collision(sprite collider, const triangle& collidee,
        _sprite_movement_direction collider_direction, int iterations = DEFAULT_BRACKET_ITERATIONS)
    {
        for (int i = 1; i <= iterations; i++)
        {
            if (!_bracket_sprite_collision(sprite_triangle_collision(collider, collidee), i, collider,
                                                                                    collider_direction))
            {
                return false;
            }
        }
        return true;
    }

    bool _bracket_sprite_quad_collision(sprite collider, const quad& collidee,
        _sprite_movement_direction collider_direction, int iterations = DEFAULT_BRACKET_ITERATIONS)
    {
        for (int i = 1; i <= iterations; i++)
        {
            if (!_bracket_sprite_collision(sprite_quad_collision(collider, collidee), i, collider,
                                                                                collider_direction))
            {
                return false;
            }
        }
        return true;
    }

    collision_direction _compare_point_collision_depth_horizontal(const point_2d& collider, const point_2d& collidee)
    {
        if (collider.x < collidee.x)
        {
            return collision_direction::RIGHT;
        }
        return collision_direction::LEFT;
    }

    collision_direction _compare_point_collision_depth_vertical(const point_2d& collider, const point_2d& collidee)
    {
        if (collider.y < collidee.y)
        {
            return collision_direction::BOTTOM;
        }
        return collision_direction::TOP;
    }

    collision_direction _calculate_containing_collision_direction(const rectangle& collider, const rectangle& collidee)
    {
        // calculate the direction of the greatest distance between the two sprites
        point_2d collider_center = rectangle_center(collider);
        point_2d collidee_center = rectangle_center(collidee);
        double x_distance = collider_center.x - collidee_center.x;
        if (x_distance < 0.0)
        {
            x_distance *= -1;
        }

        double y_distance = collider_center.y - collidee_center.y;
        if (y_distance < 0.0)
        {
            y_distance *= -1;
        }

        if (x_distance > y_distance)
        {
            return _compare_point_collision_depth_horizontal(collider_center, collidee_center);
        }
        return _compare_point_collision_depth_vertical(collider_center, collidee_center);
    }

    collision_direction _rectangle_rectangle_collision_direction(const rectangle& collider, const rectangle& collidee)
    {
        vector<line> collider_lines = lines_from(collider);
        line collider_top_edge = collider_lines[0];
        line collider_left_edge = collider_lines[1];
        line collider_right_edge = collider_lines[2];
        line collider_bottom_edge = collider_lines[3];

        bool left_edge = line_intersects_rect(collider_left_edge, collidee);
        bool right_edge = line_intersects_rect(collider_right_edge, collidee);
        bool top_edge = line_intersects_rect(collider_top_edge, collidee);
        bool bottom_edge = line_intersects_rect(collider_bottom_edge, collidee);

        if (left_edge && right_edge && top_edge && bottom_edge) // collidee contains collider
        {
            return _calculate_containing_collision_direction(collider, collidee);
        }
        if (left_edge && right_edge && top_edge)
        {
            return collision_direction::TOP;
        }
        if (left_edge && right_edge && bottom_edge)
        {
            return collision_direction::BOTTOM;
        }
        if (top_edge && bottom_edge && right_edge)
        {
            return collision_direction::RIGHT;
        }
        if (top_edge && bottom_edge && left_edge)
        {
            return collision_direction::LEFT;
        }
        if (left_edge && right_edge)
        {
            // check if the collider is more to the left or right of the collidee
            return _compare_point_collision_depth_horizontal(rectangle_center(collider), rectangle_center(collidee));
        }
        if (top_edge && bottom_edge)
        {
            // check if the collider is more to the top or bottom of the collidee
            return _compare_point_collision_depth_vertical(rectangle_center(collider), rectangle_center(collidee));
        }
        if (left_edge && top_edge)
        {
            return collision_direction::TOP_LEFT;
        }
        if (left_edge && bottom_edge)
        {
            return collision_direction::BOTTOM_LEFT;
        }
        if (right_edge && top_edge)
        {
            return collision_direction::TOP_RIGHT;
        }
        if (right_edge && bottom_edge)
        {
            return collision_direction::BOTTOM_RIGHT;
        }
        if (left_edge)
        {
            return collision_direction::LEFT;
        }
        if (right_edge)
        {
            return collision_direction::RIGHT;
        }
        if (top_edge)
        {
            return collision_direction::TOP;
        }
        if (bottom_edge)
        {
            return collision_direction::BOTTOM;
        }

        // collider contains collidee
        return _calculate_containing_collision_direction(collider, collidee);


        // // calculate the direction of the greatest distance between the two sprites
        // point_2d collider_center = rectangle_center(collider);
        // point_2d collidee_center = rectangle_center(collidee);
        // double x_distance = abs(collider_center.x - collidee_center.x);
        // double y_distance = abs(collider_center.y - collidee_center.y);

        // if (x_distance < y_distance)
        // {
        //     return _compare_point_collision_depth_horizontal(collider_center, collidee_center);
        // }
        // return _compare_point_collision_depth_vertical(collider_center, collidee_center);
    }

    collision_direction sprite_collision_direction(sprite collider, sprite collidee)
    {
        if (!sprite_collision(collider, collidee))
        {
            return collision_direction::NONE;
        }
        
        rectangle collider_rect = sprite_collision_rectangle(collider);
        rectangle collidee_rect = sprite_collision_rectangle(collidee);

        return _rectangle_rectangle_collision_direction(collider_rect, collidee_rect);
    }

    collision_direction sprite_collision_direction(sprite collider, const rectangle& collidee)
    {
        if (!sprite_rectangle_collision(collider, collidee))
        {
            return collision_direction::NONE;
        }

        rectangle collider_rect = sprite_collision_rectangle(collider);

        return _rectangle_rectangle_collision_direction(collider_rect, collidee);
    }

    collision_direction sprite_collision_direction(sprite collider, const circle& collidee)
    {
        if (!sprite_circle_collision(collider, collidee))
        {
            return collision_direction::NONE;
        }

        rectangle collider_rect = sprite_collision_rectangle(collider);
        rectangle collidee_rect = rectangle_around(collidee);

        return _rectangle_rectangle_collision_direction(collider_rect, collidee_rect);
    }

    collision_direction sprite_collision_direction(sprite collider, const triangle& collidee)
    {
        if (!sprite_triangle_collision(collider, collidee))
        {
            return collision_direction::NONE;
        }

        rectangle collider_rect = sprite_collision_rectangle(collider);
        rectangle collidee_rect = rectangle_around(collidee);

        return _rectangle_rectangle_collision_direction(collider_rect, collidee_rect);
    }

    collision_direction sprite_collision_direction(sprite collider, const quad& collidee)
    {
        if (!sprite_quad_collision(collider, collidee))
        {
            return collision_direction::NONE;
        }

        rectangle collider_rect = sprite_collision_rectangle(collider);
        rectangle collidee_rect = rectangle_around(collidee);

        return _rectangle_rectangle_collision_direction(collider_rect, collidee_rect);
    }

    void _resolve_sprite_AABB_collision(sprite collider, const rectangle& collidee_rect, collision_direction direction)
    {
        // get the bounding rectangles of the sprites
        rectangle collider_rect = sprite_collision_rectangle(collider);

        // get the intersection rectangle
        rectangle inter = intersection(collider_rect, collidee_rect);
        vector_2d amount = vector_to(inter.width, inter.height);

        _move_sprite_by_direction(collider, _direction_from_collision(direction), amount);
    }

    bool resolve_sprite_collision(sprite collider, sprite collidee, collision_direction direction)
    {
        // check if the sprites are colliding
        if (direction == collision_direction::NONE || !sprite_collision(collider, collidee))
        {
            return false;
        }

        collision_test_kind collider_kind = sprite_collision_kind(collider);
        collision_test_kind collidee_kind = sprite_collision_kind(collidee);

        if (collider_kind == AABB_COLLISIONS && collidee_kind == AABB_COLLISIONS)
        {
            _resolve_sprite_AABB_collision(collider, sprite_collision_rectangle(collidee), direction);
        }
        else // one or both of the sprites are using pixel collision
        {
            _bracket_sprite_sprite_collision(collider, collidee, _direction_from_collision(direction));
        }

        return true;
    }

    bool resolve_sprite_collision(sprite collider, const rectangle& collidee, collision_direction direction)
    {
        // check if the sprites are colliding
        if (direction == collision_direction::NONE || !sprite_rectangle_collision(collider, collidee))
        {
            return false;
        }

        collision_test_kind collider_kind = sprite_collision_kind(collider);

        if (collider_kind == AABB_COLLISIONS)
        {
            _resolve_sprite_AABB_collision(collider, collidee, direction);
        }
        else // sprite is using pixel collision
        {
            _bracket_sprite_rectangle_collision(collider, collidee, _direction_from_collision(direction));
        }

        return true;
    }

    bool resolve_sprite_collision(sprite collider, const circle& collidee, collision_direction direction)
    {
        // check if the sprites are colliding
        if (direction == collision_direction::NONE || !sprite_circle_collision(collider, collidee))
        {
            return false;
        }

        collision_test_kind collider_kind = sprite_collision_kind(collider);

        if (collider_kind == AABB_COLLISIONS)
        {
            _resolve_sprite_AABB_collision(collider, rectangle_around(collidee), direction);
        }
        else // sprite is using pixel collision
        {
            _bracket_sprite_circle_collision(collider, collidee, _direction_from_collision(direction));
        }

        return true;
    }

    bool resolve_sprite_collision(sprite collider, const triangle& collidee, collision_direction direction)
    {
        // check if the sprites are colliding
        if (direction == collision_direction::NONE || !sprite_triangle_collision(collider, collidee))
        {
            return false;
        }

        collision_test_kind collider_kind = sprite_collision_kind(collider);

        if (collider_kind == AABB_COLLISIONS)
        {
            _resolve_sprite_AABB_collision(collider, rectangle_around(collidee), direction);
        }
        else // sprite is using pixel collision
        {
            _bracket_sprite_triangle_collision(collider, collidee, _direction_from_collision(direction));
        }

        return true;
    }

    bool resolve_sprite_collision(sprite collider, const quad& collidee, collision_direction direction)
    {
        // check if the sprites are colliding
        if (direction == collision_direction::NONE || !sprite_quad_collision(collider, collidee))
        {
            return false;
        }

        collision_test_kind collider_kind = sprite_collision_kind(collider);

        if (collider_kind == AABB_COLLISIONS)
        {
            _resolve_sprite_AABB_collision(collider, rectangle_around(collidee), direction);
        }
        else // sprite is using pixel collision
        {
            _bracket_sprite_quad_collision(collider, collidee, _direction_from_collision(direction));
        }

        return true;
    }

}
