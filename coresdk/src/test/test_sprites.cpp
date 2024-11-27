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

using namespace splashkit_lib;

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

void draw_sprite_perimeter_segment(sprite s, sprite_perimeter_segment segment, color clr, int line_width)
{
    rectangle r = sprite_collision_rectangle(s);
    
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

void draw_sprite_perimeter_by_collision(sprite s, collision_direction direction, color clr, int line_width)
{
    switch (direction)
    {
    case collision_direction::TOP:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::TOP_LEFT, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::TOP_CENTER, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::TOP_RIGHT, clr, line_width);
        break;
    case collision_direction::BOTTOM:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::BOTTOM_LEFT, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::BOTTOM_CENTER, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::BOTTOM_RIGHT, clr, line_width);
        break;
    case collision_direction::LEFT:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::LEFT_TOP, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::LEFT_CENTER, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::LEFT_BOTTOM, clr, line_width);
        break;
    case collision_direction::RIGHT:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::RIGHT_TOP, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::RIGHT_CENTER, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::RIGHT_BOTTOM, clr, line_width);
        break;
    case collision_direction::TOP_LEFT:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::TOP_LEFT, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::LEFT_TOP, clr, line_width);
        break;
    case collision_direction::TOP_RIGHT:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::TOP_RIGHT, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::RIGHT_TOP, clr, line_width);
        break;
    case collision_direction::BOTTOM_LEFT:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::BOTTOM_LEFT, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::LEFT_BOTTOM, clr, line_width);
        break;
    case collision_direction::BOTTOM_RIGHT:
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::BOTTOM_RIGHT, clr, line_width);
        draw_sprite_perimeter_segment(s, sprite_perimeter_segment::RIGHT_BOTTOM, clr, line_width);
        break;
    };
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
            collision_direction dir = sprite_collision_direction(sprt, s3);
            resolve_sprite_collision(sprt, s3, dir);
            draw_sprite_perimeter_by_collision(sprt, dir, COLOR_RED, 4);
        }

        if (sprite_collision(sprt, s4))
        {
            collision_direction dir = sprite_collision_direction(sprt, s4);
            resolve_sprite_collision(sprt, s4, dir);
            draw_sprite_perimeter_by_collision(sprt, dir, COLOR_RED, 4);
        }

        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(sprt));
        draw_rectangle(COLOR_RED, sprite_collision_rectangle(s4));

        draw_line(COLOR_GREEN, line_from(center_point(sprt), matrix_multiply(rotation_matrix(sprite_rotation(sprt)), vector_multiply(sprite_velocity(sprt), 30.0))));

        refresh_screen(60);
    }
    
    show_mouse();
    
    close_all_windows();
}

