/**
 * @header drawing_options
 * @author Andrew Cain
 * @attribute group graphics
 */

#ifndef drawing_options_hpp
#define drawing_options_hpp

#include "geometry.h"
#include "types.h"
#include "window_manager.h"
#include "animations.h"
namespace splashkit_lib
{
    /**
     * Returns a `drawing_options` with default values.
     * This will draw to the current window, with default scale of 1, no
     * rotation or offset, not flipped, drawing whole images, with default
     * camera mechanisms and line width.
     *
     * @return A default drawing options.
     */
    drawing_options option_defaults();

    /**
     * Use this option to draw to a Bitmap. Pass dest the Bitmap you want to draw on.
     *
     * @param  dest The bitmap to draw to.
     * @return      Drawing options that will draw onto a bitmap.
     *
     * @attribute suffix  bitmap
     */
    drawing_options option_draw_to(bitmap dest);

    /**
     * Use this option to draw to a Bitmap. Pass dest the Bitmap you want to draw on.
     * Pass opts the other options you want use.
     *
     * @param  dest The bitmap to draw to.
     * @param  opts Values for the other options.
     * @return      Drawing options that will draw onto a bitmap.
     *
     * @attribute suffix  bitmap_with_options
     */
    drawing_options option_draw_to(bitmap dest, drawing_options opts);

    /**
     * Use this option to draw to a specified Window. Pass dest the Window you want to draw on.
     *
     * @param  dest The window to draw onto.
     * @return      A drawing option that will draw to the indicated window.
     *
     * @attribute suffix  window
     */
    drawing_options option_draw_to(window dest);

    /**
     * Use this option to draw to a Bitmap. Pass dest the Bitmap you want to draw on to.
     * Pass opts the other options you want use.
     *
     * @param  dest The window to draw onto.
     * @param  opts Values for the other options.
     * @return      A drawing option that will draw to the indicated window.
     *
     * @attribute suffix  window_with_options
     */
    drawing_options option_draw_to(window dest, drawing_options opts);

    /**
     * Use this option to scale the drawing of bitmaps. You can scale x and y separately.
     *
     * @param  scale_x The amount to scale bitmaps aalong the x axis
     * @param  scale_y The amount to scale bitmaps aalong the y axis
     * @return         Options that will scale bitmaps along the x,y axis.
     */
    drawing_options option_scale_bmp(double scale_x, double scale_y);

    /**
     * Use this option to scale the drawing of bitmaps. You can scale x and y separately.
     * Pass opts the other options you want use.
     *
     * @param  scale_x The amount to scale bitmaps aalong the x axis
     * @param  scale_y The amount to scale bitmaps aalong the y axis
     * @param  opts    Values for the other options.
     * @return         Options that will scale bitmaps along the x,y axis.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_scale_bmp(double scale_x, double scale_y, drawing_options opts);

    /**
     * Use this option to rotate the drawing of a bitmap. This allows you to set the
     * anchor point and rotate around that by a number of degrees.
     * Pass opts the other options you want use.
     *
     * @param  angle    The angle to rotate bitmaps.
     * @param  anchor_x The x location of the anchor within the bitmap
     * @param  anchor_y The y location of the anchor within the bitmap
     * @return          Options that will rotate bitmaps around an anchor point.
     *
     * @attribute suffix  with_anchor
     */
    drawing_options option_rotate_bmp(double angle, double anchor_x, double anchor_y);

    /**
     * Use this option to rotate the drawing of a bitmap. This allows you to set the
     * anchor point and rotate around that by a number of degrees.
     * Pass opts the other options you want use.
     *
     * @param  angle    The angle to rotate bitmaps.
     * @param  anchor_x The x location of the anchor within the bitmap
     * @param  anchor_y The y location of the anchor within the bitmap
     * @param  opts     Values for the other options.
     * @return          Options that will rotate bitmaps around an anchor point.
     *
     * @attribute suffix  with_anchor_and_options
     */
    drawing_options option_rotate_bmp(double angle, double anchor_x, double anchor_y, drawing_options opts);

    /**
     * Use this option to rotate a bitmap around its centre point.
     *
     * @param  angle    The angle to rotate bitmaps.
     * @param  opts     Values for the other options.
     * @return          Options that will rotate bitmaps around its center point.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_rotate_bmp(double angle, drawing_options opts);

    /**
     * Use this option to rotate a bitmap around its centre point.
     *
     * @param  angle    The angle to rotate bitmaps.
     * @return          Options that will rotate bitmaps around its center point.
     */
    drawing_options option_rotate_bmp(double angle);

    /**
     * Use this option to flip an image along its X axis.
     *
     * @return Options that will flip bitmaps horizontally.
     */
    drawing_options option_flip_x();

    /**
     * Use this option to flip an image along its X axis.
     *
     * @param  opts     Values for the other options.
     * @return Options that will flip bitmaps horizontally.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_flip_x(drawing_options opts);

    /**
     * Use this option to flip the drawing of an image along its Y axis.
     *
     * @return Options that will flip bitmaps vertically.
     */
    drawing_options option_flip_y();

