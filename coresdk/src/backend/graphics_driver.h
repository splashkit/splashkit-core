//
//  graphics_driver.h
//  sgsdl2
//
//  Created by Andrew Cain on 20/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#ifndef graphics_driver_h
#define graphics_driver_h

#ifdef __linux__
#include <SDL2/SDL.h>
#else
#include <SDL.h>
#endif

struct sk_color
{
    float r, g, b, a;
};

//
// A list of the available kinds of drawing surface.
// Drivers must support drawing onto these.
//
enum sk_drawing_surface_kind
{
    SGDS_Unknown = 0,   // Unknown, so do not draw onto this!
    SGDS_Window = 1,    // A window
    SGDS_Bitmap = 2     // A surface, bitmap, or texture
};

//
// A drawing surface is something the user can draw onto.
// The driver is then required to provide the ability to
// perform the requested drawing actions on the different
// kinds of drawing surface.
//
struct sk_drawing_surface
{
    sk_drawing_surface_kind kind;
    int width;
    int height;

    // private data used by the backend
    void * _data;
};

enum sk_renderer_flip
{
	sk_FLIP_NONE = 0,
	sk_FLIP_HORIZONTAL = 1,
	sk_FLIP_VERTICAL = 2,
	sk_FLIP_BOTH = 3
};

sk_drawing_surface sk_open_window(const char *title, int width, int height);

sk_drawing_surface sk_create_bitmap(int width, int height);

sk_drawing_surface sk_load_bitmap(const char * filename);


void sk_draw_bitmap( sk_drawing_surface * src, sk_drawing_surface * dst, float * src_data, int src_data_sz, float * dst_data, int dst_data_sz, sk_renderer_flip flip );




void sk_close_drawing_surface(sk_drawing_surface *surface);

void sk_clear_drawing_surface(sk_drawing_surface *surface, sk_color clr);
void sk_refresh_window(sk_drawing_surface *window);

void sk_draw_aabb_rect(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_fill_aabb_rect(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_draw_rect(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_fill_rect(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_draw_triangle(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_fill_triangle(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_draw_ellipse(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_fill_ellipse(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_draw_pixel(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
sk_color sk_read_pixel(sk_drawing_surface *surface, int x, int y);
void sk_draw_circle(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_fill_circle(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);
void sk_draw_line(sk_drawing_surface *surface, sk_color clr, float *data, int data_sz);

void sk_set_clip_rect(sk_drawing_surface *surface, float *data, int data_sz);
void sk_clear_clip_rect(sk_drawing_surface *surface);

void sk_to_pixels(sk_drawing_surface *surface, int *pixels, int sz);

void sk_show_border(sk_drawing_surface *surface, int border);

void sk_show_fullscreen(sk_drawing_surface *surface, int fullscreen);

void sk_resize(sk_drawing_surface *surface, int width, int height);

int sk_save_png(sk_drawing_surface * surface, const char *filename);




#endif /* defined(graphics_driver) */
