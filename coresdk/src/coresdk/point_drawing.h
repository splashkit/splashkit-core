/**
 * @header point_drawing
 * @author Andrew Cain
 * @attribute group graphics
 */

#ifndef point_drawing_h
#define point_drawing_h

#include "drawing_options.h"
#include "color.h"
namespace splashkit_lib
{
    /**
     * Draws an individual pixel to the current window.
     *
     * @param clr The color of the pixel
     * @param x   The distance from the left edge of the window to the
     *            pixel
     * @param y   The distance from the top edge of the window to the
     *            pixel
     */
    void draw_pixel(color clr, float x, float y);

    /**
     * Draws an individual pixel with the supplied options.
     *
     * @param clr The color of the pixel
     * @param x   The distance from the left edge of the window/bitmap to the
     *            pixel
     * @param y   The distance from the top edge of the window/bitmap to the
     *            pixel
     * @param opts The drawing options
     */
    void draw_pixel(color clr, float x, float y, drawing_options opts);

    /**
     * Draws an individual pixel to the current window.
     *
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     */
    void draw_pixel(color clr, const point_2d &pt);

    /**
     * Draws an individual pixel with the supplied options.
     *
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     * @param opts The drawing options
     */
    void draw_pixel(color clr, const point_2d &pt, drawing_options opts);

    /**
     * Returns the color of the pixel at the x,y location on the supplied
     * bitmap.
     *
     * @param  bmp The bitmap to get the color from
     * @param  x   The distance from the left edge of the bitmap to the pixel
     *             to read
     * @param  y   The distance from the top of the bitmap to the pixel to read
     * @return     The color of the pixel at the supplied location
     */
    color get_pixel(bitmap bmp, float x, float y);

    /**
     * Returns the color of the pixel at the location on the supplied
     * bitmap.
     *
     * @param  bmp The bitmap to get the color from
     * @param  pt  The position of the pixel
     * @return     The color of the pixel at the supplied location
     */
    color get_pixel(bitmap bmp, const point_2d &pt);

    /**
     * Returns the color of the pixel at the x,y location on the supplied
     * window.
     *
     * @param  wnd The window to get the color from
     * @param  x   The distance from the left edge of the window to the pixel
     *             to read
     * @param  y   The distance from the top of the window to the pixel to read
     * @return     The color of the pixel at the supplied location
     */
    color get_pixel(window wnd, float x, float y);

    /**
     * Returns the color of the pixel at the location on the supplied
     * window.
     *
     * @param  wnd The window to get the color from
     * @param  pt  The position of the pixel
     * @return     The color of the pixel at the supplied location
     */
    color get_pixel(window wnd, const point_2d &pt);

    /**
     * Returns the color of the pixel at the x,y location on the current
     * window.
     *
     * @param  x   The distance from the left edge of the window to the pixel
     *             to read
     * @param  y   The distance from the top of the window to the pixel to read
     * @return     The color of the pixel at the supplied location
     */
    color get_pixel(float x, float y);

    /**
     * Returns the color of the pixel at the x,y location on the current
     * window.
     *
     * @param  pt  The position of the pixel
     * @return     The color of the pixel at the supplied location
     */
    color get_pixel(const point_2d &pt);
}
#endif /* point_drawing_h */
