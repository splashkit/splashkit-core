//
//  test_sprites.cpp
//  splashkit
//
//  Created by Andrew Cain on 25/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "collisions.h"
#include "geometry.h"
#include "graphics.h"
#include "images.h"
#include "input.h"
#include "sprites.h"
#include "window_manager.h"
#include <iostream>
#include <vector>

using namespace splashkit_lib;

enum class object_type
{
    SPRITE,
    RECTANGLE,
    CIRCLE,
    TRIANGLE,
    QUAD,
};

/*
* The type of collision test to perform.
* MULTIPLE_DYNAMIC uses classify_collision_direction on each object to determine
* the direction of the collision before calling resolve_collision.
* The FIXED types do not use classify_collision_direction and instead use fixed
* static collision directions determined by each object's position. For example,
* the top-most object will always use a collision direction of DIRECTION_TOP.
*/
enum class collision_test_type
{
    MULTIPLE_DYNAMIC,
    SPRITE_FIXED,
    RECTANGLE_FIXED,
    CIRCLE_FIXED,
    TRIANGLE_FIXED,
    QUAD_FIXED,
};

enum class sprite_perimeter_segment
{
    TOP_LEFT,
    TOP_CENTER,
    TOP_RIGHT,
    BOTTOM_LEFT,
    BOTTOM_CENTER,
    BOTTOM_RIGHT,
    LEFT_TOP,
    LEFT_CENTER,
    LEFT_BOTTOM,
    RIGHT_TOP,
    RIGHT_CENTER,
    RIGHT_BOTTOM,
};

const vector_2d DIRECTION_TOP = vector_to(0.0, -1.0);
const vector_2d DIRECTION_BOTTOM = vector_to(0.0, 1.0);
const vector_2d DIRECTION_LEFT = vector_to(-1.0, 0.0);
const vector_2d DIRECTION_RIGHT = vector_to(1.0, 0.0);
const vector_2d DIRECTION_TOP_LEFT = unit_vector(vector_to(-1.0, -1.0));
const vector_2d DIRECTION_TOP_RIGHT = unit_vector(vector_to(1.0, -1.0));
const vector_2d DIRECTION_BOTTOM_LEFT = unit_vector(vector_to(-1.0, 1.0));
const vector_2d DIRECTION_BOTTOM_RIGHT = unit_vector(vector_to(1.0, 1.0));
const vector_2d DIRECTION_NONE = vector_to(0.0, 0.0);

void draw_rect_perimeter_segment(const rectangle& r, sprite_perimeter_segment segment, color clr, int line_width)
{
    switch (segment)
    {
    case sprite_perimeter_segment::TOP_LEFT:
        draw_line(clr, r.x, r.y, r.x + r.width / 3.0, r.y, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::TOP_CENTER:
        draw_line(clr, r.x + r.width / 3.0, r.y, r.x + r.width * 2.0 / 3.0, r.y, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::TOP_RIGHT:
        draw_line(clr, r.x + r.width * 2.0 / 3.0, r.y, r.x + r.width, r.y, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::BOTTOM_LEFT:
        draw_line(clr, r.x, r.y + r.height, r.x + r.width / 3.0, r.y + r.height, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::BOTTOM_CENTER:
        draw_line(clr, r.x + r.width / 3.0, r.y + r.height, r.x + r.width * 2.0 / 3.0, r.y + r.height, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::BOTTOM_RIGHT:
        draw_line(clr, r.x + r.width * 2.0 / 3.0, r.y + r.height, r.x + r.width, r.y + r.height, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::LEFT_TOP:
        draw_line(clr, r.x, r.y, r.x, r.y + r.height / 3.0, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::LEFT_CENTER:
        draw_line(clr, r.x, r.y + r.height / 3.0, r.x, r.y + r.height * 2.0 / 3.0, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::LEFT_BOTTOM:
        draw_line(clr, r.x, r.y + r.height * 2.0 / 3.0, r.x, r.y + r.height, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::RIGHT_TOP:
        draw_line(clr, r.x + r.width, r.y, r.x + r.width, r.y + r.height / 3.0, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::RIGHT_CENTER:
        draw_line(clr, r.x + r.width, r.y + r.height / 3.0, r.x + r.width, r.y + r.height * 2.0 / 3.0, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::RIGHT_BOTTOM:
        draw_line(clr, r.x + r.width, r.y + r.height * 2.0 / 3.0, r.x + r.width, r.y + r.height, option_line_width(line_width));
        break;
    };
}

void draw_rect_perimeter_segments(const rectangle& r, const std::vector<sprite_perimeter_segment>& segments, color clr, int line_width)
{
    for (const auto& segment : segments)
    {
        draw_rect_perimeter_segment(r, segment, clr, line_width);
    }
}

void draw_rect_perimeter_by_collision(const rectangle& r, const vector_2d& dir, color clr, int line_width)
{
    if (dir.x == DIRECTION_NONE.x && dir.y == DIRECTION_NONE.y)
    {
        return;
    }

    if (dir.x == DIRECTION_TOP.x && dir.y == DIRECTION_TOP.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::TOP_LEFT, sprite_perimeter_segment::TOP_CENTER, sprite_perimeter_segment::TOP_RIGHT}, clr, line_width);
    }
    else if (dir.x == DIRECTION_BOTTOM.x && dir.y == DIRECTION_BOTTOM.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::BOTTOM_LEFT, sprite_perimeter_segment::BOTTOM_CENTER, sprite_perimeter_segment::BOTTOM_RIGHT}, clr, line_width);
    }
    else if (dir.x == DIRECTION_LEFT.x && dir.y == DIRECTION_LEFT.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::LEFT_TOP, sprite_perimeter_segment::LEFT_CENTER, sprite_perimeter_segment::LEFT_BOTTOM}, clr, line_width);
    }
    else if (dir.x == DIRECTION_RIGHT.x && dir.y == DIRECTION_RIGHT.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::RIGHT_TOP, sprite_perimeter_segment::RIGHT_CENTER, sprite_perimeter_segment::RIGHT_BOTTOM}, clr, line_width);
    }
    else if (dir.x == DIRECTION_TOP_LEFT.x && dir.y == DIRECTION_TOP_LEFT.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::TOP_LEFT, sprite_perimeter_segment::LEFT_TOP}, clr, line_width);
    }
    else if (dir.x == DIRECTION_TOP_RIGHT.x && dir.y == DIRECTION_TOP_RIGHT.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::TOP_RIGHT, sprite_perimeter_segment::RIGHT_TOP}, clr, line_width);
    }
    else if (dir.x == DIRECTION_BOTTOM_LEFT.x && dir.y == DIRECTION_BOTTOM_LEFT.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::BOTTOM_LEFT, sprite_perimeter_segment::LEFT_BOTTOM}, clr, line_width);
    }
    else if (dir.x == DIRECTION_BOTTOM_RIGHT.x && dir.y == DIRECTION_BOTTOM_RIGHT.y)
    {
        draw_rect_perimeter_segments(r, {sprite_perimeter_segment::BOTTOM_RIGHT, sprite_perimeter_segment::RIGHT_BOTTOM}, clr, line_width);
    }
}

