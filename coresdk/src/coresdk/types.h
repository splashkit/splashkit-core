
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
namespace splashkit_lib
{
    /**
     * The free notifier can be registered with the system. It is called every
     * time a resource is freed.
     *
     * @param pointer   The pointer to the resource that is being freed.
     */
    typedef void (free_notifier)(void *pointer);

    /**
     * Colors can be used when drawing shapes and clearing surfaces. Color in
     * splashkit does include a alpha value used for opacity, which allows you
     * to have partially transparent colors.
     *
     * @param r   The red component of the color (between 0 and 1.0)
     * @param g   The green component of the color (between 0 and 1.0)
     * @param b   The blue component of the color (between 0 and 1.0)
     * @param a   The alpha component of the color (between 0 and 1.0)
     *
     */
    struct color
    {
        float r, g, b, a;
    };

    /**
     * Bitmaps represent image resources in SplashKit. You can load these from
     * file, download them from the internet, or create and draw them yourself.
     * Once created or loaded, you can draw the bitmap and you can draw onto
     * the bitmap.
     *
     * @attribute class bitmap
     */
    typedef struct _bitmap_data *bitmap;

    /**
     * Use font styles to set the style of a font. Setting the style is time
     * consuming, so create alternative font variables for each different
     * style you want to work with. Note that these values can be logical
     * ORed together to combine styles, e.g. BoldFont or ItalicFont = both
     * bold and italic.
     *
     * @constant NORMAL_FONT       Normal font.
     * @constant BOLD_FONT         Bold font.
     * @constant ITALIC_FONT       Italic font.
     * @constant UNDERLINE_FONT    Underlined font.
     */
    enum font_style
    {
        NORMAL_FONT      = 0,
        BOLD_FONT        = 1,
        ITALIC_FONT      = 2,
        UNDERLINE_FONT   = 4
    };

    /**
     * Fonts are used to draw text in SplashKit. These can be loaded from file
     * or downloaded from the internet. Once you have a font you can use the
     * draw text procedures to use that font when drawing.
     *
     * @attribute class font
     */
    typedef struct sk_font_data *font;

    /**
     * Animations in SplashKit are controlled by an animation script. This
     * script tells SplashKit how long to play each frame, which cell in the
     * bitmap the frame relates to, and which is the next frame. You load these
     * scripts from file and can then use them to create animations that are
     * used with the drawing options when you draw a bitmap.
     *
     * @attribute class animation_script
     */
    typedef struct _animation_script_data *animation_script;

    /**
     * Animations are created from an `animation_script`. Each animation tracks
     * the current frame for one animation sequence. You update this animation
     * and draw with it. This allows you to have the one script being used to
     * create lots of individual animations, where each animation is potentially
     * at a different frame.
     *
     * @attribute class animation
     */
    typedef struct _animation_data *animation;

    /**
     * A Point2D represents an location in Cartesian coordinates (x,y).
     * The x value represents the distance from the left edge of the window or bitmap, increasing
     * in value as you travel right. The y value represents the distance from the top
     * edge of the window or bitmap, and increases as you travel down toward the bottom.
     *
     * Point2D is a great way to keep track of the location of something in a 2D space like
     * a Window or Bitmap.
     *
     * @param x   The distance from the left side of the bitmap or window (
     *            increasing as you go to the right)
     * @param y   The distance from the top of a bitmap or window (increasing
     *            as you go down).
     */
    struct point_2d
    {
        float x, y;
    };

    /**
     * Vectors represent a direction and distance, and can be visualised as an
     * arrow from one point to another in 2 dimensional space. Internally, the
     * `vector_2d` is stored as its x and y components.
     *
     * Vector is a great way to represent movement or forces. You could use a
     * `vector_2d` to track how much a character moves each update (as the
     * vector stores the direction and distance). Similarly, you could use a
     * `vector_2d` to represent gravity or other forces. You can then
     * add a number of force vectors together to get a final force to be applied
     * to a character.
     *
     * @param x   The distance to move horizontally
     * @param y   The distance to move vertically
     */
    struct vector_2d
    {
        double x;
        double y;
    };

