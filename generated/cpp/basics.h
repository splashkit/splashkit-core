//
// SplashKit Generated Basics C++ Code
// DO NOT MODIFY
//

#ifndef __basics_h
#define __basics_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

/**
* Converts the provided Base64 encoded string back to its original form.
* For example, "TWFu" will be converted to "Man".
* @param input Base64 encoded string to decode
* @return Decoded original string
*/
string base64_decode(const string &input);
/**
* Converts the provided string into its Base64 encoded representation.
* For example, "Man" will be converted to "TWFu".
* @param input String to encode
* @return Base64 encoded string
*/
string base64_encode(const string &input);
/**
* Converts the provided binary string into an unsigned integer.
* For example, "1010" will be converted to 10.
* @param bin Binary string to convert
* @return Decimal (unsigned integer) representation of the binary string, or 0 if the string is not a valid binary string
*/
unsigned int bin_to_dec(const string &bin);
/**
* Converts the provided binary string into a hexadecimal string representation.
* For example, "1010" will be converted to "A".
* @param bin_str Binary string to convert
* @return Hexadecimal string representation of the binary string, or an empty string if the string is not a valid binary string
*/
string bin_to_hex(const string &bin_str);
/**
* Converts the provided binary string into its octal string representation.
* For example, "1010" will be converted to "12".
* @param bin_str Binary string to convert
* @return Octal string representation of the binary string, or an empty string if the string is not a valid binary string
*/
string bin_to_oct(const string &bin_str);
/**
* Returns true if the string contains the substring.
* @param text The text to search
* @param subtext The substring to search for
* @return True if the substring is found in the text.
*/
bool contains(const string &text, const string &subtext);
/**
* Convert the passed in string into a double. This can fail in an error if
* the value is not a number, consider using `is_number` to check before
* converting a string.
* @param text The text to convert.
* @return The double value read from the text.
*/
double convert_to_double(const string &text);
/**
* Convert the passed in string into an integer. This can fail in an error if
* the value is not an integer, consider using `is_integer` to check before
* converting a string.
* @param text The text to convert.
* @return The integer value read from the text.
*/
int convert_to_integer(const string &text);
/**
* Converts the provided unsigned integer into a binary string.
* For example, 10 will be converted to "1010".
* @param dec Decimal (unsigned integer) to convert
* @return Binary string representation of the decimal
*/
string dec_to_bin(unsigned int dec);
/**
* Converts the provided decimal value into its octal string representation.
* For example, 64 will be converted to "100".
* @param decimal_value Decimal (unsigned integer) to convert
* @return Octal string representation of the decimal value, or "0" if the value is 0
*/
string dec_to_oct(unsigned int decimal_value);
/**
* The greatest common divisor (GCD) of two numbers is the largest positive integer that divides both numbers without a remainder.
* @param number1 First number
* @param number2 Second number
* @return Greatest common divisor of the two numbers, or 0 if both numbers are 0
*/
int greatest_common_divisor(int number1, int number2);
/**
* Converts the provided hexadecimal string into its binary string representation.
* For example, "A" will be converted to "1010".
* @param hex_str Hexadecimal string to convert
* @return Binary string representation of the hexadecimal string, or an empty string if the string is not a valid hexadecimal string
*/
string hex_to_bin(const string &hex_str);
/**
* 
* @param hex_string the data to convert
* @return unsigned int the numeric value of the hex string
*/
unsigned int hex_to_dec(const string &hex_string);
/**
* Converts the provided hexadecimal string into its octal string representation.
* For example, "A" will be converted to "12".
* @param hex_str Hexadecimal string to convert
* @return Octal string representation of the hexadecimal string, or an empty string if the string is not a valid hexadecimal string
*/
string hex_to_oct(const string &hex_str);
/**
* Returns the index of the first occurrence of the substring in the text.
* @param text The text to search
* @param subtext The substring to search for
* @return The index of the first occurrence of the substring in the text, or -1 if the substring is not found.
*/
int index_of(const string &text, const string &subtext);
/**
* A binary string is a string that contains only '0' and '1' characters.
* @param bin_str Binary string to check
* @return True if the string is a valid binary string, false otherwise
*/
bool is_binary(const string &bin_str);
/**
* Checks if a string contains a number.
* @param text The text to check.
* @return True if the text contains a number (and only a number).
*/
bool is_double(const string &text);
/**
* A hexadecimal string is a string that contains only characters from '0' to '9'
* and 'A' to 'F' (or 'a' to 'f').
* @param hex_str Hexadecimal string to check
* @return True if the string is a valid hexadecimal string, false otherwise
*/
bool is_hex(const string &hex_str);
/**
* Checks if a string contains an integer value.
* @param text The text to check.
* @return True if the text contains a whole number (and only a whole
number).
*/
bool is_integer(const string &text);
/**
* Checks if a string contains a number.
* @param text The text to check.
* @return True if the text contains a number (and only a number).
*/
bool is_number(const string &text);
/**
* An octal string is a string that contains only characters from '0' to '7'.
* @param octal_str Octal string to check
* @return True if the string is a valid octal string, false otherwise
*/
bool is_octal(const string &octal_str);
/**
* A prime number is a number greater than 1 that has no positive divisors other than 1 and itself.
* @param number Number to check
* @return True if the number is a prime number, false otherwise
*/
bool is_prime_number(int number);
/**
* The least common multiple (LCM) of two numbers is the smallest positive integer that is divisible by both numbers.
* @param number1 First number
* @param number2 Second number
* @return Least common multiple of the two numbers, or 0 if either of the numbers are 0
*/
int least_common_multiple(int number1, int number2);
/**
* Returns the length of a string in characters.
* @param text The text to get the length of
* @return The number of characters in the string.
*/
int length_of(const string &text);
/**
* Converts the provided octal string into its binary string representation.
* For example, "12" will be converted to "1010".
* @param octal_str Octal string to convert
* @return Binary string representation of the octal string, or an empty string if the string is not a valid octal string
*/
string oct_to_bin(const string &octal_str);
/**
* Converts the provided octal string into its decimal representation.
* For example, "100" will be converted to 64.
* @param octal_string Octal string to convert
* @return Decimal (unsigned integer) representation of the octal string, or 0 if the string is not a valid octal string
*/
unsigned int oct_to_dec(const string &octal_string);
/**
* Converts the provided octal string into its hexadecimal string representation.
* For example, "12" will be converted to "A".
* @param oct_str Octal string to convert
* @return Hexadecimal string representation of the octal string, or an empty string if the string is not a valid octal string
*/
string oct_to_hex(const string &oct_str);
/**
* Replace all occurrences of a substring in a string with another string.
* @param text The text to search
* @param substr The substring to find and replace
* @param new_text The string to replace the substring with
* @return The text with all occurrences of the substring replaced with the new text.
*/
string replace_all(const string &text, const string &substr, const string &new_text);
/**
* Split a string into an array of strings based on a delimiter.
* @param text The text to split
* @param delimiter The character to split the text on
* @return An array of strings
*/
vector<string> split(const string &text, char delimiter);
/**
* Calculates the square root of the provided number using the Newton-Raphson method.
* @param number Number to calculate the square root of
* @return Square root of the number
*/
double square_root(int number);
/**
* Convert the passed in string into a double. This can fail in an error if
* the value is not a number, consider using `is_number` to check before
* converting a string.
* @param text The text to convert.
* @return The double value read from the text.
*/
double to_double(const string &text);
/**
* Convert the passed in string into an integer. This can fail in an error if
* the value is not an integer, consider using `is_integer` to check before
* converting a string.
* @param text The text to convert.
* @return The integer value read from the text.
*/
int to_integer(const string &text);
/**
* Return a lowercase version of the passed in string.
* @param text The text to convert.
* @return A lower case version of the passed in text.
*/
string to_lowercase(const string &text);
/**
* Convert the passed in double to a string, restricting
* the output the a given number of decimal places. For example
* if value is 3.14159265359 and precision is 2 then the output
* will be "3.14".
* @param value the value to convert to a string.
* @param precision the number of decimal places to output.
* @return string containing the double value.
*/
string to_string(double value, int precision);
/**
* Convert the passed in double to a string.
* @param value the value to convert to a string.
* @return string containing the double value.
*/
string to_string(double value);
/**
* Convert the passed in integer to a string.
* @param value the value to convert to a string.
* @return string containing the integer value.
*/
string to_string(int value);
/**
* Return a UPPERCASE version of the passed in string.
* @param text The text to convert.
* @return An upper case version of the passed in text.
*/
string to_uppercase(const string &text);
/**
* Return a new string that removes the spaces from the start and end of
* the input string.
* @param text The string to trim.
* @return A new string with the contents of `text`, after removing spaces
from the start and end.
*/
string trim(const string &text);

#endif /* __basics_h */
