//
//  test_ui.cpp
//  splashkit
//
//  Created by Sean Boettger on 22/03/2024.
//  Copyright © 2024 Sean Boettger. All rights reserved.
//

#include "graphics.h"
#include "terminal.h"
#include "window_manager.h"
#include "utils.h"
#include "input.h"
#include "interface.h"
extern "C" {
#include "microui.h"
}
#include <vector>
#include <iostream>
using namespace std;
using namespace splashkit_lib;

void run_ui_test()
{
    open_window("Test UI", 600, 600);

    set_interface_font(load_font("input", "arial.ttf"));
    set_interface_font_size(12);

    while( not quit_requested() )
    {
        process_events();

        clear_screen(COLOR_WHITE);

        // Show a window if it hasn't been closed.
        // Defaults to 2 column layout (for label + element)
        if (start_panel("My Window", rectangle_from(100, 100, 240, 186)))
        {
            // Draw first label + button
            label("First:");
            if (button("Button1"))
            {
                write_line("Button1 pressed");
            }

            // Draw second label + button
            label("Second:");
            if (button("Button2"))
            {
                open_popup("My Popup");
            }

            // Show the popup if it's been opened
            if (start_popup("My Popup"))
            {
                label("Hello world!");
                end_popup("My Popup");
            }

            end_panel("My Window");
        }

        // Draw the interface
        draw_interface();

        refresh_screen(60);

        if (quit_requested() ) break;
    }

    close_window(window_named("Test UI"));
}