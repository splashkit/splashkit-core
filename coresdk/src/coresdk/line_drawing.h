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
    void draw_line(color clr, double x1, double y1, double x2, double y2);

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
     *
     * @attribute suffix  with_options
     */
    void draw_line(color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);

    /**
     * Draw a line from one point to another on the current window.
     *
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     *
     * @attribute suffix  point_to_point
     */
    void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt);

    /**
     * Draw a line from one point to another on the current window.
     *
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     * @param opts The drawing options
     *
     * @attribute suffix  point_to_point_with_options
     */
    void draw_line(color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);

    /**
     * Draws a line onto the current window.
     *
     * @param clr The color of the line
     * @param l   The line's details
     *
     * @attribute suffix  record
     */
    void draw_line(color clr, const line &l);

    /**
     * Draws a line.
     *
     * @param clr The color of the line
     * @param l   The line's details
     * @param opts The drawing options
     *
     * @attribute suffix  record_with_options
     */
    void draw_line(color clr, const line &l, drawing_options opts);
    
    /**
     * Draw a line from one point to another on the given window.
     *
     * @param destination  The destination bitmap
     * @param clr The color of the line
     * @param x1  The distance from the left of the window/bitmap to the first
     *            point
     * @param y1  The distance from the top of the window/bitmap to the first
     *            point
     * @param x2  The distance from the left of the window/bitmap to the second
     *            point
     * @param y2  The distance from the top of the window/bitmap to the second
     *            point
     *
     * @attribute method  draw_line
     * @attribute class   window
     */
    void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2);
    
    /**
     * Draw a line from one point to another
     *
     * @param destination  The destination bitmap
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
     *
     * @attribute class   window
     * @attribute suffix  with_options
     * @attribute method  draw_line
     */
    void draw_line_on_window(window destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);
    
    /**
     * Draw a line from one point to another on the given window.
     *
     * @param destination  The destination bitmap
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     *
     * @attribute class   window
     * @attribute suffix  point_to_point
     * @attribute method  draw_line
     */
    void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt);
    
    /**
     * Draw a line from one point to another on the given window.
     *
     * @param destination  The destination bitmap
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     * @param opts The drawing options
     *
     * @attribute class   window
     * @attribute suffix  point_to_point_with_options
     * @attribute method  draw_line
     */
    void draw_line_on_window(window destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
    
    /**
     * Draws a line onto the given window.
     *
     * @param destination  The destination bitmap
     * @param clr The color of the line
     * @param l   The line's details
     *
     * @attribute class   window
     * @attribute suffix  record
     * @attribute method  draw_line
     */
    void draw_line_on_window(window destination, color clr, const line &l);
    
    /**
     * Draws a line on the given window.
     *
     * @param destination  The destination bitmap
     * @param clr The color of the line
     * @param l   The line's details
     * @param opts The drawing options
     *
     * @attribute class   window
     * @attribute suffix  record_with_options
     * @attribute method  draw_line
     */
    void draw_line_on_window(window destination, color clr, const line &l, drawing_options opts);
    
    /**
     * Draw a line from one point to another on the given bitmap.
     *
     * @param destination  The destination bitmap
     * @param clr The color of the line
     * @param x1  The distance from the left of the bitmap/bitmap to the first
     *            point
     * @param y1  The distance from the top of the bitmap/bitmap to the first
     *            point
     * @param x2  The distance from the left of the bitmap/bitmap to the second
     *            point
     * @param y2  The distance from the top of the bitmap/bitmap to the second
     *            point
     *
     * @attribute class   bitmap
     * @attribute method  draw_line
     */
    void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2);
    
    /**
     * Draw a line from one point to another
     *
     * @param destination  The destination bitmap
     * @param clr The color of the line
     * @param x1  The distance from the left of the bitmap/bitmap to the first
     *            point
     * @param y1  The distance from the top of the bitmap/bitmap to the first
     *            point
     * @param x2  The distance from the left of the bitmap/bitmap to the second
     *            point
     * @param y2  The distance from the top of the bitmap/bitmap to the second
     *            point
     * @param opts The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  with_options
     * @attribute method  draw_line
     */
    void draw_line_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, const drawing_options &opts);
    
    /**
     * Draw a line from one point to another on the given bitmap.
     *
     * @param destination  The destination bitmap
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     *
     * @attribute class   bitmap
     * @attribute suffix  point_to_point
     * @attribute method  draw_line
     */
    void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt);
    
    /**
     * Draw a line from one point to another on the given bitmap.
     *
     * @param destination  The destination bitmap
     * @param clr       The color of the line
     * @param from_pt   The start of the line
     * @param to_pt     The end of the line
     * @param opts The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  point_to_point_with_options
     * @attribute method  draw_line
     */
    void draw_line_on_bitmap(bitmap destination, color clr, const point_2d &from_pt, const point_2d &to_pt, const drawing_options &opts);
    
    /**
     * Draws a line onto the given bitmap.
     *
     * @param destination  The destination bitmap
     * @param clr The color of the line
     * @param l   The line's details
     *
     * @attribute class   bitmap
     * @attribute suffix  record
     * @attribute method  draw_line
     */
    void draw_line_on_bitmap(bitmap destination, color clr, const line &l);
    
    /**
     * Draws a line on the given bitmap.
     *
     * @param destination  The destination bitmap
     * @param clr The color of the line
     * @param l   The line's details
     * @param opts The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  record_with_options
     * @attribute method  draw_line
     */
    void draw_line_on_bitmap(bitmap destination, color clr, const line &l, drawing_options opts);

}
#endif /* line_drawing_h */
