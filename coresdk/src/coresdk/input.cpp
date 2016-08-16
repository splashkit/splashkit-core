//
//  input.cpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "input.h"

#include "input_driver.h"
#include "geometry.h"
#include "text.h"
#include "utility_functions.h"

#include <vector>
#include <map>
#include <iostream>
using namespace std;

struct key_down_data
{
    int code;
    int keyChar;
};

static vector<key_down_data> _keys_down;
static vector<int> _keys_just_typed; // i.e. those that have just gone down
static vector<int> _keys_released; // i.e. those that have just gone down
bool _key_pressed = false;
bool _mouse_button_clicked[6] = { false };

vector_2d _wheel_scroll = {0,0};
map<int, bool> _button_clicked;


void quit()
{
    _sk_quit = true;
}

void _handle_key_down_callback(int code)
{
    cout << "key down: " << code << endl;
}

void _process_mouse_up_event(int code)
{
    _button_clicked[code] = true;
    cout << "mouse up: " << code << endl;
}

void process_mouse_wheel_callback(int x, int y)
{
    _wheel_scroll.x += x;
    _wheel_scroll.y += y;
    cout << "mouse wheel: " << x << ":" << y << endl;
}

// occurs as text entry is accepted
void handle_input_text_callback(char *input)
{
}

void handle_editing_text(char *text, int cursor, int selection_length)
{
}

void draw_collected_text(color clr, font fnt, int font_size, float x, float y, drawing_options opts)
{
    window current = current_window();
    if ( not current ) return;
    
    string ct = current->input_text;
    draw_text(ct, clr, fnt, font_size, x, y, opts);
    font_style style = get_font_style(fnt);
    
    set_font_style(fnt, static_cast<font_style>(static_cast<int>(style) | static_cast<int>(UNDERLINE_FONT)));
    draw_text(current->composition, clr, fnt, font_size, x + text_length(ct, fnt, font_size), y, opts);
    
    set_font_style(fnt, style);
}

bool reading_text()
{
    return reading_text(current_window());
}

bool reading_text(window wind)
{
    return VALID_PTR(wind, WINDOW_PTR) and wind->reading_text;
}

void _handle_key_up_callback(int code)
{
    cout << "key up: " << code << endl;
}

void handle_window_resize(pointer p, int width, int height)
{
    cout << "resize: " << width << "x" << height << endl;
}

void handle_window_move(pointer p, int x, int y)
{
    cout << "move: " << x << ":" << y << endl;
}

void handle_window_gain_focus(pointer p)
{
    cout << "window gained focus: " << endl;
}

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
        _input_callbacks.handle_mouse_wheel   = &process_mouse_wheel_callback; // click occurs on up
        _input_callbacks.handle_input_text    = &handle_input_text_callback;
        _input_callbacks.handle_editing_text  = &handle_editing_text;
        _input_callbacks.handle_window_resize = &handle_window_resize;
        _input_callbacks.handle_window_move   = &handle_window_move;
        _input_callbacks.handle_window_gain_focus = &handle_window_gain_focus;
    }
    
    // Reset event tracking data
    _wheel_scroll = vector_to(0,0);
    _button_clicked.clear();

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

void start_reading_text(rectangle rect)
{
    start_reading_text(current_window(), rect);
}

void start_reading_text(window wind, rectangle rect)
{
    if ( INVALID_PTR(wind, WINDOW_PTR))
    {
        raise_warning("Attempting to start reading text with invalid window");
        return;
    }
    
    sk_start_reading_text(wind, rect.x, rect.y, rect.width, rect.height);
}

string text_input()
{
    return text_input(current_window());
}

string text_input(window wind)
{
    if ( INVALID_PTR(wind, WINDOW_PTR) )
    {
        raise_warning("Attempting to read input text from invalid window");
        return "";
    }
    
    return wind->input_text + wind->composition;
}

