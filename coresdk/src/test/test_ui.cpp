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
#include <vector>
#include <iostream>
using namespace std;
using namespace splashkit_lib;

void run_ui_test()
{
    open_window("Test UI", 600, 600);

    font fontA = load_font("interface font 1", "arial.ttf");
    font fontB = load_font("interface font 2", "kochi-gothic-subst.ttf");
    set_interface_font(fontA);
    set_interface_font_size(12);

    // Some variables to test the elements with
    bool checkbox_val = false;
    float val1 = 0;
    float val2 = 0;
    float val3 = 0;
    std::string text_box_val1 = "Type here!";
    std::string text_box_val2 = "And here!";

    // A sprite to test bitmap buttons
    animation_script player_animations = load_animation_script("player_animations", "player_animations.txt");
    animation anim = create_animation(player_animations, "Fly");
    bitmap player = load_bitmap("player", "player.png");
    bitmap_set_cell_details(player, 300/4, 42, 4, 1, 4);
    bool scale_image = true;

    while( not quit_requested() )
    {
        process_events();

        clear_screen(COLOR_WHITE);

        // Show a window if it hasn't been closed.
        if (start_panel("My Window", rectangle_from(300, 4, 240, 186)))
        {
            if (header("Buttons!"))
            {
                // Draw some paragraphs of text
                paragraph("Here we test out a couple of buttons! Hopefully they work!");
                set_interface_font(fontB);
                paragraph("ここではボタンをいくつか試してみます！ ちゃんと押せるといいですね！");
                set_interface_font(fontA);

                // Draw first label + button
                if (button("First:", "Button1"))
                {
                    write_line("Button1 pressed");
                }

                // Draw a disabled button
                disable_interface();
                if (button("Disabled:", "Disabled button"))
                {
                    write_line("I can't be pressed!");
                }
                enable_interface();

                // Example of custom layout
                start_custom_layout();
                add_column(60);
                add_column(60);
                add_column(-1);

                label_element("Second:");
                // Draw second label + button
                if (button("Button2"))
                {
                    open_popup("My Popup");
                }
                // Draw second label + button
                if (button("Button3"))
                {
                    open_popup("My Popup");
                    checkbox_val = true;
                }

                reset_layout();

                // Draw a checkbox
                checkbox_val = checkbox("Did they work?", checkbox_val);

                bitmap_button("Image!", player, option_scale_bmp(scale_image?0.45f:1.f,scale_image?0.45f:1.f, option_with_animation(anim)));
                scale_image = checkbox("Scale icon?", scale_image);
                update_animation(anim);

                if ( animation_ended(anim) )
                    assign_animation(anim, player_animations, "Fly");
            }

            // Show the popup if it's been opened
            if (start_popup("My Popup"))
            {
                // Increase the size of the text
                // and change font for the popup
                set_interface_font(fontB);
                set_interface_font_size(14);

                label_element("Hi world!");

                // Switch back to the original font for
                // second label.
                set_interface_font(fontA);

                label_element("Hello world!");

                // Reset text size
                set_interface_font_size(12);

                end_popup("My Popup");
            }

            if (header("Sliders!"))
            {
                // Show a slider with a label
                val1 = slider("Slider", val1, -25, 25);

                // Show two sliders without labels
                val2 = slider(val2, 0, 100);
                val3 = slider(val3, -25, 25);

                // Show checkbox that's checked when we drag the slider
                checkbox("Currently dragging third slider?", last_element_changed());
            }


            if (header("Text/Number boxes!"))
            {
                // Show a number box
                val3 = number_box("Number: ", val3, 1.0);

                // Show two text boxes
                text_box_val1 = text_box("V1", text_box_val1);
                if (last_element_confirmed())
                {
                    checkbox_val = true;
                }
                set_interface_font(fontB);
                text_box_val2 = text_box("Text:", text_box_val2, true);
                set_interface_font(fontA);
            }

            // Show if the window is currently reading text,
            // useful for testing that behaviour.
            label_element("Is reading text: " + (std::string)(reading_text()?"Yea":"Nay"));
            end_panel("My Window");
        }


        if (start_panel("Second Window", rectangle_from(300, 200, 240, 186)))
        {
            start_inset("TreeView", -25);
                if (start_treenode("Node1"))
                {
                    if (start_treenode("Inner Node"))
                    {
                        button("Hello!");
                        slider("Slider", 6, 0, 10);
                        end_treenode("Inner Node");
                    }
                    end_treenode("Node1");
                }
                if (start_treenode("Node2"))
                {
                    button("Hello again!");
                    checkbox("It works right?", true);
                    end_treenode("Node2");
                }

            end_inset("TreeView");

            end_panel("Second Window");
        }

        // show some elements on the window directly
        paragraph("Here we can see that elements can also be drawn directly onto the main window! Including paragraphs of text like this.", {40, 20, 200, 64});
        if (button("Button1", rectangle_from(40, 140, 64, 20)))
        {
            write_line("Button1 pressed");
        }
        val2 = slider(val2, 0, 40, {40, 170, 150, 20});
        text_box_val2 = text_box("V2", text_box_val2, rectangle_from(40, 200, 150, 20));

        interface_style_panel(rectangle_from(0, 600-200, 600, 200));

        // Draw the interface
        draw_interface();

        refresh_screen(60);

        if (quit_requested() ) break;
    }

    close_window(window_named("Test UI"));
}
