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
#include "utility_functions.h"

using std::cerr;
using std::endl;

namespace splashkit_lib
{
    /**
     * @brief Paths to search for system fonts
     * 
     * Loaded in 
     */
    vector<string> _system_font_paths;

    /**
     * @brief Load the system font paths vector.
     * 
     * Forward declaration.
     */
    void load_system_font_paths();

    void sk_init_text()
    {
        // LOG(TRACE) << "About to initialise splashkit - text";
        if (TTF_Init() == -1)
        {
            std::cerr << "Text loading is broken." << std::endl;
            exit(-1);
        }

        load_system_font_paths();
    }

    void sk_finalize_text()
    {
        TTF_Quit();
    }

    sk_font_data* sk_load_font(const char * filename, int font_size)
    {
        internal_sk_init();

        sk_font_data *font = new sk_font_data;
        font->id = FONT_PTR;
        font->filename = filename;
        font->was_downloaded = false;

        sk_add_font_size(font, font_size);

        if ( font->_data.size() == 0 ) // failed to load font
        {
            font->id = NONE_PTR;
            delete(font);
            font = nullptr;
        }

        return font;
    }

    /**
     * Returns the font for the given size. Loads the font size if not loaded.
     */
    TTF_Font* _get_font(sk_font_data* font, int font_size)
    {
        TTF_Font* ttf_font = nullptr;

        if (VALID_PTR(font, FONT_PTR))
        {
            // If the font size already is exists
            if (font->_data.count(font_size) > 0)
            {
                ttf_font = static_cast<TTF_Font *>(font->_data[font_size]);
            }
            else
            {
                // Load the font for the given size.
                ttf_font = TTF_OpenFont(font->filename.c_str(), font_size);

                if (!ttf_font)
                {
                    cerr << "Error loading font " << SDL_GetError() << endl;
                    return nullptr;
                }

                if (font->_data.size() > 0)
                {
                    int font_style = TTF_GetFontStyle(static_cast<TTF_Font*>(font->_data.begin()->second));
                    TTF_SetFontStyle(ttf_font, font_style);
                }

                font->_data[font_size] = ttf_font;
            }
        }
        else
        {
            LOG(WARNING) << "Trying to _get_font for invalid font pointer.";
        }

        return ttf_font;
    }

    void sk_add_font_size(sk_font_data *font, int font_size)
    {
        _get_font(font, font_size);
    }

    bool sk_contains_valid_font(sk_font_data* font)
    {
        if ( INVALID_PTR(font, FONT_PTR) ) return false;

        for (auto const it : font->_data)
        {
            if (it.second)
            {
                return true;
            }
        }

        return false;
    }

    void sk_close_font(sk_font_data* font)
    {
        if (VALID_PTR(font, FONT_PTR))
        {
            for (auto const it : font->_data)
            {
                if (it.second)
                {
                    TTF_CloseFont(static_cast<TTF_Font *>(it.second));
                }
            }

            font->name = "";
            font->id = NONE_PTR;
        }
        else
        {
            cerr << "Trying to close font that is not a valid font." << endl;
        }
    }

    int sk_text_line_skip(sk_font_data* font, int font_size)
    {
        TTF_Font* ttf_font = _get_font(font, font_size);

        if (ttf_font)
        {
            return TTF_FontLineSkip(ttf_font);
        }
        else
        {
            return 2;
        }
    }

    int sk_text_size(sk_font_data* font, int font_size, const string &text, int* w, int* h)
    {
        TTF_Font* ttf_font = _get_font(font, font_size);

        if (ttf_font)
        {
            return TTF_SizeUTF8(ttf_font, text.c_str(), w, h);
        }
        else
        {
            *w = 8 * (int)text.length();
            *h = 8;
            return 0;
        }
    }

    int sk_text_height(sk_font_data* font, int font_size)
    {
        TTF_Font* ttf_font = _get_font(font, font_size);

        if (ttf_font)
        {
            return TTF_FontHeight(ttf_font);
        }
        else
        {
            return 8;
        }
    }

    void sk_set_font_style(sk_font_data* font, int font_size, int style)
    {
        TTF_Font* ttf_font = _get_font(font, font_size);

        if (ttf_font)
        {
            TTF_SetFontStyle(ttf_font, style);
        }
        else
        {
            cerr << "Error setting font style in sk_set_font_style" << endl;
        }
    }

    int sk_get_font_style(sk_font_data* font, int font_size)
    {
        TTF_Font* ttf_font = _get_font(font, font_size);

        if (ttf_font)
        {
            return TTF_GetFontStyle(ttf_font);
        }
        else
        {
            return 0;
        }
    }

    void _sk_draw_bitmap_text( sk_drawing_surface * surface,
                              double x, double y,
                              const char * text,
                              sk_color clr )
    {
        internal_sk_init();
        gfxPrimitivesSetFont(nullptr, 0, 0);
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
                      int font_size,
                      double x, double y,
                      const char * text,
                      sk_color clr)
    {
        if (!font) // draw bitmap based text -- no font
        {
            _sk_draw_bitmap_text(surface, x, y, text, clr);
            return;
        }

        TTF_Font* ttf_font = _get_font(font, font_size);

        if (!ttf_font) return; // error with font

        SDL_Surface * text_surface = NULL;
        SDL_Texture * text_texture = NULL;

        SDL_Color sdl_color;
        sdl_color.r = static_cast<Uint8>(clr.r * 255);
        sdl_color.g = static_cast<Uint8>(clr.g * 255);
        sdl_color.b = static_cast<Uint8>(clr.b * 255);
        sdl_color.a = static_cast<Uint8>(clr.a * 255);
        
        text_surface = TTF_RenderUTF8_Blended(static_cast<TTF_Font *>(font->_data[font_size]), text, sdl_color);
        
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

    string system_font_path()
    {
        string base_fp = base_fs_path();

        #if __linux__
            base_fp += "usr/share/fonts";
        #elif WINDOWS
            base_fp = get_env_var("SYSTEMROOT") + "\\Fonts";
            //LOG(TRACE) << "base fp: " << base_fp;
        #else
            base_fp += "System/Library/Fonts";
        #endif

        return base_fp;
    }

    void load_system_font_paths()
    {
        _system_font_paths = scan_dir_recursive(system_font_path());
    }

    string sk_find_system_font_path(string name)
    {
        internal_sk_init();
        
        string path, lcpath;
        for(string dir : _system_font_paths)
        {
            path = path_from( { dir }, name);
            lcpath = path_from( { dir }, to_lower(name));

            // LOG(TRACE) << "Loading font at system path: " << path;

            if ( file_exists( path ))
            {
                return path;
            }
            else if ( file_exists( lcpath ))
            {
                return lcpath;
            }

            if ( file_exists( path + ".ttf" ))
            {
                return path + ".ttf";
            }
            else if ( file_exists( lcpath + ".ttf" ))
            {
                return lcpath + ".ttf";
            }
        }

        return "";
    }
}
