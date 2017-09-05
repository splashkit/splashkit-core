//
// TODO: This file needs to be deprecated -- all types should be placed in their
//       respective header file
//

/**
 * @header    types
 * @attribute group types
 */

#ifndef types_hpp
#define types_hpp

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace splashkit_lib
{
    /**
     * Colors can be used when drawing shapes and clearing surfaces. Color in
     * splashkit does include a alpha value used for opacity, which allows you
     * to have partially transparent colors.
     *
     * @field r   The red component of the color (between 0 and 1.0)
     * @field g   The green component of the color (between 0 and 1.0)
     * @field b   The blue component of the color (between 0 and 1.0)
     * @field a   The alpha component of the color (between 0 and 1.0)
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
     * @field x   The distance from the left side of the bitmap or window (
     *            increasing as you go to the right)
     * @field y   The distance from the top of a bitmap or window (increasing
     *            as you go down).
     */
    struct point_2d
    {
        double x, y;
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
     * @field x   The distance to move horizontally
     * @field y   The distance to move vertically
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
     * @field x   The distance to the left edge of the rectangle
     * @field y   The distance to the top edge of the rectangle
     * @field width The width of the rectangle
     * @field height The height of the rectangle
     */
    struct rectangle
    {
        double x, y;
        double width, height;
    };

    /**
     * Quads (quadrilaterals) are shapes with 4 sides, but unlike `rectangle`,
     * these shapes can have axis that do not line up with screen/bitmap axis.
     *
     * Points should be constructed with the top left as the first point, top
     * right as the second, bottom left as the third, and bottom right as the
     * last point. Other orders may give unexpected outcomes.
     *
     * @field points The array of points: top left, top right, bottom left,
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
     * @field center  The center point of the circle
     * @field radius  The radius of the circle
     */
    struct circle
    {
        point_2d center;
        double radius;
    };

    /**
     * A triangle consists of three points, being the three points of the
     * triangle.
     *
     * @field points  The points of the triangle
     */
    struct triangle
    {
        point_2d points[3];
    };

    /**
     * A line goes from a start point to an end point.
     *
     * @field start_point   The start of the line
     * @field end_point     The end of the line
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
     * @field dest            The destination of the drawing: a window or bitmap.
     * @field scale_x         How much x values are scaled.
     * @field scale_y         How much y values are scaled.
     * @field angle           A rotation angle for bitmap drawing.
     * @field anchor_offset_x The x location of the anchor point around which
     *                        bitmap drawing will rotate.
     * @field anchor_offset_y The y location of the anchor point around which
     *                        bitmap drawing will rotate.
     * @field flip_x          Should bitmaps be flipped horizontally
     * @field flip_y          Should bitmaps be flipped vertically
     * @field is_part         Indicates that part of a bitmap should be drawn
     * @field part            The area of the bitmap to draw
     * @field draw_cell       Which cell of a bitmap to draw, or -1 for all. Overrides
     *                        parts and animation settings.
     * @field camera          How the current window camera affects the drawing
     * @field line_width      How wide are lines (only lines at this stage)
     * @field anim            The animation to use, which overrides the part
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
        int draw_cell;          // The cell to draw - overridden by animation or part
        drawing_dest camera;    // Draw to world or screen coordinates (camera has effect?)
        int line_width;         // Specify the width of line drawings.
        animation anim;         // The animation for bitmap drawing
    };

    /**
     * Each display value represents a physical display attached to the
     * computer. You can use this to query the displays position and size.
     *
     * @attribute class display
     * @attribute no_destructor true
     */
    typedef struct sk_display *display;

    /**
     * Defines the HTTP status codes supported by SplashKit.
     * Refer to [this article](https://en.wikipedia.org/wiki/List_of_HTTP_status_codes)
     * for a detailed description of each code.
     *
     * @constant HTTP_STATUS_OK                         The server accepted the request.
     * @constant HTTP_STATUS_CREATED                    The request has been fulfilled, resulting in the creation of a new resource.
     * @constant HTTP_STATUS_NO_CONTENT                 The server successfully processed the request and is not returning any content.
     * @constant HTTP_STATUS_BAD_REQUEST                The server cannot or will not process the request due to an apparent client error.
     * @constant HTTP_STATUS_UNAUTHORIZED               The server requires authentication or has failed to process provided authentication.
     * @constant HTTP_STATUS_FORBIDDEN                  The request was a valid request, but the server is refusing to respond to it.
     * @constant HTTP_STATUS_NOT_FOUND                  The requested resource could not be found but may be available in the future.
     * @constant HTTP_STATUS_METHOD_NOT_ALLOWED         The request method is not support for the requested resource.
     * @constant HTTP_STATUS_REQUEST_TIMEOUT            The server timed out waiting for the request.
     * @constant HTTP_STATUS_INTERNAL_SERVER_ERROR      The server encountered an unexpected condition.
     * @constant HTTP_STATUS_NOT_IMPLEMENTED            The server does not recognize or implement the request method.
     * @constant HTTP_STATUS_SERVICE_UNAVAILABLE        The server is currently unavailable.
     */
    enum http_status_code
    {
        HTTP_STATUS_OK = 200,
        HTTP_STATUS_CREATED = 201,
        HTTP_STATUS_NO_CONTENT = 204,
        HTTP_STATUS_BAD_REQUEST = 400,
        HTTP_STATUS_UNAUTHORIZED = 401,
        HTTP_STATUS_FORBIDDEN = 403,
        HTTP_STATUS_NOT_FOUND = 404,
        HTTP_STATUS_METHOD_NOT_ALLOWED = 405,
        HTTP_STATUS_REQUEST_TIMEOUT = 408,
        HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
        HTTP_STATUS_NOT_IMPLEMENTED = 501,
        HTTP_STATUS_SERVICE_UNAVAILABLE = 503
    };
}
#endif /* types_hpp */
