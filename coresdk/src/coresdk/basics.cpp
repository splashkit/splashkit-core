//
//  basics.cpp
//  splashkit
//
//  Created by Andrew Cain on 3/6/17.
//  Copyright © 2017 Andrew Cain. All rights reserved.
//

#include "basics.h"
#include "easylogging++.h"

#include <algorithm>
#include <cstdlib>

#include <functional>
#include <cctype>
#include <locale>
#include <cmath>

namespace splashkit_lib
{

    const string BASE64_CHARS = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";

    // trim see: https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

    // trim from start
    string ltrim(const string &text)
    {
        string s = text;
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), [](int c)
                                        { return !std::isspace(c); }));
        return s;
    }

    // trim from end
    string rtrim(const string &text)
    {
        string s = text;
        s.erase(std::find_if(s.rbegin(), s.rend(), [](int c)
                             { return !std::isspace(c); })
                    .base(),
                s.end());
        return s;
    }

    // trim from both ends
    string trim(const string &text)
    {
        return ltrim(rtrim(text));
    }

    string to_lowercase(const string &text)
    {
        string data = text;
        std::transform(data.begin(), data.end(), data.begin(), ::tolower);
        return data;
    }

    string to_uppercase(const string &text)
    {
        string data = text;
        std::transform(data.begin(), data.end(), data.begin(), ::toupper);
        return data;
    }

    int length_of(const string &text)
    {
        return text.length();
    }

    bool contains(const string &text, const string &subtext)
    {
        return index_of(text, subtext) != -1;
    }

    int index_of(const string &text, const string &subtext)
    {
        size_t pos = text.find(subtext);
        if (pos == string::npos)
            return -1;
        return static_cast<int>(pos);
    }

    string replace_all(const string &text, const string &substr, const string &new_text)
    {
        if (substr.empty())
            return text;

        string result = text;
        size_t pos = 0;
        while ((pos = result.find(substr, pos)) != string::npos)
        {
            result.replace(pos, substr.length(), new_text);
            pos += new_text.length();
        }
        return result;
    }

    vector<string> split(const string &text, char delimiter)
    {
        vector<string> result;
        string::size_type start = 0;
        string::size_type end = text.find(delimiter);
        while (end != string::npos)
        {
            result.push_back(text.substr(start, end - start));
            start = end + 1;
            end = text.find(delimiter, start);
        }
        result.push_back(text.substr(start));
        return result;
    }

    // integer check see: https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int#2845275

    bool is_integer(const string &text)
    {
        string s = trim(text);
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            return false;

        char *p;
        strtol(s.c_str(), &p, 10);

        return (*p == 0);
    }

    bool is_double(const string &text)
    {
        return is_number(text);
    }

    bool is_number(const string &text)
    {
        string s = trim(text);
        if (s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+')))
            return false;

        char *p;
        strtod(s.c_str(), &p);

        return (*p == 0);
    }

    int convert_to_integer(const string &text)
    {
        return std::stoi(text);
    }

    double convert_to_double(const string &text)
    {
        return std::stod(text);
    }

    bool is_binary(const string &bin_str)
    {
        for (char c : bin_str)
        {
            if (c != '0' && c != '1')
                return false;
        }
        return !bin_str.empty();
    }

    bool is_hex(const string &hex_str)
    {
        for (char c : hex_str)
        {
            if (!((c >= '0' && c <= '9') || (c >= 'A' && c <= 'F') || (c >= 'a' && c <= 'f')))
                return false;
        }
        return !hex_str.empty();
    }

    bool is_octal(const string &octal_str)
    {
        for (char c : octal_str)
        {
            if (c < '0' || c > '7')
                return false;
        }
        return !octal_str.empty();
    }

    string dec_to_bin(unsigned int a_dec)
    {
        // Without this check, dec to bin will not work if dec is 0
        if (a_dec == 0)
            return "0";

        string bin_string;
        while (a_dec > 0)
        {
            bin_string = ((a_dec & 1) ? "1" : "0") + bin_string;
            a_dec >>= 1;
        }
        return bin_string;
    }

    unsigned int bin_to_dec(const string &bin_str)
    {
        if (!is_binary(bin_str))
        {
            LOG(ERROR) << "Invalid binary string passed to bin_to_dec, returning 0";
            return 0;
        }

        return stoi(bin_str, nullptr, 2);
    }

    string hex_to_bin(const string &hex_str)
    {
        if (!is_hex(hex_str))
        {
            LOG(ERROR) << "Invalid hexadecimal string passed to hex_to_bin, returning empty string";
            return "";
        }

        string bin_string;
        for (char hex_char : hex_str)
        {
            int hex_val = 0;

            if (hex_char >= '0' && hex_char <= '9')
                hex_val = hex_char - '0';
            else if (hex_char >= 'A' && hex_char <= 'F')
                hex_val = hex_char - 'A' + 10;
            else if (hex_char >= 'a' && hex_char <= 'f')
                hex_val = hex_char - 'a' + 10;

            for (int i = 3; i >= 0; i--)
            {
                bin_string += ((hex_val >> i) & 1) ? '1' : '0';
            }
        }

        if (hex_str.length() == 1)
        {
            size_t first_one = bin_string.find_first_not_of('0');
            return (first_one == string::npos) ? "0" : bin_string.substr(first_one);
        }

        return bin_string;
    }

    string bin_to_hex(const string &bin_str)
    {
        if (!is_binary(bin_str))
        {
            LOG(ERROR) << "Invalid binary string passed to bin_to_hex, returning empty string";
            return "";
        }

        string hex_string;
        int length = bin_str.length();

        int padding = (4 - (length % 4)) % 4;
        string padded_bin_str = string(padding, '0') + bin_str;

        for (size_t i = 0; i < padded_bin_str.length(); i += 4)
        {
            int hex_val = 0;
            for (size_t j = 0; j < 4; j++)
            {
                hex_val <<= 1;
                if (padded_bin_str[i + j] == '1')
                    hex_val |= 1;
            }

            if (hex_val < 10)
                hex_string += '0' + hex_val;
            else
                hex_string += 'A' + (hex_val - 10);
        }
        return hex_string;
    }

    string dec_to_oct(unsigned int decimal_value)
    {
        if (decimal_value == 0)
        {
            LOG(ERROR) << "Invalid decimal value passed to dec_to_oct: " << decimal_value << ", returning 0";
            return "0";
        }

        string octal_string;
        while (decimal_value > 0)
        {
            octal_string = std::to_string(decimal_value % 8) + octal_string;
            decimal_value /= 8;
        }
        return octal_string;
    }

    unsigned int oct_to_dec(const string &octal_string)
    {
        if (!is_octal(octal_string))
        {
            LOG(ERROR) << "Invalid octal string passed to oct_to_dec: " << octal_string << ", returning 0";
            return 0;
        }

        return stoi(octal_string, nullptr, 8);
    }

    unsigned int hex_to_dec(const string &hex_string)
    {
        if (!is_hex(hex_string))
        {
            LOG(ERROR) << "Invalid octal string passed to hex_to_dec: " << hex_string << ", returning 0";
            return 0;
        }

        return stoi(hex_string, nullptr, 16);
    }

    string oct_to_bin(const string &octal_str)
    {
        if (!is_octal(octal_str))
        {
            LOG(ERROR) << "Invalid octal string passed to oct_to_bin: " << octal_str << ", returning empty string";
            return "";
        }

        string bin_string;
        for (char oct_char : octal_str)
        {
            int oct_val = oct_char - '0';

            // Convert each octal digit to a 3-bit binary representation
            for (int i = 2; i >= 0; i--)
            {
                bin_string += ((oct_val >> i) & 1) ? '1' : '0';
            }
        }

        size_t first_one = bin_string.find_first_not_of('0');
        return (first_one == string::npos) ? "0" : bin_string.substr(first_one);
    }

    string bin_to_oct(const string &bin_str)
    {
        if (!is_binary(bin_str))
        {
            LOG(ERROR) << "Invalid binary string passed to bin_to_oct: " << bin_str << ", returning empty string";
            return "";
        }

        string octal_string;

        // Pad binary string with leading zeros to make its length a multiple of 3
        int padding = (3 - (bin_str.length() % 3)) % 3;
        string padded_bin_str = string(padding, '0') + bin_str;

        for (size_t i = 0; i < padded_bin_str.length(); i += 3)
        {
            int oct_val = 0;
            for (size_t j = 0; j < 3; j++)
            {
                oct_val <<= 1;
                if (padded_bin_str[i + j] == '1')
                    oct_val |= 1;
            }

            octal_string += '0' + oct_val;
        }

        size_t first_non_zero = octal_string.find_first_not_of('0');
        return (first_non_zero == string::npos) ? "0" : octal_string.substr(first_non_zero);
    }

    string hex_to_oct(const string &hex_str)
    {
        if (!is_hex(hex_str))
        {
            LOG(ERROR) << "Invalid hexadecimal string passed to hex_to_oct: " << hex_str << ", returning empty string";
            return "";
        }

        string bin_str = hex_to_bin(hex_str);
        return bin_to_oct(bin_str);
    }

    string oct_to_hex(const string &octal_str)
    {
        if (!is_octal(octal_str))
        {
            LOG(ERROR) << "Invalid octal string passed to oct_to_hex: " << octal_str << ", returning empty string";
            return "";
        }

        string bin_str = oct_to_bin(octal_str);
        return bin_to_hex(bin_str);
    }

    string base64_encode(const string &input)
    {
        string encoded;
        int val = 0, bits = -6;
        const unsigned int b63 = 0x3F;

        for (unsigned char c : input)
        {
            val = (val << 8) + c;
            bits += 8;

            while (bits >= 0)
            {
                encoded.push_back(BASE64_CHARS[(val >> bits) & b63]);
                bits -= 6;
            }
        }

        if (bits > -6)
        {
            encoded.push_back(BASE64_CHARS[((val << 8) >> (bits + 8)) & b63]);
        }

        while (encoded.size() % 4)
        {
            encoded.push_back('='); // Padding to make the length a multiple of 4
        }

        return encoded;
    }

    string base64_decode(const string &input)
    {
        string decoded;
        int val = 0, bits = -8;
        for (unsigned char c : input)
        {
            if (BASE64_CHARS.find(c) == string::npos)
            {
                if (c == '=')
                    break; // Padding character, stop decoding
                continue;  // Ignore any characters not in Base64 alphabet
            }

            val = (val << 6) + BASE64_CHARS.find(c);
            bits += 6;

            if (bits >= 0)
            {
                decoded.push_back(char((val >> bits) & 0xFF));
                bits -= 8;
            }
        }
        return decoded;
    }

    double square_root(int number)
    {
        if (number == 0 || number == 1)
            return number;

        return sqrt(static_cast<double>(number));
    }

    bool is_prime_number(int number)
    {
        if (number <= 1)
            return false;
        for (int i = 2; i <= square_root(number); i++)
        {
            if (number % i == 0)
                return false;
        }
        return true;
    }

    int greatest_common_divisor(int number1, int number2)
    {
        // gcd(0, 0) == 0
        if (number1 == 0 && number2 == 0)
        {
            return 0;
        }

        while (number2 != 0)
        {
            int temp = number2;
            number2 = number1 % number2;
            number1 = temp;
        }
        return number1;
    }

    int least_common_multiple(int number1, int number2)
    {
        // lcm(0, n) == 0
        if (number1 == 0 || number2 == 0)
        {
            return 0;
        }
        return abs(number1 * number2) / greatest_common_divisor(number1, number2);
    }

}