    /**
     * Use this option to flip the drawing of an image along its Y axis.
     *
     * @param  opts     Values for the other options.
     * @return Options that will flip bitmaps vertically.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_flip_y(drawing_options opts);

    /**
     * Use this option to flip the drawing of an image along both X and Y axis.
     *
     * @return Options that flip bitmap drawing both vertically and
     *         horizontally.
     */
    drawing_options option_flip_xy();

    /**
     * Use this option to flip the drawing of an image along both X and Y axis.
     *
     * @param  opts     Values for the other options.
     * @return Options that flip bitmap drawing both vertically and
     *         horizontally.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_flip_xy(drawing_options opts);

    /**
     * Use this option to draw only a part of a bitmap.
     *
     * @param  x The x coordinate of the part within the bitmap.
     * @param  y The y coordinate of the part within the bitmap.
     * @param  w The width of the part within the bitmap.
     * @param  h The height of the part within the bitmap.
     * @return   Options to draw parts of a bitmap.
     */
    drawing_options option_part_bmp(double x, double y, double w, double h);

    /**
     * Use this option to draw only a part of a bitmap.
     *
     * @param  x The x coordinate of the part within the bitmap.
     * @param  y The y coordinate of the part within the bitmap.
     * @param  w The width of the part within the bitmap.
     * @param  h The height of the part within the bitmap.
     * @param  opts     Values for the other options.
     * @return   Options to draw parts of a bitmap.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_part_bmp(double x, double y, double w, double h, drawing_options opts);

    /**
     * Use this option to draw only part of a bitmap.
     *
     * @param  part The rectangle of the part of the bitmap to draw.
     * @return   Options to draw parts of a bitmap.
     *
     * @attribute suffix  from_rectangle
     */
    drawing_options option_part_bmp(rectangle part);

    /**
     * Use this option to draw only part of a bitmap.
     *
     * @param  part The rectangle of the part of the bitmap to draw.
     * @param  opts     Values for the other options.
     * @return   Options to draw parts of a bitmap.
     *
     * @attribute suffix  from_rectangle_with_options
     */
    drawing_options option_part_bmp(rectangle part, drawing_options opts);

    /**
     * Use this option to draw in World coordinates -- these are affected by
     * the movement of the camera.
     *
     * @return Options that will draw with camera effects.
     */
    drawing_options option_to_world();

    /**
     * Use this option to draw in World coordinates -- these are affected by
     * the movement of the camera.
     *
     * @param  opts     Values for the other options.
     * @return Options that will draw with camera effects.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_to_world(drawing_options opts);

    /**
     * Use this option to draw to the screen, ignoring the positon of the
     * camera.
     *
     * @return Options that will draw to the surface without camera effects.
     */
    drawing_options option_to_screen();

    /**
     * Use this option to draw to the screen, ignoring the positon of the
     * camera.
     *
     * @param  opts     Values for the other options.
     * @return Options that will draw to the surface without camera effects.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_to_screen(drawing_options opts);

    /**
     * Use this option to change the width of line drawings.
     *
     * @param  width The new line width for line drawing.
     * @return       Options to draw lines with the indicated width.
     */
    drawing_options option_line_width(int width);

    /**
     * Use this option to change the width of line drawings.
     *
     * @param  width The new line width for line drawing.
     * @param  opts     Values for the other options.
     * @return       Options to draw lines with the indicated width.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_line_width(int width, drawing_options opts);

    /**
     * Use details from the animation to select an appropriate cell from the
     * bitmaps being drawn.
     *
     * @param  anim The animation with the cell details to be used.
     * @return      A drawing option that will draw the current cell from the
     *              animation.
     */
    drawing_options option_with_animation(animation anim);

    /**
     * Use details from the animation to select an appropriate cell from the
     * bitmaps being drawn. This extends the passed in drawing options with
     * the animation details.
     *
     * @param  anim The animation with the cell details to be used.
     * @param  opts The existing options to extend.
     * @return      A drawing option that will draw the current cell from the
     *              animation.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_with_animation(animation anim, drawing_options opts);
    
    /**
     * When drawing the bitmap this will only draw the cell. To use this the bitmap
     * needs to have been provided with its cell details (see `bitmap_set_cell_details`).
     * This option overrides the animation or part drawing options. This extends
     * the passed in drawing options with the cell details.
     *
     * @param  cell The cell to draw from the bitmap (-1 for entire bitmap)
     * @param  opts The existing options to extend.
     * @return      A drawing option that will draw the selected cell.
     *
     * @attribute suffix  with_options
     */
    drawing_options option_with_bitmap_cell(int cell, drawing_options opts);
    
    /**
     * When drawing the bitmap this will only draw the cell. To use this the bitmap
     * needs to have been provided with its cell details (see `bitmap_set_cell_details`).
     * This option overrides the animation or part drawing options.
     *
     * @param  cell The cell to draw from the bitmap (-1 for entire bitmap)
     * @return      A drawing option that will draw the selected cell.
     */
    drawing_options option_with_bitmap_cell(int cell);

}
#endif /* drawing_options_hpp */
