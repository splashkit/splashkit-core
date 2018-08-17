//
//  text_input.cpp
//  splashkit
//
//  Created by Andrew Cain on 16/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "text_input.h"

#include "input_driver.h"
#include "text.h"
#include "utility_functions.h"

#include <vector>
#include <map>

using std::map;
using std::vector;

namespace splashkit_lib
{
    void draw_collected_text(color clr, font fnt, int font_size, const drawing_options &opts)
    {
        window current = static_cast<window>(opts.dest);

        if ( INVALID_PTR( current, WINDOW_PTR) )
        {
            return;
        }

        string ct = current->input_text;

        rectangle input_area = current->input_area;
        double x = input_area.x;
        double y = input_area.y;

        draw_text(ct, clr, fnt, font_size, x, y, opts);
        font_style style = get_font_style(fnt);

        set_font_style(fnt, static_cast<font_style>(static_cast<int>(style) | static_cast<int>(UNDERLINE_FONT)));
        draw_text(current->composition, clr, fnt, font_size, x + text_width(ct, fnt, font_size), y, opts);

        set_font_style(fnt, style);
    }

    bool reading_text()
    {
        return reading_text(current_window());
    }

    bool reading_text(window wind)
    {
        return VALID_PTR(wind, WINDOW_PTR) and wind->reading_text;
    }

    void start_reading_text(rectangle rect)
    {
        start_reading_text(current_window(), rect, "");
    }

    void start_reading_text(rectangle rect, string initial_text)
    {
        start_reading_text(current_window(), rect, initial_text);
    }

    void start_reading_text(window wind, rectangle rect)
    {
        start_reading_text(wind, rect, "");
    }

    void start_reading_text(window wind, rectangle rect, string initial_text)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR))
        {
            LOG(WARNING) << "Attempting to start reading text with invalid window";
            return;
        }

        sk_start_reading_text(wind, rect.x, rect.y, rect.width, rect.height, initial_text);
    }

    string text_input()
    {
        return text_input(current_window());
    }

    string text_input(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR) )
        {
            LOG(WARNING) << "Attempting to read input text from invalid window";
            return "";
        }

        return wind->input_text + wind->composition;
    }

    bool text_entry_cancelled()
    {
        return text_entry_cancelled(current_window());
    }

    bool text_entry_cancelled(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR) )
        {
            LOG(WARNING) << "Attempting to check if text entry cancelled on invalid window";
            return false;
        }

        return wind->cancelled_text_reading;
    }
    
    void end_reading_text()
    {
        end_reading_text(current_window());
    }
    
    void end_reading_text(window wind)
    {
        if ( INVALID_PTR(wind, WINDOW_PTR) )
        {
            LOG(WARNING) << "Ending reading text with invalid window";
            return;
        }
        
        wind->reading_text = false;
    }
}
