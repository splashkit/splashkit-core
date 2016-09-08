/**
 * @header Images
 * @author Andrew Cain
 * @brief SplashKit Images allow drawing of bitmaps and sprites to graphic windows.
 *
 *
 * @attribute static images
 */

#ifndef images_h
#define images_h

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

/**
 * Returns the `bitmap` that has been loaded with the specified name,
 * see `load_bitmap`. This will attempt to load the bitmap if it has not
 * been loaded.
 *
 * @param  name The name of the bitmap to check.
 * @returns      The bitmap with the name specified, which may refer to nothing
 *              if the bitmap has not been loaded.
 */
bitmap bitmap_named(string name);

/// Releases the SwinGame resources associated with the bitmap of the
/// specified ``name``.
///
void free_bitmap(bitmap to_delete);

void free_all_bitmaps();

/**
 * Draws the bitmap supplied into `bmp` to the current window.
 * at `x` and `y`.
 *
 * @param bmp the bitmap which will be drawn to the screen
 * @param x   the x location which represents where the bitmap
 *            will be drawn
 * @param y   the y location which represents where the bitmap
 *            will be drawn
 *
 * @attribute class   bitmap
 * @attribute method  draw
 * @attribute self    bmp
 */
void draw_bitmap(bitmap bmp, float x, float y);

/**
 * Draws the bitmap supplied into `bmp` to the current window.
 * with extra drawing options supplied in `opts` at `x` and `y`.
 *
 * @param bmp the bitmap which will be drawn to the screen
 * @param x     the x location which represents where the bitmap
 *              will be drawn
 * @param y     the y location which represents where the bitmap
 *              will be drawn
 * @param opts  the `drawing_options` which provide extra information
 *              for how to draw the `bitmap`
 *
 * @attribute class   bitmap
 * @attribute method  draw
 * @attribute self    bmp
 * @attribute suffix  with_options
 */
void draw_bitmap(bitmap bmp, float x, float y, drawing_options opts);

/**
 * Searches and draws a bitmap with name `name` to the current window.
 * with extra drawing options supplied in `opts` at `x` and `y`.
 *
 * @param name  the name of the bitmap which will be drawn to the screen
 * @param x     the x location which represents where the bitmap
 *              will be drawn
 * @param y     the y location which represents where the bitmap
 *              will be drawn
 *
 * @attribute method  draw_bitmap
 * @attribute suffix  named
 */
void draw_bitmap(string name, float x, float y);

/**
 * Searches and draws a bitmap with name `name` to the current window.
 * with extra drawing options supplied in `opts` at `x` and `y`.
 *
 * @param name  the name of the bitmap which will be drawn to the screen
 * @param x     the x location which represents where the bitmap
 *              will be drawn
 * @param y     the y location which represents where the bitmap
 *              will be drawn
 * @param opts  the `drawing_options` which provide extra information
 *              for how to draw the `bitmap`
 *
 * @attribute method  draw_bitmap
 * @attribute suffix  named_with_options
 */
void draw_bitmap(string name, float x, float y, drawing_options opts);

bitmap create_bitmap(string name, int width, int height);

/**
 * Returns the filename from which the bitmap was loaded. This will be an empty
 * string for created bitmaps.
 *
 * @param  bmp The bitmap to get the filename from.
 * @returns     The file name of the bitmap.
 */
string bitmap_filename(bitmap bmp);

/**
 * Returns the name of the bitmap was loaded. This is the name you can use to
 * access this bitmap.
 *
 * @param  bmp The bitmap to get the name from.
 * @returns     The name of the bitmap.
 */
string bitmap_name(bitmap bmp);

void clear_bitmap(bitmap bmp, color clr);

void clear_bitmap(string name, color clr);

int bitmap_width(bitmap bmp);

int bitmap_width(string name);

/**
 * Returns the total height of the bitmap. If the bitmap contains cells, you ca
 * get the height of a cell using `bitmap_cell_height`.
 *
 * @param  bmp The bitmap to get the details from.
 * @returns     The height of the bitmap.
 */
int bitmap_height(bitmap bmp);

/**
 * Returns the total height of the bitmap. If the bitmap contains cells, you ca
 * get the height of a cell using `bitmap_cell_height`.
 *
 * @param  name The name of the bitmap to get the details from.
 * @returns      The height of the bitmap.
 */
int bitmap_height(string name);

/**
 * This returns a point that represents the center of the bitmap in local
 * space.
 *
 * @param bmp   The bitmap to get the center of.
 * @returns     A point in the center of the bitmap.
 */
point_2d bitmap_center(bitmap bmp);

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
 * Returns the number of rows of cells in the bitmap. These details are set in
 * `bitmap_set_cell_details`.
 *
 * @param  bmp The bitmap to get the details from.
 * @returns     The number of rows of cells in the bitmap.
 */
int bitmap_cell_rows(bitmap bmp);

/**
 * This returns a point that represents the center of a cell from this
 * bitmap in local space.
 *
 * @param bmp   The bitmap to get the center of.
 * @returns     A point in the center of a cell for this bitmap.
 */
point_2d bitmap_cell_center(bitmap bmp);

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
 *  Returns a rectangle that will encompass a cell of the bitmap.
 *
 * @param src   The bitmap to get the details from
 * @returns     A rectangle with width and height from the bitmap's cell details.
 */
rectangle bitmap_cell_rectangle(bitmap src);

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

/**
 * Returns a circle that will encompass the bitmap cell if it were drawn
 * at the indicated point.
 *
 * @param bmp   The bitmap to get the details from.
 * @param pt    The point indicating the location of the bitmap.
 * @returns     A circle that will encompass the bitmap cell.
 */
circle bitmap_cell_circle(bitmap bmp, const point_2d pt);

/**
 * Returns a circle that will encompass the bitmap cell if it were drawn
 * at the indicated point.
 *
 * @param bmp   The bitmap to get the details from.
 * @param x     The the x location of the bitmap.
 * @param y     The the y location of the bitmap.
 * @returns     A circle that will encompass the bitmap cell.
 */
circle bitmap_cell_circle(bitmap bmp, float x, float y);

/**
 * Returns a circle that will encompass the entire bitamp.
 *
 * @param  bmp The bitmap to encompass.
 * @param  pt  The point where the bitmap is located.
 * @returns     A circle that surrounds the bitmap.
 */
circle bitmap_circle(bitmap bmp, const point_2d &pt);

/**
 * Returns the number of cell columns in the bitmap.
 * This is setup using `bitmap_set_cell_details`
 *
 * @param  bmp The bitmap to check
 * @returns     The number of cell columns
 */
int bitmap_cell_columns(bitmap bmp);

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

#endif /* images_h */
