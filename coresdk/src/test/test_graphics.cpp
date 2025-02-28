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

extern const char splashkit_logo_base64[];

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
    
    color in_clr = string_to_color("#ffeebbaa");
    
    color clr;

    bitmap bmp = load_bitmap_base64("SplashScreen", splashkit_logo_base64);
    
    while ( ! window_close_requested(w1) )
    {
        process_events();
        
        for (int x = 0; x < window_width(w1); x++)
        {
            for (int y = 0; y < window_height(w1); y++)
            {
                clr = hsb_color(x / (window_width(w1) * 1.0f), y / (window_height(w1) * 1.0f), y / (window_height(w1) * 1.0f));
                draw_pixel(clr, x, y);
            }
        }
        
        fill_rectangle(in_clr, 100, 100, 100, 100);

        draw_bitmap("SplashScreen", 5, 5);
        
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
        
        refresh_screen();
    }
    
    close_window(w1);
}

const char splashkit_logo_base64[] = {"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"};
