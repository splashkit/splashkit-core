
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
#include "utility_functions.h"

#include "interface_driver.h"

namespace splashkit_lib
{


    // this is an awful hack to work around the fact that 'interface.cpp'
    // has no way to run on initialization, not without directly referring to it
    // from the backend, which also seems wrong.
    static struct style_callback_handler
    {
        static void initial_style_set(){
            sk_interface_style_set_font(get_system_font());
        }

        style_callback_handler() {
            sk_interface_set_init_style_callback(&initial_style_set);
        }
    } set_style_callback_handler;

    enum class panel_type
    {
        panel,
        inset,
        treenode,
        column,
        popup
    };

    struct container_info
    {
        panel_type type;
        std::string name;
        // is inherited
        int label_width = 60;
        // is reset
        std::vector<int> layout_widths = {-1};
        int layout_height = 0;
    };

    // default inherited values
    int label_width = 60;

    static std::vector<container_info> container_stack;
    bool errors_occurred = false;

    const char* panel_type_to_string(panel_type type)
    {
        switch(type)
        {
            case panel_type::panel:    return "panel";
            case panel_type::inset:    return "inset";
            case panel_type::treenode: return "treenode";
            case panel_type::column:   return "column";
            case panel_type::popup:    return "popup";
        }
        return "";
    }

    void _interface_sanity_check()
    {
        if (!sk_interface_is_started())
        {
            CLOG(WARNING, "interface") << "Interface function called before 'process_events' - make sure to call this first!";
            sk_interface_start();
        }
        if (sk_interface_capacity_limited())
        {
            CLOG(WARNING, "interface") << "Too many interface items have been created without drawing/clearing them! Are you forgetting to call 'process_events' and 'draw_interface'?";
            CLOG(WARNING, "interface") << "The interface has now been cleared, to stop the program from crashing.";
            sk_interface_start();
        }
    }

    // updates the immediate layout settings - cannot update row widths
    void _update_layout()
    {
        if (container_stack.size() == 0) return;

        sk_interface_set_layout_height(container_stack.back().layout_height);
    }

    // updates the layout of the row - will force to a new row
    // if row has already started being used.
    void _update_row_layout()
    {
        if (container_stack.size() == 0) return;

        sk_interface_set_layout(container_stack.back().layout_widths.size(), &container_stack.back().layout_widths[0], container_stack.back().layout_height);
    }

    void _push_container_stack(bool open, panel_type type, std::string name)
    {
        if (open)
            container_stack.push_back({type, name});
        _update_layout();
        _update_row_layout();
    }

    const char* _get_end_function_prefix(panel_type type)
    {
        if (type == panel_type::column)
        {
            return "leave_";
        }
        return "end_";
    }

    void _pop_container_by_type(panel_type type)
    {
        switch(type)
        {
            case panel_type::panel:
                sk_interface_end_panel();
                break;
            case panel_type::popup:
                sk_interface_end_popup();
                break;
            case panel_type::inset:
                sk_interface_end_inset();
                break;
            case panel_type::treenode:
                sk_interface_end_treenode();
                break;
            case panel_type::column:
                sk_interface_end_column();
                break;
        }
    }