void sprite_collision_resolution_test()
{
    sprite collider, sprt_pixel, sprt_AABB;
    bitmap bmp;
    rectangle rect;
    circle circ;
    triangle tri;
    quad q;

    open_window("Sprite Collision Resolution", 600, 600);

    hide_mouse();

    collider = create_sprite("rocket_sprt.png");
    sprite_set_x(collider, 300.0);
    sprite_set_y(collider, 300.0);
    sprite_set_collision_kind(collider, PIXEL_COLLISIONS);

    sprt_pixel = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_pixel, 100.0);
    sprite_set_y(sprt_pixel, 100.0);
    sprite_set_collision_kind(sprt_pixel, PIXEL_COLLISIONS);

    sprt_AABB = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_AABB, 50.0);
    sprite_set_y(sprt_AABB, 400.0);
    sprite_set_collision_kind(sprt_AABB, AABB_COLLISIONS);

    rect = rectangle_from(400.0, 450.0, 100.0, 50.0);
    circ = circle_at(400.0, 300.0, 50.0);
    tri = triangle_from(400.0, 100.0, 500.0, 100.0, 450.0, 50.0);

    rectangle r = rectangle_from(400, 100, 100, 50);
    q = quad_from(r);
    apply_matrix(matrix_multiply(translation_matrix(0.0, 50.0), rotation_matrix(45.0)), q);

    while (! quit_requested())
    {
        process_events();

        clear_screen(COLOR_WHITE);

        if ( key_down(LEFT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) - 5.0);

        if ( key_down(RIGHT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) + 5.0);

        if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
        {
            if ( key_down(UP_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) + 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) - 0.1);
        }
        else
        {
            if ( key_down(UP_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) - 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) + 0.1);
        }

        update_sprite(collider);

        draw_rectangle(COLOR_RED, sprite_collision_rectangle(sprt_AABB));
        fill_rectangle(COLOR_GREEN, rect);
        fill_circle(COLOR_GREEN, circ);
        fill_triangle(COLOR_GREEN, tri);
        fill_quad(COLOR_GREEN, q);
        draw_sprite(sprt_pixel);
        draw_sprite(sprt_AABB);

        if (sprite_collision(collider, sprt_pixel))
        {
            collision_direction dir = sprite_collision_direction(collider, sprt_pixel);
            resolve_sprite_collision(collider, sprt_pixel, dir);
            draw_sprite_perimeter_by_collision(collider, dir, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_AABB))
        {
            collision_direction dir = sprite_collision_direction(collider, sprt_AABB);
            resolve_sprite_collision(collider, sprt_AABB, dir);
            draw_sprite_perimeter_by_collision(collider, dir, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect))
        {
            collision_direction dir = sprite_collision_direction(collider, rect);
            resolve_sprite_collision(collider, rect, dir);
            draw_sprite_perimeter_by_collision(collider, dir, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ))
        {
            collision_direction dir = sprite_collision_direction(collider, circ);
            resolve_sprite_collision(collider, circ, dir);
            draw_sprite_perimeter_by_collision(collider, dir, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri))
        {
            collision_direction dir = sprite_collision_direction(collider, tri);
            resolve_sprite_collision(collider, tri, dir);
            draw_sprite_perimeter_by_collision(collider, dir, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, q))
        {
            collision_direction dir = sprite_collision_direction(collider, q);
            resolve_sprite_collision(collider, q, dir);
            draw_sprite_perimeter_by_collision(collider, dir, COLOR_RED, 4);
        }

        draw_sprite(collider);
        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(collider));

        refresh_screen(60);
    }

    show_mouse();

    close_all_windows();
}

