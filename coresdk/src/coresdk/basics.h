/**
 * @header  basics
 * @author  Andrew Cain
 * @brief   SplashKit provides some basic data manipulation functions to
 *          help make it easy to get some basic tasks performed.
 *
 * @attribute group  utilities
 * @attribute static utilities
 */

#ifndef basics_hpp
#define basics_hpp

#include <string>

using std::string;

namespace splashkit_lib
{
    
    /**
     * Return a new string that removes the spaces from the start and end of
     * the input string.
     *
     * @param  text The string to trim.
     * @return      A new string with the contents of `text`, after removing spaces
     *                from the start and end.
     */
    string trim(const string &text);

    /**
     * Return a lowercase version of the passed in string.
     *
     * @param  text The text to convert.
     * @return      A lower case version of the passed in text.
     */
    string to_lowercase(const string &text);

    /**
     * Return a UPPERCASE version of the passed in string.
     *
     * @param  text The text to convert.
     * @return      An upper case version of the passed in text.
     */
    string to_uppercase(const string &text);

    /**
     * Checks if a string contains an integer value.
     *
     * @param  text The text to check.
     * @return      True if the text contains a whole number (and only a whole
     *                   number).
     */
    bool is_integer(const string &text);

    /**
     * Checks if a string contains a number.
     *
     * @param  text The text to check.
     * @return      True if the text contains a number (and only a number).
     */
    bool is_double(const string &text);

    /**
     * Checks if a string contains a number.
     *
     * @param  text The text to check.
     * @return      True if the text contains a number (and only a number).
     */
    bool is_number(const string &text);

    /**
     * Convert the passed in string into an integer. This can fail in an error if
     * the value is not an integer, consider using `is_integer` to check before
     * converting a string.
     *
     * @param  text The text to convert.
     * @return      The integer value read from the text.
     */
    int convert_to_integer(const string &text);

    /**
     * Convert the passed in string into a double. This can fail in an error if
     * the value is not a number, consider using `is_number` to check before
     * converting a string.
     *
     * @param  text The text to convert.
     * @return      The double value read from the text.
     */
    double convert_to_double(const string &text);
}

#endif /* basics_hpp */
