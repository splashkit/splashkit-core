//
//  test_graphics.cpp
//  splashkit
//
//  Created by Kai Renshaw on 27/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "graphics.h"
#include "input.h"
#include "color.h"
#include "random.h"

#include <iostream>
using namespace std;

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
}