void sprite_sprite_collision_resolution_direction_test()
{
    sprite collider, sprt_TOP, sprt_BOTTOM, sprt_LEFT, sprt_RIGHT, sprt_TOP_LEFT,
        sprt_TOP_RIGHT, sprt_BOTTOM_LEFT, sprt_BOTTOM_RIGHT;

    open_window("Sprite-Sprite Collision Resolution Fixed Direction", 600, 600);

    hide_mouse();

    collider = create_sprite("rocket_sprt.png");
    sprite_set_x(collider, 300.0);
    sprite_set_y(collider, 300.0);
    sprite_set_collision_kind(collider, PIXEL_COLLISIONS);

    sprt_TOP = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_TOP, 300.0);
    sprite_set_y(sprt_TOP, 100.0);
    sprite_set_collision_kind(sprt_TOP, PIXEL_COLLISIONS);

    sprt_BOTTOM = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_BOTTOM, 300.0);
    sprite_set_y(sprt_BOTTOM, 500.0);
    sprite_set_collision_kind(sprt_BOTTOM, PIXEL_COLLISIONS);

    sprt_LEFT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_LEFT, 100.0);
    sprite_set_y(sprt_LEFT, 300.0);
    sprite_set_collision_kind(sprt_LEFT, PIXEL_COLLISIONS);

    sprt_RIGHT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_RIGHT, 500.0);
    sprite_set_y(sprt_RIGHT, 300.0);
    sprite_set_collision_kind(sprt_RIGHT, PIXEL_COLLISIONS);

    sprt_TOP_LEFT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_TOP_LEFT, 100.0);
    sprite_set_y(sprt_TOP_LEFT, 100.0);
    sprite_set_collision_kind(sprt_TOP_LEFT, PIXEL_COLLISIONS);

    sprt_TOP_RIGHT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_TOP_RIGHT, 500.0);
    sprite_set_y(sprt_TOP_RIGHT, 100.0);
    sprite_set_collision_kind(sprt_TOP_RIGHT, PIXEL_COLLISIONS);

    sprt_BOTTOM_LEFT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_BOTTOM_LEFT, 100.0);
    sprite_set_y(sprt_BOTTOM_LEFT, 500.0);
    sprite_set_collision_kind(sprt_BOTTOM_LEFT, PIXEL_COLLISIONS);

    sprt_BOTTOM_RIGHT = create_sprite("rocket_sprt.png");
    sprite_set_x(sprt_BOTTOM_RIGHT, 500.0);
    sprite_set_y(sprt_BOTTOM_RIGHT, 500.0);
    sprite_set_collision_kind(sprt_BOTTOM_RIGHT, PIXEL_COLLISIONS);

    while (! quit_requested())
    {
        process_events();

        clear_screen(COLOR_WHITE);

        if ( key_down(LEFT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) - 5.0);

        if ( key_down(RIGHT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) + 5.0);

        if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
        {
            if ( key_down(UP_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) + 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) - 0.1);
        }
        else
        {
            if ( key_down(UP_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) - 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) + 0.1);
        }

        update_sprite(collider);

        draw_sprite(sprt_TOP);
        draw_sprite(sprt_BOTTOM);
        draw_sprite(sprt_LEFT);
        draw_sprite(sprt_RIGHT);
        draw_sprite(sprt_TOP_LEFT);
        draw_sprite(sprt_TOP_RIGHT);
        draw_sprite(sprt_BOTTOM_LEFT);
        draw_sprite(sprt_BOTTOM_RIGHT);

        if (sprite_collision(collider, sprt_TOP))
        {
            resolve_sprite_collision(collider, sprt_TOP, collision_direction::TOP);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_BOTTOM))
        {
            resolve_sprite_collision(collider, sprt_BOTTOM, collision_direction::BOTTOM);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_LEFT))
        {
            resolve_sprite_collision(collider, sprt_LEFT, collision_direction::LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::LEFT, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_RIGHT))
        {
            resolve_sprite_collision(collider, sprt_RIGHT, collision_direction::RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::RIGHT, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_TOP_LEFT))
        {
            resolve_sprite_collision(collider, sprt_TOP_LEFT, collision_direction::TOP_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_LEFT, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_TOP_RIGHT))
        {
            resolve_sprite_collision(collider, sprt_TOP_RIGHT, collision_direction::TOP_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_RIGHT, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_BOTTOM_LEFT))
        {
            resolve_sprite_collision(collider, sprt_BOTTOM_LEFT, collision_direction::BOTTOM_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_LEFT, COLOR_RED, 4);
        }
        if (sprite_collision(collider, sprt_BOTTOM_RIGHT))
        {
            resolve_sprite_collision(collider, sprt_BOTTOM_RIGHT, collision_direction::BOTTOM_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_RIGHT, COLOR_RED, 4);
        }

        draw_sprite(collider);
        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(collider));

        refresh_screen(60);
    }

    show_mouse();

    close_all_windows();
}

