//
//  test_camera.cpp
//  splashkit
//
//  Created by Andrew Cain on 1/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "window_manager.h"
#include "sprites.h"
#include "graphics.h"
#include "camera.h"
#include "input.h"

using namespace splashkit_lib;

void set_keys(key_code keys[], sprite s){
    if ( key_down(keys[0]) ) sprite_set_dx(s, -1);
    else if ( key_down(keys[1]) ) sprite_set_dx(s, 1);
    else sprite_set_dx(s, 0);

    if ( key_down(keys[2]) ) sprite_set_dy(s, -1);
    else if ( key_down(keys[3]) ) sprite_set_dy(s, 1);
    else sprite_set_dy(s, 0);
}

void run_camera_test_single()
{
    window w1 = open_window("Camera Test Single", 600, 600);

    load_bitmap("ufo", "ufo.png");
    sprite s = create_sprite("ufo");
    sprite_set_position(s, {300,300});

    key_code keys [] = {LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY};

    sprite_set_anchor_point(s, bitmap_cell_center(sprite_layer(s, 0)));

    bool follow = true;

    while ( ! window_close_requested(w1) )
    {
        process_events();

        if ( key_typed(F_KEY) )
        {
            follow =  !follow;
        }
        
        set_keys(keys, s);
        update_sprite(s);

        if (follow){
            center_camera_on(s, 0, 0);
        }else{
            set_camera_x(0);
            set_camera_y(0);
        }

        clear_screen(COLOR_WHITE);

        fill_rectangle(COLOR_RED, 0, 0, 10, 10);
        draw_rectangle(COLOR_RED, 0, screen_height() - 10, 10, 10);
        fill_circle(COLOR_GREEN, screen_width() - 10, 10, 10);
        draw_circle(COLOR_GREEN, screen_width() - 10, screen_height() - 10, 10);

        draw_triangle(COLOR_AQUA, screen_width() / 2, 0, 0, screen_height(), screen_width(), screen_height());

        draw_sprite(s);

        refresh_screen();
    }

    close_window(w1);
}
