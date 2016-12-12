/**
 * @header text_input
 * @author Andrew Cain
 * @attribute group input
 */

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
     *
     * @attribute suffix  in_window
     */
    void start_reading_text(window wind, rectangle rect);

    /**
     * Start reading text in the current window within the bounds of the
     * supplied rectangle. The text will start with an initial value.
     *
     * @param rect The area where the text will be entered.
     * @param initial_text The initial text, which may be edited by the user.
     *
     * @attribute suffix  with_initial_text
     */
    void start_reading_text(rectangle rect, string initial_text);

    /**
     * Start reading text in the window within the bounds of the
     * supplied rectangle. The text will start with an initial value.
     *
     * @param wind The window where the text will be entered
     * @param rect The area where the text will be entered.
     * @param initial_text The initial text, which may be edited by the user.
     *
     * @attribute suffix  in_window_with_initial_text
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
    void draw_collected_text(color clr, font fnt, int font_size, const drawing_options &opts);

    /**
     * Returns true when the current window is reading text.
     *
     * @return True when window is setup to read input from the user.
     */
    bool reading_text();

    /**
     * Returns true when the window is reading text.
     *
     * @param wind  The window to check
     * @return      True when window is setup to read input from the user.
     *
     * @attribute suffix  in_window
     */
    bool reading_text(window wind);

    /**
     * Ends reading text in for the current window.
     */
    void end_reading_text();

    /**
     * Ends reading text for the passed in window.
     *
     * @param wind The window to end reading text
     *
     * @attribute suffix  in_window
     */
    void end_reading_text(window wind);

    /**
     * Did the user press escape and cancel the enterring of text?
     *
     * @return True when the use has cancelled text entry
     */
    bool text_entry_cancelled();

    /**
     * Did the user press escape and cancel the enterring of text?
     *
     * @param wind  The window to check
     * @return True when the use has cancelled text entry
     *
     * @attribute suffix  in_window
     */
    bool text_entry_cancelled(window wind);

    /**
     * The text the user has currently enterred on the current window.
     *
     * @return The user's text entry
     */
    string text_input();

    /**
     * The text the user has currently enterred on the current window.
     *
     * @param wind  The window to check
     * @return The user's text entry
     *
     * @attribute suffix  in_window
     */
    string text_input(window wind);
}
#endif /* text_input_hpp */
