//
// SplashKit Generated Graphics C++ Code
// DO NOT MODIFY
//

#ifndef __graphics_h
#define __graphics_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* Clears the current screen to color white.

*
*/;
void clear_screen();
/**
* 
* @param clr The color to clear the screen's background color to.
*
*/;
void clear_screen(color clr);
/**
* Returns the details about one of the displays attached to the computer.
* @param index The display number (from 0 to `number_of_displays` - 1)
* @return The details of this display
*/;
display display_details(unsigned int index);
/**
* Return the height of the display in pixels, read from the system details.
* @param disp The display details
* @return The height of the display
*/;
int display_height(display disp);
/**
* Return the name of the display, read from the system details.
* @param disp The display details
* @return The name of the display
*/;
string display_name(display disp);
/**
* Return the width of the display in pixels, read from the system details.
* @param disp The display details
* @return The width of the display
*/;
int display_width(display disp);
/**
* Return a relative x location for the display in pixels, read from the
* system details. This can be used to work out the arrangement of displays.
* @param disp The display details
* @return The x location of the display
*/;
int display_x(display disp);
/**
* Return a relative y location for the display in pixels, read from the
* system details. This can be used to work out the arrangement of displays.
* @param disp The display details
* @return The y location of the display
*/;
int display_y(display disp);
/**
* Returns the number of physical displays attached to the computer.

* @return The number of displays attached to the computer
*/;
int number_of_displays();
/**
* 

*
*/;
void refresh_screen();
/**
* Refreshes all open windows with a target FPS (frames per second). This will
* delay a period of time that will approximately meet the targeted frames per
* second.
* @param target_fps The targeted frames per second to refresh the screen at.
*
*/;
void refresh_screen(unsigned int target_fps);
/**
* Save the bitmap to the user's desktop.
* @param bmp The bitmap to save
* @param basename The base of the filename. If there is a file of this name
* already, then the name will be changed to generate a
* unique filename.
*
*/;
void save_bitmap(bitmap bmp, const string &basename);
/**
* Returns the height of the current window.

* @return The height of the current window.
*/;
int screen_height();
/**
* Returns the width of the current window.

* @return The width of the current window.
*/;
int screen_width();
/**
* Saves a screenshot of the current window to a bitmap file. The file will
* be saved onto the user's desktop.
* @param basename The base of the filename. If there is a file of this name
* already, then the name will be changed to generate a
* unique filename.
*
*/;
void take_screenshot(const string &basename);
/**
* Saves a screenshot of the current window to a bitmap file. The file will
* be saved onto the user's desktop.
* @param wind The window to capture in the screenshot
* @param basename The base of the filename. If there is a file of this name
* already, then the name will be changed to generate a
* unique filename.
*
*/;
void take_screenshot(window wind, const string &basename);

#endif /* __graphics_h */
