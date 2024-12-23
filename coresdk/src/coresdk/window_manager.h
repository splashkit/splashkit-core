/**
 * @header  window_manager
 * @author  Andrew Cain
 * @brief   Window Manager in SplashKit can be used create, and manipulate
 *          graphics windows
 *
 * @attribute group  windows
 * @attribute static window_manager
 */

#ifndef window_manager_hpp
#define window_manager_hpp

#include "color.h"

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     * The Window type is used to refer to a window that you have opened
     * in SplashKit. You create new Windows using `open_window` and they can
     * be closed using `close_window`.
     *
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
     *
     * @param  caption The title of the window. If a window with this caption
     *                 already exists, SplashKit will alter the caption to
     *                 ensure that it is unique.
     * @param  width   The width of the window
     * @param  height  The height of the window
     * @return         A new window
     */
    window open_window(string caption, int width, int height);

    /**
     * Closes and frees the graphics window supplied in `wind`.
     *
     * @attribute class           window
     * @attribute destructor      true
     * @attribute self            wind
     * @attribute method          close
     *
     * @param wind The window to close
     */
    void close_window(window wind);

    /**
     * Closes and frees the current window.
     */
    void close_current_window();

    /**
     * Closes and frees the graphics window identified by `name`.
     *
     * @param name The name (caption) of the window to close
     *
     * @attribute suffix  named
     */
    void close_window(const string &name);

    /**
     * Releases all of the windows which have been loaded.
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
     * Returns an opened `window` with the given name `caption`, if a window with
     * name `caption` is found.
     *
     * @param  caption the `string` name of the window.
     *
     * @returns Returns a `window` with the name specified by `caption`
     */
    window window_named(string caption);

    /**
     * Returns the window that the user currently has selected. This may be
     * different to the current window.
     *
     * @return The window the user has selected
     */
    window window_with_focus();
    
    /**
     * Indicates if the window has focus.
     * 
     * @param wind The window
     * @return True if the window has the user's focus
     *
     * @attribute class window
     * @attribute getter has_focus
     */
    bool window_has_focus(window wind);

    /**
     * Returns the window that you are currently interacting with. This will be
     * the default window for drawing options, and events.
     *
     * @return The current window
     */
    window current_window();

    /**
     * Change the current window. Use this so that you can draw to different
     * windows by default.
     *
     * @param wind The new current window
     *
     * @attribute class window
     * @attribute method make_current
     */
    void set_current_window(window wind);

    /**
     * Set the current window to the window with the supplied caption.
     *
     * @param name The caption of the new current window.
     *
     * @attribute suffix  named
     */
    void set_current_window(const string &name);

    /**
     * Check if the requested window is the current window.
     *
     * @param wind The window to check
     * @returns true if the window is the current window
     *
     * @attribute class window
     * @attribute getter is_current_window
     */
    bool is_current_window(window wind);
    
    /**
     * Closes the window given in `wind`
     *
     * @param  wind the `window` to be closed
     *
     * @returns Returns `true` if the window is closed,
     * `false` if there is an error.
     *
     * @attribute class window
     * @attribute self wind
     * @attribute getter close_requested
     */
    bool window_close_requested(window wind);

    /**
     * Checks all opened windows in the current program
     * to determin if a window with the name `name` is
     * currently open, and will close a window if one is found.
     *
     * @param name The name of the window to close
     *
     * @returns Returns `true` if the window has been asked to close.
     *
     * @attribute suffix  named
     */
    bool window_close_requested(const string &name);

    /**
     * Refreshes the window `wind`.
     *
     * @param  wind the `window` to refresh.
     *
     * @attribute class   window
     * @attribute method  refresh
     */
    void refresh_window(window wind);

    /**
     * Refreshes the window `wind`.
     *
     * @param  wind the `window` to refresh.
     * @param  target_fps the desired framerate
     *
     * @attribute class   window
     * @attribute method  refresh
     * @attribute suffix  with_target_fps
     */
    void refresh_window(window wind, unsigned int target_fps);
    
    /**
     * clears a window to the specified color given in `clr`
     *
     * @param wind the `window` to clear
     * @param clr  the `color` to clear the window to.
     *
     * @attribute class   window
     * @attribute method  clear
     */
    void clear_window(window wind, color clr);

    /**
     * Returns the width of the window in pixels.
     *
     * @attribute class window
     * @attribute getter width
     *
     * @param  wind The window
     * @return      The width of the window
     */
    int window_width(window wind);

    /**
     * Returns the width of the window with the indicated name in pixels.
     *
     * @param  name The name of the window
     * @return      The width of the window
     *
     * @attribute suffix  named
     */
    int window_width(const string &name);

    /**
     * Returns the width of the current window.
     *
     * @return      The width of the current window
     */
    int current_window_width();

    /**
     * Returns the height of the window in pixels.
     *
     * @attribute class window
     * @attribute getter height
     *
     * @param  wind The window
     * @return      The height of the window
     */
    int window_height(window wind);

    /**
     * Returns the height of the window with the indicated name in pixels.
     *
     * @param  name The name of the window
     * @return      The height of the window
     *
     * @attribute suffix  named
     */
    int window_height(const string &name);

    /**
     * Returns the height of the current window.
     *
     * @return      The height of the current window
     */
    int current_window_height();

    /**
     * Sets the icon of the current window.
     *
     * @param wind The window to change the icon of
     * @param bmp  The image with the details to show in the icon
     *
     * @attribute class   window
     * @attribute setter  icon
     */
    void window_set_icon(window wind, bitmap bmp);

    /**
     * Change the size of the window.
     *
     * @param wnd    The window to change.
     * @param width  Its new width
     * @param height Its new height
     *
     * @attribute class window
     * @attribute method resize
     */
    void resize_window(window wnd, int width, int height);

    /**
     * Change the size of the current window.
     *
     * @param width  Its new width
     * @param height Its new height
     */
    void resize_current_window(int width, int height);

    /**
     * Move the window to the new location on the displays.
     *
     * @param wind the window to move.
     * @param x    The new x location
     * @param y    The new y location
     *
     * @attribute class window
     * @attribute method move_to
     */
    void move_window_to(window wind, int x, int y);

    /**
     * Move the window to the new location on the displays.
     *
     * @param name The name of the window to move
     * @param x    The new x location
     * @param y    The new y location
     *
     * @attribute suffix  named
     */
    void move_window_to(const string &name, int x, int y);

    /**
     * Move the current window to the new location on the displays.
     *
     * @param x    The new x location
     * @param y    The new y location
     */
    void move_current_window_to(int x, int y);

    /**
     * Is the window currently fullscreen?
     *
     * @param  wnd The window to check
     * @return     True when the window is fullscreen
     *
     * @attribute class   window
     * @attribute getter  is_fullscreen
     */
    bool window_is_fullscreen(window wnd);

    /**
     * Is the window currently fullscreen?
     *
     * @param  name The name of the window to check
     * @return     True when the window is fullscreen
     *
     * @attribute suffix  named
     */
    bool window_is_fullscreen(const string &name);

    /**
     * Is the current window currently fullscreen?
     *
     * @return     True when the window is fullscreen
     */
    bool current_window_is_fullscreen();

    /**
     * Toggle the fullscreen property of the window
     *
     * @param wnd The window to change
     *
     * @attribute class   window
     * @attribute method  toggle_fullscreen
     */
    void window_toggle_fullscreen(window wnd);

    /**
     * Toggle the fullscreen property of the window
     *
     * @param name The name of the window to change
     *
     * @attribute suffix  named
     */
    void window_toggle_fullscreen(const string &name);

    /**
     * Toggle the fullscreen property of the current window
     */
    void current_window_toggle_fullscreen();

    /**
     * Indicate if the window has a border.
     *
     * @param  wnd The window
     * @return     True if the window has a border
     *
     * @attribute class   window
     * @attribute getter  has_border
     */
    bool window_has_border(window wnd);

    /**
     * Indicate if the window has a border.
     *
     * @param  name The name of the window
     * @return     True if the window has a border
     *
     * @attribute suffix  named
     */
    bool window_has_border(const string &name);

    /**
     * Indicate if the current window has a border.
     *
     * @return     True if the window has a border
     */
    bool current_window_has_border();

    /**
     * Toggle the window border.
     *
     * @param wnd The window to change
     *
     * @attribute class   window
     * @attribute method  toggle_border
     */
    void window_toggle_border(window wnd);

    /**
     * Toggle the window border.
     *
     * @param name The name of the window to change
     *
     * @attribute suffix  named
     */
    void window_toggle_border(const string &name);

    /**
     * Toggle the current window border.
     */
    void current_window_toggle_border();

    /**
     * The x location of the window on the displays.
     *
     * @param  wnd The window
     * @return     Its location on the displays
     *
     * @attribute class   window
     * @attribute getter  x
     */
    int window_x(window wnd);

    /**
     * The x location of the window on the displays.
     *
     * @param  name The name of the window
     * @return     Its location on the displays
     *
     * @attribute suffix  named
     */
    int window_x(const string &name);

    /**
     * The x location of the current window on the displays.
     *
     * @return     Its location on the displays
     */
    int current_window_x();

    /**
     * The y location of the window on the displays.
     *
     * @param  wnd The window
     * @return     Its location on the displays
     *
     * @attribute class   window
     * @attribute getter  y
     */
    int window_y(window wnd);

    /**
     * The y location of the window on the displays.
     *
     * @param  name The name of the window
     * @return     Its location on the displays
     *
     * @attribute suffix  named
     */
    int window_y(const string &name);

    /**
     * The y location of the current window on the displays.
     *
     * @return     Its location on the displays
     */
    int current_window_y();

    /**
     * The location of the window.
     *
     * @param  wnd The window.
     * @return     Its location on the displays
     *
     * @attribute class   window
     * @attribute getter  position
     */
    point_2d window_position(window wnd);

    /**
     * The location of the window.
     *
     * @param  name The name of the window.
     * @return     Its location on the displays
     *
     * @attribute suffix  named
     */
    point_2d window_position(const string &name);

    /**
     * The location of the current window.
     *
     * @return     Its location on the displays
     */
    point_2d current_window_position();
    
    /**
     * The caption of the window.
     * 
     * @param wind The window
     * @returns The window's caption.
     *
     * @attribute class   window
     * @attribute getter  caption
     */
    string window_caption(window wind);

}
#endif /* window_manager_hpp */
