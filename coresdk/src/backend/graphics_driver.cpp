//
//  skGraphics.cpp
//  sk
//
//  Created by Andrew Cain on 20/11/2013.
//  Copyright (c) 2013 Andrew Cain. All rights reserved.
//

#include <limits.h>
#include <iostream>

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include <SDL2/SDL_image.h>
#else
#include <SDL.h>
#include <SDL2_gfxPrimitives.h>
#include <SDL_image.h>
#endif

#include "png.h"
#include <string.h>

#include "core_driver.h"
#include "graphics_driver.h"

using std::cerr;
using std::endl;

namespace splashkit_lib
{
    unsigned int _sk_renderer_count(sk_drawing_surface *surface);
    SDL_Renderer * _sk_prepared_renderer(sk_drawing_surface* surface, unsigned int idx);
    void _sk_complete_render(sk_drawing_surface* surface, unsigned int idx);


    static sk_window_be ** _sk_open_windows = nullptr;
    static unsigned int _sk_num_open_windows = 0;

    static sk_bitmap_be ** _sk_open_bitmaps = nullptr;
    static unsigned int _sk_num_open_bitmaps = 0;

    //
    // Misc
    //
    sk_window_be *_sk_get_window_with_id(unsigned int window_id)
    {
        SDL_Window *window = SDL_GetWindowFromID(window_id);

        return _sk_get_window_with_pointer(window);
    }

    sk_window_be *_sk_get_window_with_pointer(pointer p)
    {
        SDL_Window *window = (SDL_Window *)p;

        for (unsigned int i = 0; i < _sk_num_open_windows; i++)
        {
            if (window == _sk_open_windows[i]->window)
            {
                return _sk_open_windows[i];
            }
        }

        return nullptr;
    }


    //--------------------------------------------------------------------------------------
    //
    // Functions to work with renderer targets - switching targets etc
    //
    //--------------------------------------------------------------------------------------

    void _sk_restore_default_render_target(sk_window_be *window_be, sk_bitmap_be *from_bmp)
    {
        SDL_SetRenderTarget(window_be->renderer, window_be->backing);
        SDL_SetRenderDrawBlendMode(window_be->renderer, SDL_BLENDMODE_BLEND);
        if ( window_be->clipped )
        {
            SDL_RenderSetClipRect(window_be->renderer, &window_be->clip);
        }
        else if ( from_bmp && from_bmp->clipped )
        {
            SDL_RenderSetClipRect(window_be->renderer, nullptr);
        }
    }

    void _sk_restore_default_render_target(unsigned int window_idx, sk_bitmap_be *from_bmp)
    {
        _sk_restore_default_render_target(_sk_open_windows[window_idx], from_bmp);
    }

    void _sk_set_renderer_target(unsigned int window_idx, sk_bitmap_be *target)
    {
        sk_window_be * window_be = _sk_open_windows[window_idx];
        SDL_SetRenderTarget(window_be->renderer, target->texture[window_idx]);
        SDL_SetRenderDrawBlendMode(window_be->renderer, SDL_BLENDMODE_BLEND);

        if ( target->clipped )
        {
            SDL_RenderSetClipRect(window_be->renderer, &target->clip);
        }
    }

    void _sk_make_drawable(sk_bitmap_be *bitmap)
    {
        // recreate all textures with target access

        int access, w, h;

        for (unsigned int i = 0; i < _sk_num_open_windows; i++)
        {
            SDL_Renderer *renderer = _sk_open_windows[i]->renderer;

            SDL_Texture *orig_tex = bitmap->texture[i];

            SDL_QueryTexture(orig_tex, nullptr, &access, &w, &h);

            if ( access == SDL_TEXTUREACCESS_TARGET ) continue; // already target

            // Create new texture
            SDL_Texture *tex = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
            bitmap->texture[i] = tex;

            // Draw onto new texture
            SDL_SetRenderTarget(renderer, tex);
            SDL_RenderCopy(renderer, orig_tex, nullptr, nullptr);

            // Destroy old
            SDL_DestroyTexture(orig_tex);

            _sk_restore_default_render_target(_sk_open_windows[i], bitmap);
        }

        // Remove surface
        SDL_FreeSurface(bitmap->surface);
        bitmap->surface = nullptr;

        // Set drawable
        bitmap->drawable = true;
    }


    //--------------------------------------------------------------------------------------
    //
    // Window and Bitmap store functions
    //
    //--------------------------------------------------------------------------------------

    // The initial window is used when drawing to a bitmap without having any open windows
    // as a window is required in order for drawing operations to be performed.
    static bool _sk_has_initial_window = false;
    static sk_window_be * _sk_initial_window = nullptr;

    //forward declare functions needed for window open
    void _sk_present_window(sk_window_be *window_be);

    // The initial window is a hidden window that is always "open"
    // This allows drawing without the user having to open a window initially.
    void _sk_create_initial_window()
    {
        if (_sk_num_open_windows > 0 ) return;
        if (_sk_open_windows)
        {
            // error windows exist!
            exit(-1);
        }

        _sk_has_initial_window = true;
        _sk_initial_window = static_cast<sk_window_be *>(malloc(sizeof(sk_window_be)));

        _sk_initial_window->window = SDL_CreateWindow("SplashKit",
                                                      SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 200, 200,
                                                      SDL_WINDOW_HIDDEN | SDL_WINDOW_ALLOW_HIGHDPI );

        if ( ! _sk_initial_window->window )
        {
            cerr << "Splashkit failed to load a window." << endl << SDL_GetError() << endl;;
            exit(-1);
        }

        _sk_initial_window->renderer = SDL_CreateRenderer(_sk_initial_window->window,
                                                          -1,
                                                          SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );

        if ( ! _sk_initial_window->renderer )
        {
            _sk_initial_window->renderer = SDL_CreateRenderer(_sk_initial_window->window, -1, SDL_RENDERER_TARGETTEXTURE );

            if ( ! _sk_initial_window->renderer )
            {
                cerr << "Splashkit failed to create a renderer for the window." << endl << (SDL_GetError()) << endl;
                exit(EXIT_FAILURE);
            }
        }

        SDL_SetRenderDrawBlendMode(_sk_initial_window->renderer, SDL_BLENDMODE_BLEND);
        SDL_PumpEvents();
        //HACK: Change size of Mojave
        SDL_SetWindowSize(_sk_initial_window->window, 200, 200);

        //    std::cout << "Initial Renderer is " << _sk_initial_window->renderer << std::endl;

        // The user cannot draw onto this window!
        _sk_initial_window->backing = nullptr;
        _sk_initial_window->surface = nullptr;

        _sk_initial_window->event_data.close_requested = false;
        _sk_initial_window->event_data.has_focus = false;
        _sk_initial_window->event_data.mouse_over = false;
        _sk_initial_window->event_data.shown = false;

        _sk_initial_window->clipped = false;
        _sk_initial_window->clip = {0,0,0,0};

        _sk_open_windows = static_cast<sk_window_be **>(malloc(sizeof(sk_window_be *)));

        _sk_open_windows[0] = _sk_initial_window;
        _sk_initial_window->idx = 0;
        _sk_num_open_windows = 1;

        SDL_SetRenderDrawColor(_sk_initial_window->renderer,
                               static_cast<Uint8>(0.66 * 255),
                               static_cast<Uint8>(0.66 * 255),
                               static_cast<Uint8>(0.66 * 255),
                               static_cast<Uint8>(1.0 * 255));
        SDL_RenderClear(_sk_initial_window->renderer);
        SDL_Rect rect = { 0, 0, 200, 200 };
        SDL_RenderFillRect(_sk_initial_window->renderer, &rect);
        SDL_RenderPresent(_sk_initial_window->renderer);
        SDL_PumpEvents();

        SDL_Texture ** textures = nullptr;

        for (uint bmp_idx = 0; bmp_idx < _sk_num_open_bitmaps; bmp_idx++)
        {
            sk_bitmap_be *current_bmp = _sk_open_bitmaps[bmp_idx];

            if (current_bmp->surface)
            {
                // expand texture array in bitmap
                textures = (SDL_Texture**)realloc(current_bmp->texture, sizeof(SDL_Texture*) * _sk_num_open_windows);
                if ( !textures ) exit (-1); // out of memory

                current_bmp->texture = textures;
                current_bmp->texture[0] = SDL_CreateTextureFromSurface(_sk_initial_window->renderer, current_bmp->surface );
            }
            else
            {
                // cout << "failed to load bitmap image with new window" << endl;
                exit(-1);
            }
        }

        //    std::cout << "CREATED INITIAL WINDOW" << std::endl;
        _sk_present_window(_sk_initial_window);
        SDL_PumpEvents();
    }

