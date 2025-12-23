//
// SplashKit Generated Images C++ Code
// DO NOT MODIFY
//

#ifndef __images_h
#define __images_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

/**
* Returns a circle that will encompass the entire bitamp.
* @param bmp The bitmap to encompass.
* @param pt The point where the bitmap is located.
* @return A circle that surrounds the bitmap.
*/;
circle bitmap_bounding_circle(bitmap bmp, const point_2d &pt);
/**
* Returns a rectangle that is the same size as a bitmap (the whole bitmap).
* @param bmp The bitmap
* @return A rectangle with the same size as the bitmap.
*/;
rectangle bitmap_bounding_rectangle(bitmap bmp);
/**
* Returns a rectangle that is the same size as the bitmap and is located at
* the indicated position.
* @param bmp The bitmap
* @param x The x location of the rectangle
* @param y The y location of the rectangle
* @return A rectangle with the same size as the bitmap, at the
indicated location.
*/;
rectangle bitmap_bounding_rectangle(bitmap bmp, double x, double y);
/**
* This returns a point that represents the center of a cell from this
* bitmap in local space.
* @param bmp The bitmap to get the center of.
* @return A point in the center of a cell for this bitmap.
*/;
point_2d bitmap_cell_center(bitmap bmp);
/**
* Returns a circle that will encompass the bitmap cell if it were drawn
* at the indicated point.
* @param bmp The bitmap to get the details from.
* @param x The the x location of the bitmap.
* @param y The the y location of the bitmap.
* @return A circle that will encompass the bitmap cell.
*/;
circle bitmap_cell_circle(bitmap bmp, double x, double y);
/**
* Returns a circle that will encompass the bitmap cell if it were drawn
* at the indicated point.
* @param bmp The bitmap to get the details from.
* @param pt The point indicating the location of the bitmap.
* @return A circle that will encompass the bitmap cell.
*/;
circle bitmap_cell_circle(bitmap bmp, const point_2d pt);
/**
* Returns a circle that will encompass the bitmap cell if it were drawn
* at the indicated point, with the provided scale.
* @param bmp The bitmap to get the details from.
* @param pt The point indicating the location of the bitmap.
* @param scale The scaling factor for the bitmap drawing.
* @return A circle that will encompass the bitmap cell.
*/;
circle bitmap_cell_circle(bitmap bmp, const point_2d pt, double scale);
/**
* Returns the number of cell columns in the bitmap.
* This is setup using `bitmap_set_cell_details`
* @param bmp The bitmap to check
* @return The number of cell columns
*/;
int bitmap_cell_columns(bitmap bmp);
/**
* Returns the number of cells within the bitmap.
* @param bmp The bitmap to check.
* @return The number of individual cells within the bitmap.
*/;
int bitmap_cell_count(bitmap bmp);
/**
* Returns the height of each cell in this bitmap.
* @param bmp The bitmap to get the details from.
* @return The height of each cells in bmp
*/;
int bitmap_cell_height(bitmap bmp);
/**
* Returns a vector that represents the movement needed to get to a given
* cell within a bitmap.
* @param src The bitmap with the cell details.
* @param cell The index of the cell
* @return The offset needed to get to the cell from the top left of the bitmap.
*/;
vector_2d bitmap_cell_offset(bitmap src, int cell);
/**
* Returns a rectangle that will encompass a cell of the bitmap.
* @param src The bitmap to get the details from
* @return A rectangle with width and height from the bitmap's cell details.
*/;
rectangle bitmap_cell_rectangle(bitmap src);
/**
* Returns a rectangle that will encompass the bitmap cell if it were drawn
* at the indicated point.
* @param src The bitmap to get the details from
* @param pt The point details for the rectangle.
* @return A rectangle at pt, with width and height from the bitmap's cell details.
*/;
rectangle bitmap_cell_rectangle(bitmap src, const point_2d &pt);
/**
* Returns the number of rows of cells in the bitmap. These details are set in
* `bitmap_set_cell_details`.
* @param bmp The bitmap to get the details from.
* @return The number of rows of cells in the bitmap.
*/;
int bitmap_cell_rows(bitmap bmp);
/**
* Returns the width of each cell in this bitmap.
* @param bmp The bitmap to get the details from.
* @return The width of each cells in bmp
*/;
int bitmap_cell_width(bitmap bmp);
/**
* This returns a point that represents the center of the bitmap in local
* space.
* @param bmp The bitmap to get the center of.
* @return A point in the center of the bitmap.
*/;
point_2d bitmap_center(bitmap bmp);
/**
* Returns the filename from which the bitmap was loaded. This will be an empty
* string for created bitmaps.
* @param bmp The bitmap to get the filename from.
* @return The file name of the bitmap.
*/;
string bitmap_filename(bitmap bmp);
/**
* Returns the total height of the bitmap. If the bitmap contains cells, you ca
* get the height of a cell using `bitmap_cell_height`.
* @param bmp The bitmap to get the details from.
* @return The height of the bitmap.
*/;
int bitmap_height(bitmap bmp);
/**
* Returns the total height of the bitmap. If the bitmap contains cells, you ca
* get the height of a cell using `bitmap_cell_height`.
* @param name The name of the bitmap to get the details from.
* @return The height of the bitmap.
*/;
int bitmap_height(string name);
/**
* Returns the name of the bitmap was loaded. This is the name you can use to
* access this bitmap.
* @param bmp The bitmap to get the name from.
* @return The name of the bitmap.
*/;
string bitmap_name(bitmap bmp);
/**
* Returns the `bitmap` that has been loaded with the specified name,
* see `load_bitmap`. This will attempt to load the bitmap if it has not
* been loaded.
* @param name The name of the bitmap to check.
* @return The bitmap with the name specified, which may refer to nothing
if the bitmap has not been loaded.
*/;
bitmap bitmap_named(string name);
/**
* Returns a rectangle that can be used to access the part of a bitmap
* related to an individual cell.
* @param src The bitmap
* @param cell The cell
* @return The area of the cell within the bitmap
*/;
rectangle bitmap_rectangle_of_cell(bitmap src, int cell);
/**
* Initialise the bitmap cell details. This allows parts of the bitmap to be
* drawn as individual cells.
* @param bmp The bitmap
* @param width The width of each cell
* @param height The height of each cell
* @param columns The number of cell columns within the bitmap
* @param rows The number of cell rows within the bitmap
* @param count The total number of cells, may be fewer than columns *
* rows
*
*/;
void bitmap_set_cell_details(bitmap bmp, int width, int height, int columns, int rows, int count);
/**
* Lets you test if bitmap value is valid. This will return true when it is a valid bitmap.
* @param bmp the bitmap to test
* @return true when the bitmap is valid.
*/;
bool bitmap_valid(bitmap bmp);
/**
* Returns the width of the bitmap.
* @param bmp The bitmap
* @return The width of the bitmap
*/;
int bitmap_width(bitmap bmp);
/**
* Returns the width of the bitmap.
* @param name The name of the bitmap
* @return The width of the bitmap
*/;
int bitmap_width(string name);
/**
* Clear the bitmap to the indicated color. This will ensure the entire
* surface of the bitmap is set to that color.
* @param bmp The bitmap
* @param clr The new color for the surface of the bitmap
*
*/;
void clear_bitmap(bitmap bmp, color clr);
/**
* Clear the bitmap to the indicated color. This will ensure the entire
* surface of the bitmap is set to that color.
* @param name The name of the bitmap
* @param clr The new color for the surface of the bitmap
*
*/;
void clear_bitmap(string name, color clr);
/**
* Creates a new bitmap that you can draw to. Initially the bitmap will
* be transparent.
* @param name The name of the bitmap resource to be created. If this
* already exists SplashKit will alter the name to make it
* unique.
* @param width The width of the created bitmap
* @param height The height of the created bitmap
* @return A new transparent bitmap
*/;
bitmap create_bitmap(string name, int width, int height);
/**
* Draws the bitmap supplied into `bmp` to the current window.
* at `x` and `y`.
* @param bmp the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
*
*/;
void draw_bitmap(bitmap bmp, double x, double y);
/**
* Draws the bitmap supplied into `bmp` to the current window.
* with extra drawing options supplied in `opts` at `x` and `y`.
* @param bmp the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
* @param opts the `drawing_options` which provide extra information
* for how to draw the `bitmap`
*
*/;
void draw_bitmap(bitmap bmp, double x, double y, drawing_options opts);
/**
* Searches and draws a bitmap with name `name` to the current window.
* with extra drawing options supplied in `opts` at `x` and `y`.
* @param name the name of the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
*
*/;
void draw_bitmap(string name, double x, double y);
/**
* Searches and draws a bitmap with name `name` to the current window.
* with extra drawing options supplied in `opts` at `x` and `y`.
* @param name the name of the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
* @param opts the `drawing_options` which provide extra information
* for how to draw the `bitmap`
*
*/;
void draw_bitmap(string name, double x, double y, drawing_options opts);
/**
* Draws the bitmap supplied into `bmp` to the given bitmap.
* at `x` and `y`.
* @param destination the bitmap to draw the bitmap to
* @param bmp the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
*
*/;
void draw_bitmap_on_bitmap(bitmap destination, bitmap bmp, double x, double y);
/**
* Draws the bitmap supplied into `bmp` to the given bitmap.
* with extra drawing options supplied in `opts` at `x` and `y`.
* @param destination the bitmap to draw the bitmap to
* @param bmp the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
* @param opts the `drawing_options` which provide extra information
* for how to draw the `bitmap`
*
*/;
void draw_bitmap_on_bitmap(bitmap destination, bitmap bmp, double x, double y, drawing_options opts);
/**
* Draws the bitmap supplied into `bmp` to the given window.
* at `x` and `y`.
* @param destination the window to draw the bitmap to
* @param bmp the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
*
*/;
void draw_bitmap_on_window(window destination, bitmap bmp, double x, double y);
/**
* Draws the bitmap supplied into `bmp` to the given window.
* with extra drawing options supplied in `opts` at `x` and `y`.
* @param destination the window to draw the bitmap to
* @param bmp the bitmap which will be drawn to the screen
* @param x the x location which represents where the bitmap
* will be drawn
* @param y the y location which represents where the bitmap
* will be drawn
* @param opts the `drawing_options` which provide extra information
* for how to draw the `bitmap`
*
*/;
void draw_bitmap_on_window(window destination, bitmap bmp, double x, double y, drawing_options opts);
/**
* Free all of the loaded bitmap resources.

*
*/;
void free_all_bitmaps();
/**
* Frees the bitmap resource.
* @param to_delete The bitmap to be freed.
*
*/;
void free_bitmap(bitmap to_delete);
/**
* Determines if SplashKit has a bitmap loaded for the supplied name.
* This checks against all bitmaps loaded.
* @param name The name to check
* @return True if SplashKit has a bitmap with that name
*/;
bool has_bitmap(string name);
/**
* Loads and returns a bitmap. The supplied `filename` is used to
* locate the Bitmap to load. The supplied `name` indicates the
* name to use to refer to this Bitmap in SplashKit. The `bitmap` can then
* be retrieved by passing this `name` to the `bitmap_named` function.
* @param name The name of the bitmap resource in SplashKit
* @param filename The filename to load
* @return The loaded bitmap
*/;
bitmap load_bitmap(string name, string filename);
/**
* Check if the bitmap has a pixel drawn at the indicated point.
* @param bmp The bitmap to check.
* @param pt The point within the bitmap to check.
* @return True if the pixel at that point in the bitmap is drawn.
*/;
bool pixel_drawn_at_point(bitmap bmp, const point_2d &pt);
/**
* Check if the bitmap has a pixel drawn at the indicated point.
* @param bmp The bitmap to check.
* @param x The x coordinate within the bitmap to check
* @param y The y coordinate within the bitmap to check
* @return True if the pixel at that point in the bitmap is drawn.
*/;
bool pixel_drawn_at_point(bitmap bmp, double x, double y);
/**
* Check if the bitmap has a pixel drawn at the indicated point in the cell.
* @param bmp The bitmap to check.
* @param cell The bitmap cell to check.
* @param pt The point within the bitmap to check.
* @return True if the pixel at that point in the bitmap's cell is
drawn.
*/;
bool pixel_drawn_at_point(bitmap bmp, int cell, const point_2d &pt);
/**
* Check if the bitmap has a pixel drawn at the indicated point in the cell.
* @param bmp The bitmap to check.
* @param cell The bitmap cell to check.
* @param x The x coordinate within the bitmap to check
* @param y The y coordinate within the bitmap to check
* @return True if the pixel at that point in the bitmap's cell is
drawn.
*/;
bool pixel_drawn_at_point(bitmap bmp, int cell, double x, double y);
/**
* Sets up the collision mask for a bitmap. This enables collision detection between
* this bitmap and other bitmaps or shapes.
* 
* This is automatically called when a bitmap is loaded, and only needs to be 
* called on bitmaps created using `create_bitmap`, and when a bitmap is
* changed by drawing onto the bitmap.
* @param bmp the bitmap to setup
*
*/;
void setup_collision_mask(bitmap bmp);

#endif /* __images_h */