    // This function handles 'ending' a container, and also recovering from when
    // the user has made a mistake and mismatched a 'start_*' 'end_*' pair
    void _pop_container_stack(panel_type type, std::string name)
    {
        if (container_stack.size() == 0)
        {
            CLOG(WARNING, "interface") << "Unexpected call to "<< _get_end_function_prefix(type) << panel_type_to_string(type) << "(\"" << name << "\") - no "
                         << panel_type_to_string(type) << "s (or any other containers at all) started!";

            errors_occurred = true;
            return;
        }

        container_info& container = container_stack.back();

        // Check if the next item on the stack matches the type/name pair
        if (container.type == type && container.name == name)
        {
            // If so, pop it and return!
            _pop_container_by_type(container.type);
            container_stack.pop_back();
            _update_layout();
            return;
        }


        // If we get here, then the user has made a mistake...
        errors_occurred = true;
        typedef std::vector<container_info>::reverse_iterator iterator;

        // Now to recover:
        // First, check to see if we can find the container with the right type/name on the stack
        // then unwind until that point.
        iterator correct_container = container_stack.rend();
        for(iterator i = container_stack.rbegin(); i != container_stack.rend(); i++)
        {
            if (i->type == type && i->name == name)
            {
                correct_container = i;
                break;
            }
        }

        // If we didn't find it, just ignore!
        if (correct_container == container_stack.rend())
        {
            CLOG(WARNING, "interface") << "Unexpected call to "<< _get_end_function_prefix(type) << panel_type_to_string(type) << "(\"" << name << "\") - no "
                                       << panel_type_to_string(type) << " named '" << name << "' started! Maybe it's a typo?";
            CLOG(WARNING, "interface") << "    We were expecting a " << panel_type_to_string(container.type) << " named \"" << container.name << "\" instead.";

            return;
        }

        // If we found one, let the user know it was called too early
        CLOG(WARNING, "interface") << _get_end_function_prefix(type) << panel_type_to_string(type) << "(\"" << name << "\"); called too early!";

        // Then show them the current set of the containers on the stack
        CLOG(WARNING, "interface") << "Make sure to call these first:";
        for(iterator i = container_stack.rbegin(); i != correct_container; i++)
        {
            CLOG(WARNING, "interface") << "    " << _get_end_function_prefix(i->type) << panel_type_to_string(i->type) << "(\"" << i->name << "\");";
        }

        // Finally unwind
        correct_container++;
        for(iterator i = container_stack.rbegin(); i != correct_container; i++)
        {
            _pop_container_by_type(i->type);
            container_stack.pop_back();
        }
        _update_layout();
    }

    void _two_column_layout()
    {
        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.clear();
        container_stack.back().layout_widths.push_back(get_interface_label_width());
        container_stack.back().layout_widths.push_back(-1);
        _update_row_layout();
    }

    void draw_interface()
    {
        _interface_sanity_check();

        // Close any unclosed containers, and alert user
        typedef std::vector<container_info>::reverse_iterator iterator;
        for(iterator i = container_stack.rbegin(); i != container_stack.rend(); i++)
        {
            CLOG(WARNING, "interface") << "\"" << i->name << "\" ( a "<<panel_type_to_string(i->type)<<" ) not closed before drawing! - make sure to call "
                                       << _get_end_function_prefix(i->type) << panel_type_to_string(i->type) << "(\"" << i->name << "\")!";
            _pop_container_by_type(i->type);
            container_stack.pop_back();

            errors_occurred = true;
        }

        if (errors_occurred)
            CLOG(WARNING, "interface") << "=================Errors Occured in Interface!=================";
        errors_occurred = false;

        drawing_options opts = option_defaults();

        sk_interface_draw(opts);
    }

    void set_interface_font(font fnt)
    {
        sk_interface_style_set_font(fnt);
    }

    void set_interface_font(const string& fnt)
    {
        set_interface_font(font_named(fnt));
    }

    void set_interface_font_size(int size)
    {
        sk_interface_style_set_font_size(size);
    }

    void set_interface_label_width(int width)
    {
        if (container_stack.size() == 0)
            label_width = width;
        else
            container_stack.back().label_width = width;
    }

    int get_interface_label_width()
    {
        if (container_stack.size() == 0)
            return label_width;
        else
            return container_stack.back().label_width;
    }

    bool start_panel(const string& name, rectangle initial_rectangle)
    {
        _interface_sanity_check();

        bool open = sk_interface_start_panel(name, initial_rectangle);

        _push_container_stack(open, panel_type::panel, name);

        return open;
    }

    void end_panel(const string& name)
    {
        _interface_sanity_check();

        _pop_container_stack(panel_type::panel, name);
    }

    bool start_popup(const string& name)
    {
        _interface_sanity_check();

        bool open = sk_interface_start_popup(name);

        _push_container_stack(open, panel_type::popup, name);

        if (open)
            single_line_layout();

        return open;
    }

    void end_popup(const string& name)
    {
        _interface_sanity_check();

        _pop_container_stack(panel_type::popup, name);
    }