    void _sk_get_pixels_from_renderer(SDL_Renderer *renderer, int x, int y, int w, int h, int *pixels);

    SDL_Texture* _sk_copy_texture(SDL_Texture *src_tex, SDL_Renderer *src_renderer, SDL_Renderer *dest_renderer)
    {
        // Read from initial window
        void *pixels;
        int w, h;

        SDL_QueryTexture(src_tex, nullptr, nullptr, &w, &h);
        pixels = malloc(static_cast<size_t>(4 * w * h));

        SDL_SetRenderTarget(src_renderer, src_tex);
        _sk_get_pixels_from_renderer(src_renderer, 0, 0, w, h, (int*)pixels);
        
        //SDL_RenderReadPixels(src_renderer, nullptr, SDL_PIXELFORMAT_RGBA8888, pixels, 4 * w);

        SDL_Texture *tex = SDL_CreateTexture(dest_renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, w, h);
        SDL_SetTextureBlendMode(tex, SDL_BLENDMODE_BLEND);

        SDL_UpdateTexture(tex, nullptr, pixels, 4 * w);
        free(pixels);

        // Restore default target
        SDL_SetRenderTarget(src_renderer, nullptr);

        return tex;
    }

    void _sk_create_texture_for_bitmap_window(sk_bitmap_be *current_bmp, unsigned int src_window_idx, unsigned int dest_window_idx)
    {
        sk_window_be *window = _sk_open_windows[dest_window_idx];

        // if the surface exists, use that to create the new bitmap... otherwise extract from texture
        if (current_bmp->surface && not current_bmp->drawable)
        {
            current_bmp->texture[dest_window_idx] = SDL_CreateTextureFromSurface(window->renderer, current_bmp->surface );
        }
        else
        {
            SDL_Texture *src_tex = current_bmp->texture[src_window_idx];
            current_bmp->texture[dest_window_idx] = _sk_copy_texture(src_tex,
                                                                     _sk_open_windows[src_window_idx]->renderer, window->renderer);
        }
    }

    //
    // Add a window to the array of windows, and update all textures so
    // they can be drawn to this window
    //
    void _sk_add_window(sk_window_be * window)
    {
        // expand array
        _sk_num_open_windows++;

        sk_window_be ** windows = nullptr;
        windows = static_cast<sk_window_be **>(realloc(_sk_open_windows, sizeof(sk_window_be*) * _sk_num_open_windows));
        if ( windows == nullptr )
        {
            // out of memory exception!
            exit(-1);
        }
        _sk_open_windows = windows;

        unsigned int idx = _sk_num_open_windows - 1; // get idx for later use
        windows[idx] = window;
        window->idx = idx;

        // create textures for new window

        SDL_Texture ** textures = nullptr;
        sk_bitmap_be *current_bmp;

        for (unsigned int i = 0; i < _sk_num_open_bitmaps; i++)
        {
            current_bmp = _sk_open_bitmaps[i];

            // expand texture array in bitmap
            textures = static_cast<SDL_Texture **>(realloc(current_bmp->texture, sizeof(SDL_Texture*) * _sk_num_open_windows));
            if ( !textures ) exit (-1); // out of memory

            current_bmp->texture = textures;

            if ( idx > 0 ) // this is not the first window open
                _sk_create_texture_for_bitmap_window(current_bmp, 0, idx);
            else // first window... copy surface
            {
                current_bmp->texture[0] = SDL_CreateTextureFromSurface(window->renderer, current_bmp->surface );
                //TODO: Could the surface be nullptr here?
            }
        }
    }

    bool _sk_has_open_bitmap_without_surface()
    {
        for (uint i = 0; i < _sk_num_open_bitmaps; i++)
        {
            if ( ! _sk_open_bitmaps[i]->surface ) return true;
        }

        return false;
    }

    void _sk_get_pixels_from_renderer(SDL_Renderer *renderer, int x, int y, int w, int h, int *pixels)
    {
        SDL_Rect rect = {x, y, w, h};

        int *raw_pixels = (int*)malloc( sizeof(int) * static_cast<unsigned long>(w * h) );
        SDL_RenderReadPixels(renderer, &rect, SDL_PIXELFORMAT_RGBA8888, raw_pixels, w * 4);

        for (int row = 0; row < h; row++)
        {
            // Copy a row from the paw pixels to the dest pixels
#ifdef WINDOWS
            memcpy(&pixels[(h - row - 1) * w], &raw_pixels[row *  w], sizeof(int) * static_cast<unsigned long>(w));
#else
            memcpy(&pixels[row * w], &raw_pixels[row *  w], sizeof(int) * static_cast<unsigned long>(w));
#endif
        }
        free(raw_pixels);
    }

    void _sk_bitmap_be_texture_to_pixels(sk_bitmap_be *bitmap_be, int *pixels, int sz, int w, int h)
    {
        if (bitmap_be->drawable && _sk_num_open_windows > 0)
        {
            // read pixels from the texture
            _sk_set_renderer_target(0, bitmap_be);
            _sk_get_pixels_from_renderer(_sk_open_windows[0]->renderer, 0, 0, w, h, pixels);
            _sk_restore_default_render_target(_sk_open_windows[0], bitmap_be);
        }
        else
        {
            // cannot read pixels ... make black image
            for (int i = 0; i < sz; i++) {
                pixels[i] = 255;
            }
        }
    }

