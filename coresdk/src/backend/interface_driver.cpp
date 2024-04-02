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
#include <set>

using namespace std;

extern "C" {
#include "microui.h"
}

namespace splashkit_lib
{
    #include "interface_driver_atlas.h"

    static mu_Context *ctx = nullptr;

    static char button_map[256];
    static char key_map[256];

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

    // Font handling
    static font current_font = nullptr;
    static int current_font_size = 14;

    // Store font/size pairs inside a set.
    //
    // Iterators stay valid while inserting,
    // so this is used as a stable place to
    // store these pairs, which can then be assigned
    // to MicroUI's font void* and used later on
    typedef std::pair<font, int> font_size_pair;
    static std::set<font_size_pair> fonts_this_frame;

    // Adds a pair to the set and returns a void* to it
    void* _add_font_size_pair(font fnt, int size)
    {
        return (void*)&*fonts_this_frame.insert({fnt, size}).first;
    }

    // Returns the font/size pair from a pointer
    font_size_pair* _get_font_size_pair(void* ptr)
    {
        return (font_size_pair*)ptr;
    }

    int _text_width(mu_Font font, const char *text, int len)
    {
        if (len == -1) { len = strlen(text); }

        font_size_pair* font_info = _get_font_size_pair(font);

        if (!font_info || !font_info->first) return 8 * len;

        int w,h;
        sk_text_size(font_info->first, font_info->second, text, &w, &h);
        return w;
    }

    int _text_height(mu_Font font)
    {
        font_size_pair* font_info = _get_font_size_pair(font);

        if (!font_info || !font_info->first) return 8;

        return sk_text_height(font_info->first, font_info->second);
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

    // Delay loading of the ui atlas until it's actually needed
    // otherwise we'll trigger creating the 'initial window' unnecessarily
    sk_drawing_surface* get_ui_atlas()
    {
        static sk_drawing_surface ui_atlas;
        static bool ui_atlas_loaded = false;

        if (!ui_atlas_loaded)
        {
            ui_atlas = sk_create_bitmap(ATLAS_WIDTH, ATLAS_HEIGHT);

            // Fill the bitmap with values from atlas_texture
            for(int y = 0; y < ATLAS_HEIGHT; y++)
                for(int x = 0; x < ATLAS_WIDTH; x++)
                    sk_draw_pixel(&ui_atlas, {1.f, 1.f, 1.f, atlas_texture[y * ATLAS_WIDTH + x]/255.f}, x, y);

            ui_atlas_loaded = true;
        }

        return &ui_atlas;
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
        }
    }

    void sk_interface_draw(drawing_options opts)
    {
        sk_interface_end();

        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        sk_drawing_surface* ui_atlas = get_ui_atlas();

        if (surface)
        {
            mu_Command *cmd = NULL;
            while (mu_next_command(ctx, &cmd))
            {
                switch (cmd->type)
                {
                    case MU_COMMAND_TEXT:
                        const font_size_pair* font_info;
                        font_info = _get_font_size_pair(cmd->text.font);

                        if (cmd->text.font)
                            sk_draw_text(surface, font_info->first, font_info->second, cmd->text.pos.x, cmd->text.pos.y, cmd->text.str, from_mu(cmd->text.color));

                        break;

                    case MU_COMMAND_RECT:
                        sk_fill_aa_rect(surface, from_mu(cmd->rect.color), cmd->rect.rect.x, cmd->rect.rect.y, cmd->rect.rect.w, cmd->rect.rect.h);

                        break;

                    case MU_COMMAND_ICON:
                        rectangle atlas_rect;
                        double src_data[4];
                        double dst_data[7];
                        sk_renderer_flip flip;

                        atlas_rect = atlas[cmd->icon.id];

                        src_data[0] = atlas_rect.x;
                        src_data[1] = atlas_rect.y;
                        src_data[2] = atlas_rect.width;
                        src_data[3] = atlas_rect.height;

                        dst_data[0] = cmd->icon.rect.x + (cmd->icon.rect.w - atlas_rect.width) / 2; // X
                        dst_data[1] = cmd->icon.rect.y + (cmd->icon.rect.h - atlas_rect.height) / 2; // Y
                        dst_data[2] = opts.angle; // Angle
                        dst_data[3] = opts.anchor_offset_x; // Centre X
                        dst_data[4] = opts.anchor_offset_y; // Centre Y
                        dst_data[5] = opts.scale_x; // Scale X
                        dst_data[6] = opts.scale_y; // Scale Y

                        flip = sk_FLIP_NONE;

                        sk_draw_bitmap(ui_atlas, surface, src_data, 4, dst_data, 7, flip);

                        break;

                    case MU_COMMAND_CLIP:
                        sk_set_clip_rect(surface, cmd->clip.rect.x, cmd->clip.rect.y, cmd->clip.rect.w, cmd->clip.rect.h);

                        break;
                }
            }
        }
    }

    void sk_interface_style_set_font(font fnt)
    {
        current_font = fnt;

        ctx->style->font = _add_font_size_pair(current_font, current_font_size);
        ctx->style->size.y = current_font_size;
    }

    void sk_interface_style_set_font_size(int size)
    {
        current_font_size = size;

        ctx->style->font = _add_font_size_pair(current_font, current_font_size);
        ctx->style->size.y = current_font_size;
    }

    void sk_interface_start()
    {
        fonts_this_frame.clear();
        ctx->style->font = _add_font_size_pair(current_font, current_font_size);

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