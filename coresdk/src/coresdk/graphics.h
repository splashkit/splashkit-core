/**
 * @header  graphics
 * @author  Andrew Cain
 * @attribute group graphics
 */

#ifndef graphics_hpp
#define graphics_hpp

#include "drawing_options.h"

#include "circle_drawing.h"
#include "rectangle_drawing.h"
#include "triangle_drawing.h"
#include "point_drawing.h"
#include "ellipse_drawing.h"
#include "line_drawing.h"
#include "clipping.h"

namespace splashkit_lib
{
    //---------------------------------------------------------------------------------------------------------
    // Screen management...
    //---------------------------------------------------------------------------------------------------------

    /**
     * Refreshes the current drawing on all open windows. This must be
     * called to display anything to the screen. This will show all drawing
     * operations, as well as any text being entered by the user.
     *
     * This will add in delays to limit the framerate to around 60 frames per
     * second.
     *
     * The current drawing is shown on the screen as a result.
     *
     * @brief Refreshes the current drawing on all open windows.
     */
    void refresh_screen();

    /**
     * Refreshes all open windows with a target FPS (frames per second). This will
     * delay a period of time that will approximately meet the targeted frames per
     * second.
     *
     * @param target_fps The targeted frames per second to refresh the screen at.
     *
     * @attribute suffix  with_target_fps
     */
    void refresh_screen(unsigned int target_fps);

    /**
     * When called, all open windows will have their contents removed and will be
     * redrawn with a background color set to the `clr` that was provided.
     *
     * You can use this to make a solid background color on all windows opened
     * on the screen and wipe all their previous drawings away.
     *
     * @brief Clears all open windows to the `clr` provided.
     *
     * @param clr The color to clear the screen's background color to.
     */
    void clear_screen(color clr);

    /**
     * Clears the current screen to color white.
     *
     * @attribute suffix  to_white
     */
    void clear_screen();

    /**
     * Returns the width of the current window.
     *
     * @return The width of the current window.
     */
    int screen_width();

    /**
     * Returns the height of the current window.
     *
     * @return The height of the current window.
     */
    int screen_height();

    /**
     *  Saves a screenshot of the current window to a bitmap file. The file will
     *  be saved onto the user's desktop.
     *
     * @param basename The base of the filename. If there is a file of this name
     *                 already, then the name will be changed to generate a
     *                 unique filename.
     */
    void take_screenshot(const string &basename);

    /**
     *  Saves a screenshot of the current window to a bitmap file. The file will
     *  be saved onto the user's desktop.
     *
     * @param wind     The window to capture in the screenshot
     * @param basename The base of the filename. If there is a file of this name
     *                 already, then the name will be changed to generate a
     *                 unique filename.
     *
     * @attribute suffix  of_window
     */
    void take_screenshot(window wind, const string &basename);

    /**
     * Save the bitmap to the user's desktop.
     *
     * @param bmp      The bitmap to save
     * @param basename The base of the filename. If there is a file of this name
     *                 already, then the name will be changed to generate a
     *                 unique filename.
     */
    void save_bitmap(bitmap bmp, const string &basename);

    /**
     * Returns the number of physical displays attached to the computer.
     *
     * @return The number of displays attached to the computer
     */
    int number_of_displays();

    /**
     * Returns the details about one of the displays attached to the computer.
     *
     * @param  index The display number (from 0 to `number_of_displays` - 1)
     * @return       The details of this display
     */
    display display_details(unsigned int index);

    /**
     * Return the name of the display, read from the system details.
     *
     * @param  disp The display details
     * @return      The name of the display
     *
     * @attribute class display
     * @attribute getter name
     */
    string display_name(display disp);

    /**
     * Return the width of the display in pixels, read from the system details.
     *
     * @param  disp The display details
     * @return      The width of the display
     *
     * @attribute class display
     * @attribute getter width
     */
    int display_width(display disp);

    /**
     * Return the height of the display in pixels, read from the system details.
     *
     * @param  disp The display details
     * @return      The height of the display
     *
     * @attribute class display
     * @attribute getter height
     */
    int display_height(display disp);

    /**
     * Return a relative x location for the display in pixels, read from the
     * system details. This can be used to work out the arrangement of displays.
     *
     * @param  disp The display details
     * @return      The x location of the display
     *
     * @attribute class display
     * @attribute getter x
     */
    int display_x(display disp);

    /**
     * Return a relative y location for the display in pixels, read from the
     * system details. This can be used to work out the arrangement of displays.
     *
     * @param  disp The display details
     * @return      The y location of the display
     *
     * @attribute class display
     * @attribute getter y
     */
    int display_y(display disp);

}
#endif /* graphics_hpp */