    void start_inset(const string& name, int height)
    {
        _interface_sanity_check();

        set_layout_height(height);
        sk_interface_start_inset(name);

        _push_container_stack(true, panel_type::inset, name);
    }

    void end_inset(const string& name)
    {
        _interface_sanity_check();

        _pop_container_stack(panel_type::inset, name);
    }

    bool start_treenode(const string& name)
    {
        _interface_sanity_check();

        bool open = sk_interface_start_treenode(name);

        _push_container_stack(open, panel_type::treenode, name);

        return open;
    }

    void end_treenode(const string& name)
    {
        _interface_sanity_check();

        _pop_container_stack(panel_type::treenode, name);
    }

    void open_popup(const string& name)
    {
        _interface_sanity_check();

        sk_interface_open_popup(name);
    }

    void reset_layout()
    {
        _interface_sanity_check();

        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.clear();
        container_stack.back().layout_widths.push_back(-1);
        _update_layout();
        _update_row_layout();
    }

    void single_line_layout()
    {
        _interface_sanity_check();

        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.clear();
        _update_row_layout();
    }

    void start_custom_layout()
    {
        _interface_sanity_check();

        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.clear();
        _update_row_layout();
    }

    void add_column(int width)
    {
        _interface_sanity_check();

        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.push_back(width);
        _update_row_layout();
    }

    void add_column_relative(double width)
    {
        if (width == -1) // handle -1 special case
            return add_column(-1);

        _interface_sanity_check();

        if (container_stack.size() == 0) return;

        int w = sk_interface_get_layout_width();
        int p = sk_interface_style_get_padding();

        container_stack.back().layout_widths.push_back((int)(w * width) - p);
        _update_row_layout();
    }

    void split_into_columns(int count)
    {
        split_into_columns(count, -1);
    }

    void split_into_columns_relative(int count, double last_width)
    {
        int w = sk_interface_get_layout_width();

        split_into_columns(count, w * last_width);
    }

    void split_into_columns(int count, int last_width)
    {
        _interface_sanity_check();

        if (container_stack.size() == 0) return;

        int w = sk_interface_get_layout_width();
        int p = sk_interface_style_get_padding();

        if (last_width > 0)
        {
            w -= last_width;

            if (count > 1)
                w /= count-1;
        }
        else
        {
            w /= count;
        }

        for (int i = 0; i < count-1 ; i ++)
        {
            container_stack.back().layout_widths.push_back(w - p);
        }
        container_stack.back().layout_widths.push_back(-1);

        _update_row_layout();
    }

    void set_layout_height(int height)
    {
        _interface_sanity_check();

        if (container_stack.size() == 0) return;

        container_stack.back().layout_height = height;
        _update_layout();
    }

    void enter_column()
    {
        _interface_sanity_check();

        sk_interface_start_column();

        _push_container_stack(true, panel_type::column, "");
    }

    void leave_column()
    {
        _interface_sanity_check();

        _pop_container_stack(panel_type::column, "");
    }

    bool header(const string& label)
    {
        _interface_sanity_check();

        bool open = sk_interface_header(label);

        return open;
    }

    void label(const string& label)
    {
        _interface_sanity_check();

        sk_interface_label(label);
    }

    void paragraph(const string& text)
    {
        _interface_sanity_check();

        sk_interface_text(text);
    }

    bool button(const string& label, const string& text)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        sk_interface_label(label);
        bool res = button(text);

        leave_column();

