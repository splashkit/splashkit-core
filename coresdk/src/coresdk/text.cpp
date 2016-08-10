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

#include <map>

static map<string, font> _fonts;

struct _font_data
{
    string              name;
    pointer_identifier  id;
    sk_font_data        font;
};

bool has_font(string name)
{
    return _fonts.count(name) > 0;
}

font font_named(string name)
{
    if (has_font(name))
        return _fonts[name];
    else
        return nullptr;
}

void free_font(font fnt)
{
    if ( VALID_PTR(fnt, FONT_PTR) )
    {
        _fonts.erase(fnt->name);
        sk_close_font(&fnt->font);
        fnt->id = NONE_PTR;  // ensure future use of this pointer will fail...
        delete(fnt);
    }
    else
    {
        raise_warning("Delete font called without valid font");
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
            raise_warning("Fonts contained an invalid pointer");
            _fonts.erase(_fonts.begin());
        }
    }
}

font load_font(string name, string filename, int size)
{
    if (has_font(name)) return font_named(name);
    
    font result;

    string file_path = path_to_resource(filename, FONT_RESOURCE);
    
    if ( ! file_exists(file_path) )
    {
        file_path = path_to_resource(filename + ".ttf", FONT_RESOURCE);
    
        if ( ! file_exists(file_path) )
        {
            raise_warning(cat({ "Unable to locate file for ", name, " (", file_path, ")"}));
            return nullptr;
        }
    }
    
    result = new _font_data;
    result->id = FONT_PTR;
    result->name = name;
    
    result->font = sk_load_font(file_path.c_str(), size);
    
    if ( ! result->font._data)
    {
        delete result;
        result = nullptr;
        raise_warning("LoadFont failed: " + name + " (" + file_path + ")");
    }

    return result;
}

void _print_strings(void *dest, font fnt, string str, rectangle rc, color fg_clr, color bg_clr, font_alignment flags)
{
    if (bg_clr.a > 0)
    {
        sk_fill_aa_rect(to_surface_ptr(dest), bg_clr, rc.x, rc.y, rc.width, rc.height);
    }
    
    sk_draw_text(to_surface_ptr(dest), &fnt->font, rc.x, rc.y, str.c_str(), fg_clr);
}

void draw_text(string text, color clr, font fnt, float x, float y, drawing_options opts)
{
    rectangle rect;
    if ( ! VALID_PTR(fnt, FONT_PTR) )
    {
        raise_warning("Error attempting to draw text with invalid font.");
        return;
    }
    
    if (text.length() < 1) return;

    xy_from_opts(opts, x, y);
    rect.x = x;
    rect.y = y;

    rect.width = -1;
    rect.height = -1;
    
    _print_strings(opts.dest, fnt, text, rect, clr, COLOR_TRANSPARENT, ALIGN_LEFT);
}

void draw_text(string text, color clr, font fnt, float x, float y)
{
    draw_text(text, clr, fnt, x, y, option_defaults());
}
