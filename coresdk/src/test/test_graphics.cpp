//
//  test_graphics.cpp
//  splashkit
//
//  Created by Kai Renshaw on 27/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "window_manager.h"
#include "graphics.h"
#include "input.h"
#include "color.h"
#include "random.h"
#include "text.h"
#include "utils.h"

#include <iostream>
using namespace std;
using namespace splashkit_lib;

void test_drawing_on_new_window()
{
    bitmap user_image;

    user_image = create_bitmap ("user_image", 20, 20);
    save_bitmap(user_image, "0");
    clear_bitmap (user_image, COLOR_BRIGHT_GREEN);
    save_bitmap(user_image, "1");
    fill_rectangle_on_bitmap (user_image, COLOR_BLACK, 0, 0, 10, 10);
    save_bitmap(user_image, "2");

    window my_window = open_window ("Black TL+BR", 200, 200);
    clear_window (my_window, COLOR_WHITE);
    fill_rectangle_on_bitmap (user_image, COLOR_BLACK, 10, 10, 10, 10);
    save_bitmap(user_image, "3");

    draw_bitmap_on_window (my_window, user_image, 0, 0);
    save_bitmap(user_image, "4");
    refresh_window(my_window);
    
    bitmap user_image1;
    
    user_image1 = create_bitmap ("user_image1", 20, 20);
    clear_bitmap (user_image1, COLOR_BLACK);
    fill_rectangle_on_bitmap (user_image1, COLOR_BRIGHT_GREEN, 10, 0, 10, 10);
    fill_rectangle_on_bitmap (user_image1, COLOR_BRIGHT_GREEN, 0, 10, 10, 10);
    
    draw_bitmap_on_window (my_window, user_image1, 30, 0);
    save_bitmap(user_image, "4");
    
    // Get pixel from bitmap
    color bitmap_clr0 = get_pixel(user_image1, 0, 0);
    color bitmap_clr1 = get_pixel(user_image1, 0, 10);
    string bitmap_clr_str0 = "Clr@0,0 " + color_to_string(bitmap_clr0);
    string bitmap_clr_str1 = "Clr@0,10 " + color_to_string(bitmap_clr1);
    draw_text_on_window(my_window, bitmap_clr_str0, COLOR_BLACK, 0, 20);
    draw_text_on_window(my_window, bitmap_clr_str1, COLOR_BLACK, 0, 30);
    refresh_window(my_window);

    delay (5000);

    close_window(my_window);
    free_bitmap(user_image);
}

void test_clipping(window w1)
{
    clear_window(w1, COLOR_WHITE_SMOKE);
    draw_text("White Smoke Bottom Right", COLOR_BLACK, 10, 280);
    set_clip(w1, rectangle_from(0, 0, 250, 250));
    fill_rectangle(string_to_color("#ff0000ff"), 0, 0, 300, 300, option_draw_to(w1));
    draw_text("Testing Clipping", COLOR_BLACK, 10, 10);
    draw_text("Red Top Left", COLOR_BLACK, 10, 20);
    
    push_clip(rectangle_from(50, 50, 250, 250));
    fill_rectangle(string_to_color("#00ff00ff"), 0, 0, 300, 300, option_draw_to(w1));
    
    push_clip(rectangle_from(145, 0, 10, 300));
    fill_rectangle(COLOR_GOLD, 0, 0, 300, 300, option_draw_to(w1));
    
    pop_clip();
    push_clip(rectangle_from(0, 145, 300, 10));
    fill_rectangle(COLOR_GOLD, 0, 0, 300, 300, option_draw_to(w1));
    
    reset_clip();
    
    refresh_screen();
    delay(3000);
    
    bitmap bmp = create_bitmap("bmp", 100, 100);
    set_clip(bmp, rectangle_from(0, 0, 75, 75));
    fill_rectangle(COLOR_RED, 0, 0, 100, 100, option_draw_to(bmp));
    push_clip(bmp, rectangle_from(0, 0, 50, 50));
    fill_rectangle(COLOR_GREEN, 0, 0, 100, 100, option_draw_to(bmp));
    
    push_clip(bmp, rectangle_from(20, 0, 10, 100));
    fill_rectangle(COLOR_GOLD, 0, 0, 100, 100, option_draw_to(bmp));
    pop_clip(bmp);
    
    push_clip(bmp, rectangle_from(0, 20, 100, 10));
    fill_rectangle(COLOR_GOLD, 0, 0, 100, 100, option_draw_to(bmp));
    pop_clip(bmp);
    
    push_clip(bmp, rectangle_from(0, 0, 25, 25));
    fill_rectangle(COLOR_BLUE, 0, 0, 100, 100, option_draw_to(bmp));
    reset_clip(bmp);
    
    clear_window(w1, COLOR_SILVER);
    draw_text("B > G > R from top left of bmp", COLOR_BLACK, 10, 10);
    draw_bitmap(bmp, 100, 100);
    save_bitmap(bmp, "bmp");
    refresh_screen();
    delay(3000);
}

