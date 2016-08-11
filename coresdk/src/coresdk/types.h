//
//  types.hpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef types_hpp
#define types_hpp

typedef unsigned char byte;

struct color
{
    float r, g, b, a;
};

/// The bitmap type is a pointer to a BitmapData. The BitmapData record
/// contains the data used by the SwinGame API to represent
/// bitmaps. You can create new bitmaps in memory for drawing operatings
/// using the `CreateBitmap` function. This can then be optimised for drawing
/// to the screen using the `OptimiseBitmap` routine. Also see the `DrawBitmap`
/// routines.
///
/// @class Bitmap
/// @pointer_wrapper
/// @field pointer: pointer
typedef struct _bitmap_data *bitmap;

/// Use font styles to set the style of a font. Setting the style is time
/// consuming, so create alternative font variables for each different
/// style you want to work with. Note that these values can be logical
/// ORed together to combine styles, e.g. BoldFont or ItalicFont = both
/// bold and italic.
///
/// @enum font_style
enum font_style
{
    NORMAL_FONT      = 0,
    BOLD_FONT        = 1,
    ITALIC_FONT      = 2,
    UNDERLINE_FONT   = 4
};

/// Provides an overload that allows combining font styles with the bit or 
/// operator.
/// Source: http://stackoverflow.com/a/1448478
inline font_style operator|(font_style a, font_style b)
{
    return static_cast<font_style>(static_cast<int>(a) | static_cast<int>(b));
}

/// Use font alignment for certain drawing operations. With these
/// operations you specify the area to draw in as well as the alignment
/// within that area. See DrawTextLines.
///
/// @enum font_alignment
enum font_alignment
{
    ALIGN_LEFT   = 1,
    ALIGN_CENTER = 2,
    ALIGN_RIGHT  = 4
};


/// Fonts are used to render text to bitmaps and to the screen.
/// Fonts must be loaded using the CreateFont routine. Also see the
/// DrawText and DrawTextLines routines.
///
/// @class Font
/// @pointer_wrapper
/// @field pointer: pointer
typedef struct _font_data *font;

#endif /* types_hpp */
