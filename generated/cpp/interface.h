//
// SplashKit Generated Interface C++ Code
// DO NOT MODIFY
//

#ifndef __interface_h
#define __interface_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

void add_column(int width);
void add_column_relative(double width);
bool bitmap_button(bitmap bmp);
bool bitmap_button(bitmap bmp, const rectangle &rect);
bool bitmap_button(bitmap bmp, const rectangle &rect, drawing_options opts);
bool bitmap_button(bitmap bmp, drawing_options opts);
bool bitmap_button(const string &label_text, bitmap bmp);
bool bitmap_button(const string &label_text, bitmap bmp, drawing_options opts);
bool button(const string &text, const rectangle &rect);
bool button(const string &text);
bool button(const string &label_text, const string &text);
bool checkbox(const string &text, const bool &value, const rectangle &rect);
bool checkbox(const string &text, const bool &value);
bool checkbox(const string &label_text, const string &text, const bool &value);
color color_slider(const color &clr, const rectangle &rect);
color color_slider(const color &clr);
color color_slider(const string &label_text, const color &clr);
void disable_interface();
void draw_interface();
void enable_interface();
void end_inset(const string &name);
void end_panel(const string &name);
void end_popup(const string &name);
void end_treenode(const string &label_text);
void enter_column();
int get_interface_label_width();
bool header(const string &label_text);
color hsb_color_slider(const color &clr, const rectangle &rect);
color hsb_color_slider(const color &clr);
color hsb_color_slider(const string &label_text, const color &clr);
bool interface_enabled();
void interface_style_panel(const rectangle &initial_rectangle);
void label_element(const string &text);
void label_element(const string &text, const rectangle &rect);
bool last_element_changed();
bool last_element_confirmed();
void leave_column();
float number_box(const float &value, float step, const rectangle &rect);
float number_box(const float &value, float step);
float number_box(const string &label_text, const float &value, float step);
void open_popup(const string &name);
void paragraph(const string &text);
void paragraph(const string &text, const rectangle &rect);
void reset_layout();
void set_interface_accent_color(color clr, float contrast);
void set_interface_border_color(color clr);
void set_interface_colors_auto(color main_clr, color accent_clr, float contrast, float accent_contrast, float border_contrast);
void set_interface_element_color(color clr, float contrast);
void set_interface_element_shadows(int radius, color clr, point_2d offset);
void set_interface_font(const string &fnt);
void set_interface_font(font fnt);
void set_interface_font_size(int size);
void set_interface_label_width(int width);
void set_interface_panel_shadows(int radius, color clr, point_2d offset);
void set_interface_root_text_color(color clr);
void set_interface_shadows(int radius, color clr, point_2d offset);
void set_interface_spacing(int spacing, int padding);
void set_interface_style(interface_style style);
void set_interface_style(interface_style style, color clr);
void set_interface_text_color(color clr);
void set_layout_height(int height);
void single_line_layout();
float slider(const float &value, float min_value, float max_value, const rectangle &rect);
float slider(const float &value, float min_value, float max_value);
float slider(const string &label_text, const float &value, float min_value, float max_value);
void split_into_columns(int count);
void split_into_columns(int count, int last_width);
void split_into_columns_relative(int count, double last_width);
void start_custom_layout();
void start_inset(const string &name, const rectangle &rect);
void start_inset(const string &name, int height);
bool start_panel(const string &name, rectangle initial_rectangle);
bool start_popup(const string &name);
bool start_treenode(const string &label_text);
string text_box(const string &value);
string text_box(const string &value, const rectangle &rect);
string text_box(const string &label_text, const string &value);

#endif /* __interface_h */
