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

bool has_window(string caption);

window window_named(string caption);

void refresh_window(window wind);

void clear_window(window wind, color clr);

#endif /* window_manager_hpp */