void sprite_test()
{
    sprite sprt, s2, s3, s4;
    triangle tri, init_tri;
    triangle tri_b, init_tri_b;
    rectangle r;
    quad q;

    open_window("Sprite Rotation", 600, 600);
    
    hide_mouse();

    sprt = create_sprite("rocket_sprt.png");
    sprite_set_move_from_anchor_point(sprt, true);
    sprite_set_x(sprt, 300);
    sprite_set_y(sprt, 300);

    s2 = create_sprite(bitmap_named("rocket_sprt.png"));
    sprite_set_move_from_anchor_point(s2, true);
    sprite_set_x(s2, 100);
    sprite_set_y(s2, 100);

    s3 = create_sprite(bitmap_named("rocket_sprt.png"));
    sprite_set_move_from_anchor_point(s3, true);
    sprite_set_x(s3, 100);
    sprite_set_y(s3, 400);

    s4 = create_sprite(bitmap_named("rocket_sprt.png"));
    sprite_set_move_from_anchor_point(s4, true);
    sprite_set_x(s4, 400);
    sprite_set_y(s4, 400);
    sprite_set_collision_kind(s4, AABB_COLLISIONS);

    r = rectangle_from(400, 100, 100, 50);
    q = quad_from(r);
    apply_matrix(matrix_multiply(translation_matrix(0, 50), rotation_matrix(45)), q);

    init_tri = triangle_from(0, 0, bitmap_width(bitmap_named("rocket_sprt.png")), bitmap_height(bitmap_named("rocket_sprt.png")), 0, bitmap_height(bitmap_named("rocket_sprt.png")));
    init_tri_b = triangle_from(bitmap_width(bitmap_named("rocket_sprt.png")), 0, bitmap_width(bitmap_named("rocket_sprt.png")), bitmap_height(bitmap_named("rocket_sprt.png")), 0, 0);

    while ( not quit_requested() )
    {
        process_events();

        clear_screen(COLOR_WHITE);

        if ( key_down(LEFT_KEY) )
            sprite_set_rotation(sprt, sprite_rotation(sprt) - 5);

        if ( key_down(RIGHT_KEY) )
            sprite_set_rotation(sprt, sprite_rotation(sprt) + 5);

        if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
        {
            if ( key_down(UP_KEY) )
                sprite_set_scale(sprt, sprite_scale(sprt) + 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_scale(sprt, sprite_scale(sprt) - 0.1);
        }
        else
        {
            if ( key_down(UP_KEY) )
                sprite_set_dy(sprt, sprite_dy(sprt) - 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_dy(sprt, sprite_dy(sprt) + 0.1);
        }

        if ( key_typed(NUM_0_KEY) ) sprite_set_rotation(sprt, 0);
        if ( key_typed(NUM_9_KEY) ) sprite_set_rotation(sprt, 45);

        tri = init_tri;
        tri_b = init_tri_b;
        
        apply_matrix(sprite_location_matrix(sprt), tri);
        apply_matrix(sprite_location_matrix(sprt), tri_b);
        
        fill_triangle(COLOR_GREEN, tri);
        fill_triangle(COLOR_GREEN, tri_b);

        tri = init_tri;
        tri_b = init_tri_b;
        apply_matrix(sprite_location_matrix(s2), tri);
        apply_matrix(sprite_location_matrix(s2), tri_b);
        
        fill_triangle(COLOR_BLUE, tri);
        fill_triangle(COLOR_BLUE, tri_b);
        // FillQuad(RGBAColor(0,0,255,62), q);

        draw_sprite(sprt);
        draw_sprite(s2);
        draw_sprite(s3);
        draw_sprite(s4);
        
        if (sprite_rectangle_collision(sprt, r))
		{
            draw_rectangle(COLOR_RED, r);
		}
        else
		{
            draw_rectangle(COLOR_PURPLE, r);
		}

        draw_bitmap("ufo.png", 400, 300);

        if (sprite_bitmap_collision(sprt, bitmap_named("ufo.png"), 400, 300))
		{
            draw_rectangle(COLOR_PURPLE, 400, 300, bitmap_width(bitmap_named("ufo.png")), bitmap_height(bitmap_named("ufo.png")));
		}

        if (sprite_at(sprt, mouse_position()))
		{
            draw_circle(COLOR_RED, sprite_collision_circle(sprt));
            draw_circle(COLOR_RED, mouse_x(), mouse_y(), 1);
		}
        else
        {
            draw_circle(COLOR_PLUM, mouse_x(), mouse_y(), 1);
            draw_circle(COLOR_GREEN, sprite_collision_circle(sprt));
        }

        update_sprite(sprt);

        if (sprite_collision(sprt, s2))
		{
            draw_circle(COLOR_RED, sprite_collision_circle(s2));
		}

        if (sprite_collision(sprt, s3))
        {
            vector_2d dir = calculate_collision_direction(sprt, s3);
            resolve_collision(sprt, s3, dir);
            draw_rect_perimeter_by_collision(sprite_collision_rectangle(sprt), dir, COLOR_RED, 4);
        }

        if (sprite_collision(sprt, s4))
        {
            vector_2d dir = calculate_collision_direction(sprt, s4);
            resolve_collision(sprt, s4, dir);
            draw_rect_perimeter_by_collision(sprite_collision_rectangle(sprt), dir, COLOR_RED, 4);
        }

        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(sprt));
        draw_rectangle(COLOR_RED, sprite_collision_rectangle(s4));

        draw_line(COLOR_GREEN, line_from(sprite_center_point(sprt), matrix_multiply(rotation_matrix(sprite_rotation(sprt)), vector_multiply(sprite_velocity(sprt), 30.0))));

        refresh_screen(60);
    }
    
    show_mouse();
    
    close_all_windows();
}

void reset_sprite(sprite s)
{
    sprite_set_x(s, 300.0);
    sprite_set_y(s, 300.0);
    sprite_set_rotation(s, 0.0f);
    sprite_set_scale(s, 1.0f);
    sprite_set_dx(s, 0.0);
    sprite_set_dy(s, 0.0);
    sprite_set_collision_kind(s, PIXEL_COLLISIONS);
}

void reset_rectangle(rectangle &r)
{
    r = rectangle_from(300.0, 300.0, 150.0, 50.0);
}

void reset_circle(circle &c)
{
    c = circle_at(300.0, 300.0, 40.0);
}

void reset_triangle(triangle &t)
{
    t = triangle_from(300.0, 300.0, 400.0, 300.0, 350.0, 250.0);
}

void reset_quad(quad &q)
{
    rectangle r = rectangle_from(300, 300, 100, 50);
    q = quad_from(r);
    apply_matrix(matrix_multiply(translation_matrix(0.0, -150.0), rotation_matrix(45.0)), q);
}

void _move_obj_by_vector(sprite& obj, const vector_2d& amount)
{
    sprite_set_x(obj, sprite_x(obj) + amount.x);
    sprite_set_y(obj, sprite_y(obj) + amount.y);
}

void _move_obj_by_vector(rectangle& obj, const vector_2d& amount)
{
    obj.x += amount.x;
    obj.y += amount.y;
}

void _move_obj_by_vector(circle& obj, const vector_2d& amount)
{
    obj.center.x += amount.x;
    obj.center.y += amount.y;
}

void _move_obj_by_vector(triangle& obj, const vector_2d& amount)
{
    obj.points[0].x += amount.x;
    obj.points[0].y += amount.y;
    obj.points[1].x += amount.x;
    obj.points[1].y += amount.y;
    obj.points[2].x += amount.x;
    obj.points[2].y += amount.y;
}

void _move_obj_by_vector(quad& obj, const vector_2d& amount)
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

template <typename T>
void move_obj_by_arrows(T& obj)
{
    if ( key_down(LEFT_KEY) )
    {
        _move_obj_by_vector(obj, DIRECTION_LEFT);
    }
    if ( key_down(RIGHT_KEY) )
    {
        _move_obj_by_vector(obj, DIRECTION_RIGHT);
    }
    if ( key_down(UP_KEY) )
    {
        _move_obj_by_vector(obj, DIRECTION_TOP);
    }
    if ( key_down(DOWN_KEY) )
    {
        _move_obj_by_vector(obj, DIRECTION_BOTTOM);
    }
}

rectangle _object_AABB(const sprite& obj)
{
    return sprite_collision_rectangle(obj);
}

rectangle _object_AABB(const rectangle& obj)
{
    return obj;
}

rectangle _object_AABB(const circle& obj)
{
    return rectangle_around(obj);
}

rectangle _object_AABB(const triangle& obj)
{
    return rectangle_around(obj);
}

rectangle _object_AABB(const quad& obj)
{
    return rectangle_around(obj);
}

template <typename T1, typename T2>
void resolve_and_draw(T1& collider, const T2& collidee, const vector_2d& direction)
{
    constexpr int COLLISION_INDICATOR_WIDTH = 4;
    if (is_zero_vector(direction))
    {
        return;
    }
    
    bool collision = false;
    rectangle perimeter = _object_AABB(collider);

    collision = resolve_collision(collider, collidee, direction);

    if (collision)
    {
        draw_rect_perimeter_by_collision(perimeter, direction, COLOR_RED, COLLISION_INDICATOR_WIDTH);
    }
}

void draw_object(sprite& obj, bool draw_AABB)
{
    draw_sprite(obj);
    if (draw_AABB)
    {
        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(obj));
    }
}