void sprite_rectangle_collision_resolution_direction_test()
{
    sprite collider;
    rectangle rect_TOP, rect_BOTTOM, rect_LEFT, rect_RIGHT, rect_TOP_LEFT,
        rect_TOP_RIGHT, rect_BOTTOM_LEFT, rect_BOTTOM_RIGHT;

    open_window("Sprite-Rectangle Collision Resolution Fixed Direction", 600, 600);

    hide_mouse();

    collider = create_sprite("rocket_sprt.png");
    sprite_set_x(collider, 300.0);
    sprite_set_y(collider, 300.0);
    sprite_set_collision_kind(collider, PIXEL_COLLISIONS);

    rect_TOP = rectangle_from(300.0, 100.0, 100.0, 50.0);
    rect_BOTTOM = rectangle_from(300.0, 500.0, 100.0, 50.0);
    rect_LEFT = rectangle_from(100.0, 300.0, 50.0, 100.0);
    rect_RIGHT = rectangle_from(500.0, 300.0, 50.0, 100.0);
    rect_TOP_LEFT = rectangle_from(100.0, 100.0, 50.0, 50.0);
    rect_TOP_RIGHT = rectangle_from(500.0, 100.0, 50.0, 50.0);
    rect_BOTTOM_LEFT = rectangle_from(100.0, 500.0, 50.0, 50.0);
    rect_BOTTOM_RIGHT = rectangle_from(500.0, 500.0, 50.0, 50.0);

    while (! quit_requested())
    {
        process_events();

        clear_screen(COLOR_WHITE);

        if ( key_down(LEFT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) - 5.0);

        if ( key_down(RIGHT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) + 5.0);

        if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
        {
            if ( key_down(UP_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) + 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) - 0.1);
        }
        else
        {
            if ( key_down(UP_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) - 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) + 0.1);
        }

        update_sprite(collider);

        fill_rectangle(COLOR_GREEN, rect_TOP);
        fill_rectangle(COLOR_GREEN, rect_BOTTOM);
        fill_rectangle(COLOR_GREEN, rect_LEFT);
        fill_rectangle(COLOR_GREEN, rect_RIGHT);
        fill_rectangle(COLOR_GREEN, rect_TOP_LEFT);
        fill_rectangle(COLOR_GREEN, rect_TOP_RIGHT);
        fill_rectangle(COLOR_GREEN, rect_BOTTOM_LEFT);
        fill_rectangle(COLOR_GREEN, rect_BOTTOM_RIGHT);

        if (sprite_rectangle_collision(collider, rect_TOP))
        {
            resolve_sprite_collision(collider, rect_TOP, collision_direction::TOP);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect_BOTTOM))
        {
            resolve_sprite_collision(collider, rect_BOTTOM, collision_direction::BOTTOM);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect_LEFT))
        {
            resolve_sprite_collision(collider, rect_LEFT, collision_direction::LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::LEFT, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect_RIGHT))
        {
            resolve_sprite_collision(collider, rect_RIGHT, collision_direction::RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::RIGHT, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect_TOP_LEFT))
        {
            resolve_sprite_collision(collider, rect_TOP_LEFT, collision_direction::TOP_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_LEFT, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect_TOP_RIGHT))
        {
            resolve_sprite_collision(collider, rect_TOP_RIGHT, collision_direction::TOP_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_RIGHT, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect_BOTTOM_LEFT))
        {
            resolve_sprite_collision(collider, rect_BOTTOM_LEFT, collision_direction::BOTTOM_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_LEFT, COLOR_RED, 4);
        }
        if (sprite_rectangle_collision(collider, rect_BOTTOM_RIGHT))
        {
            resolve_sprite_collision(collider, rect_BOTTOM_RIGHT, collision_direction::BOTTOM_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_RIGHT, COLOR_RED, 4);
        }

        draw_sprite(collider);
        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(collider));

        refresh_screen(60);
    }

    show_mouse();

    close_all_windows();
}

