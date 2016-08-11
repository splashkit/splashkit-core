//
//  SGSDL2Text.h
//  sgsdl2
//
//  Created by James Armstrong on 11/12/2013.
//

#include <iostream>

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#else
#include <SDL.h>
#include <SDL_ttf.h>
#include <SDL2_gfxPrimitives.h>
#endif

#include "text_driver.h"
#include "graphics_driver.h"
#include "backend_types.h"
#include "core_driver.h"

void sk_init_text()
{
    if (TTF_Init() == -1)
    {
        std::cerr << "Text loading is broken." << std::endl;
        exit(-1);
    }
}

void sk_finalize_text()
{
    TTF_Quit();
}

sk_font_data sk_load_font(const char * filename, int font_size)
{
    internal_sk_init();

    sk_font_data font;
    font.kind = SKFT_TTF;
    font._data = TTF_OpenFont(filename, font_size);
    if (!font._data)
    {
        cerr << "Error loading font " << SDL_GetError() << endl;
    }
    return font;
}

void sk_close_font(sk_font_data* font)
{
    if (font && font->_data)
    {
        TTF_CloseFont(static_cast<TTF_Font *>(font->_data));
        font->kind = SKFT_UNKNOWN;
        font->_data = NULL;
    }
}

int sk_text_line_skip(sk_font_data* font)
{
    if (font && font->_data)
        return TTF_FontLineSkip(static_cast<TTF_Font *>(font->_data));
    else
        return 0;
}

int sk_text_size(sk_font_data* font, char* text, int* w, int* h)
{
    if (font && font->_data)
        return TTF_SizeText(static_cast<TTF_Font *>(font->_data), text, w, h);
    else
        return 0;
}

void sk_set_font_style(sk_font_data* font, int style)
{
    if (font && font->_data) 
    {
        TTF_SetFontStyle(static_cast<TTF_Font *>(font->_data), style);
    }
    else {
        cerr << "Error setting font style in sk_set_font_style" << endl;
    }
}

int sk_get_font_style(sk_font_data* font)
{
    if (font && font->_data)
        return TTF_GetFontStyle(static_cast<TTF_Font *>(font->_data));
    else
        return 0;
}

void _sk_draw_bitmap_text( sk_drawing_surface * surface,
                               float x, float y,
                               const char * text,
                               sk_color clr )
{
    internal_sk_init();
    unsigned int count = _sk_renderer_count(surface);

    for (unsigned int i = 0; i < count; i++)
    {
        SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
        stringRGBA(renderer,
                   static_cast<Sint16>(x),
                   static_cast<Sint16>(y),
                   text,
                   static_cast<Uint8>(clr.r * 255),
                   static_cast<Uint8>(clr.g * 255),
                   static_cast<Uint8>(clr.b * 255),
                   static_cast<Uint8>(clr.a * 255) );
        _sk_complete_render(surface, i);
    }

}

void sk_draw_text(
        sk_drawing_surface * surface,
        sk_font_data* font,
        float x, float y,
        const char * text,
        sk_color clr)
{
    if (!font) // draw bitmap based text -- no font
    {
        _sk_draw_bitmap_text(surface, x, y, text, clr);
        return;
    }
    if (! (font && font->_data)) return; // error with font

    SDL_Surface * text_surface = NULL;
    SDL_Texture * text_texture = NULL;

    SDL_Color sdl_color;
    sdl_color.r = static_cast<Uint8>(clr.r * 255);
    sdl_color.g = static_cast<Uint8>(clr.g * 255);
    sdl_color.b = static_cast<Uint8>(clr.b * 255);
    sdl_color.a = static_cast<Uint8>(clr.a * 255);

    text_surface = TTF_RenderText_Blended(static_cast<TTF_Font *>(font->_data), text, sdl_color);

    if (text_surface == NULL)
    {
        // fail
    }
    else
    {
        unsigned int count = _sk_renderer_count(surface);

        for (unsigned int i = 0; i < count; i++)
        {
            SDL_Renderer *renderer = _sk_prepared_renderer(surface, i);
            text_texture = SDL_CreateTextureFromSurface(renderer, text_surface);
            if (text_texture == NULL)
            {
                // fail
            }
            else
            {
                SDL_Rect rect;
                rect.x = static_cast<int>(x);
                rect.y = static_cast<int>(y);
                rect.w = text_surface->w;
                rect.h = text_surface->h;

                SDL_RenderCopy(renderer, text_texture, NULL, &rect);

                _sk_complete_render(surface, i);

                SDL_DestroyTexture(text_texture);
            }
        }
        SDL_FreeSurface(text_surface);
    }
}
