//
//  terminal.hpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef terminal_h
#define terminal_h

#include "color.h"

#include <string>
using std::string;

namespace splashkit_lib
{
    void activate_advanced_terminal();
    void end_advanced_terminal();
    void terminal_move_cursor_to(int x, int y);
    void terminal_refresh();
    void terminal_clear();
    string read_line();
    int terminal_width();
    int terminal_height();
    void terminal_set_bold(bool value);
    void terminal_set_echo_input(bool value);
    void write(string text);
    void write_line();
    void write_line(string line);
    void terminal_write(string text, int x, int y);
    void termal_set_colors(color foreground, color background);
    bool advanced_terminal_active();
}

#endif /* terminal_h */
