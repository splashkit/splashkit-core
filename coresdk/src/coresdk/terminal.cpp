//
//  terminal.cpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <easylogging++.h>

#ifdef WINDOWS
    #include <ncursesw/ncurses.h>
#else
    #include <ncurses.h>
#endif

#include "types.h"

#include <iostream>
#include <map>

using std::map;
using std::pair;
using std::cout;
using std::to_string;
using std::endl;
using std::cin;

namespace splashkit_lib
{
    inline bool operator< (const color& lhs, const color& rhs)
    {
        if ( lhs.a != rhs.a ) return lhs.a < rhs.a;
        if ( lhs.r != rhs.r ) return lhs.r < rhs.r;
        if ( lhs.g != rhs.g ) return lhs.g < rhs.g;
        if ( lhs.b != rhs.b ) return lhs.b < rhs.b;
        return false;
    }

    struct color_pair_data
    {
        int idx;
    };

    static bool _ncurses_active = false;
    static map<pair<color, color>, int> _color_pair_map;

    static map<color, int> _color_map;

    int map_color(color clr)
    {
        // Try and find it first...
        if ( _color_map.count(clr) > 0 )
            return _color_map[clr];

        // Now need to register it...
        if ( _color_map.size() >= COLORS)
        {
            LOG(ERROR) << "You have exceeded the number of colors available in the terminal. The terminal only supports " << COLORS << " colors.";
            return 0;
        }

        int result = static_cast<int>(_color_map.size());

        short r, g, b;
        r = static_cast<short>(clr.r * 1000);
        g = static_cast<short>(clr.g * 1000);
        b = static_cast<short>(clr.b * 1000);

        init_color(result, r, g, b);
        _color_map[clr] = result;

        return result;
    }

    int map_color_pair(color fg, color bg)
    {
        pair<color, color> clr_pair = pair<color, color>(fg, bg);

        // Find it?
        if ( _color_pair_map.count(clr_pair) > 0 )
            return _color_pair_map[clr_pair];

        // Create it
        int result = static_cast<int>(_color_pair_map.size() + 1);
        _color_pair_map[clr_pair] = result;

        init_pair(result, map_color(fg), map_color(bg));

        return result;
    }

    color color_black();
    color color_cyan();
    color color_dark_red();
    color color_green();
    color color_dark_blue();
    color color_dark_cyan();
    color color_dark_gray();
    color color_dark_green();
    color color_yellow();
    color color_light_yellow();
    color color_magenta();
    color color_dark_magenta();
    color color_white();
    color color_gray();
    color color_red();
    color color_blue();

    void move_cursor_to(int x, int y);
    void set_terminal_colors(color foreground, color background);
    void set_terminal_bold(bool value);
    void set_terminal_echo_input(bool value);
    void set_terminal_clear_color(color background);

    void activate_advanced_terminal()
    {
        if ( _ncurses_active ) return;

        if ( initscr() != nullptr )
        {
            _ncurses_active = true;
            if ( has_colors() )
            {
                start_color();
                use_default_colors();

                _color_pair_map.clear();
                _color_map.clear();

                //dull
                map_color( color_black() );
                map_color( color_dark_red() );
                map_color( color_dark_green() );
                map_color( color_yellow() );
                map_color( color_dark_blue() );
                map_color( color_dark_magenta() );
                map_color( color_dark_cyan() );
                map_color( color_gray() );

                //bright
                map_color( color_dark_gray() );
                map_color( color_red() );
                map_color( color_green() );
                map_color( color_light_yellow() );
                map_color( color_blue() );
                map_color( color_magenta() );
                map_color( color_cyan() );
                map_color( color_white() );

            }
            else
                LOG(WARNING) << "The terminal you are using does not support colors";

            keypad(stdscr, true);

            set_terminal_echo_input(true);
            set_terminal_bold(false);
            move_cursor_to(0, 0);
            attron(COLOR_PAIR(0));
            bkgdset(COLOR_PAIR(0));
            clear();
        }
        else
        {
            LOG(WARNING) << "Failed to activate advanced terminal.";
        }
    }

    void set_terminal_echo_input(bool value)
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to set echo status";
            return;
        }

        if ( value ) echo();
        else noecho();
    }

    void clear_terminal()
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to clear the terminal";
            return;
        }

        clear();
    }

    void refresh_terminal()
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to refresh the terminal";
            return;
        }

        refresh();
    }

    bool advanced_terminal_active()
    {
        return _ncurses_active;
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
    
    void write(int data)
    {
        write(to_string(data));
    }

    void write(char data)
    {
        write(string("") + data);
    }
    
    void write(double data)
    {
        write(to_string(data));
    }

    void write_line()
    {
        if (_ncurses_active )
            printw("\n");
        else
            cout << endl;
    }

    void write_line(string line)
    {
        if (_ncurses_active )
            printw("%s\n", line.c_str());
        else
            cout << line << endl;
    }
    
    void write_line(int data)
    {
        write_line(to_string(data));
    }
    
    void write_line(double data)
    {
        write_line(to_string(data));
    }

    void write_line(char data)
    {
        write_line(string("") + data);
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

    void set_terminal_colors(color foreground, color background)
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to print bold text";
            return;
        }
        if ( not can_change_color() )
        {
            LOG(WARNING) << "Unable to change terminal colors in this Terminal";
            return;
        }

        int pair = map_color_pair(foreground, background);
        attron(COLOR_PAIR(pair));
        bkgdset(COLOR_PAIR(pair));
    }

    void set_terminal_bold(bool value)
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to print bold text";
            return;
        }

        if (value) attron(A_BOLD);
        else attroff(A_BOLD);
    }

    void move_cursor_to(int x, int y)
    {
        if ( not _ncurses_active )
        {
            LOG(WARNING) << "You must activate advanced terminal features to move within the terminal";
            return;
        }

        move(y, x);
    }

    void write_at(string text, int x, int y)
    {
        move_cursor_to(x, y);
        write(text);
    }

    string read_line()
    {
        if ( not _ncurses_active )
        {
            string result;
            getline(std::cin, result);
            return result;
        }
        else
        {
            char line[2096];
            getnstr(line, 2095);
            return string(line);
        }
    }

    char read_char()
    {
        char result = 0;
        if ( not _ncurses_active )
            cin >> result;
        else
            result = getch();

        return result;
    }
}
