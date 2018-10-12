/**
 * @header  terminal
 * @author  Andrew Cain
 * @brief   SplashKit Terminal allows you to read and write values to the
 * terminal in a consistent manner.
 *
 * @attribute group  terminal
 * @attribute static terminal
 */

#ifndef terminal_h
#define terminal_h

#include "color.h"

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     * Start using the advanced terminal. Once you call this you will need
     * to make sure you call `refresh_terminal` to show anything you have
     * written. This will allow use of colors, bold, positioning, and other
     * advanced options.
     */
    void activate_advanced_terminal();

    /**
     * Is the terminal currently in advanced mode?
     *
     * @return True if the terminal is in advanced mode.
     */
    bool advanced_terminal_active();

    /**
     * Finish using advanced mode. The existing terminal display will be lost
     * and the user will see what was in the terminal before you called
     * `activate_advanced_terminal`.
     */
    void end_advanced_terminal();

    /**
     * In advanced mode, this will move the cursor to a given col, row of the
     * terminal. You can check the terminal size using `terminal_width` and
     * `terminal_height`. If you try to move outside this bounds then then move
     * will not occur.
     *
     * @param x The column to move to, must be between 0 and `terminal_width`
     * @param y The row to move to, must be between 0 and `terminal_height`
     */
    void move_cursor_to(int x, int y);

    /**
     * In advanced mode, this will display what has been written to the
     * terminal. You need to call this for anything to be shown in advanced
     * mode.
     */
    void refresh_terminal();

    /**
     * In advanced mode, this will clear the terminal to the background color
     * you set in `set_terminal_color`.
     */
    void clear_terminal();

    /**
     * In advanced mode, this gives you the number of columns in the terminal.
     *
     * @return The number of columns in the terminal
     */
    int terminal_width();

    /**
     * In advanced mode, this gives you the number of rows in the terminal.
     *
     * @return The number of rows in the terminal
     */
    int terminal_height();

    /**
     * In advanced mode, this allows you to set if the text should draw as bold.
     *
     * @param value Pass true to have the terminal write in bold
     */
    void set_terminal_bold(bool value);

    /**
     * In advanced mode, this allows you to stop text read with `read_char`
     * appearing on the terminal. You can use this for reading passwords, or to
     * control what is written.
     *
     * @param value Pass true if you want characters to appear as typed.
     */
    void set_terminal_echo_input(bool value);

    /**
     * Write the supplied text to the Terminal.
     *
     * @param text The text to write
     */
    void write(string text);
    
    /**
     * Write the passed in data to the terminal.
     *
     * @param data The text to write
     *
     * @attribute suffix int
     */
    void write(int data);
    
    /**
     * Write the passed in data to the terminal.
     *
     * @param data The text to write
     *
     * @attribute suffix double
     */
    void write(double data);

    /**
     * Write the passed in data to the terminal.
     *
     * @param data The character to write
     *
     * @attribute suffix char
     */
    void write(char data);

    /**
     * Move to the next line/row of the terminal.
     *
     * @attribute suffix  empty
     */
    void write_line();

    /**
     * Write the passed in text, then move to the next line/row of the terminal.
     *
     * @param line The text to write
     */
    void write_line(string line);
    
    /**
     * Write the passed in data, then move to the next line/row of the terminal.
     *
     * @param data The text to write
     *
     * @attribute suffix int
     */
    void write_line(int data);
    
    /**
     * Write the passed in data, then move to the next line/row of the terminal.
     *
     * @param data The text to write
     *
     * @attribute suffix double
     */
    void write_line(double data);

    /**
     * Write the passed in data, then move to the next line/row of the terminal.
     *
     * @param data The character to write
     *
     * @attribute suffix char
     */
    void write_line(char data);

    /**
     * In advanced mode, this will write the supplied text at the indicated
     * column and row.
     *
     * @param text The text to write
     * @param x    The row to position the text at
     * @param y    The column to position the text at
     */
    void write_at(string text, int x, int y);

    /**
     * In advanced mode this allows you to set the color of the foreground and
     * the background. The foreground is the color of the text.
     *
     *
     * Note that only the following colors are guaranteed to work on all
     * Terminals (others may work):
     *
     *
     *   -  `color_black`
     *
     *
     *   -  `color_dark_gray`
     *
     *
     *   -  `color_gray`
     *
     *
     *   -  `color_white`
     *
     *
     *   -  `color_red`
     *
     *
     *   -  `color_dark_red`
     *
     *
     *   -  `color_green`
     *
     *
     *   -  `color_dark_green`
     *
     *
     *   -  `color_blue`
     *
     *
     *   -  `color_dark_blue`
     *
     *
     *   -  `color_cyan`
     *
     *
     *   -  `color_dark_cyan`
     *
     *
     *   -  `color_light_yellow`
     *
     *
     *   -  `color_yellow`
     *
     *
     *   -  `color_magenta`
     *
     *
     *   -  `color_dark_magenta`
     *
     *
     * @param foreground The color of text that is drawn.
     * @param background The color of the background behind drawn text.
     */
    void set_terminal_colors(color foreground, color background);

    /**
     * Read a line of text from the terminal. The user will see the text as
     * they type it.
     *
     * @return The text entered by the user.
     */
    string read_line();

    /**
     * Get a single character input by the user. This works in both standard and
     * advanced modes. In advanced mode, you can set if the character should
     * also be echoed to the terminal using `set_terminal_echo_input`.
     *
     * @return The character typed by the user.
     */
    char read_char();
}

#endif /* terminal_h */
