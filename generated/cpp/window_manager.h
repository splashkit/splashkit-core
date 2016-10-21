/*
 * SplashKit Window Manager
 *
 * This file is generated from the SplashKit source.
 * Modifying it will cause failures.
 *
 */

#ifndef __window_manager_h
#define __window_manager_h

#include "types.h"
#include "window_manager.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _window_data;
typedef struct _window_data *window;
void clear_window(window wind, color clr);
void close_all_windows();
void close_window(const string &name);
void close_window();
void close_window(window wind);
window current_window();
bool has_window(string caption);
void move_window(int x, int y);
void move_window(const string &name, int x, int y);
void move_window(window wind, int x, int y);
window open_window(string caption, int width, int height);
void refresh_window(window wind);
void resize_window(int width, int height);
void resize_window(window wnd, int width, int height);
void set_current_window(const string &name);
void set_current_window(window wind);
bool window_close_requested(const string &name);
bool window_close_requested(window wind);
bool window_has_border();
bool window_has_border(const string &name);
bool window_has_border(window wnd);
int window_height();
int window_height(const string &name);
int window_height(window wind);
bool window_is_fullscreen();
bool window_is_fullscreen(const string &name);
bool window_is_fullscreen(window wnd);
window window_named(string caption);
point_2d window_position();
point_2d window_position(const string &name);
point_2d window_position(window wnd);
void window_set_icon(window wind, bitmap bmp);
void window_toggle_border();
void window_toggle_border(const string &name);
void window_toggle_border(window wnd);
void window_toggle_fullscreen();
void window_toggle_fullscreen(const string &name);
void window_toggle_fullscreen(window wnd);
int window_width();
int window_width(const string &name);
int window_width(window wind);
window window_with_focus();
int window_x();
int window_x(const string &name);
int window_x(window wnd);
int window_y();
int window_y(const string &name);
int window_y(window wnd);

#endif /* __window_manager_h */