void draw_object(rectangle& obj, bool draw_AABB)
{
    fill_rectangle(COLOR_ORANGE, obj);
    if (draw_AABB)
    {
        draw_rectangle(COLOR_GREEN, obj);
    }
}

void draw_object(circle& obj, bool draw_AABB)
{
    fill_circle(COLOR_ORANGE, obj);
    if (draw_AABB)
    {
        draw_rectangle(COLOR_GREEN, rectangle_around(obj));
    }
}

void draw_object(triangle& obj, bool draw_AABB)
{
    fill_triangle(COLOR_ORANGE, obj);
    if (draw_AABB)
    {
        draw_rectangle(COLOR_GREEN, rectangle_around(obj));
    }
}

void draw_object(quad& obj, bool draw_AABB)
{
    fill_quad(COLOR_ORANGE, obj);
    if (draw_AABB)
    {
        draw_rectangle(COLOR_GREEN, rectangle_around(obj));
    }
}

template <typename T>
void draw_objects(std::vector<T>& objects, bool draw_AABB = false)
{
    for (size_t i = 0; i < objects.size(); i++)
    {
        draw_object(objects[i], draw_AABB);
    }
}

template <typename T>
void multiple_dynamic_resolve_and_draw(T& collider, const sprite sprt_pixel, const sprite sprt_AABB, const rectangle& rect,
    const circle& circ, const triangle& tri, const quad& q)
{
    resolve_and_draw(collider, sprt_pixel, calculate_collision_direction(collider, sprt_pixel));
    resolve_and_draw(collider, sprt_AABB, calculate_collision_direction(collider, sprt_AABB));
    resolve_and_draw(collider, rect, calculate_collision_direction(collider, rect));
    resolve_and_draw(collider, circ, calculate_collision_direction(collider, circ));
    resolve_and_draw(collider, tri, calculate_collision_direction(collider, tri));
    resolve_and_draw(collider, q, calculate_collision_direction(collider, q));

    draw_object(collider, true);
}

