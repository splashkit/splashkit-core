/**
 * @header rectangle_drawing
 * @author Andrew Cain
 * @attribute group graphics
 */

#ifndef rectangle_drawing_hpp
#define rectangle_drawing_hpp

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"

namespace splashkit_lib
{
    /**
     * Draw a rectangle using the supplied drawing options.
     *
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the window/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the window/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     * @param opts    The drawing options
     */
    void draw_rectangle(color clr, float x, float y, float width, float height, const drawing_options &opts);

    /**
     * Draw a rectangle to the current window.
     *
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the window/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the window/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     */
    void draw_rectangle(color clr, float x, float y, float width, float height);

    /**
     * Draw a rectangle using the supplied drawing options.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     * @param opts    The drawing options
     */
    void draw_rectangle(color clr, const rectangle &rect, const drawing_options &opts);

    /**
     * Draw a rectangle onto the current window.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     */
    void draw_rectangle(color clr, const rectangle &rect);

    /**
     * Fills a rectangle using the supplied drawing options.
     *
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the window/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the window/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     * @param opts    The drawing options
     */
    void fill_rectangle(color clr, float x, float y, float width, float height, const drawing_options &opts);

    /**
     * Fills a rectangle to the current window.
     *
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the window/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the window/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     */
    void fill_rectangle(color clr, float x, float y, float width, float height);

    /**
     * Fills a rectangle using the supplied drawing options.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     * @param opts    The drawing options
     */
    void fill_rectangle(color clr, const rectangle &rect, const drawing_options &opts);

    /**
     * Fill a rectangle onto the current window.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     */
    void fill_rectangle(color clr, const rectangle &rect);

    /**
     * Draw a quad to the current window.
     *
     * @param clr   The color for the quad
     * @param q     The details of the quad
     */
    void draw_quad(color clr, const quad &q);

    /**
     * Draw a quad using the supplied drawing options.
     *
     * @param clr   The color for the quad
     * @param q     The details of the quad
     * @param opts  The drawing options
     */
    void draw_quad(color clr, const quad &q, const drawing_options &opts);

    /**
     * Fill a quad on the current window.
     *
     * @param clr   The color for the quad
     * @param q     The details of the quad
     */
    void fill_quad(color clr, const quad &q);

    /**
     * Fill a quad using the supplied drawing options.
     *
     * @param clr The color for the quad
     * @param q   The details of the quad
     * @param opts  The drawing options
     */
    void fill_quad(color clr, const quad &q, const drawing_options &opts);

}
#endif /* rectangle_drawing_hpp */
