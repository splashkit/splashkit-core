//
// SplashKit Generated Text C++ Code
// DO NOT MODIFY
//

#ifndef __text_h
#define __text_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

/**
* 
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The name of the `font` which will be used to draw the text
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
/**
* 
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The name of the `font` which will be used to draw the text
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
/**
* 
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text(const string &text, const color &clr, double x, double y);
/**
* 
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text(const string &text, const color &clr, double x, double y, const drawing_options &opts);
/**
* 
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The `font` to be used to draw the text.
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y);
/**
* 
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The `font` to be used to draw the text.
* @param font_size The desired size of the font.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
/**
* 
* @param bmp The bitmap to draw to
* @param text The text string to be written to the bitmap.
* @param clr The desired `color` of the text to be written.
* @param fnt The name of the `font` which will be used to draw the text
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
/**
* 
* @param bmp The bitmap to draw to
* @param text The text string to be written to the bitmap.
* @param clr The desired `color` of the text to be written.
* @param fnt The name of the `font` which will be used to draw the text
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
/**
* 
* @param bmp The bitmap to draw to
* @param text The text string to be written to the bitmap.
* @param clr The desired `color` of the text to be written.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y);
/**
* 
* @param bmp The bitmap to draw to
* @param text The text string to be written to the bitmap.
* @param clr The desired `color` of the text to be written.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y, const drawing_options &opts);
/**
* 
* @param bmp The bitmap to draw to
* @param text The text string to be written to the bitmap.
* @param clr The desired `color` of the text to be written.
* @param fnt The `font` to be used to draw the text.
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y);
/**
* 
* @param bmp The bitmap to draw to
* @param text The text string to be written to the bitmap.
* @param clr The desired `color` of the text to be written.
* @param fnt The `font` to be used to draw the text.
* @param font_size The desired size of the font.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
/**
* 
* @param wnd The window to draw to
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The name of the `font` which will be used to draw the text
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
/**
* 
* @param wnd The window to draw to
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The name of the `font` which will be used to draw the text
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
/**
* 
* @param wnd The window to draw to
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y);
/**
* 
* @param wnd The window to draw to
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y, const drawing_options &opts);
/**
* 
* @param wnd The window to draw to
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The `font` to be used to draw the text.
* @param font_size The size of the font which will be drawn.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
*
*/
void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y);
/**
* 
* @param wnd The window to draw to
* @param text The text string to be written to the window.
* @param clr The desired `color` of the text to be written.
* @param fnt The `font` to be used to draw the text.
* @param font_size The desired size of the font.
* @param x The x location to draw the text.
* @param y The y location to draw the text.
* @param opts The `drawing_options` which provide extra information for how to draw the text.
*
*/
void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
/**
* 
* @param name The name of the `font` to be checked.
* @param font_size The size to check.
* @return Returns true if there is a font with the supplied name that has the supplied size.
*/
bool font_has_size(const string &name, int font_size);
/**
* 
* @param fnt The `font` to be checked.
* @param font_size The size to check.
* @return Returns true if the supplied `font` has the supplied size.
*/
bool font_has_size(font fnt, int font_size);
/**
* 
* @param name The name of the `font` to load the size for.
* @param font_size The desired size of the `font`.
*
*/
void font_load_size(const string &name, int font_size);
/**
* 
* @param fnt The `font` to load the size for.
* @param font_size The desired size of the `font`.
*
*/
void font_load_size(font fnt, int font_size);
/**
* 
* @param name The name of the font to find.
* @return Returns the font that has the supplied name.
*/
font font_named(string name);
/**
* 

*
*/
void free_all_fonts();
/**
* 
* @param fnt The font to be freed.
*
*/
void free_font(font fnt);
/**
* 
* @param name The name of the font to return the style of.
* @return Returns the current `font_style` for the `font`.
*/
font_style get_font_style(const string &name);
/**
* 
* @param fnt The `font` to return the style of.
* @return Returns the current `font_style` for the `font`.
*/
font_style get_font_style(font fnt);
/**
* Searches for and (if found) returns a default system font. Otherwise defaults to the in-built font.

* @return Returns the `font` found, or the in-built font if not
*/
font get_system_font();
/**
* 
* @param fnt The `font` to check if loaded.
* @return Returns true if the specified `font` is loaded.
*/
bool has_font(font fnt);
/**
* 
* @param name The name of `font` to check if loaded.
* @return Returns whether there is a loaded font with the supplied name.
*/
bool has_font(string name);
/**
* 
* @param name The name of the `font` to be loaded from file.
* @param filename The name of the file to load the `font` from.
* @return Returns a new `font` object.
*/
font load_font(const string &name, const string &filename);
/**
* 
* @param name The name of the `font` to set the style of.
* @param style The new style for the `font`.
*
*/
void set_font_style(const string &name, font_style style);
/**
* 
* @param fnt The `font` to set the style of.
* @param style The new style for the `font`.
*
*/
void set_font_style(font fnt, font_style style);
/**
* 
* @param text The text string to check the length of.
* @param fnt The font used for the text.
* @param font_size The size of the font used for the text.
* @return Returns the height of the text as an integer.
*/
int text_height(const string &text, const string &fnt, int font_size);
/**
* 
* @param text The text string to check the length of.
* @param fnt The font used for the text.
* @param font_size The size of the font used for the text.
* @return Returns the height of the text as an integer.
*/
int text_height(const string &text, font fnt, int font_size);
/**
* 
* @param text The text string to check the length of.
* @param fnt The font used for the text.
* @param font_size The size of the font used for the text.
* @return Returns the width of the text as an integer.
*/
int text_width(const string &text, const string &fnt, int font_size);
/**
* 
* @param text The text string to check the length of.
* @param fnt The font used for the text.
* @param font_size The size of the font used for the text.
* @return Returns the width of the text as an integer.
*/
int text_width(const string &text, font fnt, int font_size);

#endif /* __text_h */