void run_graphics_test()
{
    cout << "Checking the number of displays and their details" << endl;
    cout << "There are " << number_of_displays() << " displays" << endl;
    cout << "------------------------" << endl;
    
    for (int i = 0; i < number_of_displays(); i++)
    {
        display d = display_details(i);
        cout << "Display " << i << endl;
        cout << "  name: " << display_name(d) << endl;
        cout << "     @: " << display_x(d) << "," << display_y(d) << endl;
        cout << "     s: " << display_width(d) << "x" << display_height(d) << endl;
        cout << "------------------------" << endl;
    }
    
    test_drawing_on_new_window();
    
    window w1 = open_window("Testing Graphics", 300, 300);
    
    test_clipping(w1);

    // Open a second window next to the first for testing on_window functions
    point_2d w1_pos = window_position(w1);
    window w2 = open_window("Testing Second Window", 300, 300);
    move_window_to(w2, w1_pos.x + 350, w1_pos.y);
    
    color in_clr = string_to_color("#ffeebbaa");
    
    color clr, clr2;
    
    while ( !(window_close_requested(w1) || window_close_requested(w2)) )
    {
        process_events();
        
        // First window
        for (int x = 0; x < window_width(w1); x++)
        {
            for (int y = 0; y < window_height(w1); y++)
            {
                clr = hsb_color(x / (window_width(w1) * 1.0f), y / (window_height(w1) * 1.0f), y / (window_height(w1) * 1.0f));
                draw_pixel(clr, x, y);
            }
        }
        
        fill_rectangle(in_clr, 100, 100, 100, 100);
        
        clr = get_pixel(mouse_position());
        
        string clr_string   = "Color " + color_to_string(clr);
        string r_string     = "Red   " + to_string(red_of(clr));
        string g_string     = "Green " + to_string(green_of(clr));
        string b_string     = "Blue  " + to_string(blue_of(clr));
        string a_string     = "Alpha " + to_string(alpha_of(clr));
        string h_string     = "Hue   " + to_string(hue_of(clr));
        string s_string     = "Sat   " + to_string(saturation_of(clr));
        string bri_string   = "Bri   " + to_string(brightness_of(clr));

        draw_text(clr_string, COLOR_BLACK, 20, 180);
        draw_text(r_string, COLOR_BLACK, 20, 190);
        draw_text(g_string, COLOR_BLACK, 20, 200);
        draw_text(b_string, COLOR_BLACK, 20, 210);
        draw_text(a_string, COLOR_BLACK, 20, 220);
        draw_text(h_string, COLOR_BLACK, 20, 240);
        draw_text(s_string, COLOR_BLACK, 20, 250);
        draw_text(bri_string, COLOR_BLACK, 20, 260);
        
        //  Second window
        for (int x = 0; x < window_width(w2); x++)
        {
            for (int y = 0; y < window_height(w2); y++)
            {
                clr2 = hsb_color(x / (window_width(w2) * 1.0f), y / (window_height(w2) * 1.0f), y / (window_height(w2) * 1.0f));
                draw_pixel_on_window(w2, clr2, x, y);
            }
        }
        
        fill_rectangle_on_window(w2, COLOR_MAGENTA, 100, 100, 100, 100);
        
        clr2 = get_pixel(w2, mouse_position());
        
        string clr_string2   = "Color " + color_to_string(clr2);
        string r_string2     = "Red   " + to_string(red_of(clr2));
        string g_string2     = "Green " + to_string(green_of(clr2));
        string b_string2     = "Blue  " + to_string(blue_of(clr2));
        string a_string2     = "Alpha " + to_string(alpha_of(clr2));
        string h_string2     = "Hue   " + to_string(hue_of(clr2));
        string s_string2     = "Sat   " + to_string(saturation_of(clr2));
        string bri_string2   = "Bri   " + to_string(brightness_of(clr2));
        
        draw_text_on_window(w2, clr_string2, COLOR_BLACK, 20, 180);
        draw_text_on_window(w2, r_string2, COLOR_BLACK, 20, 190);
        draw_text_on_window(w2, g_string2, COLOR_BLACK, 20, 200);
        draw_text_on_window(w2, b_string2, COLOR_BLACK, 20, 210);
        draw_text_on_window(w2, a_string2, COLOR_BLACK, 20, 220);
        draw_text_on_window(w2, h_string2, COLOR_BLACK, 20, 240);
        draw_text_on_window(w2, s_string2, COLOR_BLACK, 20, 250);
        draw_text_on_window(w2, bri_string2, COLOR_BLACK, 20, 260);

        refresh_screen();
    }
    
    close_all_windows();
}