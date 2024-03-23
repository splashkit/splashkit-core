// interface_driver.h
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Sean Boettger. All Rights Reserved.

#ifndef SPLASHKIT_INTERFACE_H
#define SPLASHKIT_INTERFACE_H

// temporary hash defines
#define FONT_SIZE 12
#define FONT_NAME font_named("input")

#include <stdint.h>
namespace splashkit_lib
{
    void sk_interface_init();
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