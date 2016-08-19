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
}