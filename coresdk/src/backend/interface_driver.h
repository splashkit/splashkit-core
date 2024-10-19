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
    void sk_interface_set_init_style_callback(void(*callback)());

    void sk_interface_draw(drawing_options opts);

    int sk_interface_register_icon(sk_drawing_surface* src, const double (&src_data)[4], const double (&dst_data)[7], sk_renderer_flip flip);

    void sk_interface_style_set_font(font fnt);
    void sk_interface_style_set_font_size(int size);

    void sk_interface_start();
    void sk_interface_end();
    bool sk_interface_is_started();
    bool sk_interface_capacity_limited();

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
    void sk_interface_set_layout_next(const rectangle& rect, bool relative);
    void sk_interface_set_layout_width(int width);
    void sk_interface_set_layout_height(int height);

    void sk_interface_start_column();
    void sk_interface_end_column();

    int sk_interface_get_container_width();
    int sk_interface_get_container_height();
    int sk_interface_get_layout_width();
    int sk_interface_get_layout_height();

    void sk_interface_push_ptr_id(void* ptr);
    void sk_interface_pop_id();

    bool sk_interface_header(const string& label_text);
    void sk_interface_label(const string& label_text);
    void sk_interface_text(const string& text);
    bool sk_interface_button(const string& label_text, int icon);
    bool sk_interface_checkbox(const string& label_text, const bool& value);
    float sk_interface_slider(const float& value, float min_value, float max_value);
    float sk_interface_number(const float& value, float step);
    std::string sk_interface_text_box(const std::string& value);

    void sk_interface_color_box(color clr);

    bool sk_interface_changed();
    bool sk_interface_confirmed();

    void* sk_interface_get_context();
    void sk_interface_mousemove(int motion_x, int motion_y);
    void sk_interface_scroll(int motion_x, int motion_y);
    void sk_interface_text(char* text);
    void sk_interface_mousedown(int x, int y, int button);
    void sk_interface_mouseup(int x, int y, int button);
    void sk_interface_keydown(int key);
    void sk_interface_keyup(int key);

    void sk_interface_style_reset();

    void sk_interface_style_set_border_color(sk_color clr);
    void sk_interface_style_set_text_color(sk_color clr);
    void sk_interface_style_set_title_color(sk_color clr);
    void sk_interface_style_set_titlebar_color(sk_color clr);
    void sk_interface_style_set_panel_color(sk_color clr);
    void sk_interface_style_set_inset_color(sk_color clr);
    void sk_interface_style_set_button_color(sk_color clr);
    void sk_interface_style_set_button_accent_colors(sk_color hover_clr, sk_color active_clr);
    void sk_interface_style_set_control_color(sk_color clr);
    void sk_interface_style_set_control_accent_colors(sk_color hover_clr, sk_color active_clr);
    void sk_interface_style_set_scroll_base_color(sk_color clr);
    void sk_interface_style_set_scrollbar_color(sk_color clr);

    void sk_interface_style_set_panel_shadow_color(sk_color clr);
    void sk_interface_style_set_panel_shadow_radius(int radius);
    void sk_interface_style_set_panel_shadow_offset(point_2d offset);

    void sk_interface_style_set_element_shadow_color(sk_color clr);
    void sk_interface_style_set_element_shadow_radius(int radius);
    void sk_interface_style_set_element_shadow_offset(point_2d offset);

    void sk_interface_style_set_padding(int padding);
    void sk_interface_style_set_spacing(int spacing);
    void sk_interface_style_set_indent(int indent);
    void sk_interface_style_set_title_height(int title_height);
    void sk_interface_style_set_scrollbar_size(int scrollbar_size);
    void sk_interface_style_set_thumb_size(int thumb_size);

    int sk_interface_style_get_padding();
    int sk_interface_style_get_spacing();

    void sk_interface_set_enabled(bool enabled);
    bool sk_interface_is_enabled();
}
#endif
