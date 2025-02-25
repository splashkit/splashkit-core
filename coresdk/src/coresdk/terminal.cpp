//
//  terminal.cpp
//  splashkit
//
//  Created by Andrew Cain on 8/10/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <easylogging++.h>
#include "types.h"
#include <iostream>
#include <map>

using std::map;
using std::pair;
using std::cout;
using std::to_string;
using std::endl;
using std::cin;

namespace splashkit_lib
{
    void write(string text)
    {
        cout << text;
        cout.flush();
    }
    
    void write(int data)
    {
        write(to_string(data));
    }

    void write(char data)
    {
        write(string("") + data);
    }
    
    void write(double data)
    {
        write(to_string(data));
    }

    void write_line()
    {
        cout << endl;
        cout.flush();
    }

    void write_line(string line)
    {
        cout << line << endl;
        cout.flush();
    }
    
    void write_line(int data)
    {
        write_line(to_string(data));
    }
    
    void write_line(double data)
    {
        write_line(to_string(data));
    }

    void write_line(char data)
    {
        write_line(std::string(1, data));
    }

    string read_line()
    {
        string result;
        cin.clear(); 
        cin.sync();
        getline(std::cin, result);
        return result;
    }

    char read_char()
    {
        char result = 0;
        cin.clear();  
        cin.sync();
        cin >> result;
        cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        return result;
    }

    bool terminal_has_input()
    {
        return cin.peek() != EOF;
    }
}
