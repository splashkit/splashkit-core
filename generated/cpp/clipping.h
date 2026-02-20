//
// SplashKit Generated Clipping C++ Code
// DO NOT MODIFY
//

#ifndef __clipping_h
#define __clipping_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

/**
* Returns the rectangle of the current clip area for the current window

* @return The current clipping rectangle for the current window
*/
rectangle current_clip();
/**
* Returns the rectangle of the current clip area for a bitmap
* @param bmp The bitmap to get the clipping rectangle from
* @return The current clipping rectangle for the bitmap
*/
rectangle current_clip(bitmap bmp);
/**
* Returns the rectangle of the current clip area for a window
* @param wnd The window to get the clipping rectangle from
* @return The current clipping rectangle for the window
*/
rectangle current_clip(window wnd);
/**
* Remove the last clipping rectangle pushed to the window. This
* will then apply the previously pushed clipping rectangle.
* @param wnd The window to change
*
*/
void pop_clip(window wnd);
/**
* Remove the last clipping rectangle pushed to the current window. This
* will then apply the previously pushed clipping rectangle.

*
*/
void pop_clip();
/**
* Remove the last clipping rectangle pushed to the bitmap. This
* will then apply the previously pushed clipping rectangle.
* @param bmp The bitmap to change
*
*/
void pop_clip(bitmap bmp);
/**
* Add the clipping rectangle of a window and uses the intersect between
* the new rectangle and previous clip.
* 
* When a clipping rectangle is provided, drawing operations will only
* affect the area specified in the current clipping rectangle.
* @param wnd The window to add clipping to
* @param r The new clipping rectangle
*
*/
void push_clip(window wnd, const rectangle &r);
/**
* Add the clipping rectangle of a bitmap and uses the intersect between
* the new rectangle and previous clip.
* 
* When a clipping rectangle is provided, drawing operations will only
* affect the area specified in the current clipping rectangle.
* @param bmp The bitmap to add clipping to
* @param r The new clipping rectangle
*
*/
void push_clip(bitmap bmp, const rectangle &r);
/**
* Push a clip rectangle to the current window. The resulting clipping
* rectangle will be the intersection of the existing clipping rectangle
* with the new rectangle provided in this call. This can be undone using
* `pop_clip`.
* 
* When a clipping rectangle is provided, drawing operations will only
* affect the area specified in the current clipping rectangle.
* @param r The new clipping rectangle
*
*/
void push_clip(const rectangle &r);
/**
* Reset the clipping rectangle on a bitmap. This will clear all
* of the clipping rectangles pushed to the bitmap.
* @param bmp The bitmap to clear the clipping rectangle
*
*/
void reset_clip(bitmap bmp);
/**
* Reset the clipping rectangle of the current window. This will clear all
* of the clipping rectangles pushed to the current window.

*
*/
void reset_clip();
/**
* Reset the clipping rectangle on a window. This will clear all
* of the clipping rectangles pushed to the window.
* @param wnd The window to clear the clipping rectangle
*
*/
void reset_clip(window wnd);
/**
* Set the clip rectangle of the current window. This will clear any
* existing clipping rectangles pushed to the current window, and use the
* supplied rectangle for clipping.
* @param r The new clipping rectangle
*
*/
void set_clip(const rectangle &r);
/**
* Set the clip rectangle of the bitmap. This will clear any existing
* clipping rectangles pushed to the bitmap, and use the supplied rectangle
* for clipping.
* @param bmp The bitmap to change
* @param r The new clipping rectangle
*
*/
void set_clip(bitmap bmp, const rectangle &r);
/**
* Set the clip rectangle of the window. This will clear any existing
* clipping rectangles pushed to the window, and use the supplied rectangle
* for clipping.
* @param wnd The window to change
* @param r The new clipping rectangle
*
*/
void set_clip(window wnd, const rectangle &r);

#endif /* __clipping_h */