        return res;
    }

    bool button(const string& text)
    {
        _interface_sanity_check();

        return sk_interface_button(text, 0);
    }

    // this code inside here is copied straight from images.cpp
    // perhaps this should be a method inside graphics.cpp instead,
    // and images.cpp should use it too?
    void _compute_bitmap_data(bitmap bmp, drawing_options opts, int x, int y, double* src_data, double* dst_data, sk_renderer_flip* flip)
    {
        if ( VALID_PTR(opts.anim, ANIMATION_PTR) || opts.draw_cell >= 0 )
        {
            int cell;
            if ( opts.draw_cell >= 0 )
                cell = opts.draw_cell;
            else
                cell = animation_current_cell(opts.anim);

            rectangle part = bitmap_rectangle_of_cell(bmp, cell);
            src_data[0] = part.x;
            src_data[1] = part.y;
            src_data[2] = part.width;
            src_data[3] = part.height;
        }
        else if (opts.is_part)
        {
            src_data[0] = opts.part.x;
            src_data[1] = opts.part.y;
            src_data[2] = opts.part.width;
            src_data[3] = opts.part.height;
        }
        else
        {
            src_data[0] = 0;
            src_data[1] = 0;
            src_data[2] = bmp->image.surface.width;
            src_data[3] = bmp->image.surface.height;
        }

        //
        if ((opts.flip_x) and (opts.flip_y))
            *flip = sk_FLIP_BOTH;
        else if (opts.flip_x)
            *flip = sk_FLIP_VERTICAL;
        else if (opts.flip_y)
            *flip = sk_FLIP_HORIZONTAL;
        else
            *flip = sk_FLIP_NONE;

        // make up dst data
        dst_data[0] = x; // X
        dst_data[1] = y; // Y
        dst_data[2] = opts.angle; // Angle
        dst_data[3] = opts.anchor_offset_x; // Centre X
        dst_data[4] = opts.anchor_offset_y; // Centre Y
        dst_data[5] = opts.scale_x; // Scale X
        dst_data[6] = opts.scale_y; // Scale Y
    }

    bool _bitmap_button_internal(bitmap bmp, const rectangle* rect, drawing_options opts)
    {
        _interface_sanity_check();

        if ( INVALID_PTR(bmp, BITMAP_PTR))
        {
            LOG(WARNING) << "Error trying to draw button icon: passed in bmp is an invalid bitmap pointer.";
            return false;
        }
        double src_data[4], dst_data[7];
        sk_renderer_flip flip;

        _compute_bitmap_data(bmp, opts, 0, 0, src_data, dst_data, &flip);
        int icon = sk_interface_register_icon(&bmp->image.surface, src_data, 4, dst_data, 7, flip);

        if (rect)
            sk_interface_set_layout_next(*rect, true);

        return sk_interface_button("", icon);
    }

    bool bitmap_button(bitmap bmp, drawing_options opts)
    {
        return _bitmap_button_internal(bmp, nullptr, opts);
    }

    bool bitmap_button(bitmap bmp)
    {
        return bitmap_button(bmp, option_defaults());
    }

    bool bitmap_button(const string& label, bitmap bmp, drawing_options opts)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label(label);

        bool res = _bitmap_button_internal(bmp, nullptr, opts);

        leave_column();

        return res;
    }

    bool bitmap_button(const string& label, bitmap bmp)
    {
        return bitmap_button(label, bmp, option_defaults());
    }

    bool checkbox(const string& label, const string& text, const bool& value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        sk_interface_label(label);
        bool res = checkbox(text, value);

        leave_column();

        return res;
    }

    bool checkbox(const string& text, const bool& value)
    {
        _interface_sanity_check();

        return sk_interface_checkbox(text, value);
    }

    float slider(const string& label, const float& value, float min_value, float max_value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        sk_interface_label(label);
        float res = slider(value, min_value, max_value);

        leave_column();

        return res;
    }

    float slider(const float& value, float min_value, float max_value)
    {
        _interface_sanity_check();

        return sk_interface_slider(value, min_value, max_value);
    }

    float number_box(const string& label, const float& value, float step)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        sk_interface_label(label);
        float res = number_box(value, step);

        leave_column();

        return res;
    }

    float number_box(const float& value, float step)
    {
        _interface_sanity_check();

        return sk_interface_number(value, step);
    }

    std::string text_box(const string& label, const std::string& value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        sk_interface_label(label);
        std::string res = text_box(value);

        leave_column();

        return res;
    }

    std::string text_box(const std::string& value)
    {
        _interface_sanity_check();

        return sk_interface_text_box(value);
    }

    bool last_element_changed()
    {
        return sk_interface_changed();
    }

    bool last_element_confirmed()
    {
        return sk_interface_confirmed();
    }
}
