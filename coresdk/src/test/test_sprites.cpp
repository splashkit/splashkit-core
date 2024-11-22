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
    switch (segment)
    {
    case sprite_perimeter_segment::TOP_LEFT:
        draw_line(clr, sprite_x(s), sprite_y(s), sprite_x(s) + sprite_width(s) / 3, sprite_y(s), option_line_width(line_width));
        break;
    case sprite_perimeter_segment::TOP_CENTER:
        draw_line(clr, sprite_x(s) + sprite_width(s) / 3, sprite_y(s), sprite_x(s) + 2 * sprite_width(s) / 3, sprite_y(s), option_line_width(line_width));
        break;
    case sprite_perimeter_segment::TOP_RIGHT:
        draw_line(clr, sprite_x(s) + 2 * sprite_width(s) / 3, sprite_y(s), sprite_x(s) + sprite_width(s), sprite_y(s), option_line_width(line_width));
        break;
    case sprite_perimeter_segment::BOTTOM_LEFT:
        draw_line(clr, sprite_x(s), sprite_y(s) + sprite_height(s), sprite_x(s) + sprite_width(s) / 3, sprite_y(s) + sprite_height(s), option_line_width(line_width));
        break;
    case sprite_perimeter_segment::BOTTOM_CENTER:
        draw_line(clr, sprite_x(s) + sprite_width(s) / 3, sprite_y(s) + sprite_height(s), sprite_x(s) + 2 * sprite_width(s) / 3, sprite_y(s) + sprite_height(s), option_line_width(line_width));
        break;
    case sprite_perimeter_segment::BOTTOM_RIGHT:
        draw_line(clr, sprite_x(s) + 2 * sprite_width(s) / 3, sprite_y(s) + sprite_height(s), sprite_x(s) + sprite_width(s), sprite_y(s) + sprite_height(s), option_line_width(line_width));
        break;
    case sprite_perimeter_segment::LEFT_TOP:
        draw_line(clr, sprite_x(s), sprite_y(s), sprite_x(s), sprite_y(s) + sprite_height(s) / 3, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::LEFT_CENTER:
        draw_line(clr, sprite_x(s), sprite_y(s) + sprite_height(s) / 3, sprite_x(s), sprite_y(s) + 2 * sprite_height(s) / 3, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::LEFT_BOTTOM:
        draw_line(clr, sprite_x(s), sprite_y(s) + 2 * sprite_height(s) / 3, sprite_x(s), sprite_y(s) + sprite_height(s), option_line_width(line_width));
        break;
    case sprite_perimeter_segment::RIGHT_TOP:
        draw_line(clr, sprite_x(s) + sprite_width(s), sprite_y(s), sprite_x(s) + sprite_width(s), sprite_y(s) + sprite_height(s) / 3, option_line_width(line_width));
        break;
    case sprite_perimeter_segment::RIGHT_CENTER:
        draw_line(clr, sprite_x(s) + sprite_width(s), sprite_y(s) + sprite_height(s) / 3, sprite_x(s) + sprite_width(s), sprite_y(s) + 2 * sprite_height(s) / 3, option_line_width(line_width));
        break;
    default: // case sprite_perimeter_segment::RIGHT_BOTTOM:
        draw_line(clr, sprite_x(s) + sprite_width(s), sprite_y(s) + 2 * sprite_height(s) / 3, sprite_x(s) + sprite_width(s), sprite_y(s) + sprite_height(s), option_line_width(line_width));
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

void run_sprite_test()
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
    sprite_set_scale(s4, 2.0f);

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
            draw_sprite_perimeter_by_collision(sprt, dir, COLOR_RED, 3);
        }

        if (sprite_collision(sprt, s4))
        {
            collision_direction dir = sprite_collision_direction(sprt, s4);
            resolve_sprite_collision(sprt, s4, dir);
            draw_sprite_perimeter_by_collision(sprt, dir, COLOR_RED, 3);
        }

        draw_rectangle(COLOR_GREEN, sprite_collision_rectangle(sprt));
        draw_rectangle(COLOR_RED, sprite_collision_rectangle(s4));

        draw_line(COLOR_GREEN, line_from(center_point(sprt), matrix_multiply(rotation_matrix(sprite_rotation(sprt)), vector_multiply(sprite_velocity(sprt), 30.0))));

        refresh_screen(60);
    }
    
    show_mouse();
    
    close_all_windows();
}
