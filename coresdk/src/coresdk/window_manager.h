//
//  window_manager.hpp
//  splashkit
//
//  Created by Andrew Cain on 15/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

/**
 * @header Window Manager
 * @author Andrew Cain
 * @brief Window Manager in SplashKit can be used create, and manipulate
 *        graphics windows
 *
 * @attribute static window_manager
 */

#ifndef window_manager_hpp
#define window_manager_hpp

#include "color.h"
#include <string>
using namespace std;


/**
 * The Window type is used to refer to a window that you have opened
 * in SplashKit. You create new Windows using `OpenWindow` and they can
 * be closed using `CloseWindow`.
 *
 *   - opened with `open_window`
 *
 *   - and must be released using `close_window` (to close a specific
 *     window) or `delete_all_windows` (to close all loaded
 *     windows).
 *
 * @attribute class window
 */
typedef struct _window_data *window;

/**
 * Opens a new graphics window. The supplied `caption` is used to
 * name and identify the window. The supplied `width` and `height` indicate
 * the size of the window. The window can be retrieved by passing `caption`
 * to the `window_named` function.
 *
 * @attribute class         window
 * @attribute constructor   true
 */
window open_window(string caption, int width, int height);

/**
 * Closes and frees the graphics window supplied in `wind`.
 *
 * @attribute class           window
 * @attribute destructor      true
 * @attribute self            wind
 */
void close_window(window wind);

/**
 * Closes and frees the graphics window identified by `name`.
 *
 * @attribute class         window
 * @attribute destructor    true
 */
void close_window(const string &name);

/**
 * Releases all of the windows which have been loaded.
 *
 * @attribute class   window
 * @attribute method  free_all_window
 */
void close_all_windows();

/**
 * Determines if SplashKit has a window loaded with the supplied name.
 * This checks against all windows loaded, those loaded without a name
 * are assigned the filename as a default. If this returns `false`, you may
 * want to use `load_window` to load in a specific window and give
 * it the desired name.
 *
 * @param caption The name of the window to check for.
 *
 * @returns Returns `true` if there is a window with the given `caption` 
 *          which has has been loaded.
 *
 */
bool has_window(string caption);


/**
 * Retrieves a `music` that has been loaded into SplashKit.
 *
 * @param name  The name of the music file to return.
 *
 * @returns Returns the `music` that has been loaded with the specified
 *          `name` using `load_music`.
 */
window window_named(string caption);

window window_with_focus();

window current_window();

void set_current_window(window wind);

void set_current_window(const string &name);

bool window_close_requested(window wind);

bool window_close_requested(const string &name);

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
int window_width(const string &name);

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
int window_height(const string &name);

void window_set_icon(window wind, bitmap bmp);

#endif /* window_manager_hpp */
