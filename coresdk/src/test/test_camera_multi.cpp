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

void set_keys(std::vector<key_code> keys, sprite s){
    if ( key_down(keys[0]) ) sprite_set_dx(s, -1);
    else if ( key_down(keys[1]) ) sprite_set_dx(s, 1);
    else sprite_set_dx(s, 0);

    if ( key_down(keys[2]) ) sprite_set_dy(s, -1);
    else if ( key_down(keys[3]) ) sprite_set_dy(s, 1);
    else sprite_set_dy(s, 0);
}

void run_camera_test_multi()
{
    window w1 = open_window("Camera Test Multi", 600, 600);

    load_bitmap("ufo", "ufo.png");
    std::vector<sprite> s_array;
    int size = 3;

    for(int i{0};i < size ; i++){
        s_array.push_back(create_sprite("ufo"));
        sprite_set_position(s_array[i], {300,300});
    }

    std::vector<std::vector<key_code>> key_arr;
    key_arr.push_back({LEFT_KEY, RIGHT_KEY, UP_KEY, DOWN_KEY});
    key_arr.push_back({A_KEY, D_KEY, W_KEY, S_KEY});
    key_arr.push_back({J_KEY, L_KEY, I_KEY, K_KEY});

    sprite_set_anchor_point(s_array[0], bitmap_cell_center(sprite_layer(s_array[0], 0)));

    bool follow = true;

    while ( ! window_close_requested(w1) )
    {
        process_events();

        if ( key_typed(F_KEY) )
        {
            follow =  !follow;
        }
        
        for(int i{0};i < size ; i++){
            set_keys(key_arr[i], s_array[i]);
            update_sprite(s_array[i]);
        }

        if (follow){
            center_camera_on(s_array, 0, 0);
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

        for(int i{0};i < size ; i++){
            draw_sprite(s_array[i]);
        }

        refresh_screen();
    }

    close_window(w1);
}
