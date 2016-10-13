//
//  test_terminal.cpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "terminal.h"
#include "utils.h"
#include "color.h"
#include <iostream>
using namespace std;

using namespace splashkit_lib;

void test_simple_terminal()
{
    write_line("Hello World!" + to_string(10));

    write("Hello");
    write(" ");
    write("World!");
    write_line();

    if ( advanced_terminal_active() )
    {
        terminal_refresh();
    }

    delay(1000);
}

void test_advanced_terminal()
{
    activate_advanced_terminal();
    terminal_clear();

    terminal_move_cursor_to(34, 10);
    termal_set_colors(COLOR_SWINBURNE_RED, COLOR_WHITE);
    write_line("Hello World!");

    terminal_write("Enter Name:", 34, 11);
    terminal_move_cursor_to(34, 12);

    string name = read_line();

    terminal_refresh();
    terminal_clear();

    terminal_set_echo_input(false);
    terminal_write("HELLO", (terminal_width() - 5) / 2, 1);
    terminal_set_bold(true);
    terminal_write(name, static_cast<int>(terminal_width() - name.length()) / 2 , terminal_height() / 2);
    terminal_set_bold(false);

    terminal_refresh();

    delay(1000);
    end_advanced_terminal();
}

void run_terminal_test()
{
    int go;

    cout << "Activate advanced terminal (1-yes, 0-no): ";
    cin >> go;

    if ( go != 0 )
    {
        activate_advanced_terminal();
    }

    test_simple_terminal();
    test_advanced_terminal();
}
