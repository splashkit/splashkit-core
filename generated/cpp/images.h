//
// SplashKit Generated Images C++ Code
// DO NOT MODIFY
//

#ifndef __images_h
#define __images_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

circle bitmap_bounding_circle(bitmap bmp, const point_2d &pt);
rectangle bitmap_bounding_rectangle(bitmap bmp);
rectangle bitmap_bounding_rectangle(bitmap bmp, double x, double y);
point_2d bitmap_cell_center(bitmap bmp);
circle bitmap_cell_circle(bitmap bmp, double x, double y);
circle bitmap_cell_circle(bitmap bmp, const point_2d pt);
circle bitmap_cell_circle(bitmap bmp, const point_2d pt, double scale);
int bitmap_cell_columns(bitmap bmp);
int bitmap_cell_count(bitmap bmp);
int bitmap_cell_height(bitmap bmp);
vector_2d bitmap_cell_offset(bitmap src, int cell);
rectangle bitmap_cell_rectangle(bitmap src);
rectangle bitmap_cell_rectangle(bitmap src, const point_2d &pt);
int bitmap_cell_rows(bitmap bmp);
int bitmap_cell_width(bitmap bmp);
point_2d bitmap_center(bitmap bmp);
string bitmap_filename(bitmap bmp);
int bitmap_height(bitmap bmp);
int bitmap_height(string name);
string bitmap_name(bitmap bmp);
bitmap bitmap_named(string name);
rectangle bitmap_rectangle_of_cell(bitmap src, int cell);
void bitmap_set_cell_details(bitmap bmp, int width, int height, int columns, int rows, int count);
int bitmap_width(bitmap bmp);
int bitmap_width(string name);
void clear_bitmap(bitmap bmp, color clr);
void clear_bitmap(string name, color clr);
bitmap create_bitmap(string name, int width, int height);
void draw_bitmap(bitmap bmp, double x, double y);
void draw_bitmap(bitmap bmp, double x, double y, drawing_options opts);
void draw_bitmap(string name, double x, double y);
void draw_bitmap(string name, double x, double y, drawing_options opts);
void draw_bitmap_on_bitmap(bitmap destination, bitmap bmp, double x, double y);
void draw_bitmap_on_bitmap(bitmap destination, bitmap bmp, double x, double y, drawing_options opts);
void draw_bitmap_on_window(window destination, bitmap bmp, double x, double y);
void draw_bitmap_on_window(window destination, bitmap bmp, double x, double y, drawing_options opts);
void free_all_bitmaps();
void free_bitmap(bitmap to_delete);
bool has_bitmap(string name);
bitmap load_bitmap(string name, string filename);
bool pixel_drawn_at_point(bitmap bmp, const point_2d &pt);
bool pixel_drawn_at_point(bitmap bmp, double x, double y);
bool pixel_drawn_at_point(bitmap bmp, int cell, const point_2d &pt);
bool pixel_drawn_at_point(bitmap bmp, int cell, double x, double y);
void setup_collision_mask(bitmap bmp);

#endif /* __images_h */
