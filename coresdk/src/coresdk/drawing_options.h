//
//  drawing_options.hpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef drawing_options_hpp
#define drawing_options_hpp

#include "geometry.h"
#include "types.h"
#include "window_manager.h"
#include "animations.h"

/// Returns a DrawingOptions with default values.
drawing_options option_defaults();

/// Use this option to draw to a Bitmap. Pass dest the Bitmap you want to draw on.
///
/// @lib OptionDrawToBitmap
drawing_options option_draw_to(bitmap dest);

/// Use this option to draw to a Bitmap. Pass dest the Bitmap you want to draw on.
/// Pass opts the other options you want use.
///
drawing_options option_draw_to(bitmap dest, drawing_options opts);

/// Use this option to draw to a specified Window. Pass dest the Window you want to draw on.
///
drawing_options option_draw_to(window dest);

/// Use this option to draw to a Bitmap. Pass dest the Bitmap you want to draw on to.
/// Pass opts the other options you want use.
///
drawing_options option_draw_to(window dest, drawing_options opts);


/// Use this option to scale the drawing of bitmaps. You can scale x and y separately.
///
drawing_options option_scale_bmp(float scale_x, float scale_y);

/// Use this option to scale the drawing of bitmaps. You can scale x and y separately.
/// Pass opts the other options you want use.
///
drawing_options option_scale_bmp(float scale_x, float scale_y, drawing_options opts);

/// Use this option to rotate the drawing of a bitmap. This allows you to set the
/// anchor point and rotate around that by a number of degrees.
///
drawing_options option_rotate_bmp(float angle, float anchor_x, float anchor_y);

/// Use this option to rotate the drawing of a bitmap. This allows you to set the
/// anchor point and rotate around that by a number of degrees.
/// Pass opts the other options you want use.
///
drawing_options option_rotate_bmp(float angle, float anchor_x, float anchor_y, drawing_options opts);

/// Use this option to rotate a bitmap around its centre point.
///
drawing_options option_rotate_bmp(float angle, drawing_options opts);

/// Use this option to rotate a bitmap around its centre point.
/// Pass opts the other options you want use.
///
/// @lib OptionRotateBmpAngle
drawing_options option_rotate_bmp(float angle);

/// Use this option to flip an image along its X axis.
///
/// @lib
drawing_options option_flip_x();

/// Use this option to flip an image along its X axis.
/// Pass opts the other options you want use.
///
drawing_options option_flip_x(drawing_options opts);

/// Use this option to flip the drawing of an image along its Y axis.
///
/// @lib
drawing_options option_flip_y();

/// Use this option to flip the drawing of an image along its Y axis.
/// Pass opts the other options you want use.
///
/// @lib OptionFlipYOpts
drawing_options option_flip_y(drawing_options opts);

/// Use this option to flow the drawing of an image along both X and Y axis.
///
/// @lib
drawing_options option_flip_xy();

/// Use this option to flow the drawing of an image along both X and Y axis.
/// Pass opts the other options you want use.
///
drawing_options option_flip_xy(drawing_options opts);

/// Use this option to draw only a part of a bitmap.
///
drawing_options option_part_bmp(float x, float y, float w, float h);

/// Use this option to draw only a part of a bitmap.
/// Pass opts the other options you want use.
///
drawing_options option_part_bmp(float x, float y, float w, float h, drawing_options opts);

/// Use this option to draw only part of a bitmap.
///
/// @lib OptionPartBmpRect
drawing_options option_part_bmp(rectangle part);

/// Use this option to draw only part of a bitmap.
/// Pass opts the other options you want use.
///
/// @lib OptionPartBmpRectOpts
drawing_options option_part_bmp(rectangle part, drawing_options opts);

/// Use this option to draw in World coordinates -- these are affected by the movement of the camera.
///
drawing_options option_to_world();

/// Use this option to draw in World coordinates -- these are affected by the movement of the camera.
/// Pass opts the other options you want use.
///
/// @lib OptionToWorldOpts
drawing_options option_to_world(drawing_options opts);

/// Use this option to draw to the screen, ignoring the positon of the camera.
///
drawing_options option_to_screen();

/// Use this option to draw to the screen, ignoring the positon of the camera.
/// Pass opts the other options you want use.
///
drawing_options option_to_screen(drawing_options opts);

/// Use this option to change the width of line drawings.
///
drawing_options option_line_width(int width);

/// Use this option to change the width of line drawings.
///
/// @lib OptionLineWidthOpts
drawing_options option_line_width(int width, drawing_options opts);

drawing_options option_with_animation(animation anim);
drawing_options option_with_animation(animation anim, drawing_options opts);


#endif /* drawing_options_hpp */
