/**
 * @header ellipse_drawing
 * @author Andrew Cain
 * @attribute group graphics
 */

#ifndef ellipse_drawing_h
#define ellipse_drawing_h

#include "color.h"
#include "drawing_options.h"
#include "geometry.h"
namespace splashkit_lib
{
    /**
     * Draws an ellipse using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     * @param opts   The drawing options
     *
     * @attribute suffix  with_options
     */
    void draw_ellipse(color clr, double x, double y, double width, double height, drawing_options opts);

    /**
     * Draws an ellipse using the provided location, and size.
     *
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     */
    void draw_ellipse(color clr, double x, double y, double width, double height);

    /**
     * Draws an ellipse using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     *
     * @attribute suffix  within_rectangle_with_options
     */
    void draw_ellipse(color clr, const rectangle rect, drawing_options opts);

    /**
     * Draws an ellipse using the provided location, and size.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     *
     * @attribute suffix  within_rectangle
     */
    void draw_ellipse(color clr, const rectangle rect);

    /**
     * Fills an ellipse using the provided location, size, and drawing options.
     *
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     * @param opts   The drawing options
     *
     * @attribute suffix  with_options
     */
    void fill_ellipse(color clr, double x, double y, double width, double height, drawing_options opts);

    /**
     * Fills an ellipse using the provided location, and size.
     *
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     */
    void fill_ellipse(color clr, double x, double y, double width, double height);

    /**
     * Fills an ellipse using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     *
     * @attribute suffix  within_rectangle_with_options
     */
    void fill_ellipse(color clr, const rectangle rect, drawing_options opts);

    /**
     * Fill an ellipse using the provided location, and size.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     *
     * @attribute suffix  within_rectangle
     */
    void fill_ellipse(color clr, const rectangle rect);
    
    /**
     * Draws an ellipse to the window, using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   window
     * @attribute suffix  with_options
     * @attribute method  draw_ellipse
     */
    void draw_ellipse_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts);
    
    /**
     * Draws an ellipse on the given window, using the provided location, and size.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     *
     * @attribute class   window
     * @attribute method  draw_ellipse
     */
    void draw_ellipse_on_window(window destination, color clr, double x, double y, double width, double height);
    
    /**
     * Draws an ellipse on the given window, using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   window
     * @attribute method  draw_ellipse
     * @attribute suffix  within_rectangle_with_options
     */
    void draw_ellipse_on_window(window destination, color clr, const rectangle rect, drawing_options opts);
    
    /**
     * Draws an ellipse on the given window, using the provided location, and size.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     *
     * @attribute class   window
     * @attribute method  draw_ellipse
     * @attribute suffix  within_rectangle
     */
    void draw_ellipse_on_window(window destination, color clr, const rectangle rect);
    
    /**
     * Fills an ellipse on the given window, using the provided location, size, and drawing options.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   window
     * @attribute method  fill_ellipse
     * @attribute suffix  with_options
     */
    void fill_ellipse_on_window(window destination, color clr, double x, double y, double width, double height, drawing_options opts);
    
    /**
     * Fills an ellipse on the given window, using the provided location, and size.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or window to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or window to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     *
     * @attribute class   window
     * @attribute method  fill_ellipse
     */
    void fill_ellipse_on_window(window destination, color clr, double x, double y, double width, double height);
    
    /**
     * Fills an ellipse on the given window, using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   window
     * @attribute method  fill_ellipse
     * @attribute suffix  within_rectangle_with_options
     */
    void fill_ellipse_on_window(window destination, color clr, const rectangle rect, drawing_options opts);
    
    /**
     * Fill an ellipse on the given window, using the provided location, and size.
     *
     * @param destination the window to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     *
     * @attribute class   window
     * @attribute method  fill_ellipse
     * @attribute suffix  within_rectangle
     */
    void fill_ellipse_on_window(window destination, color clr, const rectangle rect);
    
    /**
     * Draws an ellipse to the bitmap, using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or bitmap to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or bitmap to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   bitmap
     * @attribute method  draw_ellipse
     * @attribute suffix  with_options
     */
    void draw_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts);
    
    /**
     * Draws an ellipse on the given bitmap, using the provided location, and size.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or bitmap to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or bitmap to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     *
     * @attribute class   bitmap
     * @attribute method  draw_ellipse
     */
    void draw_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
    
    /**
     * Draws an ellipse on the given bitmap, using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   bitmap
     * @attribute method  draw_ellipse
     * @attribute suffix  within_rectangle_with_options
     */
    void draw_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect, drawing_options opts);
    
    /**
     * Draws an ellipse on the given bitmap, using the provided location, and size.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     *
     * @attribute class   bitmap
     * @attribute method  draw_ellipse
     * @attribute suffix  within_rectangle
     */
    void draw_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect);
    
    /**
     * Fills an ellipse on the given bitmap, using the provided location, size, and drawing options.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or bitmap to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or bitmap to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   bitmap
     * @attribute method  fill_ellipse
     * @attribute suffix  with_options
     */
    void fill_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height, drawing_options opts);
    
    /**
     * Fills an ellipse on the given bitmap, using the provided location, and size.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param x      The distance from the left of the bitmap or bitmap to the
     *               left edge of the ellipse
     * @param y      The distance from the top of the bitmap or bitmap to the
     *               top edge of the ellipse
     * @param width  The width of the ellipse
     * @param height The height of the ellipse
     *
     * @attribute class   bitmap
     * @attribute method  fill_ellipse
     */
    void fill_ellipse_on_bitmap(bitmap destination, color clr, double x, double y, double width, double height);
    
    /**
     * Fills an ellipse on the given bitmap, using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     *
     * @attribute class   bitmap
     * @attribute method  fill_ellipse
     * @attribute suffix  within_rectangle_with_options
     */
    void fill_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect, drawing_options opts);
    
    /**
     * Fill an ellipse on the given bitmap, using the provided location, and size.
     *
     * @param destination the bitmap to draw the ellipse on
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     *
     * @attribute class   bitmap
     * @attribute method  fill_ellipse
     * @attribute suffix  within_rectangle
     */
    void fill_ellipse_on_bitmap(bitmap destination, color clr, const rectangle rect);

}
#endif /* ellipse_drawing_h */
