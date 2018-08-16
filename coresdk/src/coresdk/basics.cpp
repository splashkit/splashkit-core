//
//  basics.cpp
//  splashkit
//
//  Created by Andrew Cain on 3/6/17.
//  Copyright © 2017 Andrew Cain. All rights reserved.
//

#include "basics.h"

#include <algorithm>
#include <cstdlib>

#include <functional>
#include <cctype>
#include <locale>

namespace splashkit_lib
{

    // trim see: https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring

    // trim from start
    string ltrim(const string &text)
    {
        string s = text;
        s.erase(s.begin(), std::find_if(s.begin(), s.end(), std::not1(std::ptr_fun<int, int>(std::isspace))));
        return s;
    }

    // trim from end
    string rtrim(const string &text)
    {
        string s = text;
        s.erase(std::find_if(s.rbegin(), s.rend(), std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
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

    // integer check see: https://stackoverflow.com/questions/2844817/how-do-i-check-if-a-c-string-is-an-int#2845275

    bool is_integer(const string &text)
    {
        string s = trim(text);
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
        
        char * p;
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
        if(s.empty() || ((!isdigit(s[0])) && (s[0] != '-') && (s[0] != '+'))) return false;
        
        char * p;
        strtod(s.c_str(), &p);
        
        return (*p == 0);
    }

    int convert_to_integer(const string &text)
    {
        return std::stoi( text );
    }

    double convert_to_double(const string &text)
    {
        return std::stod( text );
    }
}