    void _sk_restore_surfaces()
    {
        Uint32 rmask, gmask, bmask, amask;

        /* SDL interprets each pixel as a 32-bit number, so our masks must depend
         on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        rmask = 0x000000ff;
        gmask = 0x0000ff00;
        bmask = 0x00ff0000;
        amask = 0xff000000;
#else
        rmask = 0xff000000;
        gmask = 0x00ff0000;
        bmask = 0x0000ff00;
        amask = 0x000000ff;
#endif

        for (uint i = 0; i < _sk_num_open_bitmaps; i++)
        {
            if ( ! _sk_open_bitmaps[i]->surface )
            {
                int w, h;
                SDL_QueryTexture(_sk_open_bitmaps[i]->texture[0], nullptr, nullptr, &w, &h);

                int sz = 4 * w * h;
                int pixels[w * h];

                //            std::cout << "sz = " << sz << " size of pixels = " << sizeof(pixels) << std::endl;

                memset(pixels, 0, sizeof(pixels));

                _sk_bitmap_be_texture_to_pixels(_sk_open_bitmaps[i], pixels, sz, w, h);

                _sk_open_bitmaps[i]->surface = SDL_CreateRGBSurface(0, w, h, 32, rmask, gmask, bmask, amask);

                SDL_LockSurface(_sk_open_bitmaps[i]->surface);

                int x = 0, y = 0;
                int *p = (int*)_sk_open_bitmaps[i]->surface->pixels;
                for (int px = 0; px < (w * h); px++)
                {
                    p[x + (y * _sk_open_bitmaps[i]->surface->pitch / 4)] = pixels[px];
                    //                std::cout << "Set pixel[" << x <<","<<y<<"] @ "<<x + (y * _sk_open_bitmaps[i]->surface->pitch / 4) << " = " << p[x + (y * _sk_open_bitmaps[i]->surface->pitch / 4)] << " " << pixels[px] << std::endl;

                    x++;
                    if ( x >= w )
                    {
                        x = 0;
                        y++;
                    }
                }

                SDL_UnlockSurface(_sk_open_bitmaps[i]->surface);
                
                // Last window is being closed, saving the surface means the loaded bitmap will no longer be drawable!
                _sk_open_bitmaps[i]->drawable = false;
            }
        }
    }

    void _sk_remove_window(sk_window_be * window_be)
    {
        unsigned int idx = window_be->idx;
        if ( idx >= _sk_num_open_windows || _sk_open_windows[idx] != window_be)
        {
            std::cout << "error in window close - incorrect idx: " << idx << " of " << _sk_num_open_windows <<  std::endl;
            exit(-1);
        }

        if ( _sk_num_open_windows == 1 && _sk_has_open_bitmap_without_surface() )
        {
            // Need to keep a window open to retain the bitmap surface
            _sk_restore_surfaces();
        }

        // Remove all of the textures for this window
        for (unsigned int bmp_idx = 0; bmp_idx < _sk_num_open_bitmaps; bmp_idx++)
        {
            // Delete the relevant texture
            SDL_DestroyTexture(_sk_open_bitmaps[bmp_idx]->texture[idx]);

            // shuffle left from idx
            for (unsigned int i = idx; i < _sk_num_open_windows - 1; i++)
            {
                _sk_open_bitmaps[bmp_idx]->texture[i] = _sk_open_bitmaps[bmp_idx]->texture[i + 1];
            }

            // Change size of array
            _sk_open_bitmaps[bmp_idx]->texture = static_cast<SDL_Texture **>(realloc(_sk_open_bitmaps[bmp_idx]->texture, sizeof(sk_bitmap_be *) * _sk_num_open_windows - 1));
        }

        // Shuffle all windows left from idx
        for (unsigned int i = idx; i < _sk_num_open_windows - 1; i++)
        {
            _sk_open_windows[i] = _sk_open_windows[i + 1];
            _sk_open_windows[i]->idx--; // adjust index
            if ( i != _sk_open_windows[i]->idx ) {
                std::cout << "error in window close!" << std::endl;
                exit(-1);
            }
        }
        // resize windows array
        _sk_num_open_windows--;
        // std::cout << "windows open " << _sk_num_open_windows << std::endl;
        if (_sk_num_open_windows > 0)
        {
            sk_window_be ** temp = static_cast<sk_window_be **>(realloc(_sk_open_windows, sizeof(sk_window_be*) * _sk_num_open_windows));
            if (!temp)
            {
                exit(-1);
            }
            else
            {
                _sk_open_windows = temp;
            }
        }
        else
        {
            free(_sk_open_windows);
            _sk_open_windows = nullptr;
        }

    }

    void _sk_destroy_window(sk_window_be *window_be)
    {
        _sk_remove_window(window_be);

        if (window_be->backing)
        {
            SDL_DestroyTexture(window_be->backing);
        }

        SDL_DestroyRenderer(window_be->renderer);
        SDL_DestroyWindow(window_be->window);

        window_be->idx = UINT_MAX;
        window_be->renderer = nullptr;
        window_be->window = nullptr;
        window_be->backing = nullptr;

        if ( _sk_initial_window == window_be )
        {
            _sk_initial_window = nullptr;
            _sk_has_initial_window = false;
        }

        free(window_be);
    }

    void _sk_destroy_initial_window()
    {
        if (_sk_initial_window != nullptr)
        {
            _sk_destroy_window(_sk_initial_window);
        }
    }



    //
    // Add the bitmap to the array to allow it to be added to future windows opened
    //
    void _sk_add_bitmap(sk_bitmap_be *bmp)
    {
        _sk_num_open_bitmaps++;
        sk_bitmap_be **new_arr = static_cast<sk_bitmap_be **>(realloc(_sk_open_bitmaps, sizeof(sk_bitmap_be *) * _sk_num_open_bitmaps));

        if (!new_arr) exit(-1); // out of memory

        _sk_open_bitmaps = new_arr;
        new_arr[_sk_num_open_bitmaps-1] = bmp;
    }

    //
    // Remove the bitmap...
    //
    void _sk_remove_bitmap(sk_bitmap_be *bitmap_be)
    {
        unsigned int idx = 0;
        for (idx = 0; idx < _sk_num_open_bitmaps; idx++)
        {
            if ( _sk_open_bitmaps[idx] == bitmap_be ) break;
        }

        if ( idx >= _sk_num_open_bitmaps )
        {
            //unable to locate bitmap being closed!
            exit(-1);
        }

        // Shuffle bitmaps left
        for (unsigned int i = idx; i < _sk_num_open_bitmaps -1; i++)
        {
            _sk_open_bitmaps[i] = _sk_open_bitmaps[i + 1];
        }

        // Remove the bitmap
        _sk_num_open_bitmaps--;
        if (_sk_num_open_bitmaps > 0)
        {
            sk_bitmap_be ** temp = static_cast<sk_bitmap_be**>(realloc(_sk_open_bitmaps, sizeof(sk_bitmap_be *) * _sk_num_open_bitmaps));

            if (!temp)
            {
                exit(-1);
            }
            else
            {
                _sk_open_bitmaps = temp;
            }
        }
        else
        {
            free(_sk_open_bitmaps);
            _sk_open_bitmaps = nullptr;
        }

        if ( _sk_num_open_bitmaps > 0 && ! _sk_num_open_bitmaps )
        {
            // Error reducing memory allocation?
            exit(-1);
        }
    }

    void _sk_destroy_bitmap(sk_bitmap_be *bitmap_be)
    {
        _sk_remove_bitmap(bitmap_be);

        for (unsigned int bmp_idx = 0; bmp_idx < _sk_num_open_windows; bmp_idx++)
        {
            SDL_DestroyTexture(bitmap_be->texture[bmp_idx]);
            bitmap_be->texture[bmp_idx] = nullptr;
        }
        free(bitmap_be->texture);

        if (bitmap_be->surface)
        {
            SDL_FreeSurface(bitmap_be->surface);
        }

        bitmap_be->surface = nullptr;
        bitmap_be->texture = nullptr;

        free(bitmap_be);
    }


    //--------------------------------------------------------------------------------------
    //
    // Window functions
    //
    //--------------------------------------------------------------------------------------

    bool _sk_open_window(const char *title, int width, int height, unsigned int options, sk_window_be *window_be)
    {
        window_be->window = SDL_CreateWindow(title,
                                             SDL_WINDOWPOS_CENTERED,
                                             SDL_WINDOWPOS_CENTERED,
                                             width,
                                             height,
                                             options | SDL_WINDOW_ALLOW_HIGHDPI | SDL_WINDOW_INPUT_FOCUS);

        if ( ! window_be->window )
        {
            cerr << "Splashkit failed to open a window." << endl << (SDL_GetError()) << endl;
            exit(EXIT_FAILURE);
        }

        // Setup the fullscreen mode
        SDL_DisplayMode fullscreen_mode;
        SDL_zero(fullscreen_mode);
        fullscreen_mode.format = SDL_PIXELFORMAT_RGB888;
        SDL_SetWindowDisplayMode(window_be->window, &fullscreen_mode);

        // Create the actual renderer -- accellerated,
        window_be->renderer = SDL_CreateRenderer(window_be->window,
                                                 -1,
                                                 SDL_RENDERER_ACCELERATED | SDL_RENDERER_TARGETTEXTURE );

        if ( ! window_be->renderer )
        {
            window_be->renderer = SDL_CreateRenderer(window_be->window, -1, SDL_RENDERER_TARGETTEXTURE );

            if ( ! window_be->renderer )
            {
                cerr << "Splashkit failed to create a renderer for the window." << endl << (SDL_GetError()) << endl;
                exit(EXIT_FAILURE);
            }
        }

        //std::cout << "Renderer is " << window_be->renderer << std::endl;

        SDL_SetRenderDrawColor(window_be->renderer, 120, 120, 120, 255);
        SDL_RenderClear(window_be->renderer);
        SDL_RenderPresent(window_be->renderer);
        SDL_SetRenderDrawBlendMode(window_be->renderer, SDL_BLENDMODE_BLEND);

        window_be->backing = SDL_CreateTexture(window_be->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);

        SDL_SetRenderTarget(window_be->renderer, window_be->backing);
        SDL_SetRenderDrawBlendMode(window_be->renderer, SDL_BLENDMODE_BLEND);
        SDL_RenderClear(window_be->renderer);

        _sk_add_window(window_be);
        
        if( _sk_has_initial_window )
        {
            _sk_destroy_initial_window();
        }

        SDL_RaiseWindow(window_be->window);
        _sk_present_window(window_be);
        SDL_PumpEvents();
        //HACK: Change size of Mojave
        SDL_SetWindowSize(window_be->window, width, height);

        return true;
    }

    void sk_clear_drawing_surface(sk_drawing_surface *surface, sk_color clr);
    void sk_refresh_window(sk_drawing_surface *window);

    sk_drawing_surface sk_open_window(const char *title, int width, int height)
    {
        internal_sk_init();
        sk_drawing_surface  result = { SGDS_Unknown, 0, 0, nullptr };

        sk_window_be *      window_be;

        window_be = static_cast<sk_window_be *>(malloc(sizeof(sk_window_be)));

        if ( ! window_be )
        {
            cerr << "Unable to open window: Out of memory" << endl;
            exit(EXIT_FAILURE);
        }

        if ( ! _sk_open_window(title, width, height, SDL_WINDOW_SHOWN, window_be) )
        {
            free ( window_be );
            return result;
        }

        result._data = window_be;

        window_be->clipped = false;
        window_be->clip = {0,0,0,0};

        window_be->event_data.close_requested = false;
        window_be->event_data.has_focus = false;
        window_be->event_data.mouse_over = false;
        window_be->event_data.shown = true;

        result.kind = SGDS_Window;

        result.width = width;
        result.height = height;

        sk_clear_drawing_surface(&result, {1,1,1,1});
        sk_refresh_window(&result);

        SDL_PumpEvents();

        return result;
    }

    void sk_close_drawing_surface(sk_drawing_surface *surface)
    {
        if ( ! surface )
        {
            cerr << "No surface provided to close_drawing_surface" << endl;
            return;
        }

        switch (surface->kind)
        {
            case SGDS_Window:
                _sk_destroy_window(static_cast<sk_window_be *>(surface->_data));
                break;

            case SGDS_Bitmap:
                _sk_destroy_bitmap(static_cast<sk_bitmap_be *>(surface->_data));
                break;

            case SGDS_Unknown:
                break;
        }

        surface->kind = SGDS_Unknown;
        surface->_data = nullptr;
    }

    void sk_set_icon(sk_drawing_surface *surface, sk_drawing_surface *icon)
    {
        if ( surface->kind != SGDS_Window || icon->kind != SGDS_Bitmap ) return;

        sk_window_be *wind = static_cast<sk_window_be *>(surface->_data);
        sk_bitmap_be *bmp = static_cast<sk_bitmap_be *>(icon->_data);

        SDL_SetWindowIcon(wind->window, bmp->surface);
    }


    void _sk_do_clear(SDL_Renderer *renderer, sk_color clr)
    {
        SDL_SetRenderDrawColor(renderer,
                               static_cast<Uint8>(clr.r * 255),
                               static_cast<Uint8>(clr.g * 255),
                               static_cast<Uint8>(clr.b * 255),
                               static_cast<Uint8>(clr.a * 255));
        SDL_RenderClear(renderer);
    }

    void _sk_clear_window(sk_drawing_surface *window, sk_color clr)
    {
        sk_window_be * window_be;
        window_be = static_cast<sk_window_be *>(window->_data);

        if ( window_be )
        {
            _sk_do_clear(window_be->renderer, clr);

            //ATI cards are lazy, won't draw the clear screen until you actually draw something else on top of it
            SDL_Rect rect = { 0, 0, 1, 1 };
            SDL_RenderFillRect(window_be->renderer, &rect);
        }
    }

    void _sk_clear_bitmap(sk_drawing_surface *bitmap, sk_color clr)
    {
        sk_bitmap_be * bitmap_be = static_cast<sk_bitmap_be *>(bitmap->_data);

        if ( bitmap_be )
        {
            if ( ! bitmap_be->drawable ) _sk_make_drawable( bitmap_be );

            for (unsigned int i = 0; i < _sk_num_open_windows; i++)
            {
                sk_window_be *window = _sk_open_windows[i];
                SDL_Renderer *renderer = window->renderer;

                _sk_set_renderer_target(i, bitmap_be);

                _sk_do_clear(renderer, clr);

                _sk_restore_default_render_target(window, bitmap_be);
            }
        }
    }

    void sk_clear_drawing_surface(sk_drawing_surface *surface, sk_color clr)
    {
        if ( ! surface ) return;

        switch (surface->kind)
        {
            case SGDS_Window:
                _sk_clear_window(surface, clr);
                break;

            case SGDS_Bitmap:
                _sk_clear_bitmap(surface, clr);
                break;

            case SGDS_Unknown:
                break;
        }
    }

    void _sk_present_window(sk_window_be *window_be)
    {
        if ( window_be && window_be->backing )
        {
            SDL_SetRenderTarget(window_be->renderer, nullptr);

            SDL_RenderCopy(window_be->renderer, window_be->backing, nullptr, nullptr);
            SDL_RenderPresent(window_be->renderer);
            _sk_restore_default_render_target(window_be, nullptr);
        }
    }

    void sk_refresh_window(sk_drawing_surface *window)
    {
        if ( (! window) || window->kind != SGDS_Window ) return;

        sk_window_be * window_be;
        window_be = static_cast<sk_window_be *>(window->_data);

        _sk_present_window(window_be);
    }

    //
    // Renderer functions - switch between bmp and window
    //

    SDL_Renderer * _sk_prepared_renderer(sk_drawing_surface *surface, unsigned int idx)
    {
        switch (surface->kind)
        {
            case SGDS_Window:
                return static_cast<sk_window_be *>(surface->_data)->renderer;

            case SGDS_Bitmap:
            {
                sk_bitmap_be *bitmap_be = static_cast<sk_bitmap_be *>(surface->_data);
                if ( ! bitmap_be->drawable ) _sk_make_drawable( bitmap_be );
                _sk_set_renderer_target(idx, bitmap_be);

                if (idx < _sk_num_open_windows)
                    return _sk_open_windows[idx]->renderer;
                else return nullptr;
            }

            case SGDS_Unknown:
                return nullptr;
        }
    }

    void _sk_complete_render(sk_drawing_surface *surface, unsigned int idx)
    {
        switch (surface->kind)
        {
            case SGDS_Window:
                break;
            case SGDS_Bitmap:
                if (idx < _sk_num_open_windows)
                    _sk_restore_default_render_target(_sk_open_windows[idx], static_cast<sk_bitmap_be *>(surface->_data));
                break;
            case SGDS_Unknown:
                break;
        }
    }

    unsigned int _sk_renderer_count(sk_drawing_surface *surface)
    {
        switch (surface->kind)
        {
            case SGDS_Window:
                return 1;
            case SGDS_Bitmap:
                // Drawing to a bitmap... so ensure that there is at least one window
                if ( _sk_num_open_windows == 0 ) _sk_create_initial_window();
                return _sk_num_open_windows;
            case SGDS_Unknown:
                return 0;
        }
    }


    //
    //  Rectangles
    //

    void sk_draw_aa_rect(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height)
    {
        if ( (! surface) || (! surface->_data) ) return;

        SDL_Rect rect = {
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height)
        };

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            SDL_SetRenderDrawColor(renderer,
                                   static_cast<Uint8>(clr.r * 255),
                                   static_cast<Uint8>(clr.g * 255),
                                   static_cast<Uint8>(clr.b * 255),
                                   static_cast<Uint8>(clr.a * 255));

            SDL_RenderDrawRect(renderer, &rect);

            _sk_complete_render(surface, i);
        }
    }

    void sk_fill_aa_rect(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height)
    {
        if ( (! surface) || (! surface->_data)  ) return;

        SDL_Rect rect = {
            static_cast<int>(x),
            static_cast<int>(y),
            static_cast<int>(width),
            static_cast<int>(height)
        };

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            SDL_SetRenderDrawColor(renderer,
                                   static_cast<Uint8>(clr.r * 255),
                                   static_cast<Uint8>(clr.g * 255),
                                   static_cast<Uint8>(clr.b * 255),
                                   static_cast<Uint8>(clr.a * 255));

            SDL_RenderFillRect(renderer, &rect);

            _sk_complete_render(surface, i);
        }
    }


    // Rectangle points are...
    //
    //   0 ..... 1
    //   .       .
    //   .       .
    //   .       .
    //   2 ..... 3
    //
    void sk_draw_rect(sk_drawing_surface *surface, sk_color clr, double *data, int data_sz)
    {
        if ( (! surface) || ! surface->_data ) return;
        if ( data_sz != 8 ) return;

        // 8 values = 4 points
        int x1 = static_cast<int>(data[0]), y1 = static_cast<int>(data[1]);
        int x2 = static_cast<int>(data[2]), y2 = static_cast<int>(data[3]);
        int x3 = static_cast<int>(data[4]), y3 = static_cast<int>(data[5]);
        int x4 = static_cast<int>(data[6]), y4 = static_cast<int>(data[7]);

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            SDL_SetRenderDrawColor(renderer,
                                   static_cast<Uint8>(clr.r * 255),
                                   static_cast<Uint8>(clr.g * 255),
                                   static_cast<Uint8>(clr.b * 255),
                                   static_cast<Uint8>(clr.a * 255));

            SDL_RenderDrawLine(renderer, x1, y1, x2, y2);
            SDL_RenderDrawLine(renderer, x1, y1, x3, y3);
            SDL_RenderDrawLine(renderer, x4, y4, x2, y2);
            SDL_RenderDrawLine(renderer, x4, y4, x3, y3);

            _sk_complete_render(surface, i);
        }
    }

    // Rectangle points are...
    //
    //   0 ..... 1
    //   .       .
    //   .       .
    //   .       .
    //   2 ..... 3
    //
    void sk_fill_rect(sk_drawing_surface *surface, sk_color clr, double *data, int data_sz)
    {
        if ( ! surface ) return;
        if ( data_sz != 8 ) return;

        // 8 values = 4 points
        Sint16 x[4], y[4];

        x[0] = static_cast<Sint16>(data[0]);
        x[1] = static_cast<Sint16>(data[2]);
        x[2] = static_cast<Sint16>(data[6]);    // Swap last 2 for SDL_gfx order
        x[3] = static_cast<Sint16>(data[4]);

        y[0] = static_cast<Sint16>(data[1]);
        y[1] = static_cast<Sint16>(data[3]);
        y[2] = static_cast<Sint16>(data[7]);    // Swap last 2 for SDL_gfx order
        y[3] = static_cast<Sint16>(data[5]);

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            Uint8 a = static_cast<Uint8>(clr.a * 255);
            filledPolygonRGBA(
                              renderer,
                              x, y, 4,
                              static_cast<Uint8>(clr.r * 255),
                              static_cast<Uint8>(clr.g * 255),
                              static_cast<Uint8>(clr.b * 255),
                              a
                              );

            if ( a == 255 ) // SDL_Gfx changes renderer state ... undo change here
            {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            }

            _sk_complete_render(surface, i);
        }
    }



    //
    //  Triangles
    //

    void sk_draw_triangle(sk_drawing_surface *surface, sk_color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        if ( ! surface || ! surface->_data ) return;

        // 6 values = 3 points
        int px1 = static_cast<int>(x1), py1 = static_cast<int>(y1);
        int px2 = static_cast<int>(x2), py2 = static_cast<int>(y2);
        int px3 = static_cast<int>(x3), py3 = static_cast<int>(y3);

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            SDL_SetRenderDrawColor(renderer,
                                   static_cast<Uint8>(clr.r * 255),
                                   static_cast<Uint8>(clr.g * 255),
                                   static_cast<Uint8>(clr.b * 255),
                                   static_cast<Uint8>(clr.a * 255));

            SDL_RenderDrawLine(renderer, px1, py1, px2, py2);
            SDL_RenderDrawLine(renderer, px2, py2, px3, py3);
            SDL_RenderDrawLine(renderer, px3, py3, px1, py1);

            _sk_complete_render(surface, i);
        }
    }

    void sk_fill_triangle(sk_drawing_surface *surface, color clr, double x1, double y1, double x2, double y2, double x3, double y3)
    {
        if ( ! surface || ! surface->_data ) return;

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            Uint8 a = static_cast<Uint8>(clr.a * 255);
            filledTrigonRGBA(renderer,
                             static_cast<Sint16>(x1), static_cast<Sint16>(y1),
                             static_cast<Sint16>(x2), static_cast<Sint16>(y2),
                             static_cast<Sint16>(x3), static_cast<Sint16>(y3),
                             static_cast<Uint8>(clr.r * 255),
                             static_cast<Uint8>(clr.g * 255),
                             static_cast<Uint8>(clr.b * 255),
                             a
                             );

            if ( a == 255 ) // SDL_Gfx changes renderer state ... undo change here
            {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            }

            _sk_complete_render(surface, i);
        }
    }

    //
    //  Ellipse
    //

    void sk_draw_ellipse(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height)
    {
        if ( ! surface || ! surface->_data ) return;

        // 4 values = 1 point w + h
        int x1 = static_cast<int>(x), y1 = static_cast<int>(y);
        int w = static_cast<int>(width), h = static_cast<int>(height);

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            Uint8 a = static_cast<Uint8>(clr.a * 255);
            ellipseRGBA( renderer,
                        static_cast<Sint16>(x1 + w / 2),
                        static_cast<Sint16>(y1 + h / 2),
                        static_cast<Sint16>(w / 2),
                        static_cast<Sint16>(h / 2),
                        static_cast<Uint8>(clr.r * 255),
                        static_cast<Uint8>(clr.g * 255),
                        static_cast<Uint8>(clr.b * 255), a);

            if ( a == 255 ) // SDL_Gfx changes renderer state ... undo change here
            {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            }

            _sk_complete_render(surface, i);
        }
    }

    void sk_fill_ellipse(sk_drawing_surface *surface, sk_color clr, double x, double y, double width, double height)
    {
        if ( ! surface || ! surface->_data ) return;

        // 4 values = 1 point w + h
        int x1 = static_cast<int>(x), y1 = static_cast<int>(y);
        int w = static_cast<int>(width), h = static_cast<int>(height);

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            Uint8 a = static_cast<Uint8>(clr.a * 255);
            filledEllipseRGBA(renderer,
                              static_cast<Sint16>(x1 + w / 2),
                              static_cast<Sint16>(y1 + h / 2),
                              static_cast<Sint16>(w / 2),
                              static_cast<Sint16>(h / 2),
                              static_cast<Uint8>(clr.r * 255),
                              static_cast<Uint8>(clr.g * 255),
                              static_cast<Uint8>(clr.b * 255), a);

            if ( a == 255 ) // SDL_Gfx changes renderer state ... undo change here
            {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            }

            _sk_complete_render(surface, i);
        }
    }


    //
    // Pixel
    //

    void sk_draw_pixel(sk_drawing_surface *surface, sk_color clr, double x, double y)
    {
        if ( ! surface || ! surface->_data ) return;

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            SDL_SetRenderDrawColor(renderer,
                                   static_cast<Uint8>(clr.r * 255),
                                   static_cast<Uint8>(clr.g * 255),
                                   static_cast<Uint8>(clr.b * 255),
                                   static_cast<Uint8>(clr.a * 255));

            // The following works with multisampling on... use if we
            // want multisampling... otherwise use the following
            //
            //            SDL_Rect rect = { x1, y1, 1, 1 };
            //            SDL_RenderFillRect(window_be->renderer, &rect);

            // For some reason the following does not work :(
            // when multisample is 1, but without multisample 1
            // double buffer causes flicker
            //
            SDL_RenderDrawPoint(renderer, x, y);

            _sk_complete_render(surface, i);
        }

    }


    sk_color sk_read_pixel(sk_drawing_surface *surface, int x, int y)
    {
        sk_color result = {0,0,0,0};
        unsigned int clr = 0;
        
#ifdef WINDOWS
        // Texture is inverted so flip y
        SDL_Rect rect = {x, surface->height - y - 1, 1, 1};	
#else
        SDL_Rect rect = {x, y, 1, 1};
#endif

        if ( ! surface || ! surface->_data ) return result;

        if ( _sk_num_open_windows == 0 ) _sk_create_initial_window();

        SDL_Renderer *renderer = _sk_prepared_renderer(surface, 0);

        SDL_RenderReadPixels(renderer,
                             &rect,
                             SDL_PIXELFORMAT_RGBA8888,
                             &clr,
                             4 * surface->width );
        result.a = (clr & 0x000000ff) / 255.0f;
        result.r = ((clr & 0xff000000) >> 24) / 255.0f;
        result.g = ((clr & 0x00ff0000) >> 16) / 255.0f;
        result.b = ((clr & 0x0000ff00) >> 8) / 255.0f;

        _sk_complete_render(surface, 0);

        return result;
    }


    //
    // Circles
    //

    void sk_draw_circle(sk_drawing_surface *surface, sk_color clr, double x, double y, double radius)
    {
        if ( ! surface || ! surface->_data ) return;

        // 3 values = 1 point + radius
        int x1 = static_cast<int>(x), y1 = static_cast<int>(y);
        int r = static_cast<int>(radius);

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            Uint8 a = static_cast<Uint8>(clr.a * 255);

            circleRGBA(
                       renderer,
                       static_cast<Sint16>(x1),
                       static_cast<Sint16>(y1),
                       static_cast<Sint16>(r),
                       static_cast<Uint8>(clr.r * 255),
                       static_cast<Uint8>(clr.g * 255),
                       static_cast<Uint8>(clr.b * 255),
                       a
                       );

            if ( a == 255 ) // SDL_Gfx changes renderer state ... undo change here
            {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            }

            _sk_complete_render(surface, i);
        }
    }

    void sk_fill_circle(sk_drawing_surface *surface, sk_color clr, double x, double y, double radius)
    {
        if ( ! surface || ! surface->_data ) return;

        // 3 values = 1 point + radius
        int x1 = static_cast<int>(x), y1 = static_cast<int>(y);
        int r = static_cast<int>(radius);

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            Uint8 a = static_cast<Uint8>(clr.a * 255);

            filledCircleRGBA(
                             renderer,
                             static_cast<Sint16>(x1),
                             static_cast<Sint16>(y1),
                             static_cast<Sint16>(r),
                             static_cast<Uint8>(clr.r * 255),
                             static_cast<Uint8>(clr.g * 255),
                             static_cast<Uint8>(clr.b * 255),
                             a
                             );

            if ( a == 255 ) // SDL_Gfx changes renderer state ... undo change here
            {
                SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);
            }

            _sk_complete_render(surface, i);
        }
    }


    //
    // Lines
    //

    void sk_draw_line(sk_drawing_surface *surface, sk_color clr, double x1, double y1, double x2, double y2, double size)
    {
        if ( ! surface || ! surface->_data ) return;

        // 4 values = 2 points
        int x1i = static_cast<int>(x1), y1i = static_cast<int>(y1);
        int x2i = static_cast<int>(x2), y2i = static_cast<int>(y2);

        // 5th value = width (scale)
        int w = static_cast<int>(size);

        if ( w == 0 ) return;

        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);

            if ( w == 1)
            {
                SDL_SetRenderDrawColor(renderer,
                                       static_cast<Uint8>(clr.r * 255),
                                       static_cast<Uint8>(clr.g * 255),
                                       static_cast<Uint8>(clr.b * 255),
                                       static_cast<Uint8>(clr.a * 255));

                SDL_RenderDrawLine(renderer, x1i, y1i, x2i, y2i);
            }
            else
            {
                thickLineRGBA(renderer,
                              static_cast<Sint16>(x1i),
                              static_cast<Sint16>(y1i),
                              static_cast<Sint16>(x2i),
                              static_cast<Sint16>(y2i),
                              static_cast<Uint8>(w),
                              static_cast<Uint8>(clr.r * 255),
                              static_cast<Uint8>(clr.g * 255),
                              static_cast<Uint8>(clr.b * 255),
                              static_cast<Uint8>(clr.a * 255));
            }
            _sk_complete_render(surface, i);
        }
    }


    //
    // Clipping
    //

    void sk_set_clip_rect(sk_drawing_surface *surface, double x, double y, double width, double height)
    {
        if ( ! surface || ! surface->_data ) return;

        // 4 values = 1 point w + h
        int x1 = static_cast<int>(x), y1 = static_cast<int>(y);
        int w = static_cast<int>(width), h = static_cast<int>(height);

        switch (surface->kind) {
            case SGDS_Window:
            {
                sk_window_be * window_be;
                window_be = static_cast<sk_window_be *>(surface->_data);

                window_be->clipped = true;
                window_be->clip = { x1, y1, w, h };

                SDL_RenderSetClipRect(window_be->renderer, &window_be->clip);
                break;
            }
            case SGDS_Bitmap:
            {
                sk_bitmap_be * bitmap_be;
                bitmap_be = static_cast<sk_bitmap_be *>(surface->_data);

                bitmap_be->clipped = true;
                bitmap_be->clip = { x1, y1, w, h };

                break;
            }

            case SGDS_Unknown:
                break;
        }
    }

    void sk_clear_clip_rect(sk_drawing_surface *surface)
    {
        switch (surface->kind)
        {
            case SGDS_Window:
            {
                sk_window_be * window_be;
                window_be = static_cast<sk_window_be *>(surface->_data);

                window_be->clipped = false;
                window_be->clip = { 0, 0, surface->width, surface->height };
                SDL_RenderSetClipRect(window_be->renderer, nullptr);
                //SDL_RenderPresent(window_be->renderer);
                break;
            }
            case SGDS_Bitmap:
            {
                sk_bitmap_be * bitmap_be;
                bitmap_be = static_cast<sk_bitmap_be *>(surface->_data);

                bitmap_be->clipped = false;
                bitmap_be->clip = { 0, 0, surface->width, surface->height };

                // unsigned int count = _sk_renderer_count(surface);

                // for (unsigned int i = 0; i < count; i++)
                // {
                //     SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
                //     SDL_RenderPresent(renderer);
                //     _sk_complete_render(surface, i);
                // }

                break;
            }

            case SGDS_Unknown:
                break;
        }
    }

    Uint32 _get_pixel(SDL_Surface *surface, int x, int y)
    {
        Uint8 *p;

        if(!surface->pixels) return 0;

        p = static_cast<Uint8 *>(surface->pixels)
        + y * surface->pitch
        + x * surface->format->BytesPerPixel;

        if(x < 0 || y < 0 || x >= surface->w || y >= surface->h) return 0;

        uint32_t color;

        switch(surface->format->BytesPerPixel) {
            case 1:
                color = *p;
                break;
            case 2:
                color = *reinterpret_cast<Uint16 *>(p);
                break;
            case 3:
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
                color = static_cast<Uint32>(p[0] << 16 | p[1] << 8 | p[2]);
#else
                color = static_cast<Uint32>(p[0] | p[1] << 8 | p[2] << 16);
#endif
                break;
            case 4:
                color = *reinterpret_cast<Uint32 *>(p);
                break;
            default:
                color = 0;
        }

        uint8_t r, g, b, a;

        SDL_GetRGBA(color, surface->format, &r, &g, &b, &a);
        return (uint32_t)(r << 24 | g << 16 | b << 8 | a);

        //    switch(surface->format->BytesPerPixel) {
        //        case 1:
        //            return *p;
        //        case 2:
        //            return *(Uint16 *)p;
        //        case 3:
        //#if SDL_BYTEORDER == SDL_BIG_ENDIAN
        //            return static_cast<Uint32>(p[0] << 16 | p[1] << 8 | p[2]);
        //#else
        //            return static_cast<Uint32>(p[0] | p[1] << 8 | p[2] << 16);
        //#endif
        //        case 4:
        //            uint32_t color;
        //            uint8_t r, g, b, a;
        //            color = *(Uint32 *)p;
        //
        //            r = (uint8_t)((color & surface->format->Rmask) >> (surface->format->Rshift));
        //            g = (uint8_t)((color & surface->format->Gmask) >> (surface->format->Gshift));
        //            b = (uint8_t)((color & surface->format->Bmask) >> (surface->format->Bshift));
        //            a = (uint8_t)((color & surface->format->Amask) >> (surface->format->Ashift));
        //            return (uint32_t)(r << 24 | g << 16 | b << 8 | a);
        //        default:
        //            return 0;
        //    }
    }

    //
    // To Pixels
    //

    void sk_to_pixels(sk_drawing_surface *surface, int *pixels, int sz)
    {
        if ( ! surface || ! surface->_data || surface->width * surface->height != sz) return;

        switch (surface->kind)
        {
            case SGDS_Window:
            {
                sk_window_be * window_be;
                window_be = static_cast<sk_window_be *>(surface->_data);

                // read pixels from the texture
                _sk_get_pixels_from_renderer(window_be->renderer, 0, 0, surface->width, surface->height, pixels);

                break;
            }

            case SGDS_Bitmap:
            {
                sk_bitmap_be * bitmap_be = static_cast<sk_bitmap_be *>(surface->_data);

                if ( ! bitmap_be->surface ) // read from texture
                {
                    _sk_bitmap_be_texture_to_pixels(bitmap_be, pixels, sz, surface->width, surface->height);
                }
                else
                {
                    // read from surface
                    for (int y = 0; y < surface->height; y++)
                    {
                        for(int x = 0; x < surface->width; x++)
                        {
                            pixels[y * surface->width + x] = static_cast<int>(_get_pixel(bitmap_be->surface, x, y));
                        }
                    }
                }
                break;
            }

            case SGDS_Unknown:
                break;
        }
    }


    //
    // Window change functions...
    //

    void sk_show_border(sk_drawing_surface *surface, bool border)
    {
        if ( ! surface || ! surface->_data ) return;

        sk_window_be * window_be;
        window_be = static_cast<sk_window_be *>(surface->_data);

        switch (surface->kind)
        {
            case SGDS_Window:
            {
                SDL_SetWindowBordered(window_be->window, border ? SDL_TRUE : SDL_FALSE);
                SDL_PumpEvents();
                break;
            }

            case SGDS_Bitmap:
                break;

            case SGDS_Unknown:
                break;
        }
    }

    void sk_show_fullscreen(sk_drawing_surface *surface, bool fullscreen)
    {
        if ( ! surface || ! surface->_data ) return;

        sk_window_be * window_be;
        window_be = static_cast<sk_window_be *>(surface->_data);

        switch (surface->kind)
        {
            case SGDS_Window:
            {
                SDL_SetWindowFullscreen(window_be->window, fullscreen ? SDL_WINDOW_FULLSCREEN_DESKTOP : 0);
                SDL_PumpEvents();
                break;
            }

            case SGDS_Bitmap:
                break;

            case SGDS_Unknown:
                break;
        }
    }

    void sk_resize(sk_drawing_surface *surface, int width, int height)
    {
        if ( ! surface || ! surface->_data ) return;

        sk_window_be * window_be;
        window_be = static_cast<sk_window_be *>(surface->_data);

        switch (surface->kind)
        {
            case SGDS_Window:
            {
                SDL_Rect dst = {0, 0, surface->width, surface->height};

                // Get old backing texture
                SDL_Texture * old = window_be->backing;

                // Set renderer to draw onto window
                SDL_SetRenderTarget(window_be->renderer, nullptr);

                // Change window size
                SDL_SetWindowSize(window_be->window, width, height);
                surface->width = width;
                surface->height = height;

                // Clear new window surface
                SDL_RenderSetClipRect(window_be->renderer, nullptr);
                SDL_SetRenderDrawColor(window_be->renderer, 120, 120, 120, 255);
                SDL_RenderClear(window_be->renderer);

                // Create new backing
                window_be->backing = SDL_CreateTexture(window_be->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
                
                // Copy across old display data
                SDL_SetRenderTarget(window_be->renderer, window_be->backing);
                SDL_RenderClear(window_be->renderer);
                SDL_RenderCopy(window_be->renderer, old, nullptr, &dst);
                SDL_RenderPresent(window_be->renderer);
                
                // Restore clipping
                if ( window_be->clipped )
                {
                    SDL_RenderSetClipRect(window_be->renderer, &window_be->clip);
                }
                
                // Delete old backing texture
                SDL_DestroyTexture(old);
                
                SDL_PumpEvents();
                break;
            }
                
            case SGDS_Bitmap:
                break;
                
            case SGDS_Unknown:
                break;
        }
    }
    
    // Saving a surface to a png file
    void png_user_warn(png_structp ctx, png_const_charp str)
    {
        //WriteLn(stderr, 'libpng: warning: ', str);
    }
    
    void png_user_error(png_structp ctx, png_const_charp str)
    {
        //WriteLn(stderr, 'libpng: error: ', str);
    }
    
    int sk_save_png(sk_drawing_surface * surface, const char *filename)
    {
        if ( ! surface || ! surface->_data || surface->width <= 0 || surface->height <= 0  ) return 0;
        
        FILE *fp;
        png_structp png_ptr;
        png_infop info_ptr;
        int i, colortype;
        unsigned long sz;
        png_bytepp row_pointers;
        uint8_t *pixels;
        
        // Opening output file
        fp = fopen(filename, "wb");
        
        if (fp == nullptr) return 0;
        
        // Initializing png structures and callbacks
        png_ptr = png_create_write_struct(PNG_LIBPNG_VER_STRING, nullptr, &png_user_error, &png_user_warn);
        if (png_ptr == nullptr)
        {
            fclose(fp);
            return 0;
        }
        
        info_ptr = png_create_info_struct(png_ptr);
        if (info_ptr == nullptr)
        {
            png_destroy_write_struct(&png_ptr, nullptr);
            fclose(fp);
            return 0;
        }
        
        png_init_io(png_ptr, fp);
        
        colortype = PNG_COLOR_TYPE_RGBA;
        png_set_IHDR( png_ptr, info_ptr,
                     (png_uint_32)surface->width, (png_uint_32)surface->height, 8, colortype,
                     PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
        
        // Writing the image
        png_write_info(png_ptr, info_ptr);
        
        png_set_packing(png_ptr);
        png_set_swap_alpha(png_ptr);
        png_set_bgr(png_ptr);
        
        // actually get the pixel data...
        sz = (unsigned long)(surface->width * surface->height) * sizeof(uint8_t);
        pixels = (uint8_t *) malloc(sizeof(uint8_t) * sz * 4);
        
        sk_to_pixels(surface, (int *)pixels, (int)sz);
        
        row_pointers = (png_bytepp)png_malloc(png_ptr, (unsigned long)surface->height * sizeof(png_bytep));
        
        for (i = 0; i < surface->height; i++)
        {
            row_pointers[i] = png_bytep(pixels + i * surface->width * 4);
        }
        
        png_write_image(png_ptr, row_pointers);
        png_write_end(png_ptr, info_ptr); // was ptr and nullptr
        
        // Cleaning out...
        png_free(png_ptr, row_pointers);
        png_destroy_write_struct(&png_ptr, &info_ptr);
        free(pixels);
        
        fclose(fp);
        return -1; // success
    }
    
    
    //--------------------------------------------------------------------------------------
    //
    // Images
    //
    //--------------------------------------------------------------------------------------
    
    
    sk_drawing_surface sk_create_bitmap(int width, int height)
    {
        internal_sk_init();
        if ( _sk_num_open_windows == 0 ) _sk_create_initial_window();
        
        sk_drawing_surface result = { SGDS_Unknown, 0, 0, nullptr };
        
        result.kind = SGDS_Bitmap;
        sk_bitmap_be *data = static_cast<sk_bitmap_be *>(malloc(sizeof(sk_bitmap_be)));
        
        result._data = data;
        result.width = width;
        result.height = height;
        
        data->clipped = false;
        data->clip = {0, 0, width, height};
        data->drawable = true;
        data->surface = nullptr;
        data->texture = static_cast<SDL_Texture **>(malloc(sizeof(SDL_Texture*) * _sk_num_open_windows));
        
        for (unsigned int i = 0; i < _sk_num_open_windows; i++)
        {
            data->texture[i] = SDL_CreateTexture(_sk_open_windows[i]->renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
            
            SDL_SetTextureBlendMode(data->texture[i], SDL_BLENDMODE_BLEND);
            
            _sk_set_renderer_target(i, data);
            SDL_SetRenderDrawColor(_sk_open_windows[i]->renderer, 255, 255, 255, 0);
            SDL_RenderClear(_sk_open_windows[i]->renderer);
            _sk_restore_default_render_target(i, data);
        }
        
        _sk_add_bitmap(data);
        return result;
    }
    
    sk_drawing_surface sk_load_bitmap(const char * filename)
    {
        internal_sk_init();
        sk_drawing_surface result = { SGDS_Unknown, 0, 0, nullptr };
        
        SDL_Surface *surface;
        
        surface = IMG_Load(filename);
        
        if ( ! surface ) {
            std::cout << "error loading image " << IMG_GetError() << std::endl;
            return result;
        }
        sk_bitmap_be *data = static_cast<sk_bitmap_be *>(malloc(sizeof(sk_bitmap_be)));
        
        result._data = data;
        
        // Allocate space for one texture per window
        if (_sk_num_open_windows > 0)
            data->texture = static_cast<SDL_Texture **>(malloc(sizeof(SDL_Texture*) * _sk_num_open_windows));
        else
            data->texture = nullptr;
        
        for (unsigned int i = 0; i < _sk_num_open_windows; i++)
        {
            // Create a texture for each window
            data->texture[i] = SDL_CreateTextureFromSurface(_sk_open_windows[i]->renderer, surface);
        }
        
        data->surface = surface;
        data->drawable = false;
        data->clipped = false;
        data->clip = {0,0,0,0};
        
        result.kind = SGDS_Bitmap;
        result.width = surface->w;
        result.height = surface->h;
        
        _sk_add_bitmap(data);
        
        return result;
    }
    
    //x, y is the position to draw the bitmap to. As bitmaps scale around their centre, (x, y) is the top-left of the bitmap IF and ONLY IF scale = 1.
    //Angle is in degrees, 0 being right way up
    //Centre is the point to rotate around, relative to the bitmap centre (therefore (0,0) would rotate around the centre point)
    void sk_draw_bitmap( sk_drawing_surface * src, sk_drawing_surface * dst, double * src_data, int src_data_sz, double * dst_data, int dst_data_sz, sk_renderer_flip flip )
    {
        if ( ! src || ! dst || src->kind != SGDS_Bitmap )
            return;
        
        if ( dst_data_sz != 7 )
            return;
        
        // dst_data must be 7 values
        double x         = dst_data[0];
        double y         = dst_data[1];
        double angle     = dst_data[2];
        double centre_x  = dst_data[3];
        double centre_y  = dst_data[4];
        double scale_x   = dst_data[5];
        double scale_y   = dst_data[6];
        
        if ( src_data_sz != 4)
            return;
        
        // src_data must be
        double src_x     = src_data[0];
        double src_y     = src_data[1];
        double src_w     = src_data[2];
        double src_h     = src_data[3];
        
        // Other locals
        SDL_Texture *srcT;
        
        // Create destination rect from scale values
        SDL_Rect dst_rect = {
            static_cast<int>(x - (src_w * scale_x / 2.0) + src_w/2.0),
            static_cast<int>(y - (src_h * scale_y / 2.0) + src_h/2.0), //fix the drawing position as scaling broke it
            static_cast<int>(src_w * scale_x),
            static_cast<int>(src_h * scale_y)
        }; //scale bitmap
        
        SDL_Rect src_rect = {
            static_cast<int>(src_x),
            static_cast<int>(src_y),
            static_cast<int>(src_w),
            static_cast<int>(src_h)
        };
        
        // check if any size is 0... and return if nothing is to be drawn
        if ( 0 == dst_rect.w || 0 == dst_rect.h || 0 == src_rect.w || 0 == src_rect.h ) return;
        
        // Adjust centre to be relative to the bitmap centre rather than top-left
        centre_x = (centre_x * scale_x) + dst_rect.w / 2.0f;
        centre_y = (centre_y * scale_y) + dst_rect.h / 2.0f;
        
        unsigned int count = _sk_renderer_count(dst);
        
        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(dst, i);
            
            // if its a window, dont use the renderer index to get the texture
            if (dst->kind == SGDS_Window)
            {
                unsigned int idx = static_cast<sk_window_be *>(dst->_data)->idx;
                
                srcT = static_cast<sk_bitmap_be *>(src->_data)->texture[ idx ];
            }
            else
                srcT = static_cast<sk_bitmap_be *>(src->_data)->texture[ i ];
            
            //Convert parameters to format SDL_RenderCopyEx expects
            SDL_Point centre = {
                static_cast<int>(centre_x),
                static_cast<int>(centre_y)
            };
            SDL_RendererFlip sdl_flip = static_cast<SDL_RendererFlip>((flip == sk_FLIP_BOTH) ? (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL) : flip); //SDL does not have a FLIP_BOTH
            
            //Render
            SDL_RenderCopyEx(renderer, srcT, &src_rect, &dst_rect, angle, &centre, sdl_flip);
            
            _sk_complete_render(dst, i);
        }
    }
    
    void sk_finalise_graphics()
    {
        // Close all bitmaps
        for (unsigned int i = _sk_num_open_bitmaps; i > 0; i--)
        {
            _sk_destroy_bitmap(_sk_open_bitmaps[i - 1]);
        }
        
        // Close all windows
        for (unsigned int i = _sk_num_open_windows; i > 0; i--)
        {
            _sk_destroy_window(_sk_open_windows[i - 1]);
        }
    }
}
