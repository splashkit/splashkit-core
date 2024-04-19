/**
 * @header  interface
 * @author  Sean Boettger
 * @brief   SplashKit Interface provides functions to create user interfaces, with elements such as draggable panels, buttons and text boxes.
 *
 * SplashKit`s interface library provides various functions for creating
 * panels, and drawing interface elements such as buttons, text boxes, and more
 *
 * @attribute group  interface
 * @attribute static interface
 */

// Note to maintainers: This file deliberately uses double spaces at the end of some lines
// to create newlines in the resulting markdown. Be careful not to remove these
// when removing trailing newlines.

#include "graphics.h"

#include <string>
using std::string;

#ifndef interface_hpp
#define interface_hpp
namespace splashkit_lib
{
    /**
     * Draws the user interface that all the previous calls (such as `start_panel`, `button`, etc) have created.  
     * **Make sure to call this!** Without calling it, the interface won't be visible.
     */
    void draw_interface();

    /**
     * Sets the interface's font.
     *
     * @param fnt               The font to be used.
     */
    void set_interface_font(font fnt);

    /**
     * Sets the interface's font size.
     *
     * @param size              The font size to be used.
     */
    void set_interface_font_size(int size);


    /**
     * Starts the creation of a draggable panel with a title bar.  
     * Returns whether the panel is visible or not.
     *
     * Use as follows:
     * ```c++
     * if (start_panel("My panel", rectangle_from(0,0,100,100)))
     * {
     *      // Rest of interface goes here
     *      end_panel("My panel");
     * }
     * ```
     * After calling this, you can then call functions to
     * add elements such as buttons and text boxes inside the panel.
     * The function **must** be accompanied by a call to `end_panel`,
     * that is only called if the panel is visible, and is passed the same `name`.
     *
     * @param name              The name shown in the panel's titlebar.
     * @param initial_rectangle The initial position/size the panel starts off in.
     * @return                  Whether the panel is visible or not.
     */
    bool start_panel(const string& name, rectangle initial_rectangle);

    /**
     * Finishes the creation of a panel.
     *
     * @param name              The name shown in the panel's titlebar - must match with `start_panel`
     */
    void end_panel(const string& name);

    /**
     * Starts the creation of a popup.  
     * Returns whether the popup is visible or not.
     *
     * Usage is the same as `start_panel`.
     * The function **must** be accompanied by a call to `end_popup`
     * with the same name.
     *
     * @param name              The name of the popup.
     * @return                  Whether the popup is visible or not.
     */
    bool start_popup(const string& name);

    /**
     * Finishes the creation of a popup.
     *
     * @param name              The popup's name - must match with `start_popup`
     */
    void end_popup(const string& name);


    /**
     * Starts the creation of an inset area inside a panel/popup.
     *
     * Use as follows:
     * ```c++
     * start_inset("Inset area", 60);
     * // elements inside area goes here
     * end_inset("Inset area");
     *
     * ```
     * The function **must** be accompanied by a call to `end_inset`
     * with the same name.
     *
     * @param name              The name of the area.
     * @param height            Height of the inset area in pixels. -1 fills entire space. Use negative heights to fill _up to_ `height` away from the bottom.
     */
    void start_inset(const string& name, int height);

    /**
     * Finishes the creation of an inset area.
     *
     * @param name              The area's name - must match with `start_inset`
     */
    void end_inset(const string& name);

    /**
     * Starts the creation of a tree node (such as those in a file tree view).  
     * Returns whether the tree node is expanded or not.
     *
     * Usage is the same as `start_panel`.
     * The function **must** be accompanied by a call to `end_treenode`
     * with the same name.
     *
     * @param label             The name of the node.
     * @return                  Whether the tree node is expanded or not.
     */
    bool start_treenode(const string& label);

    /**
     * Finishes the creation of a tree node.
     *
     * @param label             The node's name - must match with `start_treenode`
     */
    void end_treenode(const string& label);

    /**
     * Makes the popup named `name` open/popup at the cursor's position.
     *
     * @param name              The popup's name. Must match with the same name used in `start_popup`.
     */
    void open_popup(const string& name);

    /**
     * Resets to the default layout of a single column with default height.
     */
    void reset_layout();

    /**
     * Starts layouting all elements onto a single row. Reset with `reset_layout()`.
     */
    void single_line_layout();

    /**
     * Clears the default layout so that a custom layout can be made.
     */
    void start_custom_layout();

    /**
     * Adds a column to the current layout with width `width`.
     *
     * - Positive values of width just specify the width in pixels.
     * - 0 means use the default control width - not always a good choice.
     * - Negative values specify filling to the right _until_ `width - 1` pixels away from the edge.
     *   - e.g -1 fills entirely to the right, while -20 leaves a 19 pixel gap on the right.
     *
     * @param width             Width of the column in pixels.
     */
    void add_column(int width);

    /**
     * Adds a column to the current layout with width `width` percentage of the container's width.
     *
     * @param width             Percentage of the container's width (between 0 and 1).
     */
    void add_column_relative(double width);

    /**
     * Sets the height of each row in the interface in pixels.
     * 0 resets to default.
     *
     * @param height            Height of rows in pixels.
     */
    void set_layout_height(int height);

    /**
     * Begins placing elements inside the current column. Must be paired with a call to `leave_column`.
     */
    void enter_column();

    /**
     * Stops placing elements inside the current column and moves to the next one.
     */
    void leave_column();

    /**
     * Creates a collapsable header with a label.  
     * Returns whether the header is expanded or not.
     *
     * Note: Unlike `start_panel` and other similar functions, there is
     * no need to 'end' this one. Example usage:
     * ```c++
     * if (header("Section A"))
     * {
     *      // elements inside header go here
     * }
     * ```
     *
     * @param label             The label to show in the header.
     * @return                  Whether the header is expanded or not.
     */
    bool header(const string& label);


    /**
     * Creates a label.
     *
     * @param label             The label to show.
     */
    void label(const string& label);

    /**
     * Creates a button without a label.
     * Returns whether the button is pressed.
     *
     * @param text              The text to show inside the button.
     * @return                  Whether the button is pressed.
     */
    bool button(const string& label);


#endif /* interface_hpp */
}
