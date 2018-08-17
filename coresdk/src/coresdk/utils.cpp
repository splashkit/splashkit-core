//
//  utils.cpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "utils.h"
#include "input.h"
#include "utils_driver.h"
#include "resources.h"
#include "input.h"
#include "text.h"
#include "geometry.h"
#include "graphics.h"

#include <iostream>
#include <string>
#include <fstream>

using std::string;
using std::ifstream;

namespace splashkit_lib
{
    // from window manager
    unsigned int number_open_windows();

    void delay(unsigned int milliseconds)
    {
        if (milliseconds > 0)
        {
            if (milliseconds < 50)
                sk_delay(milliseconds);
            else
            {
                unsigned int t;
                for (t = 1; t < milliseconds / 50; t++)
                {
                    if ( number_open_windows() > 0 )
                    {
                        process_events();
                        if ( quit_requested() ) return;
                    }

                    sk_delay(50);
                }
                t = milliseconds % 50;

                if (t > 0) sk_delay(t);
            }
        }
    }
    
    unsigned int current_ticks()
    {
        return sk_get_ticks();
    }

    string file_as_string(string filename, resource_kind kind)
    {
        string path = path_to_resource(filename, kind);

        ifstream ifs(path);
        std::string line;
        std::string result = "";
        while(getline(ifs, line))
        {
            result += line + "\n";
        }

        return result;
    }
    

    void draw_button(window dest, const string &text, font dialog_font, int font_size, const rectangle &rect)
    {
        if (point_in_rectangle(mouse_position(), rect))
            fill_rectangle_on_window(dest, color_light_gray(), rect);
        else
            fill_rectangle_on_window(dest, color_white(), rect);
            
        draw_rectangle_on_window(dest, color_black(), rect);
        draw_text_on_window(dest, text, color_black(), dialog_font, font_size, rect.x + 5, rect.y);
    }
    
    bool button_clicked(window wind, const rectangle &rect)
    {
        return window_with_focus() == wind and mouse_clicked(LEFT_BUTTON) and point_in_rectangle(mouse_position(), rect);
    }
    
    void display_dialog(const string &title, const string &msg, font output_font, int font_size)
    {
        int width, height;
        
        string prompt = "Press enter or OK to continue...";
        float ok_x, ok_y;
        float ok_width = text_width("OK", output_font, font_size) + 10;
        
        float msg_width = text_width(msg, output_font, font_size);
        float prompt_width = text_width(prompt, output_font, font_size);
        float msg_height = text_height(msg, output_font, font_size);
    
        // pick the biggest
        if ( msg_width > prompt_width )
            width = msg_width + 20;
        else
            width = prompt_width + 20;
        
        ok_x = width - 10 - ok_width;
        ok_y = 2 * msg_height + 30;
        
        height = msg_height * 3 + 40;
        
        window dialog = open_window(title, width, height);
        window old_current = current_window();
        
        set_current_window(dialog);
        
        clear_window(dialog, color_white());
        
        draw_text_on_window(dialog, msg, color_black(), output_font, font_size, 10, 10);
        draw_text_on_window(dialog, prompt, color_black(), output_font, font_size, 10, 20 + msg_height);
        
        rectangle ok_rect = rectangle_from(ok_x, ok_y, ok_width, msg_height);
        
        while ( ! (key_typed(RETURN_KEY) or window_close_requested(dialog) or button_clicked(dialog, ok_rect) ) )
        {
            process_events();
            draw_button(dialog, "OK", output_font, font_size, ok_rect);
            refresh_window(dialog);
        }
        set_current_window(old_current);
        close_window(dialog);
    }
    
    
}
