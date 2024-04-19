// interface_driver.h
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Sean Boettger. All Rights Reserved.

#ifndef SPLASHKIT_INTERFACE_H
#define SPLASHKIT_INTERFACE_H

#include <stdint.h>
#include "graphics_driver.h"
namespace splashkit_lib
{
    void sk_interface_init();
    void sk_interface_draw(drawing_options opts);

    void sk_interface_style_set_font(font fnt);
    void sk_interface_style_set_font_size(int size);

    void sk_interface_start();
    void sk_interface_end();

    bool sk_interface_start_panel(const string& name, rectangle initial_rectangle);
    void sk_interface_end_panel();

    bool sk_interface_start_popup(const string& name);
    void sk_interface_end_popup();

    void sk_interface_start_inset(const string& name);
    void sk_interface_end_inset();

    bool sk_interface_start_treenode(const string& name);
    void sk_interface_end_treenode();

    void sk_interface_open_popup(const string& name);

    void sk_interface_set_layout(int items, int* widths, int height);
    void sk_interface_start_column();
    void sk_interface_end_column();
    void sk_interface_get_container_size(int& w, int& h);

    bool sk_interface_header(const string& label);
    void sk_interface_label(const string& label);
    bool sk_interface_button(const string& label);

    void* sk_interface_get_context();
    void sk_interface_mousemove(int motion_x, int motion_y);
    void sk_interface_scroll(int motion_x, int motion_y);
    void sk_interface_text(char* text);
    void sk_interface_mousedown(int x, int y, int button);
    void sk_interface_mouseup(int x, int y, int button);
    void sk_interface_keydown(int key);
    void sk_interface_keyup(int key);
}
#endif