//
//  test_input.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_input.hpp"

#include "graphics.h"
#include "text.h"
#include "input.h"
#include "text_input.h"
#include "mouse_input.h"
#include "keyboard_input.h"

static string _key_typed = "", _key_down = "", _key_up = "";

void _on_key_typed(key_code code)
{
    _key_typed = key_name(code);
}

void _on_key_down(key_code code)
{
    _key_down = key_name(code);
}

void _on_key_up(key_code code)
{
    _key_up = key_name(code);
}

void run_input_test()
{
    register_callback_on_key_typed(&_on_key_typed);
    register_callback_on_key_down(&_on_key_down);
    register_callback_on_key_up(&_on_key_up);
    
    rectangle rect = { 230.0f, 50.0f, 200.0f, 30.0f };
    
    window w1 = open_window("Test Input", 600, 600);
    window w2 = open_window("Test Input Window 2", 600, 600);
    
    load_font("hara", "hara.ttf");
    load_font("taroko", "Taroko.ttf");
    
    start_reading_text(rect);
    
    set_current_window(w2);
    
    start_reading_text(rect, "教育漢字カ");
    
    color back = COLOR_WHEAT;
    
    while ( reading_text(w1) || reading_text(w2) )
    {
        process_events();
        
        set_current_window(w1);
        
        if ( not text_entry_cancelled(w1) )
            clear_screen(COLOR_WHITE);
        else
            clear_screen(COLOR_PERU);
        
        draw_text("Enter english string: ", COLOR_NAVY, "hara", 18, 30, 50);
        draw_collected_text(COLOR_BLACK, font_named("hara"), 18, 230, 50, option_defaults());
        
        if ( not reading_text(w1) )
        {
            draw_text(string("Read: "), COLOR_BLUE, "hara", 18, 30, 80);
            draw_text(text_input(w1), COLOR_BLUE, "hara", 18, 30, 110);
        }
        
        string location = "Mouse location: ";
        location += to_string(mouse_x()) + ":" + to_string(mouse_y());
        
        string left_clicked = "Left click status: ";
        left_clicked += to_string(mouse_clicked(LEFT_BUTTON)) + " up: " + to_string(mouse_up(LEFT_BUTTON)) + " down: " + to_string(mouse_down(LEFT_BUTTON));
        
        string right_clicked = "Right click status: ";
        right_clicked += to_string(mouse_clicked(RIGHT_BUTTON)) + " up: " + to_string(mouse_up(RIGHT_BUTTON)) + " down: " + to_string(mouse_down(RIGHT_BUTTON));
        
        string key_details = "T key is ";
        if ( key_down(T_KEY) ) key_details += "down";
        if ( key_up(T_KEY) ) key_details += "up";
        if ( key_released(T_KEY) ) key_details += " - released";
        if ( key_typed(T_KEY) ) key_details += " - typed";
        
        draw_text(location, COLOR_PLUM, "hara", 14, 18, 200);
        draw_text(left_clicked, COLOR_PLUM, "hara", 14, 18, 220);
        draw_text(right_clicked, COLOR_PLUM, "hara", 14, 18, 240);
        draw_text(key_details, COLOR_PLUM, "hara", 14, 18, 280);
        draw_text(_key_down, COLOR_PLUM, "hara", 14, 18, 300);
        draw_text(_key_up, COLOR_PLUM, "hara", 14, 18, 320);
        draw_text(_key_typed, COLOR_PLUM, "hara", 14, 18, 340);
        
        set_current_window(w2);
        
        if ( key_typed(C_KEY) )
        {
            back = random_rgb_color(255);
        }
        
        clear_screen(back);
        draw_text("Enter Japanese string: ", COLOR_NAVY, "hara", 18, 30, 50);
        draw_collected_text(COLOR_BLACK, font_named("taroko"), 18, 230, 50, option_defaults());
        
        if ( not reading_text(w2) )
        {
            draw_text(string("Read: "), COLOR_BLUE, "hara", 18, 30, 80);
            draw_text(text_input(w2), COLOR_BLUE, "taroko", 18, 30, 110);
        }
        
        // Get location of mouse in W2
        location = "Mouse location: ";
        location += to_string(mouse_x()) + ":" + to_string(mouse_y());
        
        draw_text(location, COLOR_PLUM, "hara", 14, 18, 200);
        draw_text(left_clicked, COLOR_PLUM, "hara", 14, 18, 220);
        draw_text(right_clicked, COLOR_PLUM, "hara", 14, 18, 240);
        draw_text(key_details, COLOR_PLUM, "hara", 14, 18, 280);
        draw_text(_key_down, COLOR_PLUM, "hara", 14, 18, 300);
        draw_text(_key_up, COLOR_PLUM, "hara", 14, 18, 320);
        draw_text(_key_typed, COLOR_PLUM, "hara", 14, 18, 340);
        
        refresh_screen();
    }
    
    close_window("Test Input");
    close_window("Test Input Window 2");
    
    deregister_callback_on_key_typed(&_on_key_typed);
    deregister_callback_on_key_down(&_on_key_down);
    deregister_callback_on_key_up(&_on_key_up);
    
    free_all_fonts();
}