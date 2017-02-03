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
     *
     * @attribute suffix  with_options
     */
    void draw_rectangle(color clr, double x, double y, double width, double height, const drawing_options &opts);

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
    void draw_rectangle(color clr, double x, double y, double width, double height);

    /**
     * Draw a rectangle using the supplied drawing options.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     * @param opts    The drawing options
     *
     * @attribute suffix  record_with_options
     */
    void draw_rectangle(color clr, const rectangle &rect, const drawing_options &opts);

    /**git stat
     * Draw a rectangle onto the current window.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     *
     * @attribute suffix  record
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
     *
     * @attribute suffix  with_options
     */
    void fill_rectangle(color clr, double x, double y, double width, double height, const drawing_options &opts);

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
    void fill_rectangle(color clr, double x, double y, double width, double height);

    /**
     * Fills a rectangle using the supplied drawing options.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     * @param opts    The drawing options
     *
     * @attribute suffix  record_with_options
     */
    void fill_rectangle(color clr, const rectangle &rect, const drawing_options &opts);

    /**
     * Fill a rectangle onto the current window.
     *
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     *
     * @attribute suffix  record
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
     *
     * @attribute suffix  with_options
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
     *
     * @attribute suffix  with_options
     */
    void fill_quad(color clr, const quad &q, const drawing_options &opts);
    
    /**
     * Fills a rectangle on the supplied window, using the supplied drawing options.
     *
     * @param destination   The destination window
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the window/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the window/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     * @param opts    The drawing options
     *
     * @attribute class   window
     * @attribute suffix  with_options
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_window(window destination, color clr, double x, double y, double width, double height, const drawing_options &opts);
    
    /**
     * Fills a rectangle on the supplied window to the current window.
     *
     * @param destination   The destination window
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the window/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the window/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     *
     * @attribute class   window
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_window(window destination, color clr, double x, double y, double width, double height);
    
    /**
     * Fills a rectangle on the supplied window using the supplied drawing options.
     *
     * @param destination   The destination window
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     * @param opts    The drawing options
     *
     * @attribute class   window
     * @attribute suffix  record_with_options
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_window(window destination, color clr, const rectangle &rect, const drawing_options &opts);
    
    /**
     * Fill a rectangle on the supplied window onto the current window.
     *
     * @param destination   The destination window
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     *
     * @attribute class   window
     * @attribute suffix  record
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_window(window destination, color clr, const rectangle &rect);
    
    /**
     * Draw a quad on the supplied window to the current window.
     *
     * @param destination   The destination window
     * @param clr   The color for the quad
     * @param q     The details of the quad
     *
     * @attribute class   window
     * @attribute method  draw_quad
     */
    void draw_quad_on_window(window destination, color clr, const quad &q);
    
    /**
     * Draw a quad on the supplied window using the supplied drawing options.
     *
     * @param destination   The destination window
     * @param clr   The color for the quad
     * @param q     The details of the quad
     * @param opts  The drawing options
     *
     * @attribute class   window
     * @attribute suffix  with_options
     * @attribute method  draw_quad
     */
    void draw_quad_on_window(window destination, color clr, const quad &q, const drawing_options &opts);
    
    /**
     * Fill a quad on the supplied window on the current window.
     *
     * @param destination   The destination window
     * @param clr   The color for the quad
     * @param q     The details of the quad
     *
     * @attribute class   window
     * @attribute method  fill_quad
     */
    void fill_quad_on_window(window destination, color clr, const quad &q);
    
    /**
     * Fill a quad on the supplied window using the supplied drawing options.
     *
     * @param destination   The destination window
     * @param clr The color for the quad
     * @param q   The details of the quad
     * @param opts  The drawing options
     *
     * @attribute class   window
     * @attribute suffix  with_options
     */
    void fill_quad_on_window(window destination, color clr, const quad &q, const drawing_options &opts);
    
    /**
     *  Draw a rectangle to the window using the supplied drawing options. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination window
     * @param clr    The color of the rectangle
     * @param x      The x location of the rectangle
     * @param y      The y location of the rectangle
     * @param width  The width of the rectangle
     * @param height The height of the rectangle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     * @attribute class     window
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts);

    /**
     *  Draw a rectangle to the window using. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination window
     * @param clr    The color of the rectangle
     * @param x      The x location of the rectangle
     * @param y      The y location of the rectangle
     * @param width  The width of the rectangle
     * @param height The height of the rectangle
     *
     * @attribute class     window
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_window(window destination, color clr, double x, double y, double width, double height);

    /**
     *  Draw a rectangle to the window using the supplied rect and drawing options. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination window
     * @param clr    The color of the rectangle
     * @param rect   the rectangle to be drawn to the window
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    record_with_options
     * @attribute class     window
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_window(window destination, color clr, const rectangle &rect, const drawing_options &opts);

    /**
     *  Draw a rectangle to the window using the supplied rect. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination window
     * @param clr    The color of the rectangle
     * @param rect   the rectangle to be drawn to the window
     *
     * @attribute suffix    record
     * @attribute class     window
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_window(window destination, color clr, const rectangle &rect);
    
    /**
     * Fills a rectangle on the supplied bitmap, using the supplied drawing options.
     *
     * @param destination   The destination bitmap
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the bitmap/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the bitmap/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     * @param opts    The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  with_options
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, const drawing_options &opts);
    
    /**
     * Fills a rectangle on the supplied bitmap to the current bitmap.
     *
     * @param destination   The destination bitmap
     * @param clr     The color of the rectangle
     * @param x       The distance from the left of the bitmap/bitmap to the
     *                rectangle
     * @param y       The distance from the top of the bitmap/bitmap to the
     *                rectangle
     * @param width   The width of the rectangle
     * @param height  The height of the rectangle
     *
     * @attribute class   bitmap
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
    
    /**
     * Fills a rectangle on the supplied bitmap using the supplied drawing options.
     *
     * @param destination   The destination bitmap
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     * @param opts    The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  record_with_options
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect, const drawing_options &opts);
    
    /**
     * Fill a rectangle on the supplied bitmap onto the current bitmap.
     *
     * @param destination   The destination bitmap
     * @param clr     The color of the rectangle
     * @param rect    The rectangle to draw
     *
     * @attribute class   bitmap
     * @attribute suffix  record
     * @attribute method  fill_rectangle
     */
    void fill_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect);
    
    /**
     * Draw a quad on the supplied bitmap to the current bitmap.
     *
     * @param destination   The destination bitmap
     * @param clr   The color for the quad
     * @param q     The details of the quad
     *
     * @attribute class   bitmap
     * @attribute method  draw_quad
     */
    void draw_quad_on_bitmap(bitmap destination, color clr, const quad &q);
    
    /**
     * Draw a quad on the supplied bitmap using the supplied drawing options.
     *
     * @param destination   The destination bitmap
     * @param clr   The color for the quad
     * @param q     The details of the quad
     * @param opts  The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  with_options
     * @attribute method  draw_quad
     */
    void draw_quad_on_bitmap(bitmap destination, color clr, const quad &q, const drawing_options &opts);
    
    /**
     * Fill a quad on the supplied bitmap on the current bitmap.
     *
     * @param destination   The destination bitmap
     * @param clr   The color for the quad
     * @param q     The details of the quad
     *
     * @attribute class   bitmap
     * @attribute method  fill_quad
     */
    void fill_quad_on_bitmap(bitmap destination, color clr, const quad &q);
    
    /**
     * Fill a quad on the supplied bitmap using the supplied drawing options.
     *
     * @param destination   The destination bitmap
     * @param clr The color for the quad
     * @param q   The details of the quad
     * @param opts  The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  with_options
     * @attribute method  fill_quad
     */
    void fill_quad_on_bitmap(bitmap destination, color clr, const quad &q, const drawing_options &opts);
    
    /**
     *  Draw a rectangle to the bitmap using the supplied drawing options. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the rectangle
     * @param x      The x location of the rectangle
     * @param y      The y location of the rectangle
     * @param width  The width of the rectangle
     * @param height The height of the rectangle
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    with_options
     * @attribute class     bitmap
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts);
    
    /**
     *  Draw a rectangle to the bitmap using. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the rectangle
     * @param x      The x location of the rectangle
     * @param y      The y location of the rectangle
     * @param width  The width of the rectangle
     * @param height The height of the rectangle
     *
     * @attribute class     bitmap
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
    
    /**
     *  Draw a rectangle to the bitmap using the supplied rect and drawing options. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the rectangle
     * @param rect   the rectangle to be drawn to the bitmap
     * @param opts   Drawing options to configure the drawing operation
     *
     * @attribute suffix    record_with_options
     * @attribute class     bitmap
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect, const drawing_options &opts);
    
    /**
     *  Draw a rectangle to the bitmap using the supplied rect. The rectangle is centred on its x, y
     *  coordinates, and has the provided width and height.
     *
     * @param destination   The destination bitmap
     * @param clr    The color of the rectangle
     * @param rect   the rectangle to be drawn to the bitmap
     *
     * @attribute suffix    record
     * @attribute class     bitmap
     * @attribute method    draw_rectangle
     */
    void draw_rectangle_on_bitmap(bitmap destination, color clr, const rectangle &rect);
    
}
#endif /* rectangle_drawing_hpp */
