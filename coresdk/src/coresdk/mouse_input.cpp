//
//  mouse_input.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "mouse_input.h"
#include "input_driver.h"

#include <vector>
#include <map>
using namespace std;

// scroll data from input backend
extern vector_2d _wheel_scroll;
extern map<int, bool> _button_clicked;

vector_2d mouse_position_vector()
{
    vector_2d result;
    sk_mouse_position(result.x, result.y);
    return result;
}

point_2d mouse_position()
{
    point_2d result;
    sk_mouse_position(result.x, result.y);
    return result;
}

float mouse_x()
{
    return mouse_position().x;
}

float mouse_y()
{
    return mouse_position().y;
}

vector_2d mouse_movement()
{
    vector_2d result;
    sk_mouse_movement(result.x, result.y);
    return result;
}

vector_2d mouse_wheel_scroll()
{
    return _wheel_scroll;
}

bool mouse_down(mouse_button button)
{
    return sk_mouse_button_down(button);
}

bool mouse_up(mouse_button button)
{
    return not mouse_down(button);
}

bool mouse_clicked(mouse_button button)
{
    if (_button_clicked.count(static_cast<int>(button)) > 0)
        return _button_clicked[static_cast<int>(button)];
    else
        return false;
}

void move_mouse(float x, float y)
{
    window wind = current_window();
    
    if ( wind )
        sk_warp_mouse(&wind->image.surface, static_cast<int>(x), static_cast<int>(y));
}

void move_mouse(point_2d point)
{
    move_mouse(point.x, point.y);
}

void show_mouse()
{
    show_mouse(true);
}

void show_mouse(bool show)
{
    sk_show_mouse(show ?  1 : 0);
}

void hide_mouse()
{
    show_mouse(false);
}

bool mouse_shown()
{
    return sk_show_mouse(-1);
}