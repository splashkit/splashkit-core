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
    bool ctx_started = false;

    static mu_Id focused_text_box = 0;

    static bool element_changed = false;
    static bool element_confirmed = false;

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

    // Style cache

    static mu_Style default_style;

    struct shadow_style
    {
        color clr;
        int radius;
        point_2d offset;
    };

    static shadow_style panel_shadow_style;
    static shadow_style element_shadow_style;

    // Font handling
    static font current_font = nullptr;
    static int current_font_size = 13;

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
        sk_text_size(font_info->first, font_info->second, std::string(text, len), &w, &h);
        return w;
    }

    int _text_height(mu_Font font)
    {
        font_size_pair* font_info = _get_font_size_pair(font);

        if (!font_info || !font_info->first) return 8;

        return sk_text_height(font_info->first, font_info->second);
    }

    // Icon Handling
    // MicroUI only allows us to pass an int (not even a void*!) for the icon, so we store
    // all the bitmap data in a vector that can be referenced using that int.
    struct registered_icon
    {
        sk_drawing_surface* src;
        double src_data[4];
        double dst_data[7];
        sk_renderer_flip flip;
    };

    std::vector<registered_icon> registered_icons_this_frame;

    // returns registered icon's index, with +MU_ICON_MAX offset
    int sk_interface_register_icon(sk_drawing_surface* src, const double (&src_data)[4], const double (&dst_data)[7], sk_renderer_flip flip)
    {
        registered_icons_this_frame.push_back({
            src,
            {src_data[0],src_data[1],src_data[2],src_data[3]},
            {dst_data[0],dst_data[1],dst_data[2],dst_data[3],dst_data[4],dst_data[5],dst_data[6]},
            flip
        });

        return registered_icons_this_frame.size()-1 + MU_ICON_MAX;
    }

    registered_icon* _get_registered_icon(int icon)
    {
        icon -= MU_ICON_MAX;

        if (icon < 0 || icon > registered_icons_this_frame.size())
            return nullptr;

        return &registered_icons_this_frame[icon];
    }


    // conversion util functions
    mu_Rect to_mu(rectangle rect)
    {
        return {(int)rect.x, (int)rect.y, (int)rect.width, (int)rect.height};
    }

    mu_Color to_mu(color col)
    {
        return {
            (unsigned char)(col.r * 255),
            (unsigned char)(col.g * 255),
            (unsigned char)(col.b * 255),
            (unsigned char)(col.a * 255)
        };
    }

    rectangle from_mu(mu_Rect rect)
    {
        return {(double)rect.x, (double)rect.y, (double)rect.w, (double)rect.h};
    }

    color from_mu(mu_Color col)
    {
        return {col.r / 255.0f, col.g / 255.0f, col.b / 255.0f, col.a / 255.0f};
    }

    // static utility functions straight from microui.c - used for consistency
    static mu_Rect expand_rect(mu_Rect rect, int n) {
        return mu_rect(rect.x - n, rect.y - n, rect.w + n * 2, rect.h + n * 2);
    }
    static mu_Rect intersect_rects(mu_Rect r1, mu_Rect r2) {
        int x1 = mu_max(r1.x, r2.x);
        int y1 = mu_max(r1.y, r2.y);
        int x2 = mu_min(r1.x + r1.w, r2.x + r2.w);
        int y2 = mu_min(r1.y + r1.h, r2.y + r2.h);
        if (x2 < x1) { x2 = x1; }
        if (y2 < y1) { y2 = y1; }
        return mu_rect(x1, y1, x2 - x1, y2 - y1);
    }
    static mu_Rect unclipped_rect = { 0, 0, 0x1000000, 0x1000000 };

    // custom microui commands
    #define MU_COMMAND_BLUR_RECT (MU_COMMAND_MAX+1)

    typedef struct { mu_BaseCommand base; mu_Rect rect; mu_Color color; int radius;} mu_BlurredRectCommand;


    // custom drawning commands
    void draw_blurred_rect(mu_Context *ctx, mu_Rect rect, mu_Color color, int blur_radius){
        rect = intersect_rects(rect, expand_rect(mu_get_clip_rect(ctx), blur_radius));

        if (rect.w > 0 && rect.h > 0) {
            int clipped = mu_check_clip(ctx, rect);
            if (clipped) { mu_set_clip(ctx, mu_get_clip_rect(ctx)); }

            mu_BlurredRectCommand* cmd = (mu_BlurredRectCommand*)mu_push_command(ctx, MU_COMMAND_BLUR_RECT, sizeof(mu_BlurredRectCommand));
            cmd->rect = rect;
            cmd->color = color;
            cmd->radius = blur_radius;

            if (clipped) { mu_set_clip(ctx, unclipped_rect); }
        }
    }

    static void draw_frame(mu_Context *ctx, mu_Rect rect, int colorid) {
        shadow_style& shadow = colorid==MU_COLOR_WINDOWBG?panel_shadow_style:element_shadow_style;

        // draw shadow if the right element type
        if (shadow.clr.a>0.f && (
            colorid == MU_COLOR_WINDOWBG ||
            colorid == MU_COLOR_SCROLLTHUMB ||
            colorid == MU_COLOR_BUTTON ||
            colorid == MU_COLOR_BUTTONHOVER ||
            colorid == MU_COLOR_BUTTONFOCUS ||
            colorid == MU_COLOR_BASE ||
            colorid == MU_COLOR_BASEHOVER ||
            colorid == MU_COLOR_BASEFOCUS
        )){
            mu_Rect shadow_rect = rect;
            shadow_rect.x += shadow.offset.x;
            shadow_rect.y += shadow.offset.y;
            draw_blurred_rect(ctx, shadow_rect, to_mu(shadow.clr), shadow.radius);
        }

        // draw main frame
        if (ctx->style->colors[colorid].a)
            mu_draw_rect(ctx, rect, ctx->style->colors[colorid]);

        if (colorid == MU_COLOR_SCROLLBASE  ||
        colorid == MU_COLOR_TITLEBG) { return; }

        // draw border
        if (ctx->style->colors[MU_COLOR_BORDER].a)
            mu_draw_box(ctx, expand_rect(rect, 1), ctx->style->colors[MU_COLOR_BORDER]);
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
                    sk_set_bitmap_pixel(&ui_atlas, {1.f, 1.f, 1.f, atlas_texture[y * ATLAS_WIDTH + x]/255.f}, x, y);

            sk_refresh_bitmap(&ui_atlas);
            ui_atlas_loaded = true;
        }

        return &ui_atlas;
    }

    static void(*style_init_callback)() = nullptr;
    void sk_interface_init()
    {
        _initialize_button_and_key_map();
        _initialize_atlas_map();

        ctx = (mu_Context*)malloc(sizeof(mu_Context));
        mu_init(ctx);
        ctx->text_width = _text_width;
        ctx->text_height = _text_height;
        ctx->draw_frame = &draw_frame;

        default_style = *ctx->style;
        sk_interface_style_reset();

        if (style_init_callback)
            style_init_callback();

        // Create custom logger - the default SplashKit is a bit verbose
        // for the messages this wants to be able to output
        el::Logger* interfaceLogger = el::Loggers::getLogger("interface");
        el::Configurations conf;
        conf.setToDefault();
        conf.setGlobally(el::ConfigurationType::Format, "%level -> %msg");
        conf.setGlobally(el::ConfigurationType::Filename, "logs/splashkit.log");

        el::Loggers::reconfigureLogger("interface", conf);
    }

    void sk_interface_set_init_style_callback(void(*callback)())
    {
        style_init_callback = callback;
        // if we've already initialized, call back now
        if (ctx)
            style_init_callback();
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

                    case MU_COMMAND_BLUR_RECT:
                        mu_BlurredRectCommand* brect;
                        brect = (mu_BlurredRectCommand*)cmd;
                        sk_draw_blurred_rect(surface, from_mu(brect->color), brect->rect.x, brect->rect.y, brect->rect.w, brect->rect.h, brect->radius);

                        break;

                    case MU_COMMAND_ICON:
                        rectangle atlas_rect;
                        double src_data[4];
                        double dst_data[7];
                        sk_renderer_flip flip;

                        // if it's a custom icon, handle specially
                        if (cmd->icon.id >= MU_ICON_MAX)
                        {
                            registered_icon* icon = _get_registered_icon(cmd->icon.id);
                            if (icon)
                            {
                                icon->dst_data[0] = cmd->icon.rect.x + (cmd->icon.rect.w - icon->src_data[2]) / 2; // X
                                icon->dst_data[1] = cmd->icon.rect.y + (cmd->icon.rect.h - icon->src_data[3]) / 2; // Y
                                sk_draw_bitmap(icon->src, surface, icon->src_data, 4, icon->dst_data, 7, icon->flip);
                            }
                        }
                        else // otherwise draw from atlas
                        {
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

                            sk_set_bitmap_tint(ui_atlas, from_mu(cmd->icon.color));
                            sk_draw_bitmap(ui_atlas, surface, src_data, 4, dst_data, 7, flip);
                        }

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
        registered_icons_this_frame.clear();
        ctx->style->font = _add_font_size_pair(current_font, current_font_size);

        // if re-starting without properly ending, end first
        if (ctx_started) sk_interface_end();

        mu_begin(ctx);
        ctx_started = true;

        // create invisible root window, so we can draw directly on the main window
        mu_begin_window_ex(ctx, "", unclipped_rect,
            MU_OPT_NOFRAME|MU_OPT_NOTITLE|MU_OPT_NOCLOSE|MU_OPT_NORESIZE|
            MU_OPT_NOINTERACT|MU_OPT_NOSCROLL
        );
        mu_get_current_container(ctx)->zindex = -1;
        int widths[] = {0};
        sk_interface_set_layout(1,widths,0);
    }

    void sk_interface_end()
    {
        // end root window
        mu_end_window(ctx);

        mu_end(ctx);
        ctx_started = false;

        // If we were focussed on a text box previously, but now aren't,
        // then stop reading.
        if (focused_text_box != 0 && ctx->focus != focused_text_box)
        {
            focused_text_box = 0;
            current_window()->reading_text = false;
        }
    }

    bool sk_interface_is_started()
    {
        return ctx_started;
    }

    bool sk_interface_capacity_limited()
    {
        #define INTERFACE_SAFE_CAPACITY 0.93 //~(30/32)
        return
        (ctx->command_list.idx      > MU_COMMANDLIST_SIZE    * INTERFACE_SAFE_CAPACITY) ||
        (ctx->root_list.idx         > MU_ROOTLIST_SIZE       * INTERFACE_SAFE_CAPACITY) ||
        (ctx->container_stack.idx   > MU_CONTAINERSTACK_SIZE * INTERFACE_SAFE_CAPACITY) ||
        (ctx->clip_stack.idx        > MU_CLIPSTACK_SIZE      * INTERFACE_SAFE_CAPACITY) ||
        (ctx->id_stack.idx          > MU_IDSTACK_SIZE        * INTERFACE_SAFE_CAPACITY) ||
        (ctx->layout_stack.idx      > MU_LAYOUTSTACK_SIZE    * INTERFACE_SAFE_CAPACITY);
        #undef INTERFACE_SAFE_CAPACITY
    }

    bool sk_interface_start_panel(const string& name, rectangle initial_rectangle)
    {
        return mu_begin_window(ctx, name.c_str(), to_mu(initial_rectangle));
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

    void sk_interface_start_inset(const string& name)
    {
        mu_begin_panel(ctx, name.c_str());
    }

    void sk_interface_end_inset()
    {
        mu_end_panel(ctx);
    }

    bool sk_interface_start_treenode(const string& name)
    {
        return mu_begin_treenode(ctx, name.c_str());
    }

    void sk_interface_end_treenode()
    {
        mu_end_treenode(ctx);
    }

    void sk_interface_open_popup(const string& name)
    {
        mu_open_popup(ctx, name.c_str());
    }

    void sk_interface_set_layout(int items, int* widths, int height)
    {
        mu_layout_row(ctx, items, widths, height);
    }

    void sk_interface_set_layout_next(const rectangle& rect, bool relative)
    {
        mu_layout_set_next(ctx, to_mu(rect), relative ? 1 : 2);/*see microui.c line 527*/
    }

    void sk_interface_set_layout_width(int width)
    {
        mu_layout_width(ctx, width);
    }

    void sk_interface_set_layout_height(int height)
    {
        mu_layout_height(ctx, height);
    }

    void sk_interface_start_column()
    {
        mu_layout_begin_column(ctx);
    }

    void sk_interface_end_column()
    {
        mu_layout_end_column(ctx);
    }

    int sk_interface_get_container_width()
    {
        return mu_get_current_container(ctx)->body.w;
    }

    int sk_interface_get_container_height()
    {
        return mu_get_current_container(ctx)->body.h;
    }

    int sk_interface_get_layout_width()
    {
        if (ctx->layout_stack.idx <= 0) return 0;

        return ctx->layout_stack.items[ctx->layout_stack.idx - 1].body.w;
    }

    int sk_interface_get_layout_height()
    {
        if (ctx->layout_stack.idx <= 0) return 0;

        return ctx->layout_stack.items[ctx->layout_stack.idx - 1].body.h;
    }

    void update_elements_changed(int result)
    {
        element_changed = result;
        element_confirmed = result & MU_RES_SUBMIT;
    }

    void sk_interface_push_ptr_id(void* ptr)
    {
        mu_push_id(ctx, &ptr, sizeof(ptr));
    }

    void sk_interface_pop_id()
    {
        mu_pop_id(ctx);
    }

    bool sk_interface_header(const string& label_text)
    {
        return mu_header(ctx, label_text.c_str());
    }

    void sk_interface_label(const string& label_text)
    {
        mu_label(ctx, label_text.c_str());
    }

    void sk_interface_text(const string& text)
    {
        mu_text(ctx, text.c_str());
    }

    bool sk_interface_button(const string& label_text, int icon)
    {
        update_elements_changed(mu_button_ex(ctx, label_text.c_str(), icon, MU_OPT_ALIGNCENTER));
        return element_confirmed;
    }

    bool sk_interface_checkbox(const string& label_text, const bool& value)
    {
        sk_interface_push_ptr_id((void*)&value);

        int temp_value = value;
        update_elements_changed(mu_checkbox(ctx, label_text.c_str(), &temp_value));

        sk_interface_pop_id();
        return temp_value;
    }

    float sk_interface_slider(const float& value, float min_value, float max_value)
    {
        sk_interface_push_ptr_id((void*)&value);

        float temp_value = value;
        update_elements_changed(mu_slider(ctx, &temp_value, min_value, max_value));

        sk_interface_pop_id();
        return temp_value;
    }

    float sk_interface_number(const float& value, float step)
    {
        sk_interface_push_ptr_id((void*)&value);

        float temp_value = value;
        update_elements_changed(mu_number(ctx, &temp_value, step));

        sk_interface_pop_id();
        return temp_value;
    }

    std::string sk_interface_text_box(const std::string& id, const std::string& value)
    {
        // const std::string* id = &value; 
        mu_Id m_id = mu_get_id(ctx, id.c_str(), id.length());
        mu_Rect r = mu_layout_next(ctx);

        // max 512 characters
        // considering the lack of word wrap or even
        // keyboard navigation, this should be enough.
        char temp_value[512];

        bool was_focused = ctx->focus == m_id;

        // If focussed, temporarily add the current composition to the string - we'll remove it at the end
        if (was_focused)
            strncpy(temp_value, (value+current_window()->composition).c_str(), sizeof(temp_value));
        else
            strncpy(temp_value, value.c_str(), sizeof(temp_value));

        temp_value[sizeof(temp_value) - 1] = 0;

        update_elements_changed(mu_textbox_raw(ctx, temp_value, sizeof(temp_value), m_id, r, 0));

        // Is this element newly focussed?
        if (ctx->focus == m_id)
        {
            // Start reading
            if (focused_text_box == 0)
                sk_start_reading_text(current_window(), r.x, r.y, r.w, r.h, "");
            focused_text_box = m_id;
        }

        // Remove the composition from the string if it was added
        if (was_focused)
            return std::string(temp_value, 0, strlen(temp_value) - current_window()->composition.size());
        else
            return temp_value;
    }

    void sk_interface_color_box(color clr)
    {
        mu_Rect rect = mu_layout_next(ctx);
        mu_draw_rect(ctx, rect, to_mu(clr));
        mu_draw_box(ctx, rect, to_mu(COLOR_BLACK));
    }

    bool sk_interface_changed()
    {
        return element_changed;
    }

    bool sk_interface_confirmed()
    {
        return element_confirmed;
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

    void sk_interface_style_reset()
    {
        *ctx->style = default_style;
        panel_shadow_style.clr = COLOR_BLACK;
        panel_shadow_style.radius = 35;
        panel_shadow_style.offset = {16,16};
        element_shadow_style.clr = COLOR_BLACK;
        element_shadow_style.radius = 7;
        element_shadow_style.offset = {3,3};
    }

    void sk_interface_style_set_border_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_BORDER] = to_mu(clr);
    }

    void sk_interface_style_set_text_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_TEXT] = to_mu(clr);
    }

    void sk_interface_style_set_title_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_TITLETEXT] = to_mu(clr);
    }

    void sk_interface_style_set_titlebar_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_TITLEBG] = to_mu(clr);
    }

    void sk_interface_style_set_panel_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_WINDOWBG] = to_mu(clr);
    }

    void sk_interface_style_set_inset_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_PANELBG] = to_mu(clr);
    }

    void sk_interface_style_set_button_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_BUTTON] = to_mu(clr);
    }

    void sk_interface_style_set_button_accent_colors(sk_color hover_clr, sk_color active_clr)
    {
        ctx->style->colors[MU_COLOR_BUTTONHOVER] = to_mu(hover_clr);
        ctx->style->colors[MU_COLOR_BUTTONFOCUS] = to_mu(active_clr);
    }

    void sk_interface_style_set_control_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_BASE] = to_mu(clr);
    }

    void sk_interface_style_set_control_accent_colors(sk_color hover_clr, sk_color active_clr)
    {
        ctx->style->colors[MU_COLOR_BASEHOVER] = to_mu(hover_clr);
        ctx->style->colors[MU_COLOR_BASEFOCUS] = to_mu(active_clr);
    }

    void sk_interface_style_set_scroll_base_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_SCROLLBASE] = to_mu(clr);
    }

    void sk_interface_style_set_scrollbar_color(sk_color clr)
    {
        ctx->style->colors[MU_COLOR_SCROLLTHUMB] = to_mu(clr);
    }

    void sk_interface_style_set_panel_shadow_color(sk_color clr)
    {
        panel_shadow_style.clr = clr;
    }

    void sk_interface_style_set_panel_shadow_radius(int radius)
    {
        panel_shadow_style.radius = radius;
    }

    void sk_interface_style_set_panel_shadow_offset(point_2d offset)
    {
        panel_shadow_style.offset = offset;
    }

    void sk_interface_style_set_element_shadow_color(sk_color clr)
    {
        element_shadow_style.clr = clr;
    }

    void sk_interface_style_set_element_shadow_radius(int radius)
    {
        element_shadow_style.radius = radius;
    }

    void sk_interface_style_set_element_shadow_offset(point_2d offset)
    {
        element_shadow_style.offset = offset;
    }

    void sk_interface_style_set_padding(int padding)
    {
        ctx->style->padding = padding;
    }

    void sk_interface_style_set_spacing(int spacing)
    {
        ctx->style->spacing = spacing;
    }

    void sk_interface_style_set_indent(int indent)
    {
        ctx->style->indent = indent;
    }

    void sk_interface_style_set_title_height(int title_height)
    {
        ctx->style->title_height = title_height;
    }

    void sk_interface_style_set_scrollbar_size(int scrollbar_size)
    {
        ctx->style->scrollbar_size = scrollbar_size;
    }

    void sk_interface_style_set_thumb_size(int thumb_size)
    {
        ctx->style->thumb_size = thumb_size;
    }

    int sk_interface_style_get_padding()
    {
        return ctx->style->padding;
    }
    int sk_interface_style_get_spacing()
    {
        return ctx->style->spacing;
    }

    static bool interface_enabled = true;

    // MicroUI has no inbuilt functionality for disabling
    // the UI, so we emulate it by taking a copy of current
    // input state, then zeroing out everything.
    // We then restore it once the interface is enabled again.
    void sk_interface_set_enabled(bool enabled)
    {
        // copy of relevant input state
        static mu_Id focus;
        static mu_Vec2 mouse_pos;
        static int mouse_down;
        static int mouse_pressed;
        static int key_down;
        static int key_pressed;

        if (interface_enabled == enabled)
            return;

        interface_enabled = enabled;

        if (interface_enabled)
        {
            ctx->focus =          focus;
            ctx->mouse_pos =      mouse_pos;
            ctx->mouse_down =     mouse_down;
            ctx->mouse_pressed =  mouse_pressed;
            ctx->key_down =       key_down;
            ctx->key_pressed =    key_pressed;
        }
        else
        {
            focus =          ctx->focus;
            mouse_pos =      ctx->mouse_pos;
            mouse_down =     ctx->mouse_down;
            mouse_pressed =  ctx->mouse_pressed;
            key_down =       ctx->key_down;
            key_pressed =    ctx->key_pressed;

            ctx->focus = -1;
            ctx->mouse_pos ={ -1, -1 };
            ctx->mouse_down = 0;
            ctx->mouse_pressed = 0;
            ctx->key_down = 0;
            ctx->key_pressed = 0;
        }
    }

    bool sk_interface_is_enabled()
    {
        return interface_enabled;
    }
}
