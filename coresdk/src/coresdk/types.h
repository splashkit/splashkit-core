//
//  types.hpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef types_hpp
#define types_hpp

#include <string>
using namespace std;

typedef unsigned char byte;

/**
 * The free notifier can be registered with the system. It is called every
 * time a resource is freed.
 *
 * @param pointer   The pointer to the resource that is being freed.
 */
typedef void (free_notifier)(void *pointer);

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
typedef struct sk_font_data *font;

typedef struct _animation_script_data *animation_script;
typedef struct _animation_data *animation;

/// A Point2D represents an location in Cartesian coordinates (x,y).
/// The x value represents the distance from the left edge of the window or bitmap, increasing
/// in value as you travel right. The y value represents the distance from the top
/// edge of the window or bitmap, and increases as you travel down toward the bottom.
///
/// Point2D is a great way to keep track of the location of something in a 2D space like
/// a Window or Bitmap.
///
/// @struct Point2D
/// @sameas Vector
struct point_2d
{
    float x, y;
};

/// Vectors represent a direction and distance, and can be visualised as an arrow from
/// one point to another in 2 dimensional space. Internally, the Vector is stored as its
/// x and y components (same as a `Point2D`).
///
/// Vector is a great way to represent movement or forces. You could use a vector to track
/// how much a character moves each update (as the Vector stores the direction and distance).
/// Similarly, you could use a Vector to represent gravity or other forces. You can then
/// add a number of force vectors together to get a final force to be applied to a character.
///
/// @struct Vector2D
/// @field x: Single
/// @field y: Single
/// @sameas Point2D
struct vector_2d
{
    float x;
    float y;
};

/// Rectangles are simple rectangle shapes that exist at a point and have a set width
/// and height. This means that the rectangle always has edges that follow the sides of
/// the Window or Bitmap (so they are aligned with the x and y axes). The rectangle's
/// position is its top left corner - it then extends to the right and down from
/// this position.
///
/// @struct Rectangle
struct rectangle
{
    float x, y;
    float width, height;
};

/// Quads (Quadrilaterals) are shapes with 4 sides, but unlike `Rectangle`, these shapes can have axis that
/// do not line up with screen/bitmap axis.
///
/// Points should be constructed with the top left as the first point, top right as the second,
/// bottom left as the third, and bottom right as the last point. Other orders may give unexpected
/// outcomes.
///
/// @struct Quad
struct quad
{
    point_2d points[4];
};

/// Circles have a center point and a radius. This means that, unlike other shapes
/// like the `Rectangle`, the circle extends out both left and right, and up and down
/// from the point you position it at.
///
/// @struct Circle
struct circle
{
    point_2d center;
    float radius;
};

/**
 * A triangle consists of three points
 */
struct triangle
{
    point_2d points[3];
};

/**
 * A line goes from a start point to an end point.
 */
struct line
{
    point_2d start_point;
    point_2d end_point;
};

/// Determines the effect of the camera on a drawing operation.
/// `DRAW_TO_SCREEN` means camera has no affect.
/// `DRAW_TO_WORLD` means camera has an affect.
/// `DRAW_DEFAULT` means camera has an affect only if drawn to the screen.
/// @enum DrawingDest
enum drawing_dest
{
    DRAW_TO_SCREEN,  // no camera effect
    DRAW_TO_WORLD,   // camera effect
    DRAW_DEFAULT     // camera effect on screen, but not on bitmaps
};

/// The drawing options struct contains the data that can
/// be used to provide different options to various drawing
/// operations.
///
/// @struct DrawingOptions
struct drawing_options
{
    void *dest;             // The bitmap or window used to draw on to
    float scale_x;          // Scale data
    float scale_y;          //
    float angle;            // Angle for rotations
    float anchor_offset_x;  // Centre point for rotations
    float anchor_offset_y;  //
    bool  flip_x;           // Flip data
    bool  flip_y;           //
    bool  is_part;          // Draw just a part?
    rectangle part;         // Part to draw
    drawing_dest camera;    // Draw to world or screen coordinates (camera has effect?)
    int line_width;         // Specify the width of line drawings.
    animation anim;         // The animation for bitmap drawing
};

/**
 * Each display value represents a physical display attached to the computer.
 * You can use this to query the displays position and size.
 *
 * @attribute class display
 */
typedef struct sk_display *display;


#endif /* types_hpp */
