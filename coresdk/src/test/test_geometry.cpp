//
//  test_geometry.cpp
//  splashkit
//
//  Created by Jacob on 19/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <iostream>
using namespace std;

#include "geometry.h"
#include "window_manager.h"
#include "graphics.h"
#include "input.h"

void test_points()
{
    point_2d p = point_at(10, 20);
    cout << "Point is at 10,20" << endl;
    cout << point_to_string(p) << endl;
    
    window w1 = open_window("Point Tests", 600, 600);
    
    triangle t1 = triangle_from(10, 10, 50, 50, 70, 55);
    rectangle r1 = rectangle_from(200, 200, -75, -100);
    circle c1 = circle_at(300, 300, 100);
    circle c2 = circle_at(300, 300, -10);
    line l = line_from(point_at_origin(), random_screen_point());
    
    while (not quit_requested())
    {
        process_events();
        
        clear_screen(COLOR_WHEAT);
        
        if ( point_in_triangle(mouse_position(), t1) )
        {
            fill_triangle(COLOR_TAN, t1);
        }
        draw_triangle(COLOR_RED, t1);

        if ( point_in_rectangle(mouse_position(), r1) )
        {
            fill_rectangle(COLOR_TAN, r1);
        }
        draw_rectangle(COLOR_RED, r1);

        if ( point_in_circle(mouse_position(), c1) )
        {
            fill_circle(COLOR_TAN, c1);
        }
        draw_circle(COLOR_RED, c1);
        
        
        if ( point_in_circle(mouse_position(), c2) )
        {
            fill_circle(COLOR_RED, c2);
        }
        draw_circle(COLOR_RED, c2);
        
        if ( point_on_line(mouse_position(), l))
        {
            fill_circle(COLOR_RED, circle_at(l.start_point, 5));
            fill_circle(COLOR_RED, circle_at(l.end_point, 5));
        }
        draw_line(COLOR_RED, l);
        
        refresh_screen();
    }
    
    close_window(w1);
}

void run_geometry_test()
{
    rectangle r;
    
    r = rectangle_from(10, 20, 30, 40);
    
    cout << "Created rectangle 10,20 30x40" << endl;
    cout << rectangle_to_string(r) << endl;
    
    cout << "Top    (should be 20) " << rectangle_top(r) << endl;
    cout << "Bottom (should be 60) " << rectangle_bottom(r) << endl;
    cout << "Left   (should be 10) " << rectangle_left(r) << endl;
    cout << "Right  (should be 40) " << rectangle_right(r) << endl;
    
    rectangle intersect;
    
    intersect = intersection(r, rectangle_from(15, 30, 100, 100));
    
    cout << "Intersection should be 15,30 25x30" << endl;
    cout << "Intersection is " << rectangle_to_string(intersect) << endl;
    
    test_points();
}