vector_2d collision_direction_by_order(size_t i)
{
    if (i > 7)
    {
        i = i % 8;
    }
    
    switch (i)
    {
    case 0:
        return DIRECTION_TOP;
    case 1:
        return DIRECTION_BOTTOM;
    case 2:
        return DIRECTION_LEFT;
    case 3:
        return DIRECTION_RIGHT;
    case 4:
        return DIRECTION_TOP_LEFT;
    case 5:
        return DIRECTION_TOP_RIGHT;
    case 6:
        return DIRECTION_BOTTOM_LEFT;
    case 7:
        return DIRECTION_BOTTOM_RIGHT;
    default:
        return DIRECTION_NONE;
    }
}

template <typename T1, typename T2>
void fixed_resolve_and_draw(T1& collider, const std::vector<T2>& collidees)
{
    vector_2d direction;

    for (size_t i = 0; i < collidees.size(); i++)
    {
        direction = collision_direction_by_order(i);
        resolve_and_draw(collider, collidees[i], direction);
    }
    
    draw_object(collider, true);
}

void multi_object_collision_resolution_test()
{
    object_type collider_type = object_type::SPRITE;
    collision_test_type test_type = collision_test_type::MULTIPLE_DYNAMIC;

    sprite collider_sprt, sprt_pixel, sprt_AABB, sprt_TOP, sprt_BOTTOM, sprt_LEFT,
        sprt_RIGHT, sprt_TOP_LEFT, sprt_TOP_RIGHT, sprt_BOTTOM_LEFT, sprt_BOTTOM_RIGHT;
    bitmap bmp;
    rectangle collider_rect, rect;
    circle collider_circ, circ;
    triangle collider_tri, tri;
    quad collider_quad, q;
    std::vector<sprite> sprites_fixed;
    std::vector<rectangle> rectangles_fixed;
    std::vector<circle> circles_fixed;
    std::vector<triangle> triangles_fixed;
    std::vector<quad> quads_fixed;

    open_window("Object Collision Resolution", 600, 600);

    hide_mouse();

    collider_sprt = create_sprite("rocket_sprt.png");
    reset_sprite(collider_sprt);
    reset_rectangle(collider_rect);
    reset_circle(collider_circ);
    reset_triangle(collider_tri);
    reset_quad(collider_quad);

    sprt_pixel = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_pixel, 100.0);
    sprite_set_y(sprt_pixel, 100.0);
    sprite_set_collision_kind(sprt_pixel, PIXEL_COLLISIONS);

    sprt_AABB = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_AABB, 50.0);
    sprite_set_y(sprt_AABB, 400.0);
    sprite_set_collision_kind(sprt_AABB, AABB_COLLISIONS);

    sprt_TOP = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_TOP, 300.0);
    sprite_set_y(sprt_TOP, 100.0);
    sprite_set_collision_kind(sprt_TOP, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_TOP);

    sprt_BOTTOM = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_BOTTOM, 300.0);
    sprite_set_y(sprt_BOTTOM, 500.0);
    sprite_set_collision_kind(sprt_BOTTOM, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_BOTTOM);

    sprt_LEFT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_LEFT, 100.0);
    sprite_set_y(sprt_LEFT, 300.0);
    sprite_set_collision_kind(sprt_LEFT, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_LEFT);

    sprt_RIGHT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_RIGHT, 500.0);
    sprite_set_y(sprt_RIGHT, 300.0);
    sprite_set_collision_kind(sprt_RIGHT, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_RIGHT);

    sprt_TOP_LEFT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_TOP_LEFT, 100.0);
    sprite_set_y(sprt_TOP_LEFT, 100.0);
    sprite_set_collision_kind(sprt_TOP_LEFT, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_TOP_LEFT);

    sprt_TOP_RIGHT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_TOP_RIGHT, 500.0);
    sprite_set_y(sprt_TOP_RIGHT, 100.0);
    sprite_set_collision_kind(sprt_TOP_RIGHT, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_TOP_RIGHT);

    sprt_BOTTOM_LEFT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_BOTTOM_LEFT, 100.0);
    sprite_set_y(sprt_BOTTOM_LEFT, 500.0);
    sprite_set_collision_kind(sprt_BOTTOM_LEFT, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_BOTTOM_LEFT);

    sprt_BOTTOM_RIGHT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_BOTTOM_RIGHT, 500.0);
    sprite_set_y(sprt_BOTTOM_RIGHT, 500.0);
    sprite_set_collision_kind(sprt_BOTTOM_RIGHT, PIXEL_COLLISIONS);
    sprites_fixed.push_back(sprt_BOTTOM_RIGHT);

    rect = rectangle_from(400.0, 450.0, 100.0, 50.0);

    rectangles_fixed.push_back(rectangle_from(300.0, 100.0, 100.0, 50.0)); // rect_TOP
    rectangles_fixed.push_back(rectangle_from(300.0, 500.0, 100.0, 50.0)); // rect_BOTTOM
    rectangles_fixed.push_back(rectangle_from(100.0, 300.0, 50.0, 100.0)); // rect_LEFT
    rectangles_fixed.push_back(rectangle_from(500.0, 300.0, 50.0, 100.0)); // rect_RIGHT
    rectangles_fixed.push_back(rectangle_from(100.0, 100.0, 50.0, 50.0)); // rect_TOP_LEFT
    rectangles_fixed.push_back(rectangle_from(500.0, 100.0, 50.0, 50.0)); // rect_TOP_RIGHT
    rectangles_fixed.push_back(rectangle_from(100.0, 500.0, 50.0, 50.0)); // rect_BOTTOM_LEFT
    rectangles_fixed.push_back(rectangle_from(500.0, 500.0, 50.0, 50.0)); // rect_BOTTOM_RIGHT

    circ = circle_at(400.0, 300.0, 50.0);

    circles_fixed.push_back(circle_at(300.0, 100.0, 50.0)); // circ_TOP
    circles_fixed.push_back(circle_at(300.0, 500.0, 50.0)); // circ_BOTTOM
    circles_fixed.push_back(circle_at(100.0, 300.0, 50.0)); // circ_LEFT
    circles_fixed.push_back(circle_at(500.0, 300.0, 50.0)); // circ_RIGHT
    circles_fixed.push_back(circle_at(100.0, 100.0, 50.0)); // circ_TOP_LEFT
    circles_fixed.push_back(circle_at(500.0, 100.0, 50.0)); // circ_TOP_RIGHT
    circles_fixed.push_back(circle_at(100.0, 500.0, 50.0)); // circ_BOTTOM_LEFT
    circles_fixed.push_back(circle_at(500.0, 500.0, 50.0)); // circ_BOTTOM_RIGHT

    tri = triangle_from(400.0, 100.0, 500.0, 100.0, 450.0, 50.0);

    triangles_fixed.push_back(triangle_from(300.0, 100.0, 400.0, 100.0, 350.0, 150.0)); // tri_TOP
    triangles_fixed.push_back(triangle_from(300.0, 500.0, 400.0, 500.0, 350.0, 450.0)); // tri_BOTTOM
    triangles_fixed.push_back(triangle_from(100.0, 300.0, 100.0, 400.0, 150.0, 350.0)); // tri_LEFT
    triangles_fixed.push_back(triangle_from(500.0, 300.0, 500.0, 400.0, 450.0, 350.0)); // tri_RIGHT
    triangles_fixed.push_back(triangle_from(100.0, 150.0, 150.0, 100.0, 150.0, 150.0)); // tri_TOP_LEFT
    triangles_fixed.push_back(triangle_from(500.0, 150.0, 450.0, 100.0, 450.0, 150.0)); // tri_TOP_RIGHT
    triangles_fixed.push_back(triangle_from(100.0, 450.0, 150.0, 500.0, 150.0, 450.0)); // tri_BOTTOM_LEFT
    triangles_fixed.push_back(triangle_from(500.0, 450.0, 450.0, 500.0, 450.0, 450.0)); // tri_BOTTOM_RIGHT

    rectangle r = rectangle_from(400, 100, 100, 50);
    q = quad_from(r);
    apply_matrix(matrix_multiply(translation_matrix(0.0, 50.0), rotation_matrix(45.0)), q);

    r = rectangle_from(0.0, 0.0, 100.0, 50.0);
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(300.0, 20.0)), quads_fixed[0]); // quad_TOP
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(300.0, 470.0)), quads_fixed[1]); // quad_BOTTOM
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(50.0, 270.0)), quads_fixed[2]); // quad_LEFT
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(500.0, 270.0)), quads_fixed[3]); // quad_RIGHT
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(50.0, 20.0)), quads_fixed[4]); // quad_TOP_LEFT
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(500.0, 20.0)), quads_fixed[5]); // quad_TOP_RIGHT
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(50.0, 470.0)), quads_fixed[6]); // quad_BOTTOM_LEFT
    quads_fixed.push_back(quad_from(r));
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(500.0, 470.0)), quads_fixed[7]); // quad_BOTTOM_RIGHT

    while (! quit_requested())
    {
        process_events();

        clear_screen(COLOR_WHITE);

        // Change the object type with number keys
        if (key_typed(NUM_1_KEY))
        {
            collider_type = object_type::SPRITE;
            reset_sprite(collider_sprt);
        }
        if (key_typed(NUM_2_KEY))
        {
            collider_type = object_type::RECTANGLE;
            reset_rectangle(collider_rect);
        }
        if (key_typed(NUM_3_KEY))
        {
            collider_type = object_type::CIRCLE;
            reset_circle(collider_circ);
        }
        if (key_typed(NUM_4_KEY))
        {
            collider_type = object_type::TRIANGLE;
            reset_triangle(collider_tri);
        }
        if (key_typed(NUM_5_KEY))
        {
            collider_type = object_type::QUAD;
            reset_quad(collider_quad);
        }
        if (key_typed(NUM_6_KEY))
        {
            test_type = collision_test_type::MULTIPLE_DYNAMIC;
        }
        if (key_typed(NUM_7_KEY))
        {
            test_type = collision_test_type::SPRITE_FIXED;
        }
        if (key_typed(NUM_8_KEY))
        {
            test_type = collision_test_type::RECTANGLE_FIXED;
        }
        if (key_typed(NUM_9_KEY))
        {
            test_type = collision_test_type::CIRCLE_FIXED;
        }
        if (key_typed(NUM_0_KEY))
        {
            test_type = collision_test_type::TRIANGLE_FIXED;
        }
        if (key_typed(MINUS_KEY))
        {
            test_type = collision_test_type::QUAD_FIXED;
        }

        if (collider_type == object_type::SPRITE)
        {
            if ( key_down(LEFT_KEY) )
            sprite_set_rotation(collider_sprt, sprite_rotation(collider_sprt) - 5.0);

            if ( key_down(RIGHT_KEY) )
                sprite_set_rotation(collider_sprt, sprite_rotation(collider_sprt) + 5.0);

            if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
            {
                if ( key_down(UP_KEY) )
                    sprite_set_scale(collider_sprt, sprite_scale(collider_sprt) + 0.1);

                if ( key_down(DOWN_KEY) )
                    sprite_set_scale(collider_sprt, sprite_scale(collider_sprt) - 0.1);
            }
            else
            {
                if ( key_down(UP_KEY) )
                    sprite_set_dy(collider_sprt, sprite_dy(collider_sprt) - 0.1);

                if ( key_down(DOWN_KEY) )
                    sprite_set_dy(collider_sprt, sprite_dy(collider_sprt) + 0.1);
            }

            update_sprite(collider_sprt);
        }
        else if (collider_type == object_type::RECTANGLE)
        {   
            move_obj_by_arrows(collider_rect);
        }
        else if (collider_type == object_type::CIRCLE)
        {
            move_obj_by_arrows(collider_circ);
        }
        else if (collider_type == object_type::TRIANGLE)
        {
            move_obj_by_arrows(collider_tri);
        }
        else if (collider_type == object_type::QUAD)
        {
            move_obj_by_arrows(collider_quad);
        }

        if (test_type == collision_test_type::MULTIPLE_DYNAMIC)
        {
            draw_rectangle(COLOR_RED, sprite_collision_rectangle(sprt_AABB));
            fill_rectangle(COLOR_GREEN, rect);
            fill_circle(COLOR_GREEN, circ);
            fill_triangle(COLOR_GREEN, tri);
            fill_quad(COLOR_GREEN, q);
            draw_sprite(sprt_pixel);
            draw_sprite(sprt_AABB);

            if (collider_type == object_type::SPRITE) // sprite vs. multiple dynamic objects
            {
                multiple_dynamic_resolve_and_draw(collider_sprt, sprt_pixel, sprt_AABB, rect, circ, tri, q);
            }
            else if (collider_type == object_type::RECTANGLE) // rect vs. multiple dynamic objects
            {
                multiple_dynamic_resolve_and_draw(collider_rect, sprt_pixel, sprt_AABB, rect, circ, tri, q);
            }
            else if (collider_type == object_type::CIRCLE) // circle vs. multiple dynamic objects
            {
                multiple_dynamic_resolve_and_draw(collider_circ, sprt_pixel, sprt_AABB, rect, circ, tri, q);
            }
            else if (collider_type == object_type::TRIANGLE) // triangle vs. multiple dynamic objects
            {
                multiple_dynamic_resolve_and_draw(collider_tri, sprt_pixel, sprt_AABB, rect, circ, tri, q);
            }
            else if (collider_type == object_type::QUAD) // quad vs. multiple dynamic objects
            {
                multiple_dynamic_resolve_and_draw(collider_quad, sprt_pixel, sprt_AABB, rect, circ, tri, q);
            }
        }
        else if (test_type == collision_test_type::SPRITE_FIXED)
        {
            draw_objects(sprites_fixed, false);

            if (collider_type == object_type::SPRITE) // sprite vs. fixed sprite objects
            {
                fixed_resolve_and_draw(collider_sprt, sprites_fixed);
            }
            else if (collider_type == object_type::RECTANGLE) // rect vs. fixed sprite objects
            {
                fixed_resolve_and_draw(collider_rect, sprites_fixed);
            }
            else if (collider_type == object_type::CIRCLE) // circle vs. fixed sprite objects
            {
                fixed_resolve_and_draw(collider_circ, sprites_fixed);
            }
            else if (collider_type == object_type::TRIANGLE) // triangle vs. fixed sprite objects
            {
                fixed_resolve_and_draw(collider_tri, sprites_fixed);
            }
            else if (collider_type == object_type::QUAD) // quad vs. fixed sprite objects
            {
                fixed_resolve_and_draw(collider_quad, sprites_fixed);
            }
        }
        else if (test_type == collision_test_type::RECTANGLE_FIXED)
        {
            draw_objects(rectangles_fixed, false);

            if (collider_type == object_type::SPRITE) // sprite vs. fixed rectangle objects
            {
                fixed_resolve_and_draw(collider_sprt, rectangles_fixed);
            }
            else if (collider_type == object_type::RECTANGLE) // rect vs. fixed rectangle objects
            {
                fixed_resolve_and_draw(collider_rect, rectangles_fixed);
            }
            else if (collider_type == object_type::CIRCLE) // circle vs. fixed rectangle objects
            {
                fixed_resolve_and_draw(collider_circ, rectangles_fixed);
            }
            else if (collider_type == object_type::TRIANGLE) // triangle vs. fixed rectangle objects
            {
                fixed_resolve_and_draw(collider_tri, rectangles_fixed);
            }
            else if (collider_type == object_type::QUAD) // quad vs. fixed rectangle objects
            {
                fixed_resolve_and_draw(collider_quad, rectangles_fixed);
            }
        }
        else if (test_type == collision_test_type::CIRCLE_FIXED)
        {
            draw_objects(circles_fixed, false);

            if (collider_type == object_type::SPRITE) // sprite vs. fixed circle objects
            {
                fixed_resolve_and_draw(collider_sprt, circles_fixed);
            }
            else if (collider_type == object_type::RECTANGLE) // rect vs. fixed circle objects
            {
                fixed_resolve_and_draw(collider_rect, circles_fixed);
            }
            else if (collider_type == object_type::CIRCLE) // circle vs. fixed circle objects
            {
                fixed_resolve_and_draw(collider_circ, circles_fixed);
            }
            else if (collider_type == object_type::TRIANGLE) // triangle vs. fixed circle objects
            {
                fixed_resolve_and_draw(collider_tri, circles_fixed);
            }
            else if (collider_type == object_type::QUAD) // quad vs. fixed circle objects
            {
                fixed_resolve_and_draw(collider_quad, circles_fixed);
            }
        }
        else if (test_type == collision_test_type::TRIANGLE_FIXED)
        {
            draw_objects(triangles_fixed, false);

            if (collider_type == object_type::SPRITE) // sprite vs. fixed triangle objects
            {
                fixed_resolve_and_draw(collider_sprt, triangles_fixed);
            }
            else if (collider_type == object_type::RECTANGLE) // rect vs. fixed triangle objects
            {
                fixed_resolve_and_draw(collider_rect, triangles_fixed);
            }
            else if (collider_type == object_type::CIRCLE) // circle vs. fixed triangle objects
            {
                fixed_resolve_and_draw(collider_circ, triangles_fixed);
            }
            else if (collider_type == object_type::TRIANGLE) // triangle vs. fixed triangle objects
            {
                fixed_resolve_and_draw(collider_tri, triangles_fixed);
            }
            else if (collider_type == object_type::QUAD) // quad vs. fixed triangle objects
            {
                fixed_resolve_and_draw(collider_quad, triangles_fixed);
            }
        }
        else if (test_type == collision_test_type::QUAD_FIXED)
        {
            draw_objects(quads_fixed, false);

            if (collider_type == object_type::SPRITE) // sprite vs. fixed quad objects
            {
                fixed_resolve_and_draw(collider_sprt, quads_fixed);
            }
            else if (collider_type == object_type::RECTANGLE) // rect vs. fixed quad objects
            {
                fixed_resolve_and_draw(collider_rect, quads_fixed);
            }
            else if (collider_type == object_type::CIRCLE) // circle vs. fixed quad objects
            {
                fixed_resolve_and_draw(collider_circ, quads_fixed);
            }
            else if (collider_type == object_type::TRIANGLE) // triangle vs. fixed quad objects
            {
                fixed_resolve_and_draw(collider_tri, quads_fixed);
            }
            else if (collider_type == object_type::QUAD) // quad vs. fixed quad objects
            {
                fixed_resolve_and_draw(collider_quad, quads_fixed);
            }
        } // end if

        refresh_screen(60);

    } // end while

    show_mouse();
    close_all_windows();
}

