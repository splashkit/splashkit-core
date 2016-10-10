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
     */
    void draw_circle(color clr, float x, float y, float radius, drawing_options opts);

    /**
     *  Draw a circle onto the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     */
    void draw_circle(color clr, float x, float y, float radius);

    /**
     *  Draw a circle with the provided drawing options, which may include options related to
     *  the drawing destination.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
     * @param opts   Drawing options to configure the drawing operation
     */
    void draw_circle(color clr, const circle &c, drawing_options opts);

    /**
     *  Draw a circle on the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
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
     */
    void fill_circle(color clr, float x, float y, float radius, drawing_options opts);

    /**
     *  Fill a circle onto the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param x      The x location of the circle
     * @param y      The y location of the circle
     * @param radius The radius of the circle
     */
    void fill_circle(color clr, float x, float y, float radius);

    /**
     *  Fill a circle with the provided drawing options, which may include options related to
     *  the drawing destination.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
     * @param opts   Drawing options to configure the drawing operation
     */
    void fill_circle(color clr, const circle &c, drawing_options opts);

    /**
     *  Draw a circle on the current window. The circle is centred on its x, y
     *  coordinates, and has the provided radius.
     *
     * @param clr    The color of the circle
     * @param c      The circle being drawn
     */
    void fill_circle(color clr, const circle &c);
}
#endif /* circle_drawing_hpp */
