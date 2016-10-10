//
//  terminal.hpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef terminal_h
#define terminal_h

#include <string>
using std::string;

namespace splashkit_lib
{
    void activate_advanced_terminal();
    void end_advanced_terminal();
    void terminal_move_cursor_to(int x, int y);
    void refresh_terminal();
    void clear_terminal();
    string read_line();
    int terminal_width();
    int terminal_height();
    void write(string text);
    void write_line(string line);
    void terminal_write(string text, int x, int y);
}

#endif /* terminal_h */
