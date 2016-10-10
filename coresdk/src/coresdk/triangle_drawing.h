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
     */
    void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3, drawing_options opts);

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
    void draw_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3);

    /**
     * Draw a triangle using the supplied drawing options.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     */
    void draw_triangle(color clr, const triangle &tri, drawing_options opts);

    /**
     * Draw a triangle onto the current window.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
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
     */
    void fill_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3, drawing_options opts);

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
    void fill_triangle(color clr, float x1, float y1, float x2, float y2, float x3, float y3);

    /**
     * Fill a triangle using the supplied drawing options.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     * @param opts The drawing options
     */
    void fill_triangle(color clr, const triangle &tri, drawing_options opts);

    /**
     * Draw a triangle onto the current window.
     *
     * @param clr  The color for the triangle
     * @param tri  The triangles details
     */
    void fill_triangle(color clr, const triangle &tri);
}
#endif /* triangle_drawing_hpp */