void sprite_circle_collision_resolution_direction_test()
{
    sprite collider;
    circle circ_TOP, circ_BOTTOM, circ_LEFT, circ_RIGHT, circ_TOP_LEFT,
        circ_TOP_RIGHT, circ_BOTTOM_LEFT, circ_BOTTOM_RIGHT;

    open_window("Sprite-Circle Collision Resolution Fixed Direction", 600, 600);

    hide_mouse();

    collider = create_sprite("rocket_sprt.png");
    sprite_set_x(collider, 300.0);
    sprite_set_y(collider, 300.0);
    sprite_set_collision_kind(collider, PIXEL_COLLISIONS);

    circ_TOP = circle_at(300.0, 100.0, 50.0);
    circ_BOTTOM = circle_at(300.0, 500.0, 50.0);
    circ_LEFT = circle_at(100.0, 300.0, 50.0);
    circ_RIGHT = circle_at(500.0, 300.0, 50.0);
    circ_TOP_LEFT = circle_at(100.0, 100.0, 50.0);
    circ_TOP_RIGHT = circle_at(500.0, 100.0, 50.0);
    circ_BOTTOM_LEFT = circle_at(100.0, 500.0, 50.0);
    circ_BOTTOM_RIGHT = circle_at(500.0, 500.0, 50.0);

    while (! quit_requested())
    {
        process_events();

        clear_screen(COLOR_WHITE);

        if ( key_down(LEFT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) - 5.0);

        if ( key_down(RIGHT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) + 5.0);

        if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
        {
            if ( key_down(UP_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) + 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) - 0.1);
        }
        else
        {
            if ( key_down(UP_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) - 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) + 0.1);
        }

        update_sprite(collider);

        fill_circle(COLOR_GREEN, circ_TOP);
        fill_circle(COLOR_GREEN, circ_BOTTOM);
        fill_circle(COLOR_GREEN, circ_LEFT);
        fill_circle(COLOR_GREEN, circ_RIGHT);
        fill_circle(COLOR_GREEN, circ_TOP_LEFT);
        fill_circle(COLOR_GREEN, circ_TOP_RIGHT);
        fill_circle(COLOR_GREEN, circ_BOTTOM_LEFT);
        fill_circle(COLOR_GREEN, circ_BOTTOM_RIGHT);

        if (sprite_circle_collision(collider, circ_TOP))
        {
            resolve_sprite_collision(collider, circ_TOP, collision_direction::TOP);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ_BOTTOM))
        {
            resolve_sprite_collision(collider, circ_BOTTOM, collision_direction::BOTTOM);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ_LEFT))
        {
            resolve_sprite_collision(collider, circ_LEFT, collision_direction::LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::LEFT, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ_RIGHT))
        {
            resolve_sprite_collision(collider, circ_RIGHT, collision_direction::RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::RIGHT, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ_TOP_LEFT))
        {
            resolve_sprite_collision(collider, circ_TOP_LEFT, collision_direction::TOP_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_LEFT, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ_TOP_RIGHT))
        {
            resolve_sprite_collision(collider, circ_TOP_RIGHT, collision_direction::TOP_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_RIGHT, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ_BOTTOM_LEFT))
        {
            resolve_sprite_collision(collider, circ_BOTTOM_LEFT, collision_direction::BOTTOM_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_LEFT, COLOR_RED, 4);
        }
        if (sprite_circle_collision(collider, circ_BOTTOM_RIGHT))
        {
            resolve_sprite_collision(collider, circ_BOTTOM_RIGHT, collision_direction::BOTTOM_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_RIGHT, COLOR_RED, 4);
        }

        draw_sprite(collider);
        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(collider));

        refresh_screen(60);
    }

    show_mouse();

    close_all_windows();
}

