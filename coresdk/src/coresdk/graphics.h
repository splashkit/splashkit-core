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

/// Draw a rectangle using the supplied drawing options.
///
/// @lib DrawRectangleOpts
/// @sn drawRectangleColor:%s atX:%s y:%s width:%s height:%s opts:%s
void draw_rectangle(color clr, float x, float y, float width, float height, drawing_options opts);

/// Draw a rectangle onto the current window.
///
/// @lib DrawRectangle
/// @sn drawRectangleColor:%s atX:%s y:%s width:%s height:%s
void draw_rectangle(color clr, float x, float y, float width, float height);

/// Fill a rectangle using the supplied drawing options.
///
/// @lib FillRectangleOpts
/// @sn fillRectangleColor:%s atX:%s y:%s width:%s height:%s opts:%s
void fill_rectangle(color clr, float x, float y, float width, float height, drawing_options opts);

/// Fill a rectangle onto the current window.
///
void fill_rectangle(color clr, float x, float y, float width, float height);


//---------------------------------------------------------------------------------------------------------
// Triangle Drawing...
//---------------------------------------------------------------------------------------------------------

/// Draw a triangle onto a destination bitmap.
///
/// @lib DrawTriangleOpts
/// @sn drawTriangleColor:%s atX1:%s y1:%s x2:%s y2:%s x3:%s y3:%s opts:%s
void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3, drawing_options opts);

/// Draw a triangle in the game.
///
/// @lib
/// @sn drawTriangleColor:%s atX1:%s y1:%s x2:%s y2:%s x3:%s y3:%s
///
/// @doc_idx 0
void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3);

///// Draw a triangle onto a destination bitmap.
/////
///// @lib DrawTriangleStructOpts
///// @sn drawTriangleColor:%s data:%s opts:%s
//procedure DrawTriangle(clr : Color; const tri: Triangle; const opts : DrawingOptions); overload;
//
///// Draw a triangle in the game.
/////
///// @lib DrawTriangleStruct
///// @sn drawTriangleColor:%s data:%s
//procedure DrawTriangle(clr : Color; const tri: Triangle);

/// Fill a triangle onto a destination bitmap.
///
/// @lib FillTriangleOpts
/// @sn fillTriangleColor:%s atX1:%s y1:%s x2:%s y2:%s x3:%s y3:%s opts:%s
void fill_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3, drawing_options opts);

/// Fill a triangle in the game.
///
/// @lib
/// @sn fillTriangleColor:%s atX1:%s y1:%s x2:%s y2:%s x3:%s y3:%s
///
/// @doc_idx 0
void fill_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3);

//---------------------------------------------------------------------------------------------------------
// Line Drawing...
//---------------------------------------------------------------------------------------------------------

/// Draw a line onto a destination bitmap.
///
/// @lib DrawLineOpts
/// @sn drawLineColor:%s atX1:%s y1:%s x2:%s y2:%s opts:%s
void draw_line(color clr, float x1, float y1, float x2, float y2, drawing_options opts);

/// Draw a line in the game.
///
/// @lib
/// @sn drawLineColor:%s atX1:%s y1:%s x2:%s y2:%s
///
/// @doc_idx 0
void draw_line(color clr, float x1, float y1, float x2, float y2);

///// Draw a line onto a destination bitmap.
/////
///// @lib DrawLineStructOpts
///// @sn drawLineColor:%s data:%s opts:%s
//procedure DrawLine(clr : Color; const tri: Line; const opts : DrawingOptions); overload;
//
///// Draw a line in the game.
/////
///// @lib DrawLineStruct
///// @sn drawLineColor:%s data:%s
//procedure DrawLine(clr : Color; const tri: Line);



#endif /* graphics_hpp */
