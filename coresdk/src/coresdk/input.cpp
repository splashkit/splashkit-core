//
//  input.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "input.h"

#include "geometry.h"
#include "input_driver.h"
#include "keyboard_input.h"
#include "text.h"
#include "utility_functions.h"

#include <vector>
#include <map>
#include <iostream>
using std::vector;
using std::map;

namespace splashkit_lib
{
    void quit()
    {
        _sk_quit = true;
    }

    void handle_window_resize(pointer p, int width, int height)
    {
        //    cout << "resize: " << width << "x" << height << endl;
    }

    void handle_window_move(pointer p, int x, int y)
    {
        //    cout << "move: " << x << ":" << y << endl;
    }

    void handle_window_gain_focus(pointer p)
    {
        //    cout << "window gained focus: " << endl;
    }

    // In keyboard input
    void _keyboard_start_process_events();
    void _handle_key_up_callback(key_code code);
    void _handle_key_down_callback(key_code code);

    // In mouse input
    void _mouse_start_process_events();
    void _process_mouse_up_event(int code);
    void _process_mouse_wheel_callback(int x, int y);

    void process_events()
    {
        // Ensure callbacks are registered
        if( ! _input_callbacks.do_quit )
        {
            _input_callbacks.do_quit              = &quit;
            _input_callbacks.handle_key_down      = &_handle_key_down_callback;
            _input_callbacks.handle_key_up        = &_handle_key_up_callback;
            _input_callbacks.handle_mouse_up      = &_process_mouse_up_event; // click occurs on up
            _input_callbacks.handle_mouse_down    = nullptr;
            _input_callbacks.handle_mouse_wheel   = &_process_mouse_wheel_callback; // click occurs on up
            _input_callbacks.handle_input_text    = nullptr;
            _input_callbacks.handle_editing_text  = nullptr;
            _input_callbacks.handle_window_resize = nullptr;
            _input_callbacks.handle_window_move   = nullptr;
            _input_callbacks.handle_window_gain_focus = nullptr;
        }

        // Reset event tracking data
        _keyboard_start_process_events();
        _mouse_start_process_events();
        
        sk_process_events();
    }
    
    bool quit_requested()
    {
        return _sk_quit;
    }
    
    void reset_quit()
    {
        _sk_quit = false;
    }
}
