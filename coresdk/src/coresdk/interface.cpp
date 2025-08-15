
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

#include <cmath>

namespace splashkit_lib
{

    // Styling
    struct interface_style_settings
    {
        color root_text_color = COLOR_BLACK;
        color text_color;
        color border_color;

        struct general_settings
        {
            color clr;
            float contrast;
        } elements, accents;

        struct shadow_settings
        {
            int radius;
            color clr;
            point_2d offset;
        } panel_shadows, element_shadows;

        int spacing;
        int padding;

        float global_transarency = 1.0;
    };

    void _set_interface_colors_auto(interface_style_settings& style, color main_clr, color accent_clr, float contrast, float accent_contrast, float border_contrast);
    interface_style_settings _get_interface_style(interface_style style, color clr = {0,0,0,-1} /*signal default color*/);

    interface_style_settings current_interface_style = _get_interface_style(SHADED_DARK_STYLE);

    void _update_interface_style_from_current_style();

    static bool interface_is_initialized = false;

    // this is an awful hack to work around the fact that 'interface.cpp'
    // has no way to run on initialization, not without directly referring to it
    // from the backend, which also seems wrong.
    static struct style_callback_handler
    {
        static void initial_style_set(){
            interface_is_initialized = true;
            sk_interface_style_set_font(get_system_font());
            _update_interface_style_from_current_style();
        }

        style_callback_handler() {
            sk_interface_set_init_style_callback(&initial_style_set);
        }
    } set_style_callback_handler;

    // static convenience functions for adjusting colors when styling
    static color hsba_color(double hue, double saturation, double brightness, double alpha){
        color res = hsb_color(hue, saturation, brightness);
        res.a = alpha;
        return res;
    }

    static color multiply_alpha(color clr, float modulation)
    {
        clr.a *= modulation;
        return clr;
    }

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

        float valr = std::min(clr.r * scale, 1.f);
        float valg = std::min(clr.g * scale, 1.f);
        float valb = std::min(clr.b * scale, 1.f);

