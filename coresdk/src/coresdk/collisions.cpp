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

using std::function;

namespace splashkit_lib
{
    const vector_2d _DIRECTION_TOP = vector_to(0.0, -1.0);
    const vector_2d _DIRECTION_BOTTOM = vector_to(0.0, 1.0);
    const vector_2d _DIRECTION_LEFT = vector_to(-1.0, 0.0);
    const vector_2d _DIRECTION_RIGHT = vector_to(1.0, 0.0);
    const vector_2d _DIRECTION_TOP_LEFT = unit_vector(vector_to(-1.0, -1.0));
    const vector_2d _DIRECTION_TOP_RIGHT = unit_vector(vector_to(1.0, -1.0));
    const vector_2d _DIRECTION_BOTTOM_LEFT = unit_vector(vector_to(-1.0, 1.0));
    const vector_2d _DIRECTION_BOTTOM_RIGHT = unit_vector(vector_to(1.0, 1.0));
    const vector_2d _DIRECTION_NONE = vector_to(0.0, 0.0);

    // #define DEBUG_STEP

    // Step over pixels in the two areas based on the supplied matrix
    //
    // See http://www.austincc.edu/cchrist1/GAME1343/TransformedCollision/TransformedCollision.htm
    bool _step_through_pixels(
        double w1, double h1,
        const matrix_2d &matrix1,
        double w2, double h2,
        const matrix_2d &matrix2,
        function<bool(int, int, int, int)> end_fn)
    {
        bool a_is_1;
        double h_a, w_a;
        double h_b, w_b;
        matrix_2d transform_a_to_b;

        // Determine the smaller area to step through.
        if (w1 * h1 <= w2 * h2) // use bitmap 1 as the one to scan
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
        y_pos_in_b = matrix_multiply(transform_a_to_b, vector_to(0, 0));

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
                if ((0 <= x_b) and (x_b < w_b) and (0 <= y_b) and (y_b < h_b))
                {
                    if ((a_is_1 and end_fn(x_a, y_a, x_b, y_b)) or ((not a_is_1) and end_fn(x_b, y_b, x_a, y_a)))
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

    bool _collision_within_bitmap_images_with_translation(bitmap bmp1, int c1, const matrix_2d &matrix1, bitmap bmp2, int c2, const matrix_2d &matrix2)
    {
        return _step_through_pixels(bitmap_cell_width(bmp1), bitmap_cell_height(bmp1), matrix1,
                                    bitmap_cell_width(bmp2), bitmap_cell_height(bmp2), matrix2,
                                    [&](int ax, int ay, int bx, int by)
                                    {
#if DEBUG_STEP
                                        point_2d apt, bpt;
                                        apt = matrix_multiply(matrix1, point_at(ax, ay));
                                        if (pixel_drawn_at_point(bmp1, c1, ax, ay))
                                            draw_circle(COLOR_RED, apt.x, apt.y, 3);
                                        bpt = matrix_multiply(matrix2, point_at(bx, by));
                                        if (pixel_drawn_at_point(bmp2, c2, bx, by))
                                            draw_circle(COLOR_PINK, bpt.x, bpt.y, 2);

                                        if (pixel_drawn_at_point(bmp1, c1, ax, ay) and pixel_drawn_at_point(bmp2, c2, bx, by))
                                        {
                                            fill_circle(COLOR_GREEN, apt.x, apt.y, 1);
                                            fill_circle(COLOR_YELLOW, bpt.x, bpt.y, 3);
                                        }
#endif
                                        return pixel_drawn_at_point(bmp1, c1, ax, ay) and pixel_drawn_at_point(bmp2, c2, bx, by);
                                    });
    }

    vector_2d _opposite_direction(const vector_2d &dir)
    {
        return vector_to(-dir.x, -dir.y);
    }

    bool _test_collision(const sprite &s1, const sprite &s2)
    {
        return sprite_collision(s1, s2);
    }

    bool _test_collision(const sprite &s, const rectangle &r)
    {
        return sprite_rectangle_collision(s, r);
    }

    bool _test_collision(const sprite &s, const circle &c)
    {
        return sprite_circle_collision(s, c);
    }

    bool _test_collision(const sprite &s, const triangle &t)
    {
        return sprite_triangle_collision(s, t);
    }

    bool _test_collision(const sprite &s, const quad &q)
    {
        return sprite_quad_collision(s, q);
    }

    bool _test_collision(const rectangle &r, const sprite &s)
    {
        return sprite_rectangle_collision(s, r);
    }

    bool _test_collision(const rectangle &r1, const rectangle &r2)
    {
        return rectangles_intersect(r1, r2);
    }

    bool _test_collision(const rectangle &r, const circle &c)
    {
        return rectangle_circle_intersect(r, c);
    }

    bool _test_collision(const rectangle &r, const triangle &t)
    {
        return triangle_rectangle_intersect(t, r);
    }

    bool _test_collision(const rectangle &r, const quad &q)
    {
        return quads_intersect(quad_from(r), q);
    }

    bool _test_collision(const circle &c, const sprite &s)
    {
        return sprite_circle_collision(s, c);
    }

    bool _test_collision(const circle &c, const rectangle &r)
    {
        return rectangle_circle_intersect(r, c);
    }

    bool _test_collision(const circle &c1, const circle &c2)
    {
        return circles_intersect(c1, c2);
    }

    bool _test_collision(const circle &c, const triangle &t)
    {
        return circle_triangle_intersect(c, t);
    }

    bool _test_collision(const circle &c, const quad &q)
    {
        return circle_quad_intersect(c, q);
    }

    bool _test_collision(const triangle &t, const sprite &s)
    {
        return sprite_triangle_collision(s, t);
    }

    bool _test_collision(const triangle &t, const rectangle &r)
    {
        return triangle_rectangle_intersect(t, r);
    }

    bool _test_collision(const triangle &t, const circle &c)
    {
        return circle_triangle_intersect(c, t);
    }

    bool _test_collision(const triangle &t1, const triangle &t2)
    {
        return triangles_intersect(t1, t2);
    }

    bool _test_collision(const triangle &t, const quad &q)
    {
        return triangle_quad_intersect(t, q);
    }

    bool _test_collision(const quad &q, const sprite &s)
    {
        return sprite_quad_collision(s, q);
    }

    bool _test_collision(const quad &q, const rectangle &r)
    {
        return quads_intersect(q, quad_from(r));
    }

    bool _test_collision(const quad &q, const circle &c)
    {
        return circle_quad_intersect(c, q);
    }

    bool _test_collision(const quad &q, const triangle &t)
    {
        return triangle_quad_intersect(t, q);
    }

    bool _test_collision(const quad &q1, const quad &q2)
    {
        return quads_intersect(q1, q2);
    }

    void _move_obj_by_vector(sprite &obj, const vector_2d &amount)
    {
        sprite_set_x(obj, sprite_x(obj) + amount.x);
        sprite_set_y(obj, sprite_y(obj) + amount.y);
    }

    void _move_obj_by_vector(rectangle &obj, const vector_2d &amount)
    {
        obj.x += amount.x;
        obj.y += amount.y;
    }

    void _move_obj_by_vector(circle &obj, const vector_2d &amount)
    {
        obj.center.x += amount.x;
        obj.center.y += amount.y;
    }

    void _move_obj_by_vector(triangle &obj, const vector_2d &amount)
    {
        obj.points[0].x += amount.x;
        obj.points[0].y += amount.y;
        obj.points[1].x += amount.x;
        obj.points[1].y += amount.y;
        obj.points[2].x += amount.x;
        obj.points[2].y += amount.y;
    }

    void _move_obj_by_vector(quad &obj, const vector_2d &amount)
    {
        obj.points[0].x += amount.x;
        obj.points[0].y += amount.y;
        obj.points[1].x += amount.x;
        obj.points[1].y += amount.y;
        obj.points[2].x += amount.x;
        obj.points[2].y += amount.y;
        obj.points[3].x += amount.x;
        obj.points[3].y += amount.y;
    }

    rectangle _object_AABB(const sprite &obj)
    {
        return sprite_collision_rectangle(obj);
    }

    rectangle _object_AABB(const rectangle &obj)
    {
        return obj;
    }

    rectangle _object_AABB(const circle &obj)
    {
        return rectangle_around(obj);
    }

    rectangle _object_AABB(const triangle &obj)
    {
        return rectangle_around(obj);
    }

    rectangle _object_AABB(const quad &obj)
    {
        return rectangle_around(obj);
    }

    template <typename T>
    collision_test_kind _collision_kind(const T &obj)
    {
        return PIXEL_COLLISIONS;
    }

    template <>
    collision_test_kind _collision_kind(const rectangle &obj)
    {
        return AABB_COLLISIONS;
    }

    template <>
    collision_test_kind _collision_kind(const sprite &obj)
    {
        return sprite_collision_kind(obj);
    }

    vector_2d _compare_point_collision_depth_horizontal(const point_2d &collider, const point_2d &collidee)
    {
        if (collider.x < collidee.x)
        {
            return _DIRECTION_RIGHT;
        }
        return _DIRECTION_LEFT;
    }

    vector_2d _compare_point_collision_depth_vertical(const point_2d &collider, const point_2d &collidee)
    {
        if (collider.y < collidee.y)
        {
            return _DIRECTION_BOTTOM;
        }
        return _DIRECTION_TOP;
    }

    vector_2d _calculate_containing_collision_direction(const rectangle &collider, const rectangle &collidee)
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

        if (x_distance < y_distance)
        {
            return _compare_point_collision_depth_horizontal(collider_center, collidee_center);
        }
        return _compare_point_collision_depth_vertical(collider_center, collidee_center);
    }

    vector_2d _rectangle_rectangle_collision_direction(const rectangle &collider, const rectangle &collidee)
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

        if (left_edge && right_edge && top_edge && bottom_edge) // collidee is equal size of collider
        {
            return _calculate_containing_collision_direction(collider, collidee);
        }
        if ((left_edge && right_edge && top_edge) || (top_edge && !(left_edge || right_edge || bottom_edge)))
        {
            return _DIRECTION_TOP;
        }
        if ((left_edge && right_edge && bottom_edge) || (bottom_edge && !(left_edge || right_edge || top_edge)))
        {
            return _DIRECTION_BOTTOM;
        }
        if ((top_edge && bottom_edge && right_edge) || (right_edge && !(left_edge || top_edge || bottom_edge)))
        {
            return _DIRECTION_RIGHT;
        }
        if ((top_edge && bottom_edge && left_edge) || (left_edge && !(right_edge || top_edge || bottom_edge)))
        {
            return _DIRECTION_LEFT;
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
            return _DIRECTION_TOP_LEFT;
        }
        if (left_edge && bottom_edge)
        {
            return _DIRECTION_BOTTOM_LEFT;
        }
        if (right_edge && top_edge)
        {
            return _DIRECTION_TOP_RIGHT;
        }
        if (right_edge && bottom_edge)
        {
            return _DIRECTION_BOTTOM_RIGHT;
        }

        // collider contains collidee or collidee contains collider
        return _calculate_containing_collision_direction(collider, collidee);
    }

