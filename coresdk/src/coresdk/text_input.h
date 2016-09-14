//
//  text_input.hpp
//  splashkit
//
//  Created by Andrew Cain on 16/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef text_input_hpp
#define text_input_hpp

#include "geometry.h"
#include "window_manager.h"
namespace splashkit_lib
{
    /**
     * Start reading text in the current window within the bounds of the
     * supplied rectangle.
     *
     * @param rect The area where the text will be entered.
     */
    void start_reading_text(rectangle rect);

    /**
     * Start reading text in the window within the bounds of the
     * supplied rectangle.
     *
     * @param wind The window where the text will be entered
     * @param rect The area where the text will be entered.
     */
    void start_reading_text(window wind, rectangle rect);

    /**
     * Start reading text in the current window within the bounds of the
     * supplied rectangle. The text will start with an initial value.
     *
     * @param rect The area where the text will be entered.
     * @param initial_text The initial text, which may be edited by the user.
     */
    void start_reading_text(rectangle rect, string initial_text);

    /**
     * Start reading text in the window within the bounds of the
     * supplied rectangle. The text will start with an initial value.
     *
     * @param rect The area where the text will be entered.
     * @param wind The window where the text will be entered
     * @param initial_text The initial text, which may be edited by the user.
     */
    void start_reading_text(window wind, rectangle rect, string initial_text);

    /**
     * Draw the text that the user is currently enterring on the current window.
     *
     * @param clr       The color for the text
     * @param fnt       The font to use
     * @param font_size The size of the font
     * @param opts      Any drawing options
     */
    void draw_collected_text(color clr, font fnt, int font_size, float x, float y, drawing_options opts);

    bool reading_text();

    bool reading_text(window wind);

    void end_reading_text();

    void end_reading_text(window wind);

    bool text_entry_cancelled();

    bool text_entry_cancelled(window wind);

    string text_input();

    string text_input(window wind);
}
#endif /* text_input_hpp */
