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
    delay(1000);
}

void run_terminal_test()
{
    test_simple_terminal();
}
