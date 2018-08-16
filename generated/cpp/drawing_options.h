//
// SplashKit Generated Drawing Options C++ Code
// DO NOT MODIFY
//

#ifndef __drawing_options_h
#define __drawing_options_h

#include "window_manager.h"
#include "types.h"
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
drawing_options option_part_bmp(double x, double y, double w, double h);
drawing_options option_part_bmp(double x, double y, double w, double h, drawing_options opts);
drawing_options option_part_bmp(rectangle part);
drawing_options option_part_bmp(rectangle part, drawing_options opts);
drawing_options option_rotate_bmp(double angle);
drawing_options option_rotate_bmp(double angle, double anchor_x, double anchor_y);
drawing_options option_rotate_bmp(double angle, double anchor_x, double anchor_y, drawing_options opts);
drawing_options option_rotate_bmp(double angle, drawing_options opts);
drawing_options option_scale_bmp(double scale_x, double scale_y);
drawing_options option_scale_bmp(double scale_x, double scale_y, drawing_options opts);
drawing_options option_to_screen();
drawing_options option_to_screen(drawing_options opts);
drawing_options option_to_world();
drawing_options option_to_world(drawing_options opts);
drawing_options option_with_animation(animation anim);
drawing_options option_with_animation(animation anim, drawing_options opts);
drawing_options option_with_bitmap_cell(int cell);
drawing_options option_with_bitmap_cell(int cell, drawing_options opts);

#endif /* __drawing_options_h */
