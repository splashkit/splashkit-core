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
#include <vector>

using namespace splashkit_lib;

void run_camera_test()
{
    window w1 = open_window("Camera Test", 600, 600);

    load_bitmap("ufo", "ufo.png");
    sprite s1 = create_sprite("ufo");
    sprite s2 = create_sprite("ufo");
    sprite s3 = create_sprite("ufo");

    sprite_set_position(s1, screen_center());
    sprite_set_position(s2, screen_center());
    sprite_set_position(s3, screen_center());

    sprite arr[3] = {s1, s2, s3};

    std::vector<sprite> vec_arr;
    vec_arr.push_back(s1);
    vec_arr.push_back(s2);
    vec_arr.push_back(s3);

    sprite_set_anchor_point(s1, bitmap_cell_center(sprite_layer(s1, 0)));

    bool follow = true;

    while ( ! window_close_requested(w1) )
    {
        process_events();

        if ( key_down( LEFT_KEY) ) sprite_set_dx(s1, -1);
        else if ( key_down( RIGHT_KEY) ) sprite_set_dx(s1, 1);
        else sprite_set_dx(s1, 0);

        if ( key_down( UP_KEY) ) sprite_set_dy(s1, -1);
        else if ( key_down( DOWN_KEY) ) sprite_set_dy(s1, 1);
        else sprite_set_dy(s1, 0);


        if ( key_down( A_KEY) ) sprite_set_dx(s2, -1);
        else if ( key_down( D_KEY) ) sprite_set_dx(s2, 1);
        else sprite_set_dx(s2, 0);

        if ( key_down( W_KEY) ) sprite_set_dy(s2, -1);
        else if ( key_down( S_KEY) ) sprite_set_dy(s2, 1);
        else sprite_set_dy(s2, 0);


        if ( key_down( J_KEY) ) sprite_set_dx(s3, -1);
        else if ( key_down( L_KEY) ) sprite_set_dx(s3, 1);
        else sprite_set_dx(s3, 0);

        if ( key_down( I_KEY) ) sprite_set_dy(s3, -1);
        else if ( key_down( K_KEY) ) sprite_set_dy(s3, 1);
        else sprite_set_dy(s3, 0);

        if ( key_typed(F_KEY) )
        {
            follow = not follow;
        }

        update_sprite(s1);
        update_sprite(s2);
        update_sprite(s3);

        if ( follow ){
            center_camera_on(vec_arr, 0, 0);
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

        draw_sprite(s1);
        draw_sprite(s2);
        draw_sprite(s3);
        refresh_screen();
    }

    close_window(w1);
}
