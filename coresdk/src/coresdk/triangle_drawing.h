/**
 * @header triangle_drawing
 * @author Andrew Cain
 * @attribute group graphics
 */

#ifndef triangle_drawing_h
#define triangle_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"

namespace splashkit_lib
{
    /**
     * Draw a triangle using the supplied drawing options.
     *
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap/window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap/window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap/window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap/window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap/window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap/window to the
     *             third point of the triangle
     * @param opts The drawing options
     *
     * @attribute suffix  with_options
     */
    void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

    /**
     * Draw a triangle to the current window.
     *
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the window to the
     *             third point of the triangle
     */
    void draw_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3);

    /**
     * Draw a triangle using the supplied drawing options.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     *
     * @attribute suffix  record_with_options
     */
    void draw_triangle(color clr, const triangle &tri, drawing_options opts);

    /**
     * Draw a triangle onto the current window.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     *
     * @attribute suffix  record
     */
    void draw_triangle(color clr, const triangle &tri);

    /**
     * Fills a triangle using the supplied drawing options.
     *
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap/window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap/window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap/window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap/window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap/window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap/window to the
     *             third point of the triangle
     * @param opts The drawing options
     *
     * @attribute suffix  with_options
     */
    void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

    /**
     * Fills a triangle on the current window.
     *
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the window to the
     *             third point of the triangle
     */
    void fill_triangle(color clr, double x1, double y1, double x2, double y2, double x3, double y3);

    /**
     * Fill a triangle using the supplied drawing options.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     *
     * @attribute suffix  record_with_options
     */
    void fill_triangle(color clr, const triangle &tri, drawing_options opts);

    /**
     * Draw a triangle onto the current window.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     *
     * @attribute suffix  record
     */
    void fill_triangle(color clr, const triangle &tri);

    /**
     * Draw a triangle to the given window, using the supplied drawing options.
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap/window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap/window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap/window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap/window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap/window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap/window to the
     *             third point of the triangle
     * @param opts The drawing options
     *
     *
     * @attribute class   window
     * @attribute suffix  with_options
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

    /**
     * Draw a triangle to the given window.
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the window to the
     *             third point of the triangle
     *
     * @attribute class   window
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);

    /**
     * Draw a triangle on a given window, using the supplied drawing options.
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     *
     * @attribute class   window
     * @attribute suffix  record_with_options
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts);

    /**
     * Draw a triangle on a given window, using the supplied drawing options.
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     *
     * @attribute class   window
     * @attribute suffix  record
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_window(window destination, color clr, const triangle &tri);

    /**
     * Fill a triangle on a given window, using the supplied drawing options.
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap/window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap/window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap/window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap/window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap/window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap/window to the
     *             third point of the triangle
     * @param opts The drawing options
     *
     * @attribute class   window
     * @attribute suffix  with_options
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

    /**
     * Fill a triangle on a given window
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the window to the
     *             first point of the triangle
     * @param y1   The distance from the top of the window to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the window to the
     *             second point of the triangle
     * @param y2   The distance from the top of the window to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the window to the
     *             third point of the triangle
     * @param y3   The distance from the top of the window to the
     *             third point of the triangle
     *
     * @attribute class   window
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_window(window destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);

    /**
     * Fill a triangle on a given window, using given drawing options
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     *
     * @attribute class   window
     * @attribute suffix  record_with_options
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_window(window destination, color clr, const triangle &tri, drawing_options opts);

    /**
     * Fill a triangle on a given window
     *
     * @param destination The window which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     *
     * @attribute class   window
     * @attribute suffix  record
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_window(window destination, color clr, const triangle &tri);

    /**
     * Draw a triangle to the given bitmap, using the supplied drawing options.
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap/bitmap to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap/bitmap to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap/bitmap to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap/bitmap to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap/bitmap to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap/bitmap to the
     *             third point of the triangle
     * @param opts The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  with_options
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

    /**
     * Draw a triangle to the given bitmap.
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap to the
     *             third point of the triangle
     *
     * @attribute class   bitmap
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);

    /**
     * Draw a triangle on a given bitmap, using the supplied drawing options.
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  record_with_options
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts);

    /**
     * Draw a triangle on a given bitmap, using the supplied drawing options.
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     *
     * @attribute class   bitmap
     * @attribute suffix  record
     * @attribute method  draw_triangle
     */
    void draw_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri);

    /**
     * Fill a triangle on a given bitmap, using the supplied drawing options.
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap/bitmap to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap/bitmap to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap/bitmap to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap/bitmap to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap/bitmap to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap/bitmap to the
     *             third point of the triangle
     * @param opts The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  with_options
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3, drawing_options opts);

    /**
     * Fill a triangle on a given bitmap
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param x1   The distance from the left side of the bitmap to the
     *             first point of the triangle
     * @param y1   The distance from the top of the bitmap to the
     *             first point of the triangle
     * @param x2   The distance from the left side of the bitmap to the
     *             second point of the triangle
     * @param y2   The distance from the top of the bitmap to the
     *             second point of the triangle
     * @param x3   The distance from the left side of the bitmap to the
     *             third point of the triangle
     * @param y3   The distance from the top of the bitmap to the
     *             third point of the triangle
     *
     * @attribute class   bitmap
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_bitmap(bitmap destination, color clr, double x1, double y1, double x2, double y2, double x3, double y3);

    /**
     * Fill a triangle on a given bitmap, using given drawing options
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     *
     * @attribute class   bitmap
     * @attribute suffix  record_with_options
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri, drawing_options opts);

    /**
     * Fill a triangle on a given bitmap
     *
     * @param destination The bitmap which the triangle will be drawn on.
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     *
     * @attribute class   bitmap
     * @attribute suffix  record
     * @attribute method  fill_triangle
     */
    void fill_triangle_on_bitmap(bitmap destination, color clr, const triangle &tri);

}
#endif /* triangle_drawing_hpp */
