//
//  test_shape_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "input.h"
#include "graphics.h"
#include "geometry.h"
#include "text.h"
#include "timers.h"
#include "window_manager.h"
#include "random.h"
#include "images.h"

void run_shape_drawing_test()
{
    window w1 = open_window("Test Shape Drawing", 600, 600);
    
    load_font("myfont", "hara.ttf");
    
    timer t = create_timer("shape drawing timer");
    start_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Drawing Circles", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            draw_circle(random_rgb_color(128), rnd() * screen_width(), rnd() * screen_height(), 1 + rnd() * 50);
        else
        {
            circle c = circle_at(rnd() * window_width(w1), rnd() * window_height("Test Shape Drawing"), 1 + rnd() * 50);
            draw_circle(random_rgb_color(128), c);
        }

        refresh_screen();
    }
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Filling Circles", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            fill_circle(random_rgb_color(128), rnd() * screen_width(), rnd() * screen_height(), 1 + rnd() * 50);
        else
        {
            circle c = circle_at(rnd() * window_width(w1), rnd() * window_height("Test Shape Drawing"), 1 + rnd() * 50);
            fill_circle(random_rgb_color(128), c);
        }
        
        refresh_screen();
    }

    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Draw Circle to Bitmap", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    bitmap bmp = create_bitmap("bitmap", 300, 300);
    drawing_options opts = option_draw_to(bmp);
    
    clear_bitmap(bmp, COLOR_WHEAT);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
        {
            draw_circle(random_rgb_color(128), rnd() * bitmap_width("bitmap"), rnd() * bitmap_width("bitmap"), 1 + rnd() * 50, opts);
            fill_circle(random_rgb_color(128), rnd() * bitmap_width(bmp), rnd() * bitmap_width(bmp), 1 + rnd() * 50, opts);
        }
        else
        {
            circle c;
            c = circle_at(rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp), 1 + rnd() * 50);
            draw_circle(random_rgb_color(128), c, opts);
            
            c = circle_at(rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp), 1 + rnd() * 50);
            fill_circle(random_rgb_color(128), c, opts);
        }
        
        draw_bitmap(bmp, 150, 150);
        
        refresh_screen();
    }
    
    free_timer(t);
    
    close_window(w1);
}