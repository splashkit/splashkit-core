/**
 * @header circle_drawing
 * @author Andrew Cain
 * @attribute group graphics
 */

#ifndef circle_drawing_h
#define circle_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"
namespace splashkit_lib
{
    /**
     *  Draw a circle using the supplied drawing options. The circle is centred on its x, y
     *  coordinates, and has the provided radius. This will use `drawing_options` to determine
     *  the destination.
     *
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     */
    void draw_circle(color clr, double x, double y, double radius, drawing_options opts);

    /**
     *  Draw a circle onto the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     */
    void draw_circle(color clr, double x, double y, double radius);

    /**
     *  Draw a circle with the provided drawing options, which may include options related to
     *  the drawing destination.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    record_with_options
     * @attribute class     circle
     * @attribute method    draw
     * @attribute self      c
     */
    void draw_circle(color clr, const circle &c, drawing_options opts);

    /**
     *  Draw a circle on the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
     *
     * @attribute suffix    record
     * @attribute class     circle
     * @attribute method    draw
     * @attribute self      c
     */
    void draw_circle(color clr, const circle &c);

    /**
     *  Fill a circle using the supplied drawing options. The circle is centred on its x, y
     *  coordinates, and has the provided radius. This will use `drawing_options` to determine
     *  the destination.
     *
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     */
    void fill_circle(color clr, double x, double y, double radius, drawing_options opts);

    /**
     *  Fill a circle onto the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     */
    void fill_circle(color clr, double x, double y, double radius);

    /**
     *  Fill a circle with the provided drawing options, which may include options related to
     *  the drawing destination.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    record_with_options
     * @attribute class     circle
     * @attribute method    fill
     * @attribute self      c
     */
    void fill_circle(color clr, const circle &c, drawing_options opts);

    /**
     *  Draw a circle on the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
     *
     * @attribute suffix    record
     * @attribute class     circle
     * @attribute method    fill
     * @attribute self      c
     */
    void fill_circle(color clr, const circle &c);
    
    /**
     *  Draw a circle to the window using the supplied drawing options. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination window
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     * @attribute class     window
     * @attribute method    draw_circle
     */
    void draw_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts);
    
    /**
     *  Draw a circle onto the destination window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination window
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     *
     * @attribute class     window
     * @attribute method    draw_circle
     */
    void draw_circle_on_window(window destination, color clr, double x, double y, double radius);

    /**
     *  Draw a circle to the bitmap using the supplied drawing options. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     * @attribute class     bitmap
     * @attribute method    draw_circle
     */
    void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts);
    
    /**
     *  Draw a circle onto the destination bitmap. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     *
     * @attribute class     bitmap
     * @attribute method    draw_circle
     */
    void draw_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius);

    /**
     *  Fill a circle to the window using the supplied drawing options. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination window
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     * @attribute class     window
     * @attribute method    fill_circle
     */
    void fill_circle_on_window(window destination, color clr, double x, double y, double radius, drawing_options opts);
    
    /**
     *  Fill a circle onto the destination window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination window
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     *
     * @attribute class     window
     * @attribute method    fill_circle
     */
    void fill_circle_on_window(window destination, color clr, double x, double y, double radius);
    
    /**
     *  Fill a circle to the bitmap using the supplied drawing options. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     * @attribute class     bitmap
     * @attribute method    fill_circle
     */
    void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius, drawing_options opts);
    
    /**
     *  Fill a circle onto the destination bitmap. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     *
     * @attribute class     bitmap
     * @attribute method    fill_circle
     */
    void fill_circle_on_bitmap(bitmap destination, color clr, double x, double y, double radius);
}
#endif /* circle_drawing_hpp */
