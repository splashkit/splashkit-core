//
//  test_shape_drawing.cpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <iostream>
using namespace std;

#include "input.h"
#include "graphics.h"
#include "geometry.h"
#include "text.h"
#include "timers.h"
#include "window_manager.h"
#include "random.h"
#include "images.h"

using namespace splashkit_lib;

void test_circle_drawing(window w1)
{
    timer t = create_timer("shape drawing timer");
    start_timer(t);

    clear_screen(COLOR_WHITE);
    draw_text("Drawing Circles", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1000)
            draw_circle(random_rgb_color(128), rnd() * screen_width(), rnd() * screen_height(), 1 + rnd() * 50);
        else if (timer_ticks(t) >= 1000 && timer_ticks(t) < 2000)
            draw_circle(random_rgb_color(128), random_screen_point(), 1 + rnd() * 50);
        else
        {
            circle c = circle_at(rnd() * window_width(w1), rnd() * window_height("Test Shape Drawing"), 1 + rnd() * 50);
            draw_circle(random_rgb_color(128), c);
        }
        
        refresh_screen();
    }
    cout << "Saving circles screenshot to desktop" << endl;
    take_screenshot("circles");
    
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
    cout << "Saving filled circles screenshot to desktop" << endl;
    take_screenshot(current_window(), "filled circles");
    
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
    cout << "Saving circles bitmap to desktop" << endl;
    save_bitmap(bmp, "circle bitmap");
    
    free_bitmap(bmp);
    free_timer(t);
}

void test_triangle_drawing(window w1)
{
    timer t = create_timer("shape drawing timer");
    start_timer(t);
    
    clear_screen(COLOR_WHITE);
    draw_text("Drawing Triangles", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            draw_triangle(random_rgb_color(128),
                          rnd() * screen_width(), rnd() * screen_height(),
                          rnd() * screen_width(), rnd() * screen_height(),
                          rnd() * screen_width(), rnd() * screen_height());
        else
        {
            triangle tri = triangle_from(rnd() * screen_width(), rnd() * screen_height(),
                                         rnd() * screen_width(), rnd() * screen_height(),
                                         rnd() * screen_width(), rnd() * screen_height());
            draw_triangle(random_rgb_color(128), tri);
        }
        
        refresh_screen();
    }
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Filling Triangles", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            fill_triangle(random_rgb_color(128),
                          rnd() * screen_width(), rnd() * screen_height(),
                          rnd() * screen_width(), rnd() * screen_height(),
                          rnd() * screen_width(), rnd() * screen_height());
        else
        {
            triangle tri = triangle_from(rnd() * screen_width(), rnd() * screen_height(),
                                         rnd() * screen_width(), rnd() * screen_height(),
                                         rnd() * screen_width(), rnd() * screen_height());
            fill_triangle(random_rgb_color(128), tri);
        }
        
        refresh_screen();
    }
    
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Draw Triangles to Bitmap", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    bitmap bmp = create_bitmap("bitmap", 300, 300);
    drawing_options opts = option_draw_to(bmp);
    
    clear_bitmap(bmp, COLOR_WHEAT);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
        {
            draw_triangle(random_rgb_color(128),
                          rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                          rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                          rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                          opts);
            fill_triangle(random_rgb_color(128),
                          rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                          rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                          rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                          opts);
        }
        else
        {
            triangle tri = triangle_from(rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                                         rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                                         rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp));
            fill_triangle(random_rgb_color(128), tri, opts);
            
            tri = triangle_from(rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                                rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp),
                                rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp));
            draw_triangle(random_rgb_color(128), tri, opts);
        }
        
        draw_bitmap(bmp, 150, 150);
        
        refresh_screen();
    }
    
    free_bitmap(bmp);
    free_timer(t);
}

void test_quad_drawing(window w1)
{
    timer t = create_timer("shape drawing timer");
    start_timer(t);
    
    clear_screen(COLOR_WHITE);
    draw_text("Drawing Quads", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    point_2d tl;
    quad q;
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        tl = random_screen_point();
        q = quad_from(tl, point_at(tl.x + 100, tl.y + 25), point_at(tl.x + 25, tl.y + 100), point_at(tl.x + 125, tl.y + 125));
        
        if ( timer_ticks(t) < 1500)
            draw_quad(random_rgb_color(128), q);
        else
        {
            fill_quad(random_rgb_color(128), q);
        }
        
        refresh_screen();
    }
    
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Draw Triangles to Bitmap", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    bitmap bmp = create_bitmap("bitmap", 300, 300);
    drawing_options opts = option_draw_to(bmp);
    
    clear_bitmap(bmp, COLOR_WHEAT);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        tl = random_screen_point();
        q = quad_from(tl, point_at(tl.x + 100, tl.y + 25), point_at(tl.x + 25, tl.y + 100), point_at(tl.x + 125, tl.y + 125));

        
        if ( timer_ticks(t) < 1500)
        {
            draw_quad(random_rgb_color(128), q, opts);
        }
        else
        {
            fill_quad(random_rgb_color(128), q, opts);
        }
        
        draw_bitmap(bmp, 150, 150);
        
        refresh_screen();
    }
    
    free_bitmap(bmp);
    free_timer(t);
}

