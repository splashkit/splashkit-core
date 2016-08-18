//
//  point_drawing.hpp
//  splashkit
//
//  Created by Andrew Cain on 18/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef point_drawing_h
#define point_drawing_h

#include "drawing_options.h"
#include "color.h"

void draw_pixel(color clr, float x, float y);
void draw_pixel(color clr, float x, float y, drawing_options opts);
void draw_pixel(color clr, const point_2d &pt);
void draw_pixel(color clr, const point_2d &pt, drawing_options opts);

/// Returns the color of the pixel at the x,y location on
/// the supplied bitmap.
///
/// @lib GetPixelFromBitmap
/// @sn bitmap:%s colorAtX:%s y:%s
///
/// @class Bitmap
/// @method GetPixel
/// @csn colorAtX:%s y:%s
color get_pixel(bitmap bmp, float x, float y);

color get_pixel(bitmap bmp, const point_2d &pt);

/// Returns the color of the pixel at the x,y location on
/// the supplied window.
///
/// @lib GetPixelFromWindow
/// @sn WindowPixelColor:%s x:%s y:%s
///
/// @class Window
/// @method GetPixel
/// @csn colorAtX:%s y:%s
color get_pixel(window wnd, float x, float y);

color get_pixel(window wnd, const point_2d &pt);

/// Returns the color of the pixel at the given x,y location.
///
/// @lib
/// @sn colorOnScreenAtX:%s y:%s
color get_pixel(float x, float y);

color get_pixel(const point_2d &pt);

#endif /* point_drawing_h */
