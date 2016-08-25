//
//  text.hpp
//  splashkit
//
//  Created by Andrew Cain on 25/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef text_hpp
#define text_hpp

#include "types.h"
#include "drawing_options.h"

#include <string>
using namespace std;

/// Loads a font from file with the specified side. Fonts must be freed using
/// the FreeFont routine once finished with. Once the font is loaded you
/// can set its style using SetFontStyle. Fonts are then used to draw and
/// measure text in your programs.
///
/// @lib
/// @sn loadFontFile:%s size:%s
///
/// @class Font
/// @constructor
/// @csn initWithFontName:%s andSize:%s

void set_font_style(font fnt, font_style style);

void set_font_style(string name, font_style style);

font_style get_font_style(font fnt);

font_style get_font_style(string name);

font load_font(string name, string filename);

void free_font(font fnt);

void free_all_fonts();

void font_load_size(font fnt, int font_size);

void font_load_size(string name, int font_size);

bool has_font(font fnt);

bool has_font(string name);

bool font_has_size(font fnt, int font_size);

bool font_has_size(string name, int font_size);

font font_named(string name);

void draw_text(string text, color clr, font fnt, int font_size, float x, float y, drawing_options opts);

void draw_text(string text, color clr, font fnt, int font_size, float x, float y);

void draw_text(string text, color clr, string fnt, int font_size, float x, float y, drawing_options opts);

void draw_text(string text, color clr, string fnt, int font_size, float x, float y);

void draw_text(string text, color clr, float x, float y, drawing_options opts);

void draw_text(string text, color clr, float x, float y);

int text_length(string text, font fnt, int font_size);
int text_length(string text, string fnt, int font_size);

#endif /* text_hpp */
