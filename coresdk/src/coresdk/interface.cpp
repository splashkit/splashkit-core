
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
        std::vector<int> layout_widths = {-1};
        int layout_height = 0;
    };

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

    void _update_layout()
    {
        if (container_stack.size() == 0) return;

        sk_interface_set_layout(container_stack.back().layout_widths.size(), &container_stack.back().layout_widths[0], container_stack.back().layout_height);
    }

    void _push_container_stack(bool open, panel_type type, std::string name)
    {
        if (open)
            container_stack.push_back({type, name});
        _update_layout();
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
    }

    void draw_interface()
    {
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

    void set_interface_font_size(int size)
    {
        sk_interface_style_set_font_size(size);
    }

    bool start_panel(const string& name, rectangle initial_rectangle)
    {
        bool open = sk_interface_start_panel(name, initial_rectangle);

        _push_container_stack(open, panel_type::panel, name);

        return open;
    }

    void end_panel(const string& name)
    {
        _pop_container_stack(panel_type::panel, name);
    }

    bool start_popup(const string& name)
    {
        bool open = sk_interface_start_popup(name);

        _push_container_stack(open, panel_type::popup, name);

        if (open)
            single_line_layout();
        return open;
    }

    void end_popup(const string& name)
    {
        _pop_container_stack(panel_type::popup, name);
    }

    void start_inset(const string& name, int height)
    {
        set_layout_height(height);
        sk_interface_start_inset(name);

        _push_container_stack(true, panel_type::inset, name);
    }

    void end_inset(const string& name)
    {
        _pop_container_stack(panel_type::inset, name);
    }

    bool start_treenode(const string& name)
    {
        bool open = sk_interface_start_treenode(name);

        _push_container_stack(open, panel_type::treenode, name);

        return open;
    }

    void end_treenode(const string& name)
    {
        _pop_container_stack(panel_type::treenode, name);
    }

    void open_popup(const string& name)
    {
        sk_interface_open_popup(name);
    }

    void reset_layout()
    {
        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.clear();
        container_stack.back().layout_widths.push_back(-1);
        _update_layout();
    }

    void single_line_layout()
    {
        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.clear();
        _update_layout();
    }

    void start_custom_layout()
    {
        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.clear();
        _update_layout();
    }

    void add_column(int width)
    {
        if (container_stack.size() == 0) return;

        container_stack.back().layout_widths.push_back(width);
        _update_layout();
    }

    void add_column_relative(double width)
    {
        if (container_stack.size() == 0) return;
        int w, h;
        sk_interface_get_container_size(w, h);

        container_stack.back().layout_widths.push_back((int)(w * width));
        _update_layout();
    }

    void set_layout_height(int height)
    {
        if (container_stack.size() == 0) return;

        container_stack.back().layout_height = height;
        _update_layout();
    }

    void enter_column()
    {
        sk_interface_start_column();

        _push_container_stack(true, panel_type::column, "");
    }

    void leave_column()
    {
        _pop_container_stack(panel_type::column, "");
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
