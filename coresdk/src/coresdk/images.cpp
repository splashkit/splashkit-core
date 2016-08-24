//
//  images.cpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "images.h"

#include "graphics_driver.h"
#include "backend_types.h"
#include "utility_functions.h"
#include "resources.h"

#include "resource_event_notifications.h"

#include <map>
#include <cstdlib>

using namespace std;

static map<string, bitmap> _bitmaps;


void setup_collision_mask(_bitmap_data *bmp)
{
    int *pixels;
    int sz;
    int r, c;

    sz = bmp->image.surface.width * bmp->image.surface.height;
    pixels = (int *) malloc(sizeof(int) * sz);

    sk_to_pixels(&bmp->image.surface, pixels, sz);

    bmp->pixel_mask = (bool *) malloc( sizeof(bool) * sz );

    // WriteLn(bmp^.name);
    for (r = 0; r < bmp->image.surface.height; r++)
    {
        for(c = 0; c < bmp->image.surface.width; c++)
        {
            bmp->pixel_mask[c + r * bmp->image.surface.width] = ((pixels[c + r * bmp->image.surface.width] & 0x000000FF) > 0x0000007F );
            // if b^.nonTransparentPixels[c, r] then Write(1) else Write(0);
        }
        // WriteLn();
    }
    // WriteLn();

    free(pixels);
}

bool has_bitmap(string name)
{
    return _bitmaps.count(name) > 0;
}

bitmap bitmap_named(string name)
{
    if (has_bitmap(name))
        return _bitmaps[name];
    else
        return nullptr;
}


bitmap load_bitmap(string name, string filename)
{
    if (has_bitmap(name)) return bitmap_named(name);

    sk_drawing_surface surface;
    bitmap result = nullptr;

    string file_path = filename;

    if ( ! file_exists(file_path) )
    {
        file_path = path_to_resource(filename, IMAGE_RESOURCE);

        if ( ! file_exists(file_path) )
        {
            raise_warning(cat({ "Unable to locate file for ", name, " (", file_path, ")"}));
            return nullptr;
        }
    }

    surface = sk_load_bitmap(file_path.c_str());
    if ( not surface._data )
    {
        raise_warning ( cat({ "Error loading image for ", name, " (", file_path, ")"}) );
        return nullptr;
    }

    result = new _bitmap_data;
    result->image.surface = surface;

    result->id         = BITMAP_PTR;
    result->cell_w     = surface.width;
    result->cell_h     = surface.height;
    result->cell_cols  = 1;
    result->cell_rows  = 1;
    result->cell_count = 1;

    result->name       = name;
    result->filename   = file_path;

    setup_collision_mask(result);

    _bitmaps[name] = result;

    return result;
}

bitmap create_bitmap(string name, int width, int height)
{
    bitmap result = new(_bitmap_data);
    
    result->id = BITMAP_PTR;
    result->image.surface = sk_create_bitmap(width, height);
    
    result->cell_w     = width;
    result->cell_h     = height;
    result->cell_cols  = 1;
    result->cell_rows  = 1;
    result->cell_count = 1;
    
    result->filename   = "";
    
    int idx = 0;
    string key = name;
    while (has_bitmap(key))
    {
        key = name + to_string(idx);
        idx++;
    }

    result->name       = key;
    
    _bitmaps[key] = result;
    
    return result;
}

void free_bitmap(bitmap bmp)
{
    if ( VALID_PTR(bmp, BITMAP_PTR) )
    {
        notify_handlers_of_free(bmp);
        
        _bitmaps.erase(bmp->name);
        sk_close_drawing_surface(&bmp->image.surface);
        bmp->id = NONE_PTR;  // ensure future use of this pointer will fail...
        delete(bmp);
    }
    else
    {
        raise_warning("Delete bitmap called without valid bitmap");
    }
}

void free_all_bitmaps()
{
    FREE_ALL_FROM_MAP(_bitmaps, BITMAP_PTR, free_bitmap);
}

void clear_bitmap(bitmap bmp, color clr)
{
    if ( INVALID_PTR(bmp, BITMAP_PTR))
    {
        raise_warning("Attempting to clear invalid bitmap");
        return;
    }
    
    sk_clear_drawing_surface(&bmp->image.surface, clr);
}

void clear_bitmap(string name, color clr)
{
    clear_bitmap(bitmap_named(name), clr);
}


