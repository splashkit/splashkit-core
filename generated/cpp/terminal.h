//
// SplashKit Generated Terminal C++ Code
// DO NOT MODIFY
//

#ifndef __terminal_h
#define __terminal_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

/**
* Get a single character input by the user.

* @return The character typed by the user.
*/
char read_char();
/**
* Read a line of text from the terminal. The user will see the text as
* they type it.

* @return The text entered by the user.
*/
string read_line();
/**
* Checks if there is data waiting to be read by read line or read char.

* @return true if there is data waiting to be read.
*/
bool terminal_has_input();
/**
* Write the passed in data to the terminal.
* @param data The character to write
*
*/
void write(char data);
/**
* Write the passed in data to the terminal.
* @param data The text to write
*
*/
void write(double data);
/**
* Write the passed in data to the terminal.
* @param data The text to write
*
*/
void write(int data);
/**
* Write the supplied text to the Terminal.
* @param text The text to write
*
*/
void write(string text);
/**
* Write the passed in data, then move to the next line/row of the terminal.
* @param data The character to write
*
*/
void write_line(char data);
/**
* Move to the next line/row of the terminal.

*
*/
void write_line();
/**
* Write the passed in data, then move to the next line/row of the terminal.
* @param data The text to write
*
*/
void write_line(double data);
/**
* Write the passed in data, then move to the next line/row of the terminal.
* @param data The text to write
*
*/
void write_line(int data);
/**
* Write the passed in text, then move to the next line/row of the terminal.
* @param line The text to write
*
*/
void write_line(string line);

#endif /* __terminal_h */