    template <typename T>
    void _move_object_by_direction(T &obj, const vector_2d &movement_direction, const vector_2d &amount)
    {
        if (is_zero_vector(amount))
        {
            return;
        }

        _move_obj_by_vector(obj, vector_to(amount.x * movement_direction.x,
                                           amount.y * movement_direction.y));
    }

    template <typename T>
    void _move_object_by_direction_relative_to_size(T &obj, const vector_2d &movement_direction,
                                                    double relative_amount = 1.0)
    {
        if (is_zero_vector(movement_direction))
        {
            return;
        }

        if (relative_amount == 0.0)
        {
            return;
        }

        rectangle obj_aabb = _object_AABB(obj);

        double relative_width = obj_aabb.width * relative_amount;
        double relative_height = obj_aabb.height * relative_amount;

        if (movement_direction.x == 0.0)
        {
            relative_width = 0.0;
        }
        else if (movement_direction.y == 0.0)
        {
            relative_height = 0.0;
        }

        _move_object_by_direction(obj, movement_direction, vector_to(relative_width, relative_height));
    }

    /**
     * Moves the object back and forth with decreasing step size for
     * the given number of iterations.
     */
    template <typename T>
    bool _bracket_obj_collision_single(bool colliding, int i, T &collider,
                                       const vector_2d &collider_direction)
    {
        const double ITERATION_POWER = 1.5;
        if (colliding)
        {
            _move_object_by_direction_relative_to_size(collider, collider_direction,
                                                       1.0 / pow(ITERATION_POWER, static_cast<double>(i)));
        }
        else if (i == 1) // no collision in the first iteration
        {
            return false;
        }
        else
        {
            _move_object_by_direction_relative_to_size(collider, _opposite_direction(collider_direction),
                                                       1.0 / pow(ITERATION_POWER, static_cast<double>(i)));
        }
        return true;
    }