void draw_bitmap(bitmap bmp, float x, float y)
{
    draw_bitmap(bmp, x, y, option_defaults());
}

void draw_bitmap(bitmap bmp, float x, float y, drawing_options opts)
{
    if ( INVALID_PTR(bmp, BITMAP_PTR))
    {
        raise_warning("Error trying to draw bitmap: passed in bmp is an invalid bitmap pointer.");
        return;
    }

    float src_data[4];
    float dst_data[7];
    sk_renderer_flip flip;
    sk_drawing_surface * dest;

    if ( VALID_PTR(opts.anim, ANIMATION_PTR) )
    {
        rectangle part = bitmap_rectangle_of_cell(bmp, animation_current_cell(opts.anim));
        src_data[0] = part.x;
        src_data[1] = part.y;
        src_data[2] = part.width;
        src_data[3] = part.height;
    }
    else if (not opts.is_part)
    {
        src_data[0] = 0;
        src_data[1] = 0;
        src_data[2] = bmp->image.surface.width;
        src_data[3] = bmp->image.surface.height;
    }
    else
    {
        src_data[0] = opts.part.x;
        src_data[1] = opts.part.y;
        src_data[2] = opts.part.width;
        src_data[3] = opts.part.height;
    }

    //
    if ((opts.flip_x) and (opts.flip_y))
        flip = sk_FLIP_BOTH;
    else if (opts.flip_x)
        flip = sk_FLIP_VERTICAL;
    else if (opts.flip_y)
        flip = sk_FLIP_HORIZONTAL;
    else
        flip = sk_FLIP_NONE;

    // make up dst data
    dst_data[0] = x; // X
    dst_data[1] = y; // Y
    dst_data[2] = opts.angle; // Angle
    dst_data[3] = opts.anchor_offset_x; // Centre X
    dst_data[4] = opts.anchor_offset_y; // Centre Y
    dst_data[5] = opts.scale_x; // Scale X
    dst_data[6] = opts.scale_y; // Scale Y

    xy_from_opts(opts, dst_data[0], dst_data[1]); // Camera?

    dest = to_surface_ptr(opts.dest);
    sk_draw_bitmap(&bmp->image.surface, dest, src_data, 4, dst_data, 7, flip);
}

void draw_bitmap(string name, float x, float y)
{
    draw_bitmap(bitmap_named(name), x, y, option_defaults());
}

void draw_bitmap(string name, float x, float y, drawing_options opts)
{
    draw_bitmap(bitmap_named(name), x, y, opts);
}

rectangle bitmap_rectangle_of_cell(bitmap src, int cell)
{
    rectangle result;

    if ( (not VALID_PTR(src, BITMAP_PTR)) or (cell >= src->cell_count))
        result = rectangle_from(0,0,0,0);
    else if (cell < 0)
        result = rectangle_from(0,0,src->image.surface.width, src->image.surface.width);
    else
    {
        result.x = (cell % src->cell_cols) * src->cell_w;
        result.y = (cell - (cell % src->cell_cols)) / src->cell_cols * src->cell_h;
        result.width = src->cell_w;
        result.height = src->cell_h;
    }
    
    return result;
}

void bitmap_set_cell_details(bitmap bmp, int width, int height, int columns, int rows, int count)
{
    if ( not VALID_PTR(bmp, BITMAP_PTR))
    {
        raise_warning("Trying to set cell details of invalid bitmap.");
        return;
    }

    bmp->cell_w     = width;
    bmp->cell_h     = height;
    bmp->cell_cols  = columns;
    bmp->cell_rows  = rows;
    bmp->cell_count = count;
}

int bitmap_width(bitmap bmp)
{
    if ( INVALID_PTR(bmp, BITMAP_PTR))
    {
        raise_warning("Attempting to get width of invalid bitmap");
        return 0;
    }
    
    return bmp->image.surface.width;
}

int bitmap_width(string name)
{
    return bitmap_width(bitmap_named(name));
}

int bitmap_height(bitmap bmp)
{
    if ( INVALID_PTR(bmp, BITMAP_PTR))
    {
        raise_warning("Attempting to get height of invalid bitmap");
        return 0;
    }
    
    return bmp->image.surface.height;
}

int bitmap_height(string name)
{
    return bitmap_height(bitmap_named(name));
}
