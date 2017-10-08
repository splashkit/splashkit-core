//
//  clipping.hpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef clipping_h
#define clipping_h

#include "geometry.h"
#include "window_manager.h"

/// Push a clip rectangle to the current window. This can be undone using PopClip.
void push_clip(const rectangle &r);

/// Add the clipping rectangle of a bitmap and uses the intersect between the new rectangle and previous clip.
void push_clip(bitmap bmp, const rectangle &r);

/// Add the clipping rectangle of a window and uses the intersect between the new rectangle and previous clip.
void push_clip(window wnd, const rectangle &r);

/// Reset the clipping rectangle of the current window.
void reset_clip();

/// Reset the clipping rectangle on a window.
void reset_clip(window wnd);

/// Reset the clipping rectangle on a bitmap.
void reset_clip(bitmap bmp);

/// Set the clip rectangle of the bitmap.
void set_clip(bitmap bmp, const rectangle &r);

/// Set the clip rectangle of a window.
void set_clip(window wnd, const rectangle &r);

/// Set the clip rectangle of the current window.
void set_clip(const rectangle &r);

/// Pop the clip rectangle of the screen.
void pop_clip();

/// Pop the clipping rectangle of a bitmap.
void pop_clip(bitmap bmp);

/// Pop the clipping rectangle of a bitmap.
void pop_clip(window wnd);

/// Returns the rectangle of the current clip area for a bitmap
rectangle current_clip(bitmap bmp);

/// Returns the rectangle of the clip area for a window
rectangle current_clip(window wnd);

/// Returns the rectangle of the clip area of the current window
rectangle current_clip();

#endif /* clipping_h */
