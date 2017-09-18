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

using namespace splashkit_lib;

void do_test_vector()
{
    window w1 = open_window("Vector Test", 600, 600);
    
    rectangle r1 = rectangle_from(50, 50, 200, 200), mouse_rect;
    vector_2d v1 = vector_to(0,0);
    circle c = circle_at(300, 300, 50), mouse_circle;
    line l;
    vector_2d velocity = vector_to(10, 0);
    
    bitmap bmp = create_bitmap("test", 100, 100);
    clear_bitmap(bmp, COLOR_RED);
    
    setup_collision_mask(bmp);
    
    while( not window_close_requested(w1))
    {
        mouse_circle = circle_at(mouse_position(), 10);
        mouse_rect = rectangle_from(mouse_x() - 2, mouse_y() - 2, 5, 5);
        
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
        draw_bitmap(bmp, 100, 100);
        
        draw_circle(COLOR_RED, mouse_circle);
        draw_rectangle(COLOR_RED, mouse_rect);
        
        if ( point_in_rectangle(mouse_position(), r1))
        {
            v1 = vector_out_of_rect_from_point(mouse_position(), r1, velocity);
            l = line_from(mouse_position(), v1);
            
            draw_line(COLOR_RED, l);
//            draw_circle(COLOR_RED, circle_at(l.end_point, 10));
            
            v1 = vector_out_of_rect_from_circle(mouse_circle, r1, velocity);
            draw_circle(COLOR_RED, circle_at(point_offset_by(mouse_position(), v1), 10));
            
            v1 = vector_out_of_rect_from_rect(mouse_rect, r1, velocity);
            draw_rectangle(COLOR_RED, rectangle_offset_by(mouse_rect, v1));
        }
        
        if ( point_in_circle(mouse_position(), c))
        {
            v1 = vector_out_of_circle_from_circle(mouse_circle, c, velocity);
            l = line_from(mouse_position(), v1);
            
            draw_line(COLOR_RED, l);
            draw_circle(COLOR_RED, circle_at(l.end_point, 10));
        }
        
        if ( bitmap_point_collision(bmp, 100, 100, mouse_x(), mouse_y()))
        {
            draw_rectangle(COLOR_BLACK, 100, 100, 100, 100);
        }
        
        refresh_screen();
    }
    
    free_bitmap(bmp);
    close_window(w1);
}

void run_physics_test()
{
    matrix_2d matrix = identity_matrix();
    matrix_2d inv_matrix = matrix_inverse(matrix);
    
    cout << "Identity Matrix" << endl;
    cout << matrix_to_string(matrix) << endl;
    cout << endl << " inverse " << endl;
    cout << matrix_to_string(inv_matrix) << endl;
    
    matrix = scale_matrix(4);
    inv_matrix = matrix_inverse(matrix);
    
    cout << "Scale Matrix - 4x" << endl;
    cout << matrix_to_string(matrix) << endl;
    cout << endl << " inverse " << endl;
    cout << matrix_to_string(inv_matrix) << endl;
    cout << endl << " check... " << endl;
    cout << matrix_to_string(matrix_multiply(matrix, inv_matrix)) << endl;
    
    matrix = rotation_matrix(45);
    inv_matrix = matrix_inverse(matrix);
    
    cout << "Rotation Matrix - 45deg" << endl;
    cout << matrix_to_string(matrix) << endl;
    cout << endl << " inverse " << endl;
    cout << matrix_to_string(inv_matrix) << endl;
    cout << endl << " check... " << endl;
    cout << matrix_to_string(matrix_multiply(matrix, inv_matrix)) << endl;
    
    matrix = translation_matrix(100, -100);
    inv_matrix = matrix_inverse(matrix);
    
    cout << "Translation Matrix - 100,-100" << endl;
    cout << matrix_to_string(matrix) << endl;
    cout << endl << " inverse " << endl;
    cout << matrix_to_string(inv_matrix) << endl;
    cout << endl << " check... " << endl;
    cout << matrix_to_string(matrix_multiply(matrix, inv_matrix)) << endl;
    
    cout << "Rotate 45%" << endl;
    cout << matrix_to_string(rotation_matrix(45)) << endl;
    
    cout << "translate 10,10" << endl;
    cout << matrix_to_string(translation_matrix(10, 10)) << endl;
    
    matrix = matrix_multiply(rotation_matrix(45), translation_matrix(10, 10)); //scale_rotate_translate_matrix(point_at(4, 4), 89, point_at(100, -100));
    inv_matrix = matrix_inverse(matrix);
    
    cout << "Combination" << endl;
    cout << matrix_to_string(matrix) << endl;
    cout << endl << " inverse " << endl;
    cout << matrix_to_string(inv_matrix) << endl;
    cout << endl << " check... " << endl;
    cout << matrix_to_string(matrix_multiply(matrix, inv_matrix)) << endl;
    
    do_test_vector();
}