void test_aa_rect_drawing(window w1)
{
    timer t = create_timer("shape drawing timer");
    start_timer(t);
    
    clear_screen(COLOR_WHITE);
    draw_text("Drawing Rectangles", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            draw_rectangle(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200);
        else
        {
            rectangle r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            draw_rectangle(random_rgb_color(128), r);
        }
        
        refresh_screen();
    }
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Filling Rectangles", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            fill_rectangle(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200);
        else
        {
            rectangle r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            fill_rectangle(random_rgb_color(128), r);
        }
        
        refresh_screen();
    }
    
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Draw Rectangles to Bitmap", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    bitmap bmp = create_bitmap("bitmap", 300, 300);
    drawing_options opts = option_draw_to(bmp);
    
    clear_bitmap(bmp, COLOR_WHEAT);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
        {
            draw_rectangle(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200, opts);
            fill_rectangle(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200, opts);
        }
        else
        {
            rectangle r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            draw_rectangle(random_rgb_color(128), r, opts);
            
            r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            fill_rectangle(random_rgb_color(128), r, opts);
        }
        
        draw_bitmap(bmp, 150, 150);
        
        refresh_screen();
    }
    
    free_bitmap(bmp);
    free_timer(t);
}

void test_ellipse_drawing(window w1)
{
    timer t = create_timer("shape drawing timer");
    start_timer(t);
    
    clear_screen(COLOR_WHITE);
    draw_text("Drawing Ellipse", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            draw_ellipse(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200);
        else
        {
            rectangle r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            draw_ellipse(random_rgb_color(128), r);
        }
        
        refresh_screen();
    }
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Filling Ellipses", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            fill_ellipse(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200);
        else
        {
            rectangle r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            fill_ellipse(random_rgb_color(128), r);
        }
        
        refresh_screen();
    }
    
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Draw Ellipses to Bitmap", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    bitmap bmp = create_bitmap("bitmap", 300, 300);
    drawing_options opts = option_draw_to(bmp);
    
    clear_bitmap(bmp, COLOR_WHEAT);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
        {
            draw_ellipse(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200, opts);
            fill_ellipse(random_rgb_color(128), rnd() * screen_width() - 100, rnd() * screen_height() - 100, 1 + rnd() * 200, 1 + rnd() * 200, opts);
        }
        else
        {
            rectangle r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            draw_ellipse(random_rgb_color(128), r, opts);
            
            r = rectangle_from(rnd() * window_width(w1) - 100, rnd() * window_height("Test Shape Drawing") - 100, 1 + rnd() * 200, 1 + rnd() * 200);
            fill_ellipse(random_rgb_color(128), r, opts);
        }
        
        draw_bitmap(bmp, 150, 150);
        
        refresh_screen();
    }
    
    free_bitmap(bmp);
    free_timer(t);
}

void test_line_drawing(window w1)
{
    timer t = create_timer("shape drawing timer");
    start_timer(t);
    
    clear_screen(COLOR_WHITE);
    draw_text("Drawing Lines", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        if ( timer_ticks(t) < 1500)
            draw_line(random_rgb_color(128), rnd() * screen_width(), rnd() * screen_height(), rnd() * screen_width(), rnd() * screen_height());
        else
            draw_line(random_rgb_color(128), line_from(random_screen_point(), random_screen_point()));
        
        refresh_screen();
    }
    
    reset_timer(t);
    clear_screen(COLOR_WHITE);
    draw_text("Draw Lines to Bitmap", COLOR_TOMATO, "myfont", 18, 30, 30);
    
    bitmap bmp = create_bitmap("bitmap", 300, 300);
    drawing_options opts = option_draw_to(bmp);
    
    clear_bitmap(bmp, COLOR_WHEAT);
    
    while( not window_close_requested(w1) and timer_ticks(t) < 3000 )
    {
        process_events();
        
        opts.line_width = rnd(5) + 1;
        
        if ( timer_ticks(t) < 1500)
        {
            draw_line(random_rgb_color(128), rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp), rnd() * bitmap_width(bmp), rnd() * bitmap_height(bmp), opts);
        }
        else
        {
            draw_line(random_rgb_color(128), line_from(random_bitmap_point(bmp), random_bitmap_point(bmp)), opts);
        }
        
        draw_bitmap(bmp, 150, 150);
        
        refresh_screen();
    }
    
    free_bitmap(bmp);
    free_timer(t);
}


void run_shape_drawing_test()
{
    window w1 = open_window("Test Shape Drawing", 600, 600);
    
    load_font("myfont", "hara.ttf");
    
    test_circle_drawing(w1);
    test_aa_rect_drawing(w1);
    test_triangle_drawing(w1);
    test_quad_drawing(w1);
    test_ellipse_drawing(w1);
    test_line_drawing(w1);
    
    close_window(w1);
}