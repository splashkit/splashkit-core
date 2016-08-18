//
//  graphics.hpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef graphics_hpp
#define graphics_hpp

#include "drawing_options.h"

#include "circle_drawing.h"
#include "rectangle_drawing.h"
#include "triangle_drawing.h"
#include "point_drawing.h"
#include "ellipse_drawing.h"
#include "line_drawing.h"
#include "clipping.h"

//---------------------------------------------------------------------------------------------------------
// Screen management...
//---------------------------------------------------------------------------------------------------------

/// Refreshes the current drawing on all open windows. This must be called to display
/// anything to the screen. This will show all drawing operations, as well
/// as any text being entered by the user. This will add in delays to limit the framerate
/// to around 60 frames per second.
///
/// Side Effects:
/// - The current drawing is shown on the screen.
void refresh_screen();

/// Refresh with a target FPS. This will delay a period of time that will
/// approximately meet the targetted frames per second.
void refresh_screen(unsigned int target_fps);

void clear_screen(color clr);

/**
 * Returns the width of the current window.
 */
int screen_width();

/**
 * Returns the height of the current window.
 */
int screen_height();

/// Saves the current screen a bitmap file. The file will be saved into the
/// current directory.
///
/// @param basename   The base name for the screen shot. e.g. "GemCollector"
///
/// Side Effects:
/// - Saves the current screen image to a bitmap file.
///
/// @lib TakeScreenshot
void take_screenshot(const string &basename);

void take_screenshot(window wind, const string &basename);

void save_bitmap(bitmap bmp, const string &basename);

int number_of_displays();

display display_details(unsigned int index);

string display_name(display disp);

int display_width(display disp);

int display_height(display disp);

int display_x(display disp);

int display_y(display disp);



#endif /* graphics_hpp */
