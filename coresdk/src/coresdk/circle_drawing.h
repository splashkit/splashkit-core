//
//  circle_drawing.hpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef circle_drawing_h
#define circle_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"


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

#endif /* circle_drawing_hpp */
