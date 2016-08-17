//
//  triangle_drawing.hpp
//  splashkit
//
//  Created by Andrew Cain on 17/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef triangle_drawing_h
#define triangle_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"


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


#endif /* triangle_drawing_hpp */
