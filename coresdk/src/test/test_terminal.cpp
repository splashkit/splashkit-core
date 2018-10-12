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
    write_line("Test character output");
    write('a');
    write_line();
    write_line('c');

    if ( advanced_terminal_active() )
    {
        refresh_terminal();
    }

    delay(1000);
}

void test_advanced_terminal()
{
    move_cursor_to(34, 10);

    set_terminal_colors(COLOR_RED, COLOR_GREEN);
    clear_terminal();
    write_line("Hello World!");

    write_at("Enter Name:", 34, 11);
    move_cursor_to(34, 12);
    refresh_terminal();

    set_terminal_colors(COLOR_WHITE, COLOR_GREEN);
    string name = read_line();

    clear_terminal();


    write_at("HELLO", (terminal_width() - 5) / 2, 1);
    set_terminal_bold(true);
    write_at(name, static_cast<int>(terminal_width() - name.length()) / 2 , terminal_height() / 2);
    set_terminal_bold(false);

    refresh_terminal();

    delay(1000);
    end_advanced_terminal();
}

void run_terminal_test()
{
    int go = 0;

    cout << "Activate advanced terminal (1-yes, 0-no): ";
    cin >> go;

    if ( go != 0 )
    {
        activate_advanced_terminal();
    }

    test_simple_terminal();
    test_advanced_terminal();
}
