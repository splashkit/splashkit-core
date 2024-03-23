// interface_driver.cpp
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Sean Boettger. All Rights Reserved.

#include "interface_driver.h"
#include "input_driver.h"
#include "graphics_driver.h"
#include "text_driver.h"
#include "text.h"

#include <string>
#include <iostream>
#include <cstdlib>

using namespace std;

extern "C" {
#include "microui.h"
}

namespace splashkit_lib
{
    static mu_Context *ctx = nullptr;

    static char button_map[256];
    static char key_map[256];

    int _text_width(mu_Font font, const char *text, int len)
    {
        if (len == -1) { len = strlen(text); }
        return text_width((std::string)text, FONT_NAME, FONT_SIZE);
    }

    int _text_height(mu_Font font)
	{
        // We don't recieve a string, so use a string that contains A-Z and a-z
        const char* alphabet = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
        return text_height(alphabet, FONT_NAME, FONT_SIZE);
    }

    void _initialize_button_and_key_map()
    {
        button_map[ SDL_BUTTON_LEFT   & 0xff ] =  MU_MOUSE_LEFT;
        button_map[ SDL_BUTTON_RIGHT  & 0xff ] =  MU_MOUSE_RIGHT;
        button_map[ SDL_BUTTON_MIDDLE & 0xff ] =  MU_MOUSE_MIDDLE;

        key_map[ SDLK_LSHIFT       & 0xff ] = MU_KEY_SHIFT;
        key_map[ SDLK_RSHIFT       & 0xff ] = MU_KEY_SHIFT;
        key_map[ SDLK_LCTRL        & 0xff ] = MU_KEY_CTRL;
        key_map[ SDLK_RCTRL        & 0xff ] = MU_KEY_CTRL;
        key_map[ SDLK_LALT         & 0xff ] = MU_KEY_ALT;
        key_map[ SDLK_RALT         & 0xff ] = MU_KEY_ALT;
        key_map[ SDLK_RETURN       & 0xff ] = MU_KEY_RETURN;
        key_map[ SDLK_BACKSPACE    & 0xff ] = MU_KEY_BACKSPACE;
    }

    void sk_interface_init()
    {
        if (ctx == nullptr)
        {
            _initialize_button_and_key_map();

            ctx = (mu_Context*)malloc(sizeof(mu_Context));
            mu_init(ctx);
            ctx->text_width = _text_width;
            ctx->text_height = _text_height;
        }
    }

    void* sk_interface_get_context()
    {
        return (void*)ctx;
    }

    void sk_interface_mousemove(int motion_x, int motion_y)
    {
        mu_input_mousemove(ctx, motion_x, motion_y);
    }

    void sk_interface_scroll(int motion_x, int motion_y)
    {
        mu_input_scroll(ctx, motion_x, motion_y * -30);
    }

    void sk_interface_text(char* text)
    {
        mu_input_text(ctx, text);
    }

    void sk_interface_mousedown(int x, int y, int button)
    {
        int b = button_map[button & 0xff];
        mu_input_mousedown(ctx, x, y, b);
    }

    void sk_interface_mouseup(int x, int y, int button)
    {
        int b = button_map[button & 0xff];
        mu_input_mouseup(ctx, x, y, b);
    }

    void sk_interface_keydown(int key)
    {
        int c = key_map[key & 0xff];
        mu_input_keydown(ctx, c);
    }

    void sk_interface_keyup(int key)
    {
        int c = key_map[key & 0xff];
        mu_input_keyup(ctx, c);
    }
}