//
//  terminal.cpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "terminal.h"

#include "utility_functions.h"

#include <ncurses.h>
#include <iostream>
using namespace std;

namespace splashkit_lib
{
    static bool _ncurses_active = false;

    void activate_advanced_terminal()
    {
        if ( _ncurses_active ) return;

        if ( initscr() != nullptr )
        {
            _ncurses_active = true;
            start_color();
            keypad(stdscr, true);
        }
        else
        {
            LOG(WARNING) << "Failed to activate advanced terminal.";
        }
    }

    void terminal_set_echo_input(bool value)
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to set echo status";
            return;
        }

        if ( value ) echo();
        else noecho();
    }

    void terminal_clear()
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to clear the terminal";
            return;
        }

        clear();
    }

    void terminal_refresh()
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to refresh the terminal";
            return;
        }

        refresh();
    }

    void end_advanced_terminal()
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must have activated advanced terminal before ending them";
            return;
        }

        endwin();
        _ncurses_active = false;
    }

    void write(string text)
    {
        if ( _ncurses_active )
            printw("%s", text.c_str());
        else
            cout << text;
    }

    void write_line(string line)
    {
        if (_ncurses_active )
            printw("%s\n", line.c_str());
        else
            cout << line << endl;
    }

    int terminal_width()
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to get terminal width";
            return 0;
        }

        int x, y;
        getmaxyx(stdscr,y,x);

        return x;
    }

    int terminal_height()
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to get terminal height";
            return 0;
        }
        int x, y;
        getmaxyx(stdscr,y,x);
        return y;
    }

    void terminal_write(string text, int x, int y)
    {
        terminal_move_cursor_to(x, y);
        write(text);
    }

    void terminal_set_bold(bool value)
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to print bold text";
            return;
        }

        if (value) attron(A_BOLD);
        else attroff(A_BOLD);
    }

    void terminal_move_cursor_to(int x, int y)
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to move within the terminal";
            return;
        }

        move(y, x);
    }

    string read_line()
    {
        if ( not _ncurses_active )
        {
            string result;
            cin >> result;
            return result;
        }
        else
        {
            char line[2096];
            getnstr(line, 2095);
            return string(line);
        }
    }
}
