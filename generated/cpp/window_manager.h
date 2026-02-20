//
// SplashKit Generated Window Manager C++ Code
// DO NOT MODIFY
//

#ifndef __window_manager_h
#define __window_manager_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;

struct _window_data;
typedef struct _window_data *window;
/**
* clears a window to the specified color given in `clr`
* @param wind the `window` to clear
* @param clr the `color` to clear the window to.
*
*/
void clear_window(window wind, color clr);
/**
* Releases all of the windows which have been loaded.

*
*/
void close_all_windows();
/**
* Closes and frees the current window.

*
*/
void close_current_window();
/**
* Closes and frees the graphics window identified by `name`.
* @param name The name (caption) of the window to close
*
*/
void close_window(const string &name);
/**
* Closes and frees the graphics window supplied in `wind`.
* @param wind The window to close
*
*/
void close_window(window wind);
/**
* Returns the window that you are currently interacting with. This will be
* the default window for drawing options, and events.

* @return The current window
*/
window current_window();
/**
* Indicate if the current window has a border.

* @return True if the window has a border
*/
bool current_window_has_border();
/**
* Returns the height of the current window.

* @return The height of the current window
*/
int current_window_height();
/**
* Is the current window currently fullscreen?

* @return True when the window is fullscreen
*/
bool current_window_is_fullscreen();
/**
* The location of the current window.

* @return Its location on the displays
*/
point_2d current_window_position();
/**
* Toggle the current window border.

*
*/
void current_window_toggle_border();
/**
* Toggle the fullscreen property of the current window

*
*/
void current_window_toggle_fullscreen();
/**
* Returns the width of the current window.

* @return The width of the current window
*/
int current_window_width();
/**
* The x location of the current window on the displays.

* @return Its location on the displays
*/
int current_window_x();
/**
* The y location of the current window on the displays.

* @return Its location on the displays
*/
int current_window_y();
/**
* Determines if SplashKit has a window loaded with the supplied name.
* This checks against all windows loaded, those loaded without a name
* are assigned the filename as a default. If this returns `false`, you may
* want to use `load_window` to load in a specific window and give
* it the desired name.
* @param caption The name of the window to check for.
* @return Returns `true` if there is a window with the given `caption`
which has has been loaded.
*/
bool has_window(string caption);
/**
* Check if the requested window is the current window.
* @param wind The window to check
* @return true if the window is the current window
*/
bool is_current_window(window wind);
/**
* Move the current window to the new location on the displays.
* @param x The new x location
* @param y The new y location
*
*/
void move_current_window_to(int x, int y);
/**
* Move the window to the new location on the displays.
* @param name The name of the window to move
* @param x The new x location
* @param y The new y location
*
*/
void move_window_to(const string &name, int x, int y);
/**
* Move the window to the new location on the displays.
* @param wind the window to move.
* @param x The new x location
* @param y The new y location
*
*/
void move_window_to(window wind, int x, int y);
/**
* Opens a new graphics window. The supplied `caption` is used to
* name and identify the window. The supplied `width` and `height` indicate
* the size of the window. The window can be retrieved by passing `caption`
* to the `window_named` function.
* @param caption The title of the window. If a window with this caption
* already exists, SplashKit will alter the caption to
* ensure that it is unique.
* @param width The width of the window
* @param height The height of the window
* @return A new window
*/
window open_window(string caption, int width, int height);
/**
* Refreshes the window `wind`.
* @param wind the `window` to refresh.
*
*/
void refresh_window(window wind);
/**
* Refreshes the window `wind`.
* @param wind the `window` to refresh.
* @param target_fps the desired framerate
*
*/
void refresh_window(window wind, unsigned int target_fps);
/**
* Change the size of the current window.
* @param width Its new width
* @param height Its new height
*
*/
void resize_current_window(int width, int height);
/**
* Change the size of the window.
* @param wnd The window to change.
* @param width Its new width
* @param height Its new height
*
*/
void resize_window(window wnd, int width, int height);
/**
* Set the current window to the window with the supplied caption.
* @param name The caption of the new current window.
*
*/
void set_current_window(const string &name);
/**
* Change the current window. Use this so that you can draw to different
* windows by default.
* @param wind The new current window
*
*/
void set_current_window(window wind);
/**
* The caption of the window.
* @param wind The window
* @return The window's caption.
*/
string window_caption(window wind);
/**
* Checks all opened windows in the current program
* to determin if a window with the name `name` is
* currently open, and will close a window if one is found.
* @param name The name of the window to close
* @return Returns `true` if the window has been asked to close.
*/
bool window_close_requested(const string &name);
/**
* Closes the window given in `wind`
* @param wind the `window` to be closed
* @return Returns `true` if the window is closed,
`false` if there is an error.
*/
bool window_close_requested(window wind);
/**
* Indicate if the window has a border.
* @param name The name of the window
* @return True if the window has a border
*/
bool window_has_border(const string &name);
/**
* Indicate if the window has a border.
* @param wnd The window
* @return True if the window has a border
*/
bool window_has_border(window wnd);
/**
* Indicates if the window has focus.
* @param wind The window
* @return True if the window has the user's focus
*/
bool window_has_focus(window wind);
/**
* Returns the height of the window with the indicated name in pixels.
* @param name The name of the window
* @return The height of the window
*/
int window_height(const string &name);
/**
* Returns the height of the window in pixels.
* @param wind The window
* @return The height of the window
*/
int window_height(window wind);
/**
* Is the window currently fullscreen?
* @param name The name of the window to check
* @return True when the window is fullscreen
*/
bool window_is_fullscreen(const string &name);
/**
* Is the window currently fullscreen?
* @param wnd The window to check
* @return True when the window is fullscreen
*/
bool window_is_fullscreen(window wnd);
/**
* Returns an opened `window` with the given name `caption`, if a window with
* name `caption` is found.
* @param caption the `string` name of the window.
* @return Returns a `window` with the name specified by `caption`
*/
window window_named(string caption);
/**
* The location of the window.
* @param name The name of the window.
* @return Its location on the displays
*/
point_2d window_position(const string &name);
/**
* The location of the window.
* @param wnd The window.
* @return Its location on the displays
*/
point_2d window_position(window wnd);
/**
* Sets the icon of the current window.
* @param wind The window to change the icon of
* @param bmp The image with the details to show in the icon
*
*/
void window_set_icon(window wind, bitmap bmp);
/**
* Toggle the window border.
* @param name The name of the window to change
*
*/
void window_toggle_border(const string &name);
/**
* Toggle the window border.
* @param wnd The window to change
*
*/
void window_toggle_border(window wnd);
/**
* Toggle the fullscreen property of the window
* @param name The name of the window to change
*
*/
void window_toggle_fullscreen(const string &name);
/**
* Toggle the fullscreen property of the window
* @param wnd The window to change
*
*/
void window_toggle_fullscreen(window wnd);
/**
* Returns the width of the window with the indicated name in pixels.
* @param name The name of the window
* @return The width of the window
*/
int window_width(const string &name);
/**
* Returns the width of the window in pixels.
* @param wind The window
* @return The width of the window
*/
int window_width(window wind);
/**
* Returns the window that the user currently has selected. This may be
* different to the current window.

* @return The window the user has selected
*/
window window_with_focus();
/**
* The x location of the window on the displays.
* @param name The name of the window
* @return Its location on the displays
*/
int window_x(const string &name);
/**
* The x location of the window on the displays.
* @param wnd The window
* @return Its location on the displays
*/
int window_x(window wnd);
/**
* The y location of the window on the displays.
* @param name The name of the window
* @return Its location on the displays
*/
int window_y(const string &name);
/**
* The y location of the window on the displays.
* @param wnd The window
* @return Its location on the displays
*/
int window_y(window wnd);

#endif /* __window_manager_h */
