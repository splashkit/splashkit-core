//
// SplashKit Generated Drawing Options C++ Code
// DO NOT MODIFY
//

#ifndef __drawing_options_h
#define __drawing_options_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

drawing_options option_defaults();
drawing_options option_draw_to(bitmap dest);
drawing_options option_draw_to(bitmap dest, drawing_options opts);
drawing_options option_draw_to(window dest);
drawing_options option_draw_to(window dest, drawing_options opts);
drawing_options option_flip_x();
drawing_options option_flip_x(drawing_options opts);
drawing_options option_flip_xy();
drawing_options option_flip_xy(drawing_options opts);
drawing_options option_flip_y();
drawing_options option_flip_y(drawing_options opts);
drawing_options option_line_width(int width);
drawing_options option_line_width(int width, drawing_options opts);
drawing_options option_part_bmp(float x, float y, float w, float h);
drawing_options option_part_bmp(float x, float y, float w, float h, drawing_options opts);
drawing_options option_part_bmp(rectangle part);
drawing_options option_part_bmp(rectangle part, drawing_options opts);
drawing_options option_rotate_bmp(float angle);
drawing_options option_rotate_bmp(float angle, drawing_options opts);
drawing_options option_rotate_bmp(float angle, float anchor_x, float anchor_y);
drawing_options option_rotate_bmp(float angle, float anchor_x, float anchor_y, drawing_options opts);
drawing_options option_scale_bmp(float scale_x, float scale_y);
drawing_options option_scale_bmp(float scale_x, float scale_y, drawing_options opts);
drawing_options option_to_screen();
drawing_options option_to_screen(drawing_options opts);
drawing_options option_to_world();
drawing_options option_to_world(drawing_options opts);
drawing_options option_with_animation(animation anim);
drawing_options option_with_animation(animation anim, drawing_options opts);

#endif /* __drawing_options_h */
