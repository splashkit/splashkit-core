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
using std::to_string;

string base64_decode(const string &input);
string base64_encode(const string &input);
unsigned int bin_to_dec(const string &bin);
string bin_to_hex(const string &bin_str);
string bin_to_oct(const string &bin_str);
bool contains(const string &text, const string &subtext);
double convert_to_double(const string &text);
int convert_to_integer(const string &text);
string dec_to_bin(unsigned int dec);
string dec_to_oct(unsigned int decimal_value);
int greatest_common_divisor(int number1, int number2);
string hex_to_bin(const string &hex_str);
unsigned int hex_to_dec(const string &hex_string);
string hex_to_oct(const string &hex_str);
int index_of(const string &text, const string &subtext);
bool is_binary(const string &bin_str);
bool is_double(const string &text);
bool is_hex(const string &hex_str);
bool is_integer(const string &text);
bool is_number(const string &text);
bool is_octal(const string &octal_str);
bool is_prime_number(int number);
int least_common_multiple(int number1, int number2);
int length_of(const string &text);
string oct_to_bin(const string &octal_str);
unsigned int oct_to_dec(const string &octal_string);
string oct_to_hex(const string &oct_str);
string replace_all(const string &text, const string &substr, const string &new_text);
vector<string> split(const string &text, char delimiter);
double square_root(int number);
string to_lowercase(const string &text);
string to_uppercase(const string &text);
string trim(const string &text);

#endif /* __basics_h */
