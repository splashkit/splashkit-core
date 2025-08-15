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
#include <vector>

using std::string;
using std::vector;

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

        /**
     * Returns the length of a string in characters.
     *
     * @param text      The text to get the length of
     * @returns         The number of characters in the string.
     */
    int length_of(const string &text);

    /**
     * Returns true if the string contains the substring.
     * 
     * @param text      The text to search
     * @param subtext   The substring to search for
     * @returns         True if the substring is found in the text.
     */
    bool contains(const string &text, const string &subtext);

    /**
     * Returns the index of the first occurrence of the substring in the text.
     * 
     * @param text      The text to search
     * @param subtext   The substring to search for
     * @returns         The index of the first occurrence of the substring in the text, or -1 if the substring is not found.
     */
    int index_of(const string &text, const string &subtext);

    /**
     * Replace all occurrences of a substring in a string with another string.
     * 
     * @param text      The text to search
     * @param substr    The substring to find and replace
     * @param new_text  The string to replace the substring with
     * @returns         The text with all occurrences of the substring replaced with the new text.
     */
    string replace_all(const string &text, const string &substr, const string &new_text);

    /**
     * Split a string into an array of strings based on a delimiter.
     * 
     * @param text      The text to split
     * @param delimiter The character to split the text on
     * @returns         An array of strings
     */
    vector<string> split(const string &text, char delimiter);

    /**
     * @brief Checks if a string is a valid binary string
     *
     * A binary string is a string that contains only '0' and '1' characters.
     *
     * @param bin_str Binary string to check
     *
     * @returns True if the string is a valid binary string, false otherwise
     */
    bool is_binary(const string &bin_str);

    /**
     * @brief Checks if a string is a valid hexadecimal string
     *
     * A hexadecimal string is a string that contains only characters from '0' to '9'
     * and 'A' to 'F' (or 'a' to 'f').
     *
     * @param hex_str Hexadecimal string to check
     *
     * @returns True if the string is a valid hexadecimal string, false otherwise
     */
    bool is_hex(const string &hex_str);

    /**
     * @brief Checks if a string is a valid octal string
     *
     * An octal string is a string that contains only characters from '0' to '7'.
     *
     * @param octal_str Octal string to check
     *
     * @returns True if the string is a valid octal string, false otherwise
     */
    bool is_octal(const string &octal_str);
    
    /**
     * @brief Converts a decimal (unsigned integer) to a binary string
     *
     * Converts the provided unsigned integer into a binary string.
     * For example, 10 will be converted to "1010".
     *
     * @param dec Decimal (unsigned integer) to convert
     *
     * @returns Binary string representation of the decimal
     */
    string dec_to_bin(unsigned int dec);

    /**
     * @brief Converts a binary string to a decimal (unsigned integer)
     *
     * Converts the provided binary string into an unsigned integer.
     * For example, "1010" will be converted to 10.
     *
     * @param bin Binary string to convert
     *
     * @returns Decimal (unsigned integer) representation of the binary string, or 0 if the string is not a valid binary string
     */
    unsigned int bin_to_dec(const string &bin);

    /**
     * @brief Converts a hexadecimal string to a binary string
     *
     * Converts the provided hexadecimal string into its binary string representation.
     * For example, "A" will be converted to "1010".
     *
     * @param hex_str Hexadecimal string to convert
     *
     * @returns Binary string representation of the hexadecimal string, or an empty string if the string is not a valid hexadecimal string
     */
    string hex_to_bin(const string &hex_str);

    /**
     * @brief Converts a binary string to a hexadecimal string
     *
     * Converts the provided binary string into a hexadecimal string representation.
     * For example, "1010" will be converted to "A".
     *
     * @param bin_str Binary string to convert
     *
     * @returns Hexadecimal string representation of the binary string, or an empty string if the string is not a valid binary string
     */
    string bin_to_hex(const string &bin_str);

    /**
     * @brief Converts a decimal (unsigned integer) to an octal string
     *
     * Converts the provided decimal value into its octal string representation.
     * For example, 64 will be converted to "100".
     *
     * @param decimal_value Decimal (unsigned integer) to convert
     *
     * @returns Octal string representation of the decimal value, or "0" if the value is 0
     */
    string dec_to_oct(unsigned int decimal_value);

    /**
     * @brief Converts an octal string to a decimal (unsigned integer)
     *
     * Converts the provided octal string into its decimal representation.
     * For example, "100" will be converted to 64.
     *
     * @param octal_string Octal string to convert
     *
     * @returns Decimal (unsigned integer) representation of the octal string, or 0 if the string is not a valid octal string
     */
    unsigned int oct_to_dec(const string &octal_string);

    /**
     * @brief Converts an octal string to a binary string
     *
     * Converts the provided octal string into its binary string representation.
     * For example, "12" will be converted to "1010".
     *
     * @param octal_str Octal string to convert
     *
     * @returns Binary string representation of the octal string, or an empty string if the string is not a valid octal string
     */
    string oct_to_bin(const string &octal_str);

    /**
     * @brief Converts a binary string to an octal string
     *
     * Converts the provided binary string into its octal string representation.
     * For example, "1010" will be converted to "12".
     *
     * @param bin_str Binary string to convert
     *
     * @returns Octal string representation of the binary string, or an empty string if the string is not a valid binary string
     */
    string bin_to_oct(const string &bin_str);

    /**
     * @brief Converts a hexadecimal string to an octal string
     *
     * Converts the provided hexadecimal string into its octal string representation.
     * For example, "A" will be converted to "12".
     *
     * @param hex_str Hexadecimal string to convert
     *
     * @returns Octal string representation of the hexadecimal string, or an empty string if the string is not a valid hexadecimal string
     */
    string hex_to_oct(const string &hex_str);

    /**
     * @brief Convert a hexadecimal string to its numeric value.
     * 
     * @param hex_string the data to convert
     * 
     * @return unsigned int the numeric value of the hex string
     */
    unsigned int hex_to_dec(const string &hex_string);

    /**
     * @brief Converts an octal string to a hexadecimal string
     *
     * Converts the provided octal string into its hexadecimal string representation.
     * For example, "12" will be converted to "A".
     *
     * @param oct_str Octal string to convert
     *
     * @returns Hexadecimal string representation of the octal string, or an empty string if the string is not a valid octal string
     */
    string oct_to_hex(const string &oct_str);

    /**
     * @brief Encodes a string to Base64 format
     *
     * Converts the provided string into its Base64 encoded representation.
     * For example, "Man" will be converted to "TWFu".
     *
     * @param input String to encode
     *
     * @returns Base64 encoded string
     */
    string base64_encode(const string &input);

    /**
     * @brief Decodes a Base64 encoded string
     *
     * Converts the provided Base64 encoded string back to its original form.
     * For example, "TWFu" will be converted to "Man".
     *
     * @param input Base64 encoded string to decode
     *
     * @returns Decoded original string
     */
    string base64_decode(const string &input);

    /**
     * @brief Calculates the square root of a number
     *
     * Calculates the square root of the provided number using the Newton-Raphson method.
     *
     * @param number Number to calculate the square root of
     *
     * @returns Square root of the number
     */
    double square_root(int number);

    /**
     * @brief Checks if a number is a prime number
     *
     * A prime number is a number greater than 1 that has no positive divisors other than 1 and itself.
     *
     * @param number Number to check
     *
     * @returns True if the number is a prime number, false otherwise
     */
    bool is_prime_number(int number);

    /**
     * @brief Calculates the greatest common divisor of two numbers
     *
     * The greatest common divisor (GCD) of two numbers is the largest positive integer that divides both numbers without a remainder.
     *
     * @param number1 First number
     * @param number2 Second number
     *
     * @returns Greatest common divisor of the two numbers, or 0 if both numbers are 0
     */
    int greatest_common_divisor(int number1, int number2);

    /**
     * @brief Calculates the least common multiple of two numbers
     *
     * The least common multiple (LCM) of two numbers is the smallest positive integer that is divisible by both numbers.
     *
     * @param number1 First number
     * @param number2 Second number
     *
     * @returns Least common multiple of the two numbers, or 0 if either of the numbers are 0
     */
    int least_common_multiple(int number1, int number2);

}
#endif /* basics_hpp */
