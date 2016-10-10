//
//  test_terminal.cpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "terminal.h"
#include "utils.h"
#include <iostream>
using namespace std;

using namespace splashkit_lib;

void run_terminal_test()
{
    int go;

    cout << "Run advanced terminal (1-yes, 0-no): ";
    cin >> go;

    if ( go != 0 )
    {
        activate_advanced_terminal();
    }

    clear_terminal();

    terminal_move_cursor_to(34, 10);
    write_line("Hello World!");

    terminal_write("Enter Name:", 34, 11);
    terminal_move_cursor_to(34, 12);

    string name = read_line();

    refresh_terminal();

    clear_terminal();

    terminal_write("HELLO", (terminal_width() - 5) / 2, 1);
    terminal_write(name, static_cast<int>(terminal_width() - name.length()) / 2 , terminal_height() / 2);

    refresh_terminal();

    delay(1000);
    end_advanced_terminal();
}
