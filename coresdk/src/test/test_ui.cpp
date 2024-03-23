//
//  test_ui.cpp
//  splashkit
//
//  Created by Sean Boettger on 22/03/2024.
//  Copyright © 2024 Sean Boettger. All rights reserved.
//

#include "graphics.h"
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

    // temporary
    load_font("input", "arial.ttf");

    while( not quit_requested() )
    {
        process_events();

        clear_screen(COLOR_WHITE);

        // still need to wrap/abstract out usage of mu_*
        mu_Context* ctx = (mu_Context*)get_interface_ctx();
        mu_begin(ctx);
        if (mu_begin_window(ctx, "My Window", mu_rect(10, 10, 140, 86)))
        {
            int l[] = { 60, -1 };
            mu_layout_row(ctx, 2, l, 0);

            mu_label(ctx, "First:");
            if (mu_button(ctx, "Button1"))
            {
                printf("Button1 pressed\n");
            }

            mu_label(ctx, "Second:");
            if (mu_button(ctx, "Button2"))
            {
                mu_open_popup(ctx, "My Popup");
            }

            if (mu_begin_popup(ctx, "My Popup"))
            {
                mu_label(ctx, "Hello world!");
                mu_end_popup(ctx);
            }

            mu_end_window(ctx);
        }

        mu_end(ctx);

        draw_interface();

        refresh_screen();

        if (quit_requested() ) break;
    }

    close_window(window_named("Test UI"));
}