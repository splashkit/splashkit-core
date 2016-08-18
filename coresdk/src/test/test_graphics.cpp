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

void test_clipping(window w1)
{
    clear_window(w1, COLOR_WHITE_SMOKE);
    draw_text("White Smoke Bottom Right", COLOR_BLACK, 10, 280);
    
    set_clip(w1, rectangle_from(0, 0, 250, 250));
    clear_window(w1, COLOR_RED);
    draw_text("Testing Clipping", COLOR_BLACK, 10, 10);
    draw_text("Red Top Left", COLOR_BLACK, 10, 20);
    
    push_clip(rectangle_from(50, 50, 250, 250));
    clear_window(w1, COLOR_GREEN);
    
    push_clip(rectangle_from(145, 0, 10, 300));
    clear_window(w1, COLOR_GOLD);
    
    pop_clip();
    push_clip(rectangle_from(0, 145, 300, 10));
    clear_window(w1, COLOR_GOLD);
    
    reset_clip();
    
    refresh_screen();
    delay(3000);
    
    bitmap bmp = create_bitmap("bmp", 100, 100);
    set_clip(bmp, rectangle_from(0, 0, 75, 75));
    clear_bitmap(bmp, COLOR_RED);
    push_clip(bmp, rectangle_from(0, 0, 50, 50));
    clear_bitmap(bmp, COLOR_GREEN);
    
    push_clip(bmp, rectangle_from(20, 0, 10, 100));
    clear_bitmap(bmp, COLOR_GOLD);
    pop_clip(bmp);
    
    push_clip(bmp, rectangle_from(0, 20, 100, 10));
    clear_bitmap(bmp, COLOR_GOLD);
    pop_clip(bmp);
    
    push_clip(bmp, rectangle_from(0, 0, 25, 25));
    clear_bitmap(bmp, COLOR_BLUE);
    reset_clip(bmp);
    
    clear_window(w1, COLOR_SILVER);
    draw_text("Blue > Green > Red from top left of bmp", COLOR_BLACK, 10, 10);
    draw_bitmap(bmp, 100, 100);
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
    
    window w1 = open_window("Testing Graphics", 300, 300);
    
    test_clipping(w1);
    
    color in_clr = string_to_color("#ffeebbaa");
    
    color clr;
    
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
