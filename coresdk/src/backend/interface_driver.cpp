// interface_driver.cpp
// This file is part of the SplashKit Core Library.
// Copyright (©) 2024 Sean Boettger. All Rights Reserved.

#include "interface_driver.h"
#include "input_driver.h"
#include "graphics_driver.h"
#include "text_driver.h"
#include "utility_functions.h"
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
    #include "interface_driver_atlas.h"

    static mu_Context *ctx = nullptr;
    static sk_drawing_surface ui_atlas;


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



    mu_Rect to_mu(rectangle rect)
    {
        return {(int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height};
    }
    mu_Color to_mu(color col)
    {
        return {(unsigned char)(col.r * 255), (unsigned char)(col.g * 255), (unsigned char)(col.b * 255), (unsigned char)(col.a * 255)};
    }

    rectangle from_mu(mu_Rect rect)
    {
        return {(double)rect.x, (double)rect.y, (double)rect.w, (double)rect.h};
    }
    color from_mu(mu_Color col)
    {
        return {col.r / 255.0f, col.g / 255.0f, col.b / 255.0f, col.a / 255.0f};
    }


    void sk_interface_init()
    {
        if (ctx == nullptr)
        {
            _initialize_button_and_key_map();
            _initialize_atlas_map();

            ctx = (mu_Context*)malloc(sizeof(mu_Context));
            mu_init(ctx);
            ctx->text_width = _text_width;
            ctx->text_height = _text_height;

            ui_atlas = sk_create_bitmap(ATLAS_WIDTH, ATLAS_HEIGHT);
            for(unsigned int i = 0; i < 1/*_sk_num_open_windows*/; i++)
            {
                // sk_create_bitmap created SDL_Texture is SDL_PIXELFORMAT_RGBA8888, while atlas_texture only has 1 channel.
                // Cannot use SDL_LockTexture/SDL_UnlockTexture because the SDL_Texture does not have SDL_TEXTUREACCESS_STREAMING enabled
                // So create a temporary rgba copy of the data, update the texture, then tidy up.
                const int channels = 4;
                char* atlas_texture_rgba = (char*)malloc(sizeof(char) * ATLAS_WIDTH * ATLAS_HEIGHT * channels);

                for(int y = 0; y < ATLAS_HEIGHT; y++)
                    for(int x = 0; x < ATLAS_WIDTH; x++)
                        for(int c = 0; c < channels; c++)
                            atlas_texture_rgba[((y * ATLAS_WIDTH) + x) * channels + c] = atlas_texture[(ATLAS_HEIGHT - y - 1) * ATLAS_WIDTH + x];

                SDL_UpdateTexture(static_cast<sk_bitmap_be *>(ui_atlas._data)->texture[i], NULL, (void*)atlas_texture_rgba, ATLAS_WIDTH * channels);

                free((void*)atlas_texture_rgba);
            }
        }
    }

    void sk_interface_draw(drawing_options opts)
    {
        sk_interface_end();

        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        if (surface)
        {
            mu_Command *cmd = NULL;
            while (mu_next_command(ctx, &cmd))
            {
                switch (cmd->type)
                {
                    case MU_COMMAND_TEXT: sk_draw_text(surface, FONT_NAME, FONT_SIZE, cmd->text.pos.x, cmd->text.pos.y, cmd->text.str, from_mu(cmd->text.color));break;
                    case MU_COMMAND_RECT: sk_fill_aa_rect(surface, from_mu(cmd->rect.color), cmd->rect.rect.x, cmd->rect.rect.y, cmd->rect.rect.w, cmd->rect.rect.h); break;
                    case MU_COMMAND_ICON:
                        double src_data[4];
                        double dst_data[7];
                        sk_renderer_flip flip;

                        src_data[0] = atlas[cmd->icon.id].x;
                        src_data[1] = atlas[cmd->icon.id].y;
                        src_data[2] = atlas[cmd->icon.id].width;
                        src_data[3] = atlas[cmd->icon.id].height;
                        flip = sk_FLIP_NONE;

                        dst_data[0] = cmd->icon.rect.x + (cmd->icon.rect.w - atlas[cmd->icon.id].width) / 2; // X
                        dst_data[1] = cmd->icon.rect.y + (cmd->icon.rect.h - atlas[cmd->icon.id].height) / 2; // Y
                        dst_data[2] = opts.angle; // Angle
                        dst_data[3] = opts.anchor_offset_x; // Centre X
                        dst_data[4] = opts.anchor_offset_y; // Centre Y
                        dst_data[5] = opts.scale_x; // Scale X
                        dst_data[6] = opts.scale_y; // Scale Y

                        sk_draw_bitmap(&ui_atlas, surface, src_data, 4, dst_data, 7, flip);

                    break;

                    case MU_COMMAND_CLIP: sk_set_clip_rect(surface, cmd->clip.rect.x, cmd->clip.rect.y, cmd->clip.rect.w, cmd->clip.rect.h); break;
                }
            }
        }
    }

    void sk_interface_start()
    {
        mu_begin(ctx);
    }

    void sk_interface_end()
    {
        mu_end(ctx);
    }

    bool sk_interface_start_panel(const string& name, rectangle initial_rectangle)
    {
        bool open = mu_begin_window(ctx, name.c_str(), to_mu(initial_rectangle));

        // Default label + element layout
        int layout[] = { 60, -1 };
        mu_layout_row(ctx, 2, layout, 0);

        return open;
    }

    void sk_interface_end_panel()
    {
        mu_end_window(ctx);
    }

    bool sk_interface_start_popup(const string& name)
    {
        return mu_begin_popup(ctx, name.c_str());
    }

    void sk_interface_end_popup()
    {
        mu_end_popup(ctx);
    }

    void sk_interface_open_popup(const string& name)
    {
        mu_open_popup(ctx, name.c_str());
    }

    void sk_interface_label(const string& label)
    {
        mu_label(ctx, label.c_str());
    }

    bool sk_interface_button(const string& label)
    {
        return mu_button(ctx, label.c_str());
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