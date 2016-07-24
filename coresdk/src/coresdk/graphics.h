//
//  graphics.hpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef graphics_hpp
#define graphics_hpp

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"

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

/// Draw a circle using the supplied drawing options.
///
void draw_circle(color clr, float x, float y, float radius, drawing_options opts);

/// Draw a circle onto the current window.
///
void draw_circle(color clr, float x, float y, float radius);

/// Draw a circle onto a destination bitmap.
///
/// @lib draw_circleStructOpts
/// @sn draw_circleColor:%s data:%s opts:%s
void draw_circle(color clr, circle &c, drawing_options opts);

/// Draw a circle in the game.
///
/// @lib draw_circleStruct
/// @sn draw_circleColor:%s data:%s
void draw_circle(color clr, circle &c);


/// Fill a circle onto a destination bitmap.
///
/// @lib fill_circleOpts
/// @sn fill_circleColor:%s atX:%s y:%s radius:%s opts:%s
void fill_circle(color clr, float x, float y, float radius, drawing_options opts);

/// Fill a circle in the game.
///
/// @lib
/// @sn fill_circleColor:%s atX:%s y:%s radius:%s
///
/// @doc_idx 0
void fill_circle(color clr, float x, float y, float radius);

/// Fill a circle onto a destination bitmap.
///
/// @lib fill_circleStructOpts
/// @sn fill_circleColor:%s data:%s opts:%s
void fill_circle(color clr, circle &c,drawing_options opts);

/// Fill a circle in the game.
///
/// @lib fill_circleStruct
/// @sn fill_circleColor:%s data:%s
void fill_circle(color clr, circle &c);

/// Fill a circle at a given point using the passed in drawing options.
///
/// @lib fill_circleAtPointWithOpts
/// @sn fill_circleColor:%s at:%s radius:%s opts:%s
void fill_circle(color clr, point_2d pt, float radius, drawing_options opts);

/// Fill a circle in the game.
///
/// @lib fill_circleAtPoint
/// @sn fill_circleColor:%s at:%s radius:%s
void fill_circle(color clr, point_2d pt, float radius);



#endif /* graphics_hpp */
