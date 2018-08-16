//
// SplashKit Generated Text C++ Code
// DO NOT MODIFY
//

#ifndef __text_h
#define __text_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
void draw_text(const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
void draw_text(const string &text, const color &clr, double x, double y);
void draw_text(const string &text, const color &clr, double x, double y, const drawing_options &opts);
void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y);
void draw_text(const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y);
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, double x, double y, const drawing_options &opts);
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y);
void draw_text_on_bitmap(bitmap bmp, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y);
void draw_text_on_window(window wnd, const string &text, const color &clr, const string &fnt, int font_size, double x, double y, const drawing_options &opts);
void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y);
void draw_text_on_window(window wnd, const string &text, const color &clr, double x, double y, const drawing_options &opts);
void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y);
void draw_text_on_window(window wnd, const string &text, const color &clr, font fnt, int font_size, double x, double y, const drawing_options &opts);
bool font_has_size(const string &name, int font_size);
bool font_has_size(font fnt, int font_size);
void font_load_size(const string &name, int font_size);
void font_load_size(font fnt, int font_size);
font font_named(string name);
void free_all_fonts();
void free_font(font fnt);
font_style get_font_style(const string &name);
font_style get_font_style(font fnt);
bool has_font(font fnt);
bool has_font(string name);
font load_font(const string &name, const string &filename);
void set_font_style(const string &name, font_style style);
void set_font_style(font fnt, font_style style);
int text_height(const string &text, const string &fnt, int font_size);
int text_height(const string &text, font fnt, int font_size);
int text_width(const string &text, const string &fnt, int font_size);
int text_width(const string &text, font fnt, int font_size);

#endif /* __text_h */
