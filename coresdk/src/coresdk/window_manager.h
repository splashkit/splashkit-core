//
//  window_manager.hpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef window_manager_hpp
#define window_manager_hpp

#include "color.h"
#include <string>
using namespace std;

/// The Window type is used to refer to a window that you have opened
/// in SplashKit. You create new Windows using `OpenWindow` and they can
/// be closed using `CloseWindow`.
///
/// @class Window
/// @pointer_wrapper
/// @field pointer: pointer
typedef struct _window_data *window;

window open_window(string caption, int width, int height);

void close_window(window wind);

void close_window(string name);

/**
 * Close all of the windows that are currently open.
 */
void close_all_windows();

bool has_window(string caption);

window window_named(string caption);

window window_with_focus();

window current_window();

void set_current_window(window wind);

void set_current_window(string name);

bool window_close_requested(window wind);

bool window_close_requested(string name);

void refresh_window(window wind);

void clear_window(window wind, color clr);

/**
 * Returns the width of the window in pixels.
 *
 * @attribute class window
 * @attribute getter width
 */
int window_width(window wind);

/**
 * Returns the width of the window with the indicated name in pixels.
 *
 * @attribute class window
 * @attribute getter width
 */
int window_width(string name);

/**
 * Returns the height of the window in pixels.
 *
 * @attribute class window
 * @attribute getter height
 */
int window_height(window wind);

/**
 * Returns the height of the window with the indicated name in pixels.
 *
 * @attribute class window
 * @attribute getter height
 */
int window_height(string name);

void window_set_icon(window wind, bitmap bmp);

#endif /* window_manager_hpp */
