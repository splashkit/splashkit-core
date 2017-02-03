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
    void draw_pixel(color clr, double x, double y);

    /**
     * Draws an individual pixel with the supplied options.
     *
     * @param clr The color of the pixel
     * @param x   The distance from the left edge of the window/bitmap to the
     *            pixel
     * @param y   The distance from the top edge of the window/bitmap to the
     *            pixel
     * @param opts The drawing options
     *
     * @attribute suffix  with_options
     */
    void draw_pixel(color clr, double x, double y, drawing_options opts);

    /**
     * Draws an individual pixel to the current window.
     *
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     *
     * @attribute suffix  at_point
     */
    void draw_pixel(color clr, const point_2d &pt);

    /**
     * Draws an individual pixel with the supplied options.
     *
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     * @param opts The drawing options
     *
     * @attribute suffix  at_point_with_options
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
     *
     * @attribute suffix  from_bitmap
     */
    color get_pixel(bitmap bmp, double x, double y);

    /**
     * Returns the color of the pixel at the location on the supplied
     * bitmap.
     *
     * @param  bmp The bitmap to get the color from
     * @param  pt  The position of the pixel
     * @return     The color of the pixel at the supplied location
     *
     * @attribute suffix  from_bitmap_at_point
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
     *
     * @attribute suffix  from_window
     */
    color get_pixel(window wnd, double x, double y);

    /**
     * Returns the color of the pixel at the location on the supplied
     * window.
     *
     * @param  wnd The window to get the color from
     * @param  pt  The position of the pixel
     * @return     The color of the pixel at the supplied location
     *
     * @attribute suffix  from_window_at_point
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
    color get_pixel(double x, double y);

    /**
     * Returns the color of the pixel at the x,y location on the current
     * window.
     *
     * @param  pt  The position of the pixel
     * @return     The color of the pixel at the supplied location
     *
     * @attribute suffix  at_point
     */
    color get_pixel(const point_2d &pt);
    
    /**
     * Draws an individual pixel to the given window.
     *
     * @param destination the window to draw the pixel on
     * @param clr The color of the pixel
     * @param x   The distance from the left edge of the window to the
     *            pixel
     * @param y   The distance from the top edge of the window to the
     *            pixel
     *
     * @attribute class  window
     */
    void draw_pixel_on_window(window destination, color clr, double x, double y);
    
    /**
     * Draws an individual pixel to the given window with the given drawing options.
     *
     * @param destination The window to draw the pixel on
     * @param clr The color of the pixel
     * @param x   The distance from the left edge of the window to the
     *            pixel
     * @param y   The distance from the top edge of the window to the
     *            pixel
     * @param opts The drawing options
     *
     * @attribute class  window
     * @attribute suffix  with_options
     */
    void draw_pixel_on_window(window destination, color clr, double x, double y, drawing_options opts);
    
    /**
     * Draws an individual pixel to the given window.
     *
     * @param destination The window to draw the pixel on
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     *
     * @attribute class  window
     * @attribute suffix  at_point
     */
    void draw_pixel_on_window(window destination, color clr, const point_2d &pt);
    
    /**
     * Draws an individual pixel to the given window with the given drawing options.
     *
     * @param destination The window to draw the pixel on
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     * @param opts The drawing options
     *
     * @attribute class  window
     * @attribute suffix  at_point_with_options
     */
    void draw_pixel_on_window(window destination, color clr, const point_2d &pt, drawing_options opts);
    
    /**
     * Returns the color of the pixel at the x,y location on the given
     * window.
     *
     * @param destination The window to draw the pixel on
     * @param  x   The distance from the left edge of the window to the pixel
     *             to read
     * @param  y   The distance from the top of the window to the pixel to read
     * @return     The color of the pixel at the supplied location
     *
     * @attribute class  window
     * @attribute suffix  from_window
     */
    color get_pixel_from_window(window destination, double x, double y);
    
    /**
     * Returns the color of the pixel at the x,y location on the given
     * window.
     *
     * @param destination The window to draw the pixel on
     * @param  pt  The position of the pixel
     * @return     The color of the pixel at the supplied location
     *
     * @attribute suffix  at_point_from_window
     */
    color get_pixel_from_window(window destination, const point_2d &pt);
    
    /**
     * Draws an individual pixel to the given bitmap.
     *
     * @param destination the bitmap to draw the pixel on
     * @param clr The color of the pixel
     * @param x   The distance from the left edge of the bitmap to the
     *            pixel
     * @param y   The distance from the top edge of the bitmap to the
     *            pixel
     *
     * @attribute class  bitmap
     * @attribute method  draw_pixel
     */
    void draw_pixel_on_bitmap(bitmap destination, color clr, double x, double y);
    
    /**
     * Draws an individual pixel to the given bitmap with the given drawing options.
     *
     * @param destination the bitmap to draw the pixel on
     * @param clr The color of the pixel
     * @param x   The distance from the left edge of the bitmap to the
     *            pixel
     * @param y   The distance from the top edge of the bitmap to the
     *            pixel
     * @param opts The drawing options
     *
     * @attribute class  bitmap
     * @attribute suffix  with_options
     * @attribute method  draw_pixel
     */
    void draw_pixel_on_bitmap(bitmap destination, color clr, double x, double y, drawing_options opts);
    
    /**
     * Draws an individual pixel to the given bitmap.
     *
     * @param destination the bitmap to draw the pixel on
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     *
     * @attribute class  bitmap
     * @attribute suffix  at_point
     * @attribute method  draw_pixel
     */
    void draw_pixel_on_bitmap(bitmap destination, color clr, const point_2d &pt);
    
    /**
     * Draws an individual pixel to the given bitmap with the given drawing options.
     *
     * @param destination the bitmap to draw the pixel on
     * @param clr The color of the pixel
     * @param pt  The location of the pixel to draw
     * @param opts The drawing options
     *
     * @attribute class  bitmap
     * @attribute suffix  at_point_with_options
     * @attribute method  draw_pixel
     */
    void draw_pixel_on_bitmap(bitmap destination, color clr, const point_2d &pt, drawing_options opts);
}
#endif /* point_drawing_h */