    template <typename A, typename B>
    void _bracket_obj_obj_collision(A &collider, const B &collidee, const vector_2d &collider_direction,
                                    int iterations)
    {
        for (int i = 1; i <= iterations; i++)
        {
            if (!_bracket_obj_collision_single(_test_collision(collider, collidee), i, collider,
                                               collider_direction))
            {
                return;
            }
        }
    }

    template <typename A, typename B>
    vector_2d _calculate_object_collision_direction(const A &collider, const B &collidee)
    {
        if (!_test_collision(collider, collidee))
        {
            return vector_to(0.0, 0.0);
        }

        return _rectangle_rectangle_collision_direction(_object_AABB(collider), _object_AABB(collidee));
    }

    template <typename T>
    void _resolve_object_AABB_collision(T &collider, const rectangle &collidee_rect,
                                        const vector_2d &collision_direction)
    {
        // get the intersection rectangle
        rectangle inter = intersection(_object_AABB(collider), collidee_rect);
        vector_2d amount = vector_to(inter.width, inter.height);

        _move_object_by_direction(collider, _opposite_direction(collision_direction), amount);
    }

    template <typename A, typename B>
    bool _resolve_object_collision(A &collider, const B &collidee, const vector_2d &collision_direction)
    {
        const int BRACKET_ITERATIONS = 40;
        if (is_zero_vector(collision_direction) || !_test_collision(collider, collidee))
        {
            return false;
        }

        vector_2d unit_dir = unit_vector(collision_direction);

        if (_collision_kind(collider) == AABB_COLLISIONS && _collision_kind(collidee) == AABB_COLLISIONS)
        {
            _resolve_object_AABB_collision(collider, _object_AABB(collidee), unit_dir);
        }
        else // one or both of the sprites are using pixel collision
        {
            _bracket_obj_obj_collision(collider, collidee, _opposite_direction(unit_dir), BRACKET_ITERATIONS);
        }

        return true;
    }

