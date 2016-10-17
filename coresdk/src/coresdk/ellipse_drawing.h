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
     */
    void draw_ellipse(color clr, float x, float y, float width, float height, drawing_options opts);

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
    void draw_ellipse(color clr, float x, float y, float width, float height);

    /**
     * Draws an ellipse using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     */
    void draw_ellipse(color clr, const rectangle rect, drawing_options opts);

    /**
     * Draws an ellipse using the provided location, and size.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
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
     */
    void fill_ellipse(color clr, float x, float y, float width, float height, drawing_options opts);

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
    void fill_ellipse(color clr, float x, float y, float width, float height);

    /**
     * Fills an ellipse using the provided location, size, and drawing options.
     *
     * At this stage ellipse drawing is not affected by line width from the
     * drawing options.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     * @param opts   The drawing options
     */
    void fill_ellipse(color clr, const rectangle rect, drawing_options opts);

    /**
     * Fill an ellipse using the provided location, and size.
     *
     * @param clr    The color of the ellipse
     * @param rect   Indicates the location and size of the ellipse
     */
    void fill_ellipse(color clr, const rectangle rect);
}
#endif /* ellipse_drawing_h */
