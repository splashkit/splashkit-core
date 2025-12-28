//
// SplashKit Generated Utils C++ Code
// DO NOT MODIFY
//

#ifndef __utils_h
#define __utils_h

#include "resources.h"
#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* Gets the number of milliseconds that have passed since the program was
* started.

* @return The number of milliseconds passed
*/
unsigned int current_ticks();
/**
* Puts the program to sleep for a specified number of milliseconds. If this
* is larger than 1 second, SplashKit will check to see if the user tries to
* quit during the delay. If the user does quit, the delay function returns
* without waiting.
* @param milliseconds The number of milliseconds to wait
*
*/
void delay(int milliseconds);
/**
* Display a dialog to the screen with a message for the user.
* @param title The title of the dialog window.
* @param msg The message for the dialog window.
* @param output_font The font for the dialog text
* @param font_size The size of the font for the dialog text
*
*/
void display_dialog(const string &title, const string &msg, font output_font, int font_size);
/**
* Return a SplashKit resource of `resource_kind` with name `filename`
* as a string.
* @param filename The filename of the resource.
* @param kind The kind of resource.
* @return The file loaded into a string.
*/
string file_as_string(string filename, resource_kind kind);

#endif /* __utils_h */
