
//
//  interface.cpp
//  splashkit
//
//  Created by Sean Boettger on 22/03/2024.
//  Copyright © 2024 Sean Boettger. All rights reserved.
//

#include "interface.h"

#include "utils.h"
#include "drawing_options.h"

#include "interface_driver.h"

namespace splashkit_lib
{
    std::vector<int> layout_widths = {-1};
    int layout_height = 0;

    void _update_layout()
    {
        sk_interface_set_layout(layout_widths.size(), &layout_widths[0], layout_height);
    }

    void draw_interface()
    {
        drawing_options opts = option_defaults();

        sk_interface_draw(opts);
    }

    void set_interface_font(font fnt)
    {
        sk_interface_style_set_font(fnt);
    }

    void set_interface_font_size(int size)
    {
        sk_interface_style_set_font_size(size);
    }

    bool start_panel(const string& name, rectangle initial_rectangle)
    {
        bool open = sk_interface_start_panel(name, initial_rectangle);

        reset_layout();

        return open;
    }

    void end_panel(const string& name)
    {
        sk_interface_end_panel();
    }

    bool start_popup(const string& name)
    {
        bool open = sk_interface_start_popup(name);

        return open;
    }

    void end_popup(const string& name)
    {
        sk_interface_end_popup();
    }

    void start_inset(const string& name, int height)
    {
        int _layout_height = layout_height;
        set_layout_height(height);
        sk_interface_start_inset(name);
        // restore height afterwards
        layout_height = _layout_height;
    }

    void end_inset(const string& name)
    {
        sk_interface_end_inset();
    }

    bool start_treenode(const string& name)
    {
        bool open = sk_interface_start_treenode(name);
        return open;
    }

    void end_treenode(const string& name)
    {
        sk_interface_end_treenode();
    }

    void open_popup(const string& name)
    {
        sk_interface_open_popup(name);
    }

    void reset_layout()
    {
        layout_widths.clear();
        layout_widths.push_back(-1);
        _update_layout();
    }

    void single_line_layout()
    {
        layout_widths.clear();
        _update_layout();
    }

    void start_custom_layout()
    {
        layout_widths.clear();
        _update_layout();
    }

    void add_column(int width)
    {
        layout_widths.push_back(width);
        _update_layout();
    }

    void add_column_relative(double width)
    {
        int w, h;
        sk_interface_get_container_size(w, h);

        layout_widths.push_back((int)(w * width));
        _update_layout();
    }

    void set_layout_height(int height)
    {
        layout_height = height;
        _update_layout();
    }

    void enter_column()
    {
        sk_interface_start_column();
    }

    void leave_column()
    {
        sk_interface_end_column();
    }

    bool header(const string& label)
    {
        bool open = sk_interface_header(label);
        _update_layout();
        return open;
    }

    void label(const string& label)
    {
        sk_interface_label(label);
    }

    bool button(const string& label)
    {
        return sk_interface_button(label);
    }
}