void sprite_triangle_collision_resolution_direction_test()
{
    sprite collider;
    triangle tri_TOP, tri_BOTTOM, tri_LEFT, tri_RIGHT, tri_TOP_LEFT,
        tri_TOP_RIGHT, tri_BOTTOM_LEFT, tri_BOTTOM_RIGHT;

    open_window("Sprite-Triangle Collision Resolution Fixed Direction", 600, 600);

    hide_mouse();

    collider = create_sprite("rocket_sprt.png");
    sprite_set_x(collider, 300.0);
    sprite_set_y(collider, 300.0);
    sprite_set_collision_kind(collider, PIXEL_COLLISIONS);

    tri_TOP = triangle_from(300.0, 100.0, 400.0, 100.0, 350.0, 150.0);
    tri_BOTTOM = triangle_from(300.0, 500.0, 400.0, 500.0, 350.0, 450.0);
    tri_LEFT = triangle_from(100.0, 300.0, 100.0, 400.0, 150.0, 350.0);
    tri_RIGHT = triangle_from(500.0, 300.0, 500.0, 400.0, 450.0, 350.0);
    tri_TOP_LEFT = triangle_from(100.0, 150.0, 150.0, 100.0, 150.0, 150.0);
    tri_TOP_RIGHT = triangle_from(500.0, 150.0, 450.0, 100.0, 450.0, 150.0);
    tri_BOTTOM_LEFT = triangle_from(100.0, 450.0, 150.0, 500.0, 150.0, 450.0);
    tri_BOTTOM_RIGHT = triangle_from(500.0, 450.0, 450.0, 500.0, 450.0, 450.0);

    while (! quit_requested())
    {
        process_events();

        clear_screen(COLOR_WHITE);

        if ( key_down(LEFT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) - 5.0);

        if ( key_down(RIGHT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) + 5.0);

        if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
        {
            if ( key_down(UP_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) + 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) - 0.1);
        }
        else
        {
            if ( key_down(UP_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) - 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) + 0.1);
        }

        update_sprite(collider);

        fill_triangle(COLOR_GREEN, tri_TOP);
        fill_triangle(COLOR_GREEN, tri_BOTTOM);
        fill_triangle(COLOR_GREEN, tri_LEFT);
        fill_triangle(COLOR_GREEN, tri_RIGHT);
        fill_triangle(COLOR_GREEN, tri_TOP_LEFT);
        fill_triangle(COLOR_GREEN, tri_TOP_RIGHT);
        fill_triangle(COLOR_GREEN, tri_BOTTOM_LEFT);
        fill_triangle(COLOR_GREEN, tri_BOTTOM_RIGHT);

        if (sprite_triangle_collision(collider, tri_TOP))
        {
            resolve_sprite_collision(collider, tri_TOP, collision_direction::TOP);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri_BOTTOM))
        {
            resolve_sprite_collision(collider, tri_BOTTOM, collision_direction::BOTTOM);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri_LEFT))
        {
            resolve_sprite_collision(collider, tri_LEFT, collision_direction::LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::LEFT, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri_RIGHT))
        {
            resolve_sprite_collision(collider, tri_RIGHT, collision_direction::RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::RIGHT, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri_TOP_LEFT))
        {
            resolve_sprite_collision(collider, tri_TOP_LEFT, collision_direction::TOP_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_LEFT, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri_TOP_RIGHT))
        {
            resolve_sprite_collision(collider, tri_TOP_RIGHT, collision_direction::TOP_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_RIGHT, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri_BOTTOM_LEFT))
        {
            resolve_sprite_collision(collider, tri_BOTTOM_LEFT, collision_direction::BOTTOM_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_LEFT, COLOR_RED, 4);
        }
        if (sprite_triangle_collision(collider, tri_BOTTOM_RIGHT))
        {
            resolve_sprite_collision(collider, tri_BOTTOM_RIGHT, collision_direction::BOTTOM_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_RIGHT, COLOR_RED, 4);
        }

        draw_sprite(collider);
        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(collider));

        refresh_screen(60);
    }

    show_mouse();

    close_all_windows();
}

