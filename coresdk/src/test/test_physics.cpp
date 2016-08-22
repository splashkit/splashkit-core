//
//  test_physics.cpp
//  splashkit
//
//  Created by Clancy Light Townsend on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <iostream>
using namespace std;

#include "window_manager.h"
#include "input.h"
#include "physics.h"
#include "graphics.h"

void do_test_vector()
{
    window w1 = open_window("Vector Test", 600, 600);
    
    rectangle r1 = rectangle_from(50, 50, 200, 200);
    vector_2d v1 = vector_to(0,0);
    circle c = circle_at(300, 300, 50), mouse_circle;
    line l;
    vector_2d velocity = vector_to(10, 0);
    
    while( not window_close_requested(w1))
    {
        mouse_circle = circle_at(mouse_position(), 10);
        
        process_events();
        
        if ( key_down(RIGHT_KEY) )
        {
            velocity = vector_from_angle(vector_angle(velocity) + 1, 10);
        }
        if ( key_down(LEFT_KEY) )
        {
            velocity = vector_from_angle(vector_angle(velocity) - 1, 10);
        }
        
        clear_screen(COLOR_WHITE);
        draw_rectangle(COLOR_GREEN, r1);
        draw_circle(COLOR_GREEN, c);
        
        draw_circle(COLOR_RED, mouse_circle);
        
        if ( point_in_rectangle(mouse_position(), r1))
        {
            v1 = vector_out_of_rect_from_point(mouse_position(), r1, velocity);
            l = line_from(mouse_position(), v1);
            
            draw_line(COLOR_RED, l);
            draw_circle(COLOR_RED, circle_at(l.end_point, 10));
        }
        
        if ( point_in_circle(mouse_position(), c))
        {
            v1 = vector_out_of_circle_from_circle(mouse_circle, c, velocity);
            l = line_from(mouse_position(), v1);
            
            draw_line(COLOR_RED, l);
            draw_circle(COLOR_RED, circle_at(l.end_point, 10));
        }
        
        refresh_screen();
    }
    
    close_window(w1);
}

void run_physics_test()
{
    matrix_2d matrix = identity_matrix();
    
    cout << "Identity Matrix" << endl;
    cout << matrix_to_string(matrix) << endl;
    
    do_test_vector();
}