//
//  drawing_options.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "drawing_options.h"

#include "window_manager.h"
namespace splashkit_lib
{
    extern window _current_window;

    /// Returns a DrawingOptions with default values.
    drawing_options option_defaults()
    {
        drawing_options result;

        result.dest 			= _current_window;
        result.scale_x 			= 1;
        result.scale_y 			= 1;
        result.angle  			= 0;
        result.anchor_offset_x 	= 0;
        result.anchor_offset_y 	= 0;
        result.flip_x 			= false;
        result.flip_y 			= false;
        result.is_part 			= false;
        result.part 			= rectangle_from(0,0,1,1);
        result.camera	 		= DRAW_DEFAULT;
        result.line_width 		= 1;
        result.anim             = nullptr;
        result.draw_cell        = -1;

        return result;
    }

    drawing_options option_draw_to(bitmap dest)
    {
        return option_draw_to(dest, option_defaults());
    }

    drawing_options option_draw_to(bitmap dest, drawing_options opts)
    {
        opts.dest = dest;
        return opts;
    }

    drawing_options option_draw_to(window dest)
    {
        return option_draw_to(dest, option_defaults());
    }

    drawing_options option_draw_to(window dest, drawing_options opts)
    {
        opts.dest = dest;
        return opts;
    }

    drawing_options option_scale_bmp(double scale_x, double scale_y)
    {
        return option_scale_bmp(scale_x, scale_y, option_defaults());
    }

    drawing_options option_scale_bmp(double scale_x, double scale_y, drawing_options opts)
    {
        opts.scale_x = scale_x;
        opts.scale_y = scale_y;
        return opts;
    }

    drawing_options option_rotate_bmp(double angle, double anchor_x, double anchor_y)
    {
        return option_rotate_bmp(angle, anchor_x, anchor_y, option_defaults());
    }

    drawing_options option_rotate_bmp(double angle, double anchor_x, double anchor_y, drawing_options opts)
    {
        opts.angle += angle;
        opts.anchor_offset_x += anchor_x;
        opts.anchor_offset_y += anchor_y;
        return opts;
    }

    drawing_options option_rotate_bmp(double angle, drawing_options opts)
    {
        return option_rotate_bmp(angle, 0, 0, opts);
    }

    drawing_options option_rotate_bmp(double angle)
    {
        return option_rotate_bmp(angle, 0, 0, option_defaults());
    }

    drawing_options option_flip_x()
    {
        return option_flip_x(option_defaults());
    }

    drawing_options option_flip_x(drawing_options opts)
    {
        opts.flip_x = not opts.flip_x;
        return opts;
    }

    drawing_options option_flip_y()
    {
        return option_flip_y(option_defaults());
    }

    drawing_options option_flip_y(drawing_options opts)
    {
        opts.flip_y = not opts.flip_y;
        return opts;
    }

    drawing_options option_flip_xy()
    {
        return option_flip_xy(option_defaults());
    }

    drawing_options option_flip_xy(drawing_options opts)
    {
        opts.flip_x = not opts.flip_x;
        opts.flip_y = not opts.flip_y;
        return opts;
    }

    drawing_options option_part_bmp(double x, double y, double w, double h)
    {
        return option_part_bmp(rectangle_from(x, y, w, h), option_defaults());
    }

    drawing_options option_part_bmp(double x, double y, double w, double h, drawing_options opts)
    {
        return option_part_bmp(rectangle_from(x, y, w, h), opts);
    }

    drawing_options option_part_bmp(rectangle part)
    {
        return option_part_bmp(part, option_defaults());
    }

    drawing_options option_part_bmp(rectangle part, drawing_options opts)
    {
        opts.is_part = true;
        opts.part = part;
        return opts;
    }

    drawing_options option_to_world()
    {
        return option_to_world(option_defaults());
    }

    drawing_options option_to_world(drawing_options opts)
    {
        opts.camera = DRAW_TO_WORLD;
        return opts;
    }

    drawing_options option_to_screen()
    {
        return option_to_screen(option_defaults());
    }
    
    drawing_options option_to_screen(drawing_options opts)
    {
        opts.camera = DRAW_TO_SCREEN;
        return opts;
    }
    
    drawing_options option_line_width(int width)
    {
        return option_line_width(width, option_defaults());
    }
    
    drawing_options option_line_width(int width, drawing_options opts)
    {
        opts.line_width = width;
        return opts;
    }
    
    drawing_options option_with_animation(animation anim)
    {
        return option_with_animation(anim, option_defaults());
    }
    
    drawing_options option_with_animation(animation anim, drawing_options opts)
    {
        opts.anim = anim;
        return opts;
    }
    
    drawing_options option_with_bitmap_cell(int cell, drawing_options opts)
    {
        opts.draw_cell = cell;
        return opts;
    }
    
    drawing_options option_with_bitmap_cell(int cell)
    {
        return option_with_bitmap_cell(cell, option_defaults());
    }
}
