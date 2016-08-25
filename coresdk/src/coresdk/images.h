//
//  images.hpp
//  splashkit
//
//  Created by Andrew Cain on 24/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef images_hpp
#define images_hpp

#include "drawing_options.h"
#include "types.h"
#include "physics.h"

#include <string>
using namespace std;

/// Loads and returns a bitmap. The supplied ``filename`` is used to
/// locate the Bitmap to load. The supplied ``name`` indicates the
/// name to use to refer to this Bitmap in SwinGame. The `Bitmap` can then be
/// retrieved by passing this ``name`` to the `BitmapNamed` function.
///
/// @lib
/// @sn loadBitmapNamed:%s fromFile:%s
///
/// @class Bitmap
/// @constructor
/// @csn initWithName:%s fromFile:%s
bitmap load_bitmap(string name, string filename);

/// Determines if SwinGame has a bitmap loaded for the supplied name.
/// This checks against all bitmaps loaded, those loaded without a name
/// are assigned the filename as a default.
///
bool has_bitmap(string name);

/// Returns the `Bitmap` that has been loaded with the specified name,
/// see `LoadBitmapNamed`.
///
bitmap bitmap_named(string name);

/// Releases the SwinGame resources associated with the bitmap of the
/// specified ``name``.
///
void free_bitmap(bitmap to_delete);

void free_all_bitmaps();

void draw_bitmap(bitmap bmp, float x, float y);

void draw_bitmap(bitmap bmp, float x, float y, drawing_options opts);

void draw_bitmap(string name, float x, float y);

void draw_bitmap(string name, float x, float y, drawing_options opts);

bitmap create_bitmap(string name, int width, int height);

void clear_bitmap(bitmap bmp, color clr);

void clear_bitmap(string name, color clr);

int bitmap_width(bitmap bmp);

int bitmap_width(string name);

int bitmap_height(bitmap bmp);

int bitmap_height(string name);

/**
 * Returns the width of each cell in this bitmap.
 *
 * @param bmp   The bitmap to get the details from.
 * @returns     The width of each cells in bmp
 */
int bitmap_cell_width(bitmap bmp);

/**
 * Returns the height of each cell in this bitmap.
 *
 * @param bmp   The bitmap to get the details from.
 * @returns     The height of each cells in bmp
 */
int bitmap_cell_height(bitmap bmp);

/**
 * Returns a vector that represents the movement needed to get to a given
 * cell within a bitmap.
 * 
 * @param src   The bitmap with the cell details.
 * @param cell  The index of the cell
 * @returns     The offset needed to get to the cell from the top left of the bitmap.
 */
vector_2d bitmap_cell_offset(bitmap src, int cell);

/**
 *  Returns a rectangle that will encompass the bitmap cell if it were drawn
 *  at the indicated point.
 *
 * @param src   The bitmap to get the details from
 * @param pt    The point details for the rectangle.
 * @returns     A rectangle at pt, with width and height from the bitmap's cell details.
 */
rectangle bitmap_cell_rectangle(bitmap src, const point_2d &pt);

/**
 * Returns a circle that will encompass the bitmap cell if it were drawn
 * at the indicated point, with the provided scale.
 *
 * @param bmp   The bitmap to get the details from.
 * @param pt    The point indicating the location of the bitmap.
 * @param scale The scaling factor for the bitmap drawing.
 * @returns     A circle that will encompass the bitmap cell.
 */
circle bitmap_cell_circle(bitmap bmp, const point_2d pt, float scale);

rectangle bitmap_rectangle_of_cell(bitmap src, int cell);

void bitmap_set_cell_details(bitmap bmp, int width, int height, int columns, int rows, int count);

/**
 * Returns the number of cells within the bitmap.
 *
 * @param bmp   The bitmap to check.
 * @returns     The number of individual cells within the bitmap.
 */
int bitmap_cell_count(bitmap bmp);

/**
 * Check if the bitmap has a pixel drawn at the indicated point.
 *
 * @param bmp   The bitmap to check.
 * @param x     The x coordinate within the bitmap to check
 * @param y     The y coordinate within the bitmap to check
 * @returns     True if the pixel at that point in the bitmap is drawn.
 */
bool pixel_drawn_at_point(bitmap bmp, float x, float y);

/**
 * Check if the bitmap has a pixel drawn at the indicated point in the cell.
 *
 * @param bmp   The bitmap to check.
 * @param cell  The bitmap cell to check.
 * @param x     The x coordinate within the bitmap to check
 * @param y     The y coordinate within the bitmap to check
 * @returns     True if the pixel at that point in the bitmap's cell is drawn.
 */
bool pixel_drawn_at_point(bitmap bmp, int cell, float x, float y);

#endif /* images_hpp */
