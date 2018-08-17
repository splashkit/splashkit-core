//
//  mouse_input.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "mouse_input.h"
#include "input_driver.h"
#include "vector_2d.h"

#include <vector>
#include <map>

using std::vector;
using std::map;

namespace splashkit_lib
{
    bool _mouse_button_clicked[6] = { false };

    vector_2d _wheel_scroll = {0,0};
    map<int, bool> _button_clicked;

    void _mouse_start_process_events()
    {
        //called at the start of process events -- used to clear state

        _wheel_scroll = vector_to(0,0);
        _button_clicked.clear();
    }

    void _process_mouse_up_event(int code)
    {
        _button_clicked[code] = true;
    }

    void _process_mouse_wheel_callback(int x, int y)
    {
        _wheel_scroll.x += x;
        _wheel_scroll.y += y;
    }


    vector_2d mouse_position_vector()
    {
        return vector_to(mouse_position());
    }

    point_2d mouse_position()
    {
        window wind = current_window();
        window focus = window_with_focus();

        point_2d result;
        sk_mouse_position(result.x, result.y);

        if (wind and focus and wind != focus )
        {
            // Asking for mouse location when another window is in focus -- change based on that window
            int wx, wy, fx, fy;

            sk_window_position(&wind->image.surface, &wx, &wy);
            sk_window_position(&focus->image.surface, &fx, &fy);

            result.x += fx - wx;
            result.y += fy - wy;
        }

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
        point_2d pt;
        sk_mouse_movement(pt.x, pt.y);
        return vector_to(pt);
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

    void move_mouse(double x, double y)
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
    
}
