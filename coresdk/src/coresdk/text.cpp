//
//  text.cpp
//  splashkit
//
//  Created by Andrew Cain on 25/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "text.h"
#include "backend_types.h"
#include "resources.h"
#include "utility_functions.h"

#include "text_driver.h"
#include "graphics_driver.h"

#include <cstdio>

#include <map>
namespace splashkit_lib
{
    static map<string, font> _fonts;

    bool has_font(font fnt)
    {
        return VALID_PTR(fnt, FONT_PTR) and _fonts.count(fnt->name) > 0;
    }

    bool has_font(string name)
    {
        if ( _fonts.count(name) <= 0 ) return false;
        return has_font(_fonts.find(name)->second);
    }

    bool font_has_size(font fnt, int font_size)
    {
        if (has_font(fnt))
        {
            return fnt->_data.count(font_size) > 0;
        }
        else
        {
            LOG(WARNING) << "Asking if font has size on invalid font.";
        }

        return false;
    }

    bool font_has_size(const string &name, int font_size)
    {
        return font_has_size(font_named(name), font_size);
    }

    void font_load_size(font fnt, int font_size)
    {
        if (has_font(fnt))
        {
            sk_add_font_size(fnt, font_size);
        }
        else
        {
            LOG(WARNING) << "font_load_size failed: font does not exist.";
        }
    }

    void font_load_size(const string &name, int font_size)
    {
        return font_load_size(font_named(name), font_size);
    }

    font font_named(string name)
    {
        if (has_font(name))
        {
            return _fonts[name];
        }
        else
        {
            string filename = path_to_resource(name, FONT_RESOURCE);

            if ( file_exists(filename) or file_exists(name))
                return load_font(name, name);
            return nullptr;
        }
    }

    void free_font(font fnt)
    {
        if ( VALID_PTR(fnt, FONT_PTR) )
        {
            notify_of_free(fnt);
            
            if (fnt->was_downloaded && file_exists(fnt->filename) )
            {
                remove(fnt->filename.c_str());
            }
            _fonts.erase(fnt->name);
            sk_close_font(fnt);
            fnt->id = NONE_PTR;  // ensure future use of this pointer will fail...
            delete(fnt);
        }
        else
        {
            LOG(WARNING) << "Delete font called without valid font";
        }
    }

    void free_all_fonts()
    {
        string name;

        size_t sz = _fonts.size();

        for(size_t i = 0; i < sz; i++)
        {
            font fnt = _fonts.begin()->second;
            if (VALID_PTR(fnt, FONT_PTR))
            {
                free_font(fnt);
            }
            else
            {
                LOG(WARNING) << "Fonts contained an invalid pointer";
                _fonts.erase(_fonts.begin());
            }
        }
    }

    void set_font_style(font fnt, font_style style)
    {
        if (!VALID_PTR(fnt, FONT_PTR))
        {
            LOG(WARNING) << "Attempting to set style on invalid font.";
            return;
        }

        for (auto const it : fnt->_data)
        {
            sk_set_font_style(fnt, it.first, style);
        }
    }

    void set_font_style(const string &name, font_style style)
    {
        set_font_style(font_named(name), style);
    }

    font_style get_font_style(font fnt)
    {
        if (!VALID_PTR(fnt, FONT_PTR))
        {
            LOG(WARNING) << "Attempting to get font style on invalid font.";
            return NORMAL_FONT; // Add NONE to font_style enum?
        }

        int font_size = fnt->_data.begin()->first;

        // Should the backend not just return a font_style instead of an int?
        return static_cast<font_style>(sk_get_font_style(fnt, font_size));
    }

    font_style get_font_style(const string &name)
    {
        return get_font_style(font_named(name));
    }

    font load_font(const string &name, const string &filename)
    {
        if (has_font(name)) return font_named(name);

        string file_path = filename;

        if ( ! file_exists(file_path) )
        {
            file_path = path_to_resource(filename, FONT_RESOURCE);

            if ( ! file_exists(file_path) )
            {
                file_path = path_to_resource(filename + ".ttf", FONT_RESOURCE);

                if ( ! file_exists(file_path) )
                {
                    LOG(WARNING) << cat({ "Unable to locate file for ", name, " (", file_path, ")"});
                    return nullptr;
                }
            }
        }

        font result = sk_load_font(file_path.c_str(), 64);

        if (!sk_contains_valid_font(result))
        {
            delete result;
            result = nullptr;
            LOG(WARNING) << "LoadFont failed: " + name + " (" + file_path + ")";
        } else
        {
            _fonts[name] = result;
            result->name = name; // Need to clean this up, name is set to filename in sk_load_font
        }

        return result;
    }

    void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts)
    {
        if ( fnt != nullptr and INVALID_PTR(fnt, FONT_PTR) )
        {
            LOG(WARNING) << "Error attempting to draw text with invalid font.";
            return;
        }

        if (text.length() < 1) return;

        xy_from_opts(opts, x, y);

        sk_draw_text(to_surface_ptr(opts.dest), fnt, font_size, x, y, text.c_str(), clr);
    }

    void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_defaults());
    }

    void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, font_named(fnt), font_size, x, y, opts);
    }

    void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y)
    {
        draw_text(text, clr, font_named(fnt), font_size, x, y, option_defaults());
    }

    void draw_text(const string &text, const color &clr, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, nullptr, 0, x, y, opts);
    }

    void draw_text(const string &text, const color &clr, double x, double y)
    {
        draw_text(text, clr, x, y, option_defaults());
    }

    void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(wnd, opts));
    }
    
    void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(wnd));
    }
    
    void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(wnd, opts));
    }
    
    void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(wnd));
    }
    
    void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, x, y, option_draw_to(wnd, opts));
    }
    
    void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y)
    {
        draw_text(text, clr, x, y, option_draw_to(wnd));
    }

    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(bmp, opts));
    }
    
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(bmp));
    }
    
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(bmp, opts));
    }
    
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y)
    {
        draw_text(text, clr, fnt, font_size, x, y, option_draw_to(bmp));
    }
    
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y, const drawing_options &opts)
    {
        draw_text(text, clr, x, y, option_draw_to(bmp, opts));
    }
    
    void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y)
    {
        draw_text(text, clr, x, y, option_draw_to(bmp));
    }
    
    int text_width(const string &text, font fnt, int font_size)
    {
        if ( fnt != nullptr && INVALID_PTR(fnt, FONT_PTR) )
        {
            LOG(WARNING) << "Attempting to get string width with invalid font";
            return 0;
        }

        int w = 0, h = 0;
        sk_text_size(fnt, font_size, text.c_str(), &w, &h);
        return w;
    }

    int text_width(const string &text, const string &fnt, int font_size)
    {
        return text_width(text, font_named(fnt), font_size);
    }

    int text_height(const string &text, font fnt, int font_size)
    {
        if ( INVALID_PTR(fnt, FONT_PTR) )
        {
            LOG(WARNING) << "Attempting to get string height with invalid font";
            return 0;
        }

        int w = 0, h = 0;
        sk_text_size(fnt, font_size, text.c_str(), &w, &h);
        return h;
    }

    int text_height(const string &text, const string &fnt, int font_size)
    {
        return text_height(text, font_named(fnt), font_size);
    }
}