void sprite_quad_collision_resolution_direction_test()
{
    sprite collider;
    quad quad_TOP, quad_BOTTOM, quad_LEFT, quad_RIGHT, quad_TOP_LEFT,
        quad_TOP_RIGHT, quad_BOTTOM_LEFT, quad_BOTTOM_RIGHT;

    open_window("Sprite-Quad Collision Resolution Fixed Direction", 600, 600);

    hide_mouse();

    collider = create_sprite("rocket_sprt.png");
    sprite_set_x(collider, 300.0);
    sprite_set_y(collider, 300.0);
    sprite_set_collision_kind(collider, PIXEL_COLLISIONS);

    rectangle r = rectangle_from(0.0, 0.0, 100.0, 50.0);
    quad_TOP = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(300.0, 20.0)), quad_TOP);
    quad_BOTTOM = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(300.0, 470.0)), quad_BOTTOM);
    quad_LEFT = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(50.0, 270.0)), quad_LEFT);
    quad_RIGHT = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(500.0, 270.0)), quad_RIGHT);
    quad_TOP_LEFT = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(50.0, 20.0)), quad_TOP_LEFT);
    quad_TOP_RIGHT = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(500.0, 20.0)), quad_TOP_RIGHT);
    quad_BOTTOM_LEFT = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(50.0, 470.0)), quad_BOTTOM_LEFT);
    quad_BOTTOM_RIGHT = quad_from(r);
    apply_matrix(matrix_multiply(rotation_matrix(45.0), translation_matrix(500.0, 470.0)), quad_BOTTOM_RIGHT);

    while (! quit_requested())
    {
        process_events();

        clear_screen(COLOR_WHITE);

        if ( key_down(LEFT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) - 5.0);

        if ( key_down(RIGHT_KEY) )
            sprite_set_rotation(collider, sprite_rotation(collider) + 5.0);

        if ( key_down(LEFT_SHIFT_KEY) or key_down(RIGHT_SHIFT_KEY) )
        {
            if ( key_down(UP_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) + 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_scale(collider, sprite_scale(collider) - 0.1);
        }
        else
        {
            if ( key_down(UP_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) - 0.1);

            if ( key_down(DOWN_KEY) )
                sprite_set_dy(collider, sprite_dy(collider) + 0.1);
        }

        update_sprite(collider);

        fill_quad(COLOR_GREEN, quad_TOP);
        fill_quad(COLOR_GREEN, quad_BOTTOM);
        fill_quad(COLOR_GREEN, quad_LEFT);
        fill_quad(COLOR_GREEN, quad_RIGHT);
        fill_quad(COLOR_GREEN, quad_TOP_LEFT);
        fill_quad(COLOR_GREEN, quad_TOP_RIGHT);
        fill_quad(COLOR_GREEN, quad_BOTTOM_LEFT);
        fill_quad(COLOR_GREEN, quad_BOTTOM_RIGHT);

        if (sprite_quad_collision(collider, quad_TOP))
        {
            resolve_sprite_collision(collider, quad_TOP, collision_direction::TOP);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, quad_BOTTOM))
        {
            resolve_sprite_collision(collider, quad_BOTTOM, collision_direction::BOTTOM);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, quad_LEFT))
        {
            resolve_sprite_collision(collider, quad_LEFT, collision_direction::LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::LEFT, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, quad_RIGHT))
        {
            resolve_sprite_collision(collider, quad_RIGHT, collision_direction::RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::RIGHT, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, quad_TOP_LEFT))
        {
            resolve_sprite_collision(collider, quad_TOP_LEFT, collision_direction::TOP_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_LEFT, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, quad_TOP_RIGHT))
        {
            resolve_sprite_collision(collider, quad_TOP_RIGHT, collision_direction::TOP_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::TOP_RIGHT, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, quad_BOTTOM_LEFT))
        {
            resolve_sprite_collision(collider, quad_BOTTOM_LEFT, collision_direction::BOTTOM_LEFT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_LEFT, COLOR_RED, 4);
        }
        if (sprite_quad_collision(collider, quad_BOTTOM_RIGHT))
        {
            resolve_sprite_collision(collider, quad_BOTTOM_RIGHT, collision_direction::BOTTOM_RIGHT);
            draw_sprite_perimeter_by_collision(collider, collision_direction::BOTTOM_RIGHT, COLOR_RED, 4);
        }

        draw_sprite(collider);
        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(collider));

        refresh_screen(60);
    }

    show_mouse();

    close_all_windows();
}

void run_sprite_test()
{
    // sprite_test();
    sprite_collision_resolution_test();
    sprite_sprite_collision_resolution_direction_test();
    sprite_rectangle_collision_resolution_direction_test();
    sprite_circle_collision_resolution_direction_test();
    sprite_triangle_collision_resolution_direction_test();
    sprite_quad_collision_resolution_direction_test();
}
