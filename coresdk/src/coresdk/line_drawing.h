/**
 * @header line_drawing
 * @author Andrew Cain
 * @attribute group graphics
 */

#ifndef line_drawing_h
#define line_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"
namespace splashkit_lib
{
    /**
     * Draw a line from one point to another on the current window.
     *
     * @param clr The color of the line
     * @param x1  The distance from the left of the window/bitmap to the first
     *            point
     * @param y1  The distance from the top of the window/bitmap to the first
     *            point
     * @param x2  The distance from the left of the window/bitmap to the second
     *            point
     * @param y2  The distance from the top of the window/bitmap to the second
     *            point
     */
    void draw_line(color clr, float x1, float y1, float x2, float y2);

    /**
     * Draw a line from one point to another
     *
     * @param clr The color of the line
     * @param x1  The distance from the left of the window/bitmap to the first
     *            point
     * @param y1  The distance from the top of the window/bitmap to the first
     *            point
     * @param x2  The distance from the left of the window/bitmap to the second
     *            point
     * @param y2  The distance from the top of the window/bitmap to the second
     *            point
     * @param opts The drawing options
     */
    void draw_line(color clr, float x1, float y1, float x2, float y2, const drawing_options &opts);

    /**
     * Draw a line from one point to another on the current window.
     *
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     */
    void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt);

    /**
     * Draw a line from one point to another on the current window.
     *
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     * @param opts The drawing options
     */
    void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);

    /**
     * Draws a line onto the current window.
     *
     * @param clr The color of the line
     * @param l   The line's details
     */
    void draw_line(color clr, const line &l);

    /**
     * Draws a line.
     *
     * @param clr The color of the line
     * @param l   The line's details
     * @param opts The drawing options
     */
    void draw_line(color clr, const line &l, drawing_options opts);
}
#endif /* line_drawing_h */