        return {valr, valg, valb, clr.a};
    }

    interface_style_settings _get_interface_style(interface_style style_name, color clr)
    {
        interface_style_settings style;

        style.padding = 5;
        style.spacing = 4;

        bool user_provided_color = clr.a != -1;

        if (!user_provided_color)
        {
            switch (style_name)
            {
                case SHADED_DARK_STYLE:
                    clr = hsba_color(0.0, 0.0, 0.5f, 1.0f);
                break;
                case SHADED_LIGHT_STYLE:
                    clr = COLOR_WHITE;
                break;
                case FLAT_DARK_STYLE:
                    clr = hsba_color(0.0, 0.0, 0.5f, 1.0f);
                break;
                case FLAT_LIGHT_STYLE:
                    clr = COLOR_WHITE;
                break;
                case BUBBLE:
                    clr = COLOR_WHITE;
                break;
                case BUBBLE_MULTICOLORED:
                    clr = hsba_color(0.62, 0.39, 1.0f, 1.0f);
                break;
            }
        }

        float hue = hue_of(clr);
        float sat = saturation_of(clr);
        float bri = brightness_of(clr);
        color shadow_color;

        switch (style_name)
        {
            case SHADED_DARK_STYLE:
                style.panel_shadows = {45, hsba_color(0.0, 0.0, 0.0, 0.36), {18,18}};
                style.element_shadows = {9, hsba_color(0.0, 0.0, 0.0, 0.36), {3,3}};

                if (user_provided_color)
                    bri *= 0.5;

                _set_interface_colors_auto(style,
                    hsb_color(hue, sat*0.3, bri*0.42), // main color
                    hsb_color(hue, sat, bri*0.6),      // accent color
                    1.0, 1.0, 1.0                      //contrast, accent contrast, border contrast
                );
            break;
            case SHADED_LIGHT_STYLE:
                if (!user_provided_color)
                    shadow_color = hsba_color(0.0, 0.0, 0.22, 0.12);
                else
                    shadow_color = hsba_color(hue, sat, bri*0.5, 0.12);

                style.panel_shadows = {45, shadow_color, {18,18}};
                style.element_shadows = {9, shadow_color, {3,3}};

                _set_interface_colors_auto(style,
                    hsba_color(0, 0, 1, 0.9),           // main color
                    hsba_color(hue, sat*0.2, bri, 0.9), // accent color
                    0.0, 1.0, 0.1                       //contrast, accent contrast, border contrast
                );
            break;
            case FLAT_DARK_STYLE:
                style.panel_shadows = {0, hsba_color(0.0, 0.0, 0.0, 0.0), {0,0}};
                style.element_shadows = style.panel_shadows;

                if (user_provided_color)
                    bri *= 0.5;

                _set_interface_colors_auto(style,
                    hsb_color(hue, sat*0.3, bri*0.42), // main color
                    hsb_color(hue, sat, bri*0.6),      // accent color
                    1.0, 1.0, 1.0                      //contrast, accent contrast, border contrast
                );
            break;
            case FLAT_LIGHT_STYLE:
                style.panel_shadows = {0, hsba_color(0.0, 0.0, 0.0, 0.0), {0,0}};
                style.element_shadows = style.panel_shadows;

                _set_interface_colors_auto(style,
                    hsba_color(0.83, 0, 1, 0.9),    // main color
                    hsba_color(hue, sat, bri, 0.9), // accent color
                    0.0, 1.0, 1.0                   //contrast, accent contrast, border contrast
                );
            break;
            case BUBBLE:
                style.panel_shadows = {65, hsba_color(hue, sat, bri*0.65, 0.41), {12,12}};
                style.element_shadows = {15, hsba_color(hue, sat, bri*0.65, 0.41), {6,6}};

                _set_interface_colors_auto(style,
                    hsba_color(hue, sat*0.5, bri, 0.18),        // main color
                    hsba_color(hue, sat*0.5, bri*0.66, 0.45),   // accent color
                    1.0, 0.8, 0.6                               //contrast, accent contrast, border contrast
                );
            break;
            case BUBBLE_MULTICOLORED:
                style.panel_shadows = {65, hsba_color(std::fmod(hue-0.05, 1.0), sat, bri*0.65, 0.41), {12,12}};
                style.element_shadows = {15, hsba_color(std::fmod(hue-0.05, 1.0), sat, bri*0.65, 0.41), {6,6}};

                _set_interface_colors_auto(style,
                    hsba_color(std::fmod(hue+0.1, 1.0), sat*0.5, bri, 0.18),      // main color
                    hsba_color(std::fmod(hue+0.1, 1.0), sat*0.5, bri*0.66, 0.45), // accent color
                    1.0, 0.8, 0.6                                                 //contrast, accent contrast, border contrast
                );
            break;
        }

        return style;
    }


    // Container stack handling
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
        bool hasBackground = true;
    };

    // default inherited values
    int label_width = 60;

    static std::vector<container_info> container_stack;
    static int filledContainerCount = 0;
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

    void _interface_exists_check()
    {
        if (!interface_is_initialized)
        {
            // note: cannot use "interface" logger since it hasn't been initialized yet.
            LOG(ERROR) << "Interface function called before opening a window!\nMake sure to open a window before trying to use interface functionality.\nThe program will exit now.";
            exit(-1);
        }
    }

    void _interface_sanity_check()
    {
        _interface_exists_check();
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
        {
            container_stack.push_back({type, name, get_interface_label_width()});
            container_stack.back().hasBackground = type == panel_type::panel || type == panel_type::popup;

            if (container_stack.back().hasBackground)
                filledContainerCount++;
        }

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

            if (container_stack.back().hasBackground)
                filledContainerCount--;

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

            if (container_stack.back().hasBackground)
                filledContainerCount--;

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

    void _update_text_style(bool standaloneText = false)
    {
        if (standaloneText && filledContainerCount == 0)
            sk_interface_style_set_text_color(multiply_alpha(current_interface_style.root_text_color, current_interface_style.global_transarency));
        else
            sk_interface_style_set_text_color(multiply_alpha(current_interface_style.text_color, current_interface_style.global_transarency));
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

            if (container_stack.back().hasBackground)
                filledContainerCount--;

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

    bool header(const string& label_text)
    {
        _interface_sanity_check();

        bool open = sk_interface_header(label_text);

        return open;
    }

    void label_element(const string& text)
    {
        _interface_sanity_check();

        _update_text_style(true);
        sk_interface_label(text);
        _update_text_style();
    }

    void label_element(const string& text, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);

        label_element(text);
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

        _update_text_style(true);
        sk_interface_text(text);
        _update_text_style();
    }

    bool button(const string& label_text, const string& text)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label_element(label_text);
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

    // TODO the code inside here is copied straight from images.cpp
    // perhaps this should be a method inside utility_functions.cpp instead
    // (similar to xy_from_opts), and images.cpp should use it too?
    void _compute_bitmap_data(bitmap bmp, drawing_options opts, int x, int y, double (&src_data)[4], double (&dst_data)[7], sk_renderer_flip* flip)
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
        int icon = sk_interface_register_icon(&bmp->image.surface, src_data, dst_data, flip);

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

    bool bitmap_button(const string& label_text, bitmap bmp, drawing_options opts)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label_element(label_text);

        bool res = _bitmap_button_internal(bmp, nullptr, opts);

        leave_column();

        return res;
    }

    bool bitmap_button(const string& label_text, bitmap bmp)
    {
        return bitmap_button(label_text, bmp, option_defaults());
    }

    bool bitmap_button(bitmap bmp, const rectangle& rect, drawing_options opts)
    {
        return _bitmap_button_internal(bmp, &rect, opts);
    }

    bool bitmap_button(bitmap bmp, const rectangle& rect)
    {
        return bitmap_button(bmp, rect, option_defaults());
    }

    bool checkbox(const string& label_text, const string& text, const bool& value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label_element(label_text);
        bool res = checkbox(text, value);

        leave_column();

        return res;
    }

    bool checkbox(const string& text, const bool& value)
    {
        _interface_sanity_check();

        _update_text_style(true);
        bool res = sk_interface_checkbox(text, value);
        _update_text_style();

        return res;
    }

    bool checkbox(const string& text, const bool& value, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return checkbox(text, value);
    }

    float slider(const string& label_text, const float& value, float min_value, float max_value)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label_element(label_text);
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

    color _color_slider(const color& clr, bool hsb)
    {
        _interface_sanity_check();
        enter_column();

        sk_interface_push_ptr_id((void*)&clr);

        color temp_value = clr;
        if (hsb)
        {
            temp_value =
            {
                (float)hue_of(temp_value),
                (float)saturation_of(temp_value),
                (float)brightness_of(temp_value),
                temp_value.a
            };
        }

        start_custom_layout();

        split_into_columns_relative(5, 0.1);

        set_interface_label_width(20);

        bool already_disabled = !interface_enabled();

        // disable hue slider if can't be set
        if (hsb && (temp_value.g == 0 || temp_value.b == 0))
        {
            disable_interface();
            temp_value.r = 0.0; // hue_of returns 0.83 for some reason
        }

        temp_value.r = slider(hsb?"h:":"r:", temp_value.r, 0, 1);

        // disable saturation slider if can't be set
        if ((hsb && temp_value.b == 0) || already_disabled)
            disable_interface();
        else
            enable_interface();

        temp_value.g = slider(hsb?"s:":"g:", temp_value.g, 0, 1);

        if (!already_disabled)
            enable_interface();

        temp_value.b = slider("b:", temp_value.b, 0, 1);
        temp_value.a = slider("a:", temp_value.a, 0, 1);

        temp_value = hsb ? hsba_color(temp_value.r, temp_value.g, temp_value.b, temp_value.a) : temp_value;

        sk_interface_color_box(temp_value);

        sk_interface_pop_id();

        leave_column();

        return temp_value;
    }

    color color_slider(const string& label_text, const color& clr)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label_element(label_text);
        color res = color_slider(clr);

        leave_column();

        return res;
    }

    color color_slider(const color& clr)
    {
        return _color_slider(clr, false);
    }

    color color_slider(const color& clr, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return _color_slider(clr, false);
    }

    color hsb_color_slider(const string& label_text, const color& clr)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label_element(label_text);
        color res = hsb_color_slider(clr);

        leave_column();

        return res;
    }

    color hsb_color_slider(const color& clr)
    {
        return _color_slider(clr, true);
    }

    color hsb_color_slider(const color& clr, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return _color_slider(clr, true);
    }

    float number_box(const string& label_text, const float& value, float step)
    {
        _interface_sanity_check();

        enter_column();
        _two_column_layout();

        splashkit_lib::label_element(label_text);
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

    std::string text_box(const string& label_text, const std::string& value)
    {
        return text_box(label_text, value, false);
    }

    std::string text_box(const string& label_text, const std::string& value, bool show_label)
    {
        _interface_sanity_check();

        if (show_label)
        {
            enter_column();
            _two_column_layout();

            splashkit_lib::label_element(label_text);
        }

        std::string res = sk_interface_text_box(label_text, value);

        if (show_label)
        {
            leave_column();
        }

        return res;
    }

    std::string text_box(const string& label_text, const string& value, const rectangle& rect)
    {
        _interface_sanity_check();

        sk_interface_set_layout_next(rect, true);
        return text_box(label_text, value, false);
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
        _interface_exists_check();

        current_interface_style.text_color = clr;

        clr = multiply_alpha(clr, current_interface_style.global_transarency);

        _update_text_style();
    }

    void set_interface_root_text_color(color clr)
    {
        _interface_exists_check();

        current_interface_style.root_text_color = clr;

        clr = multiply_alpha(clr, current_interface_style.global_transarency);

        _update_text_style();
    }

    void set_interface_border_color(color clr)
    {
        _interface_exists_check();

        current_interface_style.border_color = clr;

        clr = multiply_alpha(clr, current_interface_style.global_transarency);

        sk_interface_style_set_border_color(clr);
    }

    void set_interface_shadows(int radius, color clr, point_2d offset)
    {
        _interface_exists_check();

        set_interface_panel_shadows(radius, clr, offset);
        set_interface_element_shadows(radius, clr, offset);
    }

    void set_interface_panel_shadows(int radius, color clr, point_2d offset)
    {
        _interface_exists_check();

        current_interface_style.panel_shadows.radius = radius;
        current_interface_style.panel_shadows.clr = clr;
        current_interface_style.panel_shadows.offset = offset;

        clr = multiply_alpha(clr, current_interface_style.global_transarency);

        sk_interface_style_set_panel_shadow_color(clr);
        sk_interface_style_set_panel_shadow_radius(radius);
        sk_interface_style_set_panel_shadow_offset(offset);
    }

    void set_interface_element_shadows(int radius, color clr, point_2d offset)
    {
        _interface_exists_check();

        current_interface_style.element_shadows.radius = radius;
        current_interface_style.element_shadows.clr = clr;
        current_interface_style.element_shadows.offset = offset;

        clr = multiply_alpha(clr, current_interface_style.global_transarency);

        sk_interface_style_set_element_shadow_color(clr);
        sk_interface_style_set_element_shadow_radius(radius);
        sk_interface_style_set_element_shadow_offset(offset);
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
        _interface_exists_check();

        bool currently_light_mode = _is_light_mode();

        current_interface_style.elements.clr = clr;
        current_interface_style.elements.contrast = contrast;

        bool light_mode = _is_light_mode();

        clr = multiply_alpha(clr, current_interface_style.global_transarency);

        sk_interface_style_set_border_color(_adjust_color_contrast(clr, 50, 25, contrast, false));
        sk_interface_style_set_titlebar_color(_adjust_color_contrast(clr, 50, 25, contrast, false));
        sk_interface_style_set_panel_color(_adjust_color_contrast(clr, 50, 50, contrast, light_mode));
        sk_interface_style_set_control_color(_adjust_color_contrast(clr, 50, 30, contrast, false));
        sk_interface_style_set_scroll_base_color(_adjust_color_contrast(clr, 50, 43, contrast, false));

        // if light mode changed, we need to update everything
        if (light_mode != currently_light_mode)
        {
            _update_interface_style_from_current_style();
        }
    }

    void set_interface_accent_color(color clr, float contrast)
    {
        _interface_exists_check();

        bool light_mode = _is_light_mode();

        current_interface_style.accents.clr = clr;
        current_interface_style.accents.contrast = contrast;

        clr = multiply_alpha(clr, current_interface_style.global_transarency);

        // title color handling - increase saturation and alter brightness
        double title_hue = hue_of(clr);
        double title_sat = saturation_of(clr);
        double title_bri;

        // increase saturation of title
        // HSB brightness isn't perceptually consistent - saturated blue looks darker/like its been hue shifted,
        // empirical correction - TODO perhaps using a different color space altogether would be better
        // darkest region is centered around 0.68 with a radius of 0.12 + apply power to fit color space curve better
        double blue_correction = 1.0 - std::pow(std::min(1.0, std::abs((title_hue - 0.68) / 0.12)), 2);

        title_sat = lin_interp(1.0 - std::pow(1.0 - title_sat, 5), title_sat, blue_correction) * contrast;

        if (light_mode)
            // ensure text becomes darker when desaturated, to stay readable
            // we also keep text a little off full black, which looks less harsh and is fairly common practice
            title_bri = std::max(50.0/255.0, title_sat);
        else
            // ensure text is always bright
            title_bri = 1.0;

        sk_interface_style_set_button_color(_adjust_color_contrast(clr, 75, 75, contrast, light_mode));
        sk_interface_style_set_title_color(hsba_color(title_hue, title_sat, title_bri, clr.a));
        sk_interface_style_set_button_accent_colors(_adjust_color_contrast(clr, 75, 95, contrast, light_mode), _adjust_color_contrast(clr, 75, 115, contrast, light_mode));
        sk_interface_style_set_control_accent_colors(_adjust_color_contrast(clr, 75, 35, contrast, light_mode), _adjust_color_contrast(clr, 75, 40, contrast, light_mode));
        sk_interface_style_set_scrollbar_color(_adjust_color_contrast(clr, 50, light_mode?40:20, contrast, false));
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
        _interface_exists_check();

        _set_interface_colors_auto(current_interface_style, main_clr, accent_clr, contrast, accent_contrast, border_contrast);
        _update_interface_style_from_current_style();
    }

    void set_interface_spacing(int spacing, int padding)
    {
        _interface_exists_check();

        current_interface_style.spacing = spacing;
        current_interface_style.padding = padding;
        sk_interface_style_set_spacing(current_interface_style.spacing);
        sk_interface_style_set_padding(current_interface_style.padding);
    }

    void _update_interface_style(const interface_style_settings& style)
    {
        _interface_exists_check();

        set_interface_accent_color(style.accents.clr, style.accents.contrast);
        set_interface_element_color(style.elements.clr, style.elements.contrast);
        set_interface_spacing(style.spacing, style.padding);
        set_interface_element_shadows(style.element_shadows.radius, style.element_shadows.clr, style.element_shadows.offset);
        set_interface_panel_shadows(style.panel_shadows.radius, style.panel_shadows.clr, style.panel_shadows.offset);
        set_interface_border_color(style.border_color);
        set_interface_text_color(style.text_color);
        set_interface_root_text_color(style.root_text_color);
        _update_text_style();
    }

    void _update_interface_style_from_current_style()
    {
        _interface_exists_check();

        _update_interface_style(current_interface_style);
    }

    void set_interface_style(interface_style style, color clr)
    {
        _interface_exists_check();

        _update_interface_style(_get_interface_style(style, clr));
    }

    void set_interface_style(interface_style style)
    {
        _interface_exists_check();

        _update_interface_style(_get_interface_style(style));
    }

    void interface_style_panel(const rectangle& initial_rectangle)
    {
        auto& style = current_interface_style;
        if (start_panel("Interface Style", initial_rectangle))
        {
            static color user_color = hsba_color(0.62, 0.39, 1.0f, 1.0f);
            static bool use_user_color = false;
            bool already_disabled = !interface_enabled();

            start_custom_layout();
                add_column(100);
                add_column(-1);
                use_user_color = checkbox("Use color", use_user_color);

                if (!use_user_color && !already_disabled)
                    disable_interface();
                user_color = hsb_color_slider(user_color);
                if (!already_disabled)
                    enable_interface();
            reset_layout();

            start_custom_layout();
            split_into_columns(6);
                color user_color_resolved = use_user_color ? user_color : (color){0,0,0,-1};
                if (button("Shaded Dark")) set_interface_style(SHADED_DARK_STYLE, user_color_resolved);
                if (button("Flat Dark")) set_interface_style(FLAT_DARK_STYLE, user_color_resolved);
                if (button("Shaded Light")) set_interface_style(SHADED_LIGHT_STYLE, user_color_resolved);
                if (button("Flat Light")) set_interface_style(FLAT_LIGHT_STYLE, user_color_resolved);
                if (button("Bubble")) set_interface_style(BUBBLE, user_color_resolved);
                if (button("Bubble Multi-color")) set_interface_style(BUBBLE_MULTICOLORED, user_color_resolved);
            reset_layout();

            if (header("Colors (Detailed)"))
            {
                style.elements.clr = hsb_color_slider("Main:", style.elements.clr);
                style.accents.clr = hsb_color_slider("Accent:", style.accents.clr);

                start_custom_layout();
                split_into_columns(2);
                    style.elements.contrast = slider("Contrast:", style.elements.contrast, 0, 1);
                    style.accents.contrast = slider("Accent:", style.accents.contrast, 0, 1);
                    style.border_color.a = slider("Borders:", style.border_color.a, 0, 1);
                reset_layout();
            }

            if (header("Shadows"))
            {
                style.element_shadows.clr = hsb_color_slider("Shadow:", style.element_shadows.clr);
                style.panel_shadows.clr = style.element_shadows.clr;
                start_custom_layout();
                set_interface_label_width(110);
                split_into_columns(2);
                    style.panel_shadows.radius = slider("Radius (Panel):", style.panel_shadows.radius, 0, 200);
                    style.element_shadows.radius = slider("Radius (Element):", style.element_shadows.radius, 0, 200);

                    style.panel_shadows.offset.x = slider("Distance (Panel):", style.panel_shadows.offset.x, 0, 200);
                    style.element_shadows.offset.x = slider("Distance (Element):", style.element_shadows.offset.x, 0, 200);

                    style.panel_shadows.offset.y = style.panel_shadows.offset.x;
                    style.element_shadows.offset.y = style.element_shadows.offset.x;
                reset_layout();
            }

            set_interface_colors_auto(style.elements.clr, style.accents.clr, style.elements.contrast, style.accents.contrast, style.border_color.a);
            _update_interface_style_from_current_style();

            end_panel("Interface Style");
        }
    }

    void disable_interface()
    {
        _interface_exists_check();

        sk_interface_set_enabled(false);
        current_interface_style.global_transarency = 0.5f;
        _update_interface_style_from_current_style();
    }

    void enable_interface()
    {
        _interface_exists_check();

        sk_interface_set_enabled(true);
        current_interface_style.global_transarency = 1.0f;
        _update_interface_style_from_current_style();
    }

    bool interface_enabled()
    {
        return sk_interface_is_enabled();
    }
}
