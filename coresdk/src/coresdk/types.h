//
// TODO: This file needs to be deprecated -- all types should be placed in their
//       respective header file
//

/**
 * @header    types
 * @brief SplashKit Types simplifies data type creation and management for streamlined programming.
 * @attribute group types
 */

#ifndef types_hpp
#define types_hpp

#include <cstdint>
#include <string>
#include <vector>
#include <cstdint>

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
        NORMAL_FONT = 0,
        BOLD_FONT = 1,
        ITALIC_FONT = 2,
        UNDERLINE_FONT = 4
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
        DRAW_TO_SCREEN, // no camera effect
        DRAW_TO_WORLD,  // camera effect
        DRAW_DEFAULT    // camera effect on screen, but not on bitmaps
    };

    /**
     * Drawing options allow you to customise drawing options. These should be
     * initialised using the drawing option functions such as `option_defaults`.
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
        void *dest;            // The bitmap or window used to draw on to
        float scale_x;         // Scale data
        float scale_y;         //
        float angle;           // Angle for rotations
        float anchor_offset_x; // Centre point for rotations
        float anchor_offset_y; //
        bool flip_x;           // Flip data
        bool flip_y;           //
        bool is_part;          // Draw just a part?
        rectangle part;        // Part to draw
        int draw_cell;         // The cell to draw - overridden by animation or part
        drawing_dest camera;   // Draw to world or screen coordinates (camera has effect?)
        int line_width;        // Specify the width of line drawings.
        animation anim;        // The animation for bitmap drawing
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
     * @constant HTTP_STATUS_MOVED_PERMANENTLY          The URL of the requested resource has been changed permanently.
     * @constant HTTP_STATUS_FOUND                      The URI of requested resource has been changed temporarily.
     * @constant HTTP_STATUS_SEE_OTHER                  The server sent this response to direct the client to get the requested resource at another URI with a GET request.
     * @constant HTTP_STATUS_BAD_REQUEST                The server cannot or will not process the request due to an apparent client error.
     * @constant HTTP_STATUS_UNAUTHORIZED               The server requires authentication or has failed to process provided authentication.
     * @constant HTTP_STATUS_FORBIDDEN                  The request was a valid request, but the server is refusing to respond to it.
     * @constant HTTP_STATUS_NOT_FOUND                  The requested resource could not be found but may be available in the future.
     * @constant HTTP_STATUS_METHOD_NOT_ALLOWED         The request method is not support for the requested resource.
     * @constant HTTP_STATUS_REQUEST_TIMEOUT            The server timed out waiting for the request.
     * @constant HTTP_STATUS_CONFLICT                   The request conflicts with current state of the server.
     * @constant HTTP_STATUS_INTERNAL_SERVER_ERROR      The server encountered an unexpected condition.
     * @constant HTTP_STATUS_NOT_IMPLEMENTED            The server does not recognize or implement the request method.
     * @constant HTTP_STATUS_SERVICE_UNAVAILABLE        The server is currently unavailable.
     */
    enum http_status_code
    {
        HTTP_STATUS_OK = 200,
        HTTP_STATUS_CREATED = 201,
        HTTP_STATUS_NO_CONTENT = 204,
        HTTP_STATUS_MOVED_PERMANENTLY = 301,
        HTTP_STATUS_FOUND = 302,
        HTTP_STATUS_SEE_OTHER = 303,
        HTTP_STATUS_BAD_REQUEST = 400,
        HTTP_STATUS_UNAUTHORIZED = 401,
        HTTP_STATUS_FORBIDDEN = 403,
        HTTP_STATUS_NOT_FOUND = 404,
        HTTP_STATUS_METHOD_NOT_ALLOWED = 405,
        HTTP_STATUS_REQUEST_TIMEOUT = 408,
        HTTP_STATUS_CONFLICT = 409,
        HTTP_STATUS_INTERNAL_SERVER_ERROR = 500,
        HTTP_STATUS_NOT_IMPLEMENTED = 501,
        HTTP_STATUS_SERVICE_UNAVAILABLE = 503
    };

    /**
     * Raspberry Pi GPIO Board Pin Descriptions:
     *
     * @constant PIN_1    3.3V Power Supply
     * @constant PIN_2    5V Power Supply
     * @constant PIN_3    GPIO 2 / SDA (I2C)
     * @constant PIN_4    5V Power Supply
     * @constant PIN_5    GPIO 3 / SCL (I2C)
     * @constant PIN_6    Ground
     * @constant PIN_7    GPIO 4 / GPCLK0
     * @constant PIN_8    GPIO 14 / TXD (UART)
     * @constant PIN_9    Ground
     * @constant PIN_10   GPIO 15 / RXD (UART)
     * @constant PIN_11   GPIO 17
     * @constant PIN_12   GPIO 18 / PCM_CLK
     * @constant PIN_13   GPIO 27
     * @constant PIN_14   Ground
     * @constant PIN_15   GPIO 22
     * @constant PIN_16   GPIO 23
     * @constant PIN_17   3.3V Power Supply
     * @constant PIN_18   GPIO 24
     * @constant PIN_19   GPIO 10 / MOSI (SPI)
     * @constant PIN_20   Ground
     * @constant PIN_21   GPIO 9 / MISO (SPI)
     * @constant PIN_22   GPIO 25
     * @constant PIN_23   GPIO 11 / SCLK (SPI)
     * @constant PIN_24   GPIO 8 / CE0 (SPI)
     * @constant PIN_25   Ground
     * @constant PIN_26   GPIO 7 / CE1 (SPI)
     * @constant PIN_27   ID_SD (I2C ID EEPROM)
     * @constant PIN_28   ID_SC (I2C ID EEPROM)
     * @constant PIN_29   GPIO 5
     * @constant PIN_30   Ground
     * @constant PIN_31   GPIO 6
     * @constant PIN_32   GPIO 12 / PWM0
     * @constant PIN_33   GPIO 13
     * @constant PIN_34   Ground
     * @constant PIN_35   GPIO 19 / MISO (PCM)
     * @constant PIN_36   GPIO 16 / CE0 (PCM_FS)
     * @constant PIN_37   GPIO 26
     * @constant PIN_38   GPIO 20 / MOSI (PCM_DIN)
     * @constant PIN_39   Ground
     * @constant PIN_40   GPIO 21 / SCLK (PCM_DOUT)
     */
    enum gpio_pin
    {
        PIN_1 = 1,
        PIN_2 = 2,
        PIN_3 = 3,
        PIN_4 = 4,
        PIN_5 = 5,
        PIN_6 = 6,
        PIN_7 = 7,
        PIN_8 = 8,
        PIN_9 = 9,
        PIN_10 = 10,
        PIN_11 = 11,
        PIN_12 = 12,
        PIN_13 = 13,
        PIN_14 = 14,
        PIN_15 = 15,
        PIN_16 = 16,
        PIN_17 = 17,
        PIN_18 = 18,
        PIN_19 = 19,
        PIN_20 = 20,
        PIN_21 = 21,
        PIN_22 = 22,
        PIN_23 = 23,
        PIN_24 = 24,
        PIN_25 = 25,
        PIN_26 = 26,
        PIN_27 = 27,
        PIN_28 = 28,
        PIN_29 = 29,
        PIN_30 = 30,
        PIN_31 = 31,
        PIN_32 = 32,
        PIN_33 = 33,
        PIN_34 = 34,
        PIN_35 = 35,
        PIN_36 = 36,
        PIN_37 = 37,
        PIN_38 = 38,
        PIN_39 = 39,
        PIN_40 = 40,
    };

    /**
     * GPIO Pin Modes:
     *
     * @constant GPIO_INPUT   Input mode.
     * @constant GPIO_OUTPUT  Output mode.
     * @constant GPIO_ALT0    Alternate function mode 0.
     * @constant GPIO_ALT1    Alternate function mode 1.
     * @constant GPIO_ALT2    Alternate function mode 2.
     * @constant GPIO_ALT3    Alternate function mode 3.
     * @constant GPIO_ALT4    Alternate function mode 4.
     * @constant GPIO_ALT5    Alternate function mode 5.
     * @constant GPIO_DEFAULT_MODE  Default mode.
     */
    enum gpio_pin_mode
    {
        GPIO_INPUT = 0,
        GPIO_OUTPUT = 1,
        GPIO_ALT0 = 4,
        GPIO_ALT1 = 5,
        GPIO_ALT2 = 6,
        GPIO_ALT3 = 7,
        GPIO_ALT4 = 3,
        GPIO_ALT5 = 2,
        GPIO_DEFAULT_MODE = -1,
    };

    /**
     * GPIO Pin Values:
     *
     * @constant GPIO_DEFAULT_VALUE  Default value, indicates error.
     * @constant GPIO_LOW   Logic low (0).
     * @constant GPIO_HIGH  Logic high (1).
     */
    enum gpio_pin_value
    {
        GPIO_DEFAULT_VALUE = -1,
        GPIO_LOW = 0,
        GPIO_HIGH = 1
    };

    /**
     * GPIO Pull-up/Pull-down Configurations:
     *
     * @constant PUD_OFF   No pull-up or pull-down resistor.
     * @constant PUD_DOWN  Enable pull-down resistor.
     * @constant PUD_UP    Enable pull-up resistor.
     */
    enum pull_up_down
    {
        PUD_OFF = 0,
        PUD_DOWN = 1,
        PUD_UP = 2
    };

    /**
     * ADC Pins:
     *
     * @constant ADC_PIN_0  Analog Input Channel 0
     * @constant ADC_PIN_1  Analog Input Channel 1
     * @constant ADC_PIN_2  Analog Input Channel 2
     * @constant ADC_PIN_3  Analog Input Channel 3
     * @constant ADC_PIN_4  Analog Input Channel 4
     * @constant ADC_PIN_5  Analog Input Channel 5
     * @constant ADC_PIN_6  Analog Input Channel 6
     * @constant ADC_PIN_7  Analog Input Channel 7
     */
    enum adc_pin
    {
        ADC_PIN_0 = 0,
        ADC_PIN_1 = 1,
        ADC_PIN_2 = 2,
        ADC_PIN_3 = 3,
        ADC_PIN_4 = 4,
        ADC_PIN_5 = 5,
        ADC_PIN_6 = 6,
        ADC_PIN_7 = 7,
        // ADC_SDA = 8,
        // ADC_SCL = 9,
        // ADC_VREF = 10,
        // ADC_COM = 12,
        // ADC_AD0 = 13,
        // ADC_AD1 = 14,
    };

    /**
     * Motor Movement Directions:
     * @constant MOTOR_FORWARD  Motor moves forward.
     * @constant MOTOR_BACKWARD Motor moves backward.
     *  
     * */
      enum motor_direction {
        MOTOR_FORWARD,
        MOTOR_BACKWARD
    };

    /**
     * ADC Type:
     *
     * @constant ADS7830  8-Bit, 8-Channel Sampling A/D Converter with I2C Interface
     */
    enum adc_type
    {
       ADS7830 = 0,
    //    PCF8591 = 1,
    };

    /**
     * Motor Driver Types:
     * @constant L298N  Dual H-Bridge Motor Driver
     */

    enum motor_driver_type
    {
        L298N = 0,
        // L293D = 1,
        // TB6612FNG = 2,
        // DRV8835 = 3,
        // DRV8834 = 4,
        // DRV8825 = 5,
        // A4988 = 6,
    };

    /**
     * Use these interface styles as a way to quickly
     * customize your interface.
     *
     * @constant FLAT_DARK_STYLE       A flat, dark-mode interface.
     * @constant SHADED_DARK_STYLE     A dark-mode interface with shadows and depth.
     * @constant FLAT_LIGHT_STYLE      A flat, light-mode interface.
     * @constant SHADED_LIGHT_STYLE    A light-mode interface with shadows and depth.
     * @constant BUBBLE                A light-mode interface with a semi-transparent bubbly look.
     * @constant BUBBLE_MULTICOLORED   A light-mode interface with a semi-transparent bubbly look - gives a multi-coloured result when provided a color.
     */
    enum interface_style
    {
        FLAT_DARK_STYLE = 0,
        SHADED_DARK_STYLE = 1,
        FLAT_LIGHT_STYLE = 2,
        SHADED_LIGHT_STYLE = 3,
        BUBBLE = 4,
        BUBBLE_MULTICOLORED = 5
    };
}
#endif /* types_hpp */
