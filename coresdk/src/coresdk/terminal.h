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
     * Read a line of text from the terminal. The user will see the text as
     * they type it.
     *
     * @return The text entered by the user.
     */
    string read_line();

    /**
     * Get a single character input by the user.
     *
     * @return The character typed by the user.
     */
    char read_char();
}

#endif /* terminal_h */
