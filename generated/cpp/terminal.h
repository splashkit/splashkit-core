//
// SplashKit Generated Terminal C++ Code
// DO NOT MODIFY
//

#ifndef __terminal_h
#define __terminal_h

#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void activate_advanced_terminal();
bool advanced_terminal_active();
void clear_terminal();
void end_advanced_terminal();
void move_cursor_to(int x, int y);
char read_char();
string read_line();
void refresh_terminal();
void set_terminal_bold(bool value);
void set_terminal_colors(color foreground, color background);
void set_terminal_echo_input(bool value);
int terminal_height();
int terminal_width();
void write(char data);
void write(double data);
void write(int data);
void write(string text);
void write_at(string text, int x, int y);
void write_line(char data);
void write_line();
void write_line(double data);
void write_line(int data);
void write_line(string line);

#endif /* __terminal_h */
