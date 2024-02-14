//
// SplashKit Generated Terminal C++ Code
// DO NOT MODIFY
//

#ifndef __terminal_h
#define __terminal_h

#include <string>
#include <vector>
#include <cstdint>
using std::string;
using std::vector;

char read_char();
string read_line();
bool terminal_has_input();
void write(char data);
void write(double data);
void write(int data);
void write(string text);
void write_line(char data);
void write_line();
void write_line(double data);
void write_line(int data);
void write_line(string line);

#endif /* __terminal_h */
