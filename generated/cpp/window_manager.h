//
// SplashKit Generated Window Manager C++ Code
// DO NOT MODIFY
//

#ifndef __window_manager_h
#define __window_manager_h

#include "window_manager.h"
#include "types.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _window_data;
typedef struct _window_data *window;
void clear_window(window wind, color clr);
void close_all_windows();
void close_current_window();
void close_window(const string &name);
void close_window(window wind);
window current_window();
bool current_window_has_border();
int current_window_height();
bool current_window_is_fullscreen();
point_2d current_window_position();
void current_window_toggle_border();
void current_window_toggle_fullscreen();
int current_window_width();
int current_window_x();
int current_window_y();
bool has_window(string caption);
bool is_current_window(window wind);
void move_current_window_to(int x, int y);
void move_window_to(const string &name, int x, int y);
void move_window_to(window wind, int x, int y);
window open_window(string caption, int width, int height);
void refresh_window(window wind);
void refresh_window(window wind, unsigned int target_fps);
void resize_current_window(int width, int height);
void resize_window(window wnd, int width, int height);
void set_current_window(const string &name);
void set_current_window(window wind);
string window_caption(window wind);
bool window_close_requested(const string &name);
bool window_close_requested(window wind);
bool window_has_border(const string &name);
bool window_has_border(window wnd);
bool window_has_focus(window wind);
int window_height(const string &name);
int window_height(window wind);
bool window_is_fullscreen(const string &name);
bool window_is_fullscreen(window wnd);
window window_named(string caption);
point_2d window_position(const string &name);
point_2d window_position(window wnd);
void window_set_icon(window wind, bitmap bmp);
void window_toggle_border(const string &name);
void window_toggle_border(window wnd);
void window_toggle_fullscreen(const string &name);
void window_toggle_fullscreen(window wnd);
int window_width(const string &name);
int window_width(window wind);
window window_with_focus();
int window_x(const string &name);
int window_x(window wnd);
int window_y(const string &name);
int window_y(window wnd);

#endif /* __window_manager_h */