    /**
     * Rectangles are simple rectangle shapes that exist at a point and have a
     * set width and height. This means that the rectangle always has edges that
     * follow the sides of the `window` or `bitmap` (so they are aligned with
     * the x and y axes). The rectangle's position is its top left corner - it
     * then extends to the right and down from this position.
     *
     * @param x   The distance to the left edge of the rectangle
     * @param y   The distance to the top edge of the rectangle
     * @param width The width of the rectangle
     * @param height The height of the rectangle
     */
    struct rectangle
    {
        float x, y;
        float width, height;
    };

    /**
     * Quads (quadrilaterals) are shapes with 4 sides, but unlike `rectangle`,
     * these shapes can have axis that do not line up with screen/bitmap axis.
     *
     * Points should be constructed with the top left as the first point, top
     * right as the second, bottom left as the third, and bottom right as the
     * last point. Other orders may give unexpected outcomes.
     *
     * @param points The array of points: top left, top right, bottom left,
     *                bottom right
     */
    struct quad
    {
        point_2d points[4];
    };

    /**
     * Circles have a center point and a radius. This means that, unlike shapes
     * like the `rectangle`, the circle extends out both left and right, and up
     * and down from the point you position it at.
     *
     * @param center  The center point of the circle
     * @param radius  The radius of the circle
     */
    struct circle
    {
        point_2d center;
        float radius;
    };

    /**
     * A triangle consists of three points, being the three points of the
     * triangle.
     *
     * @param points  The points of the triangle
     */
    struct triangle
    {
        point_2d points[3];
    };

    /**
     * A line goes from a start point to an end point.
     *
     * @param start_point   The start of the line
     * @param end_point     The end of the line
     */
    struct line
    {
        point_2d start_point;
        point_2d end_point;
    };

    /**
     * Determines the effect of the camera on a drawing operation.
     *
     * @constant DRAW_TO_SCREEN means camera has no affect.
     * @constant DRAW_TO_WORLD  means camera has an affect.
     * @constant DRAW_DEFAULT   means camera has an affect only if drawn to a
     *                          window.
     */
    enum drawing_dest
    {
        DRAW_TO_SCREEN,  // no camera effect
        DRAW_TO_WORLD,   // camera effect
        DRAW_DEFAULT     // camera effect on screen, but not on bitmaps
    };

    /**
     * Drawing options allow you to customise drawing options. These should be
     * initialised using the drawing option functions.
     *
     * @param dest            The destination of the drawing: a window or bitmap.
     * @param scale_x         How much x values are scaled.
     * @param scale_y         How much y values are scaled.
     * @param angle           A rotation angle for bitmap drawing.
     * @param anchor_offset_x The x location of the anchor point around which
     *                        bitmap drawing will rotate.
     * @param anchor_offset_y The y location of the anchor point around which
     *                        bitmap drawing will rotate.
     * @param flip_x          Should bitmaps be flipped horizontally
     * @param flip_y          Should bitmaps be flipped vertically
     * @param is_part         Indicates that part of a bitmap should be drawn
     * @param part            The area of the bitmap to draw
     * @param camera          How the current window camera affects the drawing
     * @param line_width      How wide are lines (only lines at this stage)
     * @param anim            The animation to use, which overrides the part
     *                        option
     */
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
     * Each display value represents a physical display attached to the
     * computer. You can use this to query the displays position and size.
     *
     * @attribute class display
     */
    typedef struct sk_display *display;

    /**
     * Defines the HTTP status codes supported by SplashKit.
     * See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * for a description of each code.
     *
     * @constant OK                         See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant CREATED                    See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant NO_CONTENT                 See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant BAD_REQUEST                See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant UNAUTHORIZED               See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant FORBIDDEN                  See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant NOT_FOUND                  See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant METHOD_NOT_ALLOWED         See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant REQUEST_TIMEOUT            See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant INTERNAL_SERVER_ERROR      See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant NOT_IMPLEMENTED            See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     * @constant SERVICE_UNAVAILABLE        See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes
     */
    enum http_status_code
    {
        OK = 200,
        CREATED = 201,
        NO_CONTENT = 204,
        BAD_REQUEST = 400,
        UNAUTHORIZED = 401,
        FORBIDDEN = 403,
        NOT_FOUND = 404,
        METHOD_NOT_ALLOWED = 405,
        REQUEST_TIMEOUT = 408,
        INTERNAL_SERVER_ERROR = 500,
        NOT_IMPLEMENTED = 501,
        SERVICE_UNAVAILABLE = 503
    };

}
#endif /* types_hpp */
