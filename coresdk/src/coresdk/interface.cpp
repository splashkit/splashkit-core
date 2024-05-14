
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

    // Styling
    struct interface_style_settings
    {
        struct general_settings
        {
            color clr;
            float contrast;
        };

        color text_color;
        color border_color;

        general_settings elements;
        general_settings accents;

        int spacing;
        int padding;
    };

    void _set_interface_colors_auto(interface_style_settings& style, color main_clr, color accent_clr, float contrast, float accent_contrast, float border_contrast);
    interface_style_settings _get_interface_style();

    interface_style_settings current_interface_style = _get_interface_style();

    void _update_interface_style_from_current_style();

    // this is an awful hack to work around the fact that 'interface.cpp'
    // has no way to run on initialization, not without directly referring to it
    // from the backend, which also seems wrong.
    static struct style_callback_handler
    {
        static void initial_style_set(){
            sk_interface_style_set_font(get_system_font());
            _update_interface_style_from_current_style();
        }

        style_callback_handler() {
            sk_interface_set_init_style_callback(&initial_style_set);
        }
    } set_style_callback_handler;

    // static convenience functions for adjusting colors when styling
    static color _adjust_color_contrast(color clr, float root, float init, float contrast, bool light)
    {
        init /= 255.0;
        root /= 255.0;

        float ratio = (init / root);

        float scale;
        if (!light)
            scale = (contrast * ratio + (1-contrast));
        else
            scale = (contrast / ratio + (1-contrast));

        float valr = clr.r * scale;
        float valg = clr.g * scale;
        float valb = clr.b * scale;

        return {valr, valg, valb, clr.a};
    }

    interface_style_settings _get_interface_style()
    {
        interface_style_settings style;

        style.padding = 5;
        style.spacing = 4;

        _set_interface_colors_auto(style,
            hsb_color(0.0, 0.0, 0.21),     // main color
            hsb_color(0.0, 0.0, 0.4),      // accent color
            1.0, 1.0, 1.0                  //contrast, accent contrast, border contrast
        );

        return style;
    }

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

    void start_inset(const string& name, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
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

    void label(const string& text, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);

        label(text);
    }

    void paragraph(const string& text, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        paragraph(text);
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

        splashkit_lib::label(label);
        bool res = button(text);

        leave_column();

        return res;
    }

    bool button(const string& text, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return button(text);
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

    bool bitmap_button(bitmap bmp, const rectangle& rect, drawing_options opts)
    {
        return _bitmap_button_internal(bmp, &rect, opts);
    }

    bool bitmap_button(bitmap bmp, const rectangle& rect)
    {
        return bitmap_button(bmp, rect, option_defaults());
    }

    bool checkbox(const string& label, const string& text, const bool& value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label(label);
        bool res = checkbox(text, value);

        leave_column();

        return res;
    }

    bool checkbox(const string& text, const bool& value)
    {
        _interface_sanity_check();

        bool res = sk_interface_checkbox(text, value);

        return res;
    }

    bool checkbox(const string& text, const bool& value, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return checkbox(text, value);
    }

    float slider(const string& label, const float& value, float min_value, float max_value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label(label);
        float res = slider(value, min_value, max_value);

        leave_column();

        return res;
    }

    float slider(const float& value, float min_value, float max_value)
    {
        _interface_sanity_check();

        return sk_interface_slider(value, min_value, max_value);
    }

    float slider(const float& value, float min_value, float max_value, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);

        return slider(value, min_value, max_value);
    }

    float number_box(const string& label, const float& value, float step)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label(label);
        float res = number_box(value, step);

        leave_column();

        return res;
    }

    float number_box(const float& value, float step)
    {
        _interface_sanity_check();

        return sk_interface_number(value, step);
    }

    float number_box(const float& value, float step, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return number_box(value, step);
    }

    std::string text_box(const string& label, const std::string& value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label(label);
        std::string res = text_box(value);

        leave_column();

        return res;
    }

    std::string text_box(const string& value, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return text_box(value);
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

    void set_interface_text_color(color clr)
    {
        current_interface_style.text_color = clr;

        sk_interface_style_set_text_color(current_interface_style.text_color);
    }

    void set_interface_border_color(color clr)
    {
        current_interface_style.border_color = clr;

        sk_interface_style_set_border_color(clr);
    }

    bool _is_light_mode(const interface_style_settings& style)
    {
        return brightness_of(style.elements.clr)>0.5;
    }

    bool _is_light_mode()
    {
        return _is_light_mode(current_interface_style);
    }

    void set_interface_element_color(color clr, float contrast)
    {
        bool currently_light_mode = _is_light_mode();

        current_interface_style.elements.clr = clr;
        current_interface_style.elements.contrast = contrast;

        bool light_mode = _is_light_mode();

        sk_interface_style_set_border_color(_adjust_color_contrast(clr, 50, 25, contrast, false));
        sk_interface_style_set_titlebar_color(_adjust_color_contrast(clr, 50, 25, contrast, false));
        sk_interface_style_set_panel_color(_adjust_color_contrast(clr, 50, 50, contrast, light_mode));
        sk_interface_style_set_control_color(_adjust_color_contrast(clr, 50, 30, contrast, false));
        sk_interface_style_set_scroll_base_color(_adjust_color_contrast(clr, 50, 43, contrast, light_mode));

        // if light mode changed, we need to update everything
        if (light_mode != currently_light_mode)
        {
            _update_interface_style_from_current_style();
        }
    }

    void set_interface_accent_color(color clr, float contrast)
    {
        bool light_mode = _is_light_mode();

        current_interface_style.accents.clr = clr;
        current_interface_style.accents.contrast = contrast;

        sk_interface_style_set_button_color(_adjust_color_contrast(clr, 75, 75, contrast, light_mode));
        sk_interface_style_set_title_color(_adjust_color_contrast(clr, 50, 240, contrast, light_mode));
        sk_interface_style_set_button_accent_colors(_adjust_color_contrast(clr, 75, 95, contrast, light_mode), _adjust_color_contrast(clr, 75, 115, contrast, light_mode));
        sk_interface_style_set_control_accent_colors(_adjust_color_contrast(clr, 75, 35, contrast, light_mode), _adjust_color_contrast(clr, 75, 40, contrast, light_mode));
        sk_interface_style_set_scrollbar_color(_adjust_color_contrast(clr, 50, 30, contrast, light_mode));
    }

    void _set_interface_colors_auto(interface_style_settings& style, color main_clr, color accent_clr, float contrast, float accent_contrast, float border_contrast)
    {
        style.elements.clr = main_clr;
        style.elements.contrast = contrast;

        style.accents.clr = accent_clr;
        style.accents.contrast = accent_contrast;

        style.border_color = _adjust_color_contrast(main_clr, 50, 25, 1.0, false);
        style.border_color.a = border_contrast;

        bool light_mode = _is_light_mode(style);

        if (light_mode)
            style.text_color = {0.f,0.f,0.f,1.f};
        else
            style.text_color = {1.f,1.f,1.f,1.f};
    }

    void set_interface_colors_auto(color main_clr, color accent_clr, float contrast, float accent_contrast, float border_contrast)
    {
        _set_interface_colors_auto(current_interface_style, main_clr, accent_clr, contrast, accent_contrast, border_contrast);
        _update_interface_style_from_current_style();
    }

    void set_interface_spacing(int spacing, int padding)
    {
        current_interface_style.spacing = spacing;
        current_interface_style.padding = padding;
        sk_interface_style_set_spacing(current_interface_style.spacing);
        sk_interface_style_set_padding(current_interface_style.padding);
    }

    void _update_interface_style(const interface_style_settings& style)
    {
        set_interface_accent_color(style.accents.clr, style.accents.contrast);
        set_interface_element_color(style.elements.clr, style.elements.contrast);
        set_interface_spacing(style.spacing, style.padding);
        set_interface_border_color(style.border_color);
        set_interface_text_color(style.text_color);
    }

    void _update_interface_style_from_current_style()
    {
        _update_interface_style(current_interface_style);
    }
}