void test_sprite_ray_collision()
{
    window w1 = open_window("Sprite Ray Collision", 800, 600);
    sprite s1 = create_sprite("on_med.png");
    sprite_set_position(s1, point_at(200.0, 200.0));
    sprite_set_rotation(s1, 45.0f);
    sprite s2 = create_sprite("rocket_sprt.png");
    sprite_set_position(s2, point_at(500.0, 100.0));
    sprite s3 = create_sprite("up_pole.png");
    sprite_set_position(s3, point_at(600.0, 300.0));
    sprite_set_rotation(s3, 10.0f);
    point_2d ray_origin = point_at(100, 100);
    vector_2d ray_heading = vector_to(200, 200);
    
    while ( !window_close_requested(w1) ) {
        process_events();
        
        clear_screen(COLOR_WHITE);

        if (key_down(UP_KEY))
            ray_origin.y -= 1.0;
        if (key_down(DOWN_KEY))
            ray_origin.y += 1.0;
        if (key_down(LEFT_KEY))
            ray_origin.x -= 1.0;
        if (key_down(RIGHT_KEY))
            ray_origin.x += 1.0;
        
        bool collision_1 = sprite_ray_collision(s1, ray_origin, ray_heading);
        bool collision_2 = sprite_ray_collision(s2, ray_origin, ray_heading);
        bool collision_3 = sprite_ray_collision(s3, ray_origin, ray_heading);

        draw_sprite(s1);
        if (collision_1)
        {
            fill_circle(COLOR_RED, circle_at(sprite_collision_circle(s1).center, 30.0));
        }

        draw_sprite(s2);
        if (collision_2)
        {
            fill_circle(COLOR_RED, circle_at(sprite_collision_circle(s2).center, 8.0));
        }

        draw_sprite(s3);
        if (collision_3)
        {
            fill_circle(COLOR_RED, circle_at(sprite_collision_circle(s3).center, 30.0));
        }

        ray_heading = vector_point_to_point(ray_origin, mouse_position());
        vector_2d normal_heading = unit_vector(ray_heading);
        draw_line(COLOR_BLACK, ray_origin, point_offset_by(ray_origin, vector_multiply(normal_heading, 800.0)));

        circle mouse_circle = circle_at(mouse_position(), 3.0);
        draw_circle(COLOR_GREEN, mouse_circle);

        circle ray_origin_circle = circle_at(ray_origin, 3.0);
        draw_circle(COLOR_BLUE, ray_origin_circle);
        
        refresh_screen();
    }
    close_window(w1);
}

void run_sprite_test()
{
    sprite_test();
    multi_object_collision_resolution_test();
    test_sprite_ray_collision();
}