    bool bitmap_point_collision(bitmap bmp, int cell, const matrix_2d &translation, const point_2d &pt)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        if (not point_in_quad(pt, quad_from(bitmap_cell_rectangle(bmp), translation)))
        {
            return false;
        }

        return _step_through_pixels(1, 1, translation_matrix(pt.x, pt.y), bmp->cell_w, bmp->cell_h, translation, [&](int ax, int ay, int bx, int by)
                                    {
#if DEBUG_STEP
                                        point_2d bpt;
                                        bpt = matrix_multiply(translation, point_at(bx,by));
                                        if ( pixel_drawn_at_point(bmp, cell, bx, by) )
                                            fill_rectangle(COLOR_PINK, bpt.x, bpt.y, translation.elements[0][0], translation.elements[1][1] );
#endif
                                        return pixel_drawn_at_point(bmp, cell, bx, by); });
    }

    bool bitmap_point_collision(bitmap bmp, const matrix_2d &translation, const point_2d &pt)
    {
        return bitmap_point_collision(bmp, 0, translation, pt);
    }

    bool bitmap_point_collision(bitmap bmp, const point_2d &bmp_pt, const point_2d &pt)
    {
        return bitmap_point_collision(bmp, translation_matrix(bmp_pt), pt);
    }

    bool bitmap_point_collision(bitmap bmp, double bmp_x, double bmp_y, double x, double y)
    {
        return bitmap_point_collision(bmp, 0, translation_matrix(bmp_x, bmp_y), point_at(x, y));
    }

    bool bitmap_point_collision(bitmap bmp, int cell, const point_2d &bmp_pt, const point_2d &pt)
    {
        return bitmap_point_collision(bmp, cell, translation_matrix(bmp_pt), pt);
    }

    bool bitmap_point_collision(bitmap bmp, int cell, double bmp_x, double bmp_y, double x, double y)
    {
        return bitmap_point_collision(bmp, cell, translation_matrix(bmp_x, bmp_y), point_at(x, y));
    }

    bool bitmap_rectangle_collision(bitmap bmp, int cell, const matrix_2d &translation, const rectangle &rect)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        quad q1, q2;

        q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        q2 = quad_from(rect);

        if (not quads_intersect(q1, q2))
            return false;

        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&](int ax, int ay, int bx, int by)
                                    { return pixel_drawn_at_point(bmp, cell, bx, by); });
    }

    bool bitmap_rectangle_collision(bitmap bmp, int cell, const point_2d &pt, const rectangle &rect)
    {
        return bitmap_rectangle_collision(bmp, cell, translation_matrix(pt), rect);
    }

    bool bitmap_rectangle_collision(bitmap bmp, const point_2d &pt, const rectangle &rect)
    {
        return bitmap_rectangle_collision(bmp, 0, translation_matrix(pt), rect);
    }

    bool bitmap_rectangle_collision(bitmap bmp, double x, double y, const rectangle &rect)
    {
        return bitmap_rectangle_collision(bmp, 0, translation_matrix(x, y), rect);
    }

    bool bitmap_rectangle_collision(bitmap bmp, int cell, double x, double y, const rectangle &rect)
    {
        return bitmap_rectangle_collision(bmp, cell, translation_matrix(x, y), rect);
    }

    bool bitmap_circle_collision(bitmap bmp, int cell, const matrix_2d &translation, const circle &circ)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        quad q1, q2;

        q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        rectangle rect = rectangle_around(circ);
        q2 = quad_from(rect);

        if (not quads_intersect(q1, q2))
            return false;

        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&](int ax, int ay, int bx, int by)
                                    { return pixel_drawn_at_point(bmp, cell, bx, by) && point_in_circle(point_at(rect.x + ax, rect.y + ay), circ); });
    }

    bool bitmap_circle_collision(bitmap bmp, int cell, const point_2d &pt, const circle &circ)
    {
        return bitmap_circle_collision(bmp, cell, translation_matrix(pt), circ);
    }

    bool bitmap_circle_collision(bitmap bmp, const point_2d &pt, const circle &circ)
    {
        return bitmap_circle_collision(bmp, 0, translation_matrix(pt), circ);
    }

    bool bitmap_circle_collision(bitmap bmp, double x, double y, const circle &circ)
    {
        return bitmap_circle_collision(bmp, 0, translation_matrix(x, y), circ);
    }

    bool bitmap_circle_collision(bitmap bmp, int cell, double x, double y, const circle &circ)
    {
        return bitmap_circle_collision(bmp, cell, translation_matrix(x, y), circ);
    }

    bool bitmap_quad_collision(bitmap bmp, int cell, const matrix_2d &translation, const quad &q)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        quad q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        rectangle rect = rectangle_around(q);

        if (not quads_intersect(q1, q))
            return false;

        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&](int ax, int ay, int bx, int by)
                                    { return pixel_drawn_at_point(bmp, cell, bx, by) && point_in_quad(point_at(rect.x + ax, rect.y + ay), q); });
    }

    bool bitmap_ray_collision(bitmap bmp, int cell, const matrix_2d &translation, const point_2d &origin, const vector_2d &heading)
    {
        constexpr double RAY_QUAD_LINE_THICKNESS = 1.0;
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        point_2d bmp_position = matrix_multiply(translation, point_at(0.0, 0.0));
        point_2d bmp_center = point_offset_by(bmp_position, vector_to(bitmap_center(bmp)));
        circle bmp_bounding_circle = bitmap_bounding_circle(bmp, bmp_center);

        vector_2d unit_ray_heading = unit_vector(heading);

        // get point which will allow segment to fully pass through the bitmap
        double distance_to_center = vector_magnitude(vector_point_to_point(origin, bmp_center));
        point_2d ray_end = point_offset_by(origin, vector_multiply(unit_ray_heading, distance_to_center + bmp_bounding_circle.radius));

        quad ray_quad = quad_from(origin, ray_end, RAY_QUAD_LINE_THICKNESS);
        return bitmap_quad_collision(bmp, cell, translation, ray_quad);
    }

    bool bitmap_ray_collision(bitmap bmp, int cell, const point_2d &pt, const point_2d &origin, const vector_2d &heading)
    {
        return bitmap_ray_collision(bmp, cell, translation_matrix(pt), origin, heading);
    }

    bool bitmap_ray_collision(bitmap bmp, int cell, double x, double y, const point_2d &origin, const vector_2d &heading)
    {
        return bitmap_ray_collision(bmp, cell, translation_matrix(x, y), origin, heading);
    }

    bool bitmap_ray_collision(bitmap bmp, double x, double y, const point_2d &origin, const vector_2d &heading)
    {
        return bitmap_ray_collision(bmp, 0, translation_matrix(x, y), origin, heading);
    }

    bool bitmap_ray_collision(bitmap bmp, const point_2d &pt, const point_2d &origin, const vector_2d &heading)
    {
        return bitmap_ray_collision(bmp, 0, translation_matrix(pt), origin, heading);
    }

    bool bitmap_triangle_collision(bitmap bmp, int cell, const matrix_2d &translation, const triangle &tri)
    {
        if (INVALID_PTR(bmp, BITMAP_PTR))
        {
            return false;
        }

        quad q1 = quad_from(bitmap_cell_rectangle(bmp), translation);
        rectangle rect = rectangle_around(tri);

        if (!triangle_quad_intersect(tri, q1))
        {
            return false;
        }

        return _step_through_pixels(rect.width, rect.height, translation_matrix(rect.x, rect.y), bmp->cell_w, bmp->cell_h, translation, [&](int ax, int ay, int bx, int by)
                                    { return pixel_drawn_at_point(bmp, cell, bx, by) && point_in_triangle(point_at(rect.x + ax, rect.y + ay), tri); });
    }

    bool bitmap_triangle_collision(bitmap bmp, int cell, const point_2d &pt, const triangle &tri)
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

    bool bitmap_triangle_collision(bitmap bmp, const point_2d &pt, const triangle &tri)
    {
        return bitmap_triangle_collision(bmp, 0, translation_matrix(pt), tri);
    }

    bool bitmap_quad_collision(bitmap bmp, int cell, const point_2d &pt, const quad &q)
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

    bool bitmap_quad_collision(bitmap bmp, const point_2d &pt, const quad &q)
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

    bool sprite_rectangle_collision(sprite s, const rectangle &rect)
    {
        if (!rectangles_intersect(sprite_collision_rectangle(s), rect))
        {
            return false;
        }

        return bitmap_rectangle_collision(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s), rect);
    }

    bool sprite_ray_collision(sprite s, const point_2d &origin, const vector_2d &heading)
    {
        return bitmap_ray_collision(sprite_collision_bitmap(s), sprite_current_cell(s), sprite_location_matrix(s), origin, heading);
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

        return _collision_within_bitmap_images_with_translation(
            sprite_collision_bitmap(s1), sprite_current_cell(s1), sprite_location_matrix(s1),
            sprite_collision_bitmap(s2), sprite_current_cell(s2), sprite_location_matrix(s2));
    }

    bool bitmap_collision(bitmap bmp1, int cell1, const matrix_2d &matrix1, bitmap bmp2, int cell2, const matrix_2d &matrix2)
    {
        quad q1 = quad_from(bitmap_cell_rectangle(bmp1), matrix1);
        quad q2 = quad_from(bitmap_cell_rectangle(bmp2), matrix2);

        if (not quads_intersect(q1, q2))
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

    vector_2d calculate_collision_direction(const sprite collider, const sprite collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const sprite collider, const rectangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const sprite collider, const circle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const sprite collider, const triangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const sprite collider, const quad &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const rectangle &collider, const sprite collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const rectangle &collider, const rectangle &collidee)
    {
        return _rectangle_rectangle_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const rectangle &collider, const circle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const rectangle &collider, const triangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const rectangle &collider, const quad &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const circle &collider, const sprite collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const circle &collider, const rectangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const circle &collider, const circle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const circle &collider, const triangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const circle &collider, const quad &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const triangle &collider, const sprite collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const triangle &collider, const rectangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const triangle &collider, const circle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const triangle &collider, const triangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const triangle &collider, const quad &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const quad &collider, const sprite collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const quad &collider, const rectangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const quad &collider, const circle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const quad &collider, const triangle &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    vector_2d calculate_collision_direction(const quad &collider, const quad &collidee)
    {
        return _calculate_object_collision_direction(collider, collidee);
    }

    bool resolve_collision(sprite collider, const sprite collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(sprite collider, const rectangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(sprite collider, const circle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(sprite collider, const triangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(sprite collider, const quad &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(rectangle &collider, const sprite collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(rectangle &collider, const rectangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(rectangle &collider, const circle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(rectangle &collider, const triangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(rectangle &collider, const quad &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(circle &collider, const sprite collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(circle &collider, const rectangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(circle &collider, const circle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(circle &collider, const triangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(circle &collider, const quad &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(triangle &collider, const sprite collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(triangle &collider, const rectangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(triangle &collider, const circle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(triangle &collider, const triangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(triangle &collider, const quad &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(quad &collider, const sprite collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(quad &collider, const rectangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(quad &collider, const circle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(quad &collider, const triangle &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }

    bool resolve_collision(quad &collider, const quad &collidee, const vector_2d &direction)
    {
        return _resolve_object_collision(collider, collidee, direction);
    }
}
