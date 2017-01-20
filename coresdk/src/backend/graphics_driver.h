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

#include "backend_types.h"
namespace splashkit_lib
{
    typedef unsigned int uint;

    struct sk_window_be
    {
        SDL_Window *    window;
        SDL_Renderer *  renderer;
        SDL_Texture *   backing;
        bool            clipped;
        SDL_Rect        clip;
        unsigned int    idx;

        // Event data store
        sk_window_data  event_data;
        sk_drawing_surface *surface;
    };

    struct sk_bitmap_be
    {
        // 1 texture per open window
        SDL_Texture **  texture;
        SDL_Surface *   surface;
        bool            clipped;
        SDL_Rect        clip;

        bool            drawable; // can be drawn on
    };

    sk_drawing_surface sk_open_window(const char *title, int width, int height);

    sk_drawing_surface sk_create_bitmap(int width, int height);

    sk_drawing_surface sk_load_bitmap(const char * filename);


    void sk_draw_bitmap( sk_drawing_surface * src, sk_drawing_surface * dst, double * src_data, int src_data_sz, double * dst_data, int dst_data_sz, sk_renderer_flip flip );

    void sk_set_icon(sk_drawing_surface *surface, sk_drawing_surface *icon);


    void sk_close_drawing_surface(sk_drawing_surface *surface);

    void sk_clear_drawing_surface(sk_drawing_surface *surface, sk_color clr);
    void sk_refresh_window(sk_drawing_surface *window);

    void sk_draw_aa_rect(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height);
    void sk_fill_aa_rect(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height);
    void sk_draw_rect(sk_drawing_surface *surface, sk_color clr, double *data, int data_sz);
    void sk_fill_rect(sk_drawing_surface *surface, sk_color clr, double *data, int data_sz);

    void sk_draw_triangle(sk_drawing_surface *surface, sk_color clr, double x1, double y1, double x2, double y2, double x3, double y3);
    void sk_fill_triangle(sk_drawing_surface *surface, color clr, double x1, double y1, double x2, double y2, double x3, double y3);

    void sk_draw_ellipse(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height);
    void sk_fill_ellipse(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height);
    void sk_draw_pixel(sk_drawing_surface *surface, sk_color clr, double x, double y);
    sk_color sk_read_pixel(sk_drawing_surface *surface, int x, int y);

    void sk_draw_circle(sk_drawing_surface *surface, sk_color clr, double x, double y, double radius);
    void sk_fill_circle(sk_drawing_surface *surface, sk_color clr, double x, double y, double radius);

    void sk_draw_line(sk_drawing_surface *surface, sk_color clr, double x1, double y1, double x2, double y2, double size);

    void sk_set_clip_rect(sk_drawing_surface *surface, double x, double y, double width, double height);
    void sk_clear_clip_rect(sk_drawing_surface *surface);

    void sk_to_pixels(sk_drawing_surface *surface, int *pixels, int sz);

    void sk_show_border(sk_drawing_surface *surface, bool border);

    void sk_show_fullscreen(sk_drawing_surface *surface, bool fullscreen);

    void sk_resize(sk_drawing_surface *surface, int width, int height);

    int sk_save_png(sk_drawing_surface * surface, const char *filename);

    struct sk_window_be;

    sk_window_be *_sk_get_window_with_id(unsigned int window_id);
    sk_window_be *_sk_get_window_with_pointer(pointer p);
    
    
    unsigned int _sk_renderer_count(sk_drawing_surface *surface);
    SDL_Renderer * _sk_prepared_renderer(sk_drawing_surface *surface, unsigned int idx);
    void _sk_complete_render(sk_drawing_surface *surface, unsigned int idx);
}

#endif /* defined(graphics_driver) */
