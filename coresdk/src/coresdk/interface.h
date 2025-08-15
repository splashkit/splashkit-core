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

#include "graphics.h"
#include "types.h"

#include <string>
using std::string;

#ifndef interface_hpp
#define interface_hpp
namespace splashkit_lib
{
    /**
     * Draws the user interface that all the previous calls (such as `start_panel`, `button`, etc) have created.
     *
     * **Make sure to call this!** Without calling it, the interface won't be visible.
     */
    void draw_interface();

    /**
     * Sets the interface's font.
     *
     * @param fnt               The font to be used
     */
    void set_interface_font(font fnt);

    /**
     * Sets the interface's font.
     *
     * @param fnt               The name of the font to be used
     *
     * @attribute suffix        font_as_string
     */
    void set_interface_font(const string& fnt);

    /**
     * Sets the interface's font size.
     *
     * @param size              The font size to be used
     */
    void set_interface_font_size(int size);

    /**
     * Sets the width of element labels. This is the maximum width
     * in pixels that a label can span in front of an element.
     *
     * Default is 60 pixels.
     *
     * @param width             The width of labels
     */
    void set_interface_label_width(int width);

    /**
     * Returns the width of element labels.
     *
     * Default is 60 pixels.
     *
     * @return                   The width of labels
     */
    int get_interface_label_width();

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
     * @param name              The name shown in the panel's titlebar
     * @param initial_rectangle The initial position/size the panel starts off in
     * @return                  Whether the panel is visible or not
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
     * Usage is the same as `start_panel`, other than the 'starting rectangle' will be automatically calculated.
     * The function **must** be accompanied by a call to `end_popup`
     * with the same name.
     *
     * @param name              The name of the popup
     * @return                  Whether the popup is visible or not
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
     * @param name              The name of the area
     * @param height            Height of the inset area in pixels. -1 fills entire space. Use negative heights to fill _up to_ `height` away from the bottom
     */
    void start_inset(const string& name, int height);

    /**
     * Starts the creation of an inset area inside an arbitrary rectangle.
     *
     * The function **must** be accompanied by a call to `end_inset`
     * with the same name.
     *
     * @param name              The name of the area
     * @param rect              The rectangle for the inset
     *
     * @attribute suffix        at_position
     */
    void start_inset(const string& name, const rectangle& rect);

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
     * @param label_text        The name of the node
     * @return                  Whether the tree node is expanded or not
     */
    bool start_treenode(const string& label_text);

    /**
     * Finishes the creation of a tree node.
     *
     * @param label_text        The node's name - must match with `start_treenode`
     */
    void end_treenode(const string& label_text);

    /**
     * Makes the popup named `name` open/popup at the cursor's position.
     *
     * @param name              The popup's name. Must match with the same name used in `start_popup`
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
     * - Negative values specify filling to the right _until_ `width + 1` pixels away from the edge.
     *   - e.g -1 fills entirely to the right, while -20 leaves a 19 pixel gap on the right.
     *
     * @param width             Width of the column in pixels
     */
    void add_column(int width);

    /**
     * Adds a column to the current layout with width `width` percentage of the container's width.
     *
     * @param width             Percentage of the container's width (between 0 and 1)
     */
    void add_column_relative(double width);

    /**
     * Adds `count` columns to the current layout, with equal widths
     *
     * @param count             Number of columns to add
     */
    void split_into_columns(int count);

    /**
     * Adds `count` columns to the current layout, with equal widths.
	 * Has extra parameter `last_width`, which lets you specify a specific
	 * width (in pixels) for the last column.
     *
     * @param count             Number of columns to add
     * @param last_width        The width of the last column in pixels
     *
     * @attribute suffix        with_last_width
     */
    void split_into_columns(int count, int last_width);

    /**
     * Adds `count` columns to the current layout, with equal widths.
	 * Has extra parameter `last_width`, which lets you specify a specific
	 * width (relative to the width of the container, between 0 and 1) for the last column.
     *
     * @param count             Number of columns to add
     * @param last_width        The width of the last column as percentage of the container's width (between 0 and 1)
     *
     * @attribute suffix        with_last_width
     */
    void split_into_columns_relative(int count, double last_width);

    /**
     * Sets the height of each row in the interface in pixels.
     * 0 resets to default.
     *
     * @param height            Height of rows in pixels
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
     * @param label_text        The label to show in the header
     * @return                  Whether the header is expanded or not
     */
    bool header(const string& label_text);

    /**
     * Creates a label with the given text.
     *
     * @param text             The label to show
     */
    void label_element(const string& text);

    /**
     * Creates a label at a specific position on screen.
     *
     * @param text             The label to show
     * @param rect             The rectangle to display the label in
     *
     * @attribute suffix        at_position
     */
    void label_element(const string& text, const rectangle& rect);

    /**
     * Creates a paragraph of text that auto-wraps.
     *
     * @param text              The text to show
     */
    void paragraph(const string& text);

    /**
     * Creates a paragraph of text that auto-wraps at a specific position on screen.
     *
     * @param text              The text to show
     * @param rect              The rectangle to display the label in
     *
     * @attribute suffix        at_position
     */
    void paragraph(const string& text, const rectangle& rect);

    /**
     * Creates a button with a label.
     * Returns whether the button was clicked.
     *
     * Example usage:
     * ```c++
     * // Test if clicked:
     * if (button("Button 1", "Click me!"))
     * {
     *      // do stuff..
     * }
     * ```
     *
     * @param label_text        The label to show in front of the button
     * @param text              The text to show inside the button
     * @return                  Whether the button was clicked
     *
     * @attribute suffix        labeled
     */
    bool button(const string& label_text, const string& text);

    /**
     * Creates a button without a label.
     * Returns whether the button was clicked.
     *
     * @param text              The text to show inside the button
     * @return                  Whether the button was clicked
     */
    bool button(const string& text);

    /**
     * Creates a button at a specific position on screen.
     * Returns whether the button was clicked.
     *
     * @param text              The text to show inside the button
     * @param rect              The rectangle to display the button in
     * @return                  Whether the button was clicked
     *
     * @attribute suffix        at_position
     */
    bool button(const string& text, const rectangle& rect);

    /**
     * Creates a button with a bitmap in it and a label.
     * Returns whether the button was clicked.
     *
     * @param label_text        The label to show in front of the button
     * @param bmp               The bitmap to show inside the button
     * @return                  Whether the button was clicked
     *
     * @attribute suffix        labeled
     */
    bool bitmap_button(const string& label_text, bitmap bmp);

    /**
     * Creates a button with a bitmap in it and a label.
     * Returns whether the button was clicked.
     *
     * @param label_text        The label to show in front of the button
     * @param bmp               The bitmap to show inside the button
     * @param opts              The drawing options
     * @return                  Whether the button was clicked
     *
     * @attribute suffix        labeled_with_options
     */
    bool bitmap_button(const string& label_text, bitmap bmp, drawing_options opts);

    /**
     * Creates a button with a bitmap in it, and no label.
     * Returns whether the button was clicked.
     *
     * @param bmp               The bitmap to show inside the button
     * @return                  Whether the button was clicked
     *
     */
    bool bitmap_button(bitmap bmp);

    /**
     * Creates a button with a bitmap in it, and no label.
     * Returns whether the button was clicked.
     *
     * @param bmp               The bitmap to show inside the button
     * @param opts              The drawing options
     * @return                  Whether the button was clicked
     *
     * @attribute suffix        with_options
     */
    bool bitmap_button(bitmap bmp, drawing_options opts);

    /**
     * Creates a button with a bitmap in it at a specific position on screen.
     * Returns whether the button was clicked.
     *
     * @param bmp               The bitmap to show inside the button
     * @param rect              The rectangle to display the button in
     * @return                  Whether the button was clicked
     *
     * @attribute suffix        at_position
     */
    bool bitmap_button(bitmap bmp, const rectangle& rect);

    /**
     * Creates a button with a bitmap in it at a specific position on screen.
     * Returns whether the button was clicked.
     *
     * @param bmp               The bitmap to show inside the button
     * @param rect              The rectangle to display the button in
     * @param opts              The drawing options
     * @return                  Whether the button was clicked
     *
     * @attribute suffix        at_position_with_options
     */
    bool bitmap_button(bitmap bmp, const rectangle& rect, drawing_options opts);

    /**
     * Creates a checkbox with a label.
     * Returns the updated value of the checkbox.
     *
     * Example usage:
     * ```c++
     * my_bool = checkbox("Checkbox 1", "Enabled?", my_bool);
     * ```
     *
     * @param label_text        The label to show in front of the checkbox
     * @param text              The text to show next to the checkbox
     * @param value             The current value of the checkbox
     * @return                  The updated value of the checkbox
     *
     * @attribute suffix        labeled
     */
    bool checkbox(const string& label_text, const string& text, const bool& value);

    /**
     * Creates a checkbox.
     * Returns the updated value of the checkbox.
     *
     * @param text              The text to show next to the checkbox
     * @param value             The current value of the checkbox
     * @return                  The updated value of the checkbox
     */
    bool checkbox(const string& text, const bool& value);

    /**
     * Creates a checkbox at a specific position on screen.
     * Returns the updated value of the checkbox.
     *
     * @param text              The text to show next to the checkbox
     * @param value             The current value of the checkbox
     * @param rect              The rectangle to display the checkbox in
     * @return                  The updated value of the checkbox
     *
     * @attribute suffix        at_position
     */
    bool checkbox(const string& text, const bool& value, const rectangle& rect);

    /**
     * Creates a slider with a label.
     * Returns the updated value of the slider.
     *
     * Example usage:
     * ```c++
     * my_float = slider("Percentage", my_float, 0, 100);
     * ```
     *
     * @param label_text        The label to show in front of the slider
     * @param value             The current value of the slider
     * @param min_value         The minimum value of the slider
     * @param max_value         The maximum value of the slider
     * @return                  The updated value of the slider
     *
     * @attribute suffix        labeled
     */
    float slider(const string& label_text, const float& value, float min_value, float max_value);

    /**
     * Creates a slider without a label.
     * Returns the updated value of the slider.
     *
     * @param value             The current value of the slider
     * @param min_value         The minimum value of the slider
     * @param max_value         The maximum value of the slider
     * @return                  The updated value of the slider
     */
    float slider(const float& value, float min_value, float max_value);

    /**
     * Creates a slider at a specific position on screen.
     * Returns the updated value of the slider.
     *
     * @param value             The current value of the slider
     * @param min_value         The minimum value of the slider
     * @param max_value         The maximum value of the slider
     * @param rect              The rectangle to display the slider in
     * @return                  The updated value of the slider
     *
     * @attribute suffix        at_position
     */
    float slider(const float& value, float min_value, float max_value, const rectangle& rect);

    /**
     * Creates a set of RGBA sliders to adjust a color, with a label.
     * Returns the updated color value of the slider.
     *
     * Example usage:
     * ```c++
     * my_color = color_slider("Player Color", my_color);
     * ```
     *
     * @param label_text        The label to show in front of the slider
     * @param clr               The current value of the color slider
     * @return                  The updated value of the slider
     *
     * @attribute suffix        labeled
     */
    color color_slider(const string& label_text, const color& clr);

    /**
     * Creates a set of RGBA sliders to adjust a color.
     * Returns the updated color value of the slider.
     *
     * @param clr               The current value of the color slider
     * @return                  The updated value of the slider
     */
    color color_slider(const color& clr);

    /**
     * Creates a set of RGBA sliders to adjust a color, at a specific position on screen.
     * Returns the updated color value of the slider.
     *
     * @param clr               The current value of the color slider
     * @param rect              The rectangle to display the slider in.
     * @return                  The updated value of the slider
     *
     * @attribute suffix        at_position
     */
    color color_slider(const color& clr, const rectangle& rect);

    /**
     * Creates a set of HSBA (hue, saturation, brightness, alpha) sliders to adjust a color, with a label.
     * Returns the updated color value of the slider.
     *
     * Example usage:
     * ```c++
     * my_color = hsb_color_slider("Player Color", my_color);
     * ```
     *
     * @param label_text        The label to show in front of the slider
     * @param clr               The current value of the color slider
     * @return                  The updated value of the slider
     *
     * @attribute suffix        labeled
     */
    color hsb_color_slider(const string& label_text, const color& clr);

    /**
     * Creates a set of HSBA (hue, saturation, brightness, alpha) sliders to adjust a color.
     * Returns the updated color value of the slider.
     *
     * @param clr               The current value of the color slider
     * @return                  The updated value of the slider
     */
    color hsb_color_slider(const color& clr);

    /**
     * Creates a set of HSBA (hue, saturation, brightness, alpha) sliders to adjust a color, at a specific position on screen.
     * Returns the updated color value of the slider.
     *
     * @param clr               The current value of the color slider
     * @param rect              The rectangle to display the slider in.
     * @return                  The updated value of the slider
     *
     * @attribute suffix        at_position
     */
    color hsb_color_slider(const color& clr, const rectangle& rect);

    /**
     * Creates a number entry box with a label.
     * Returns the updated value of the number box.
     *
     * Example usage:
     * ```c++
     * my_float = number_box("Percentage", my_float, 1);
     * ```
     *
     * @param label_text        The label to show in front of the number box
     * @param value             The current value of the number box
     * @param step              The amount incremented when dragging on the box
     * @return                  The updated value of the slider
     *
     * @attribute suffix        labeled
     */
    float number_box(const string& label_text, const float& value, float step);

    /**
     * Creates a number entry box with a label.
     * Returns the updated value of the number box.
     *
     * @param value             The current value of the number box
     * @param step              The amount incremented when dragging on the box
     * @return                  The updated value of the slider
     */
    float number_box(const float& value, float step);

    /**
     * Creates a number entry box at a specific position on screen.
     * Returns the updated value of the number box.
     *
     * @param value             The current value of the number box
     * @param step              The amount incremented when dragging on the box
     * @param rect              The rectangle to display the slider in
     * @return                  The updated value of the slider
     *
     * @attribute suffix        at_position
     */
    float number_box(const float& value, float step, const rectangle& rect);

    /**
     * Creates a text entry box with a label.
     * Returns the updated value of the text box.
     *
     * Example usage:
     * ```c++
     * my_string = text_box("Name", my_string);
     * ```
     *
     * @param label_text        Unique identifier for the text box (not drawn)
     * @param value             The current value of the text box
     * @return                  The updated value of the text box
     */
    string text_box(const string& label_text, const string& value);

    /**
     * Creates a text entry box with a label that can be shown.
     * Returns the updated value of the text box.
     *
     * Example usage:
     * ```c++
     * my_string = text_box("Name", my_string, true);
     * ```
     *
     * @param label_text        Unique identifier for the text box (not drawn)
     * @param value             The current value of the text box
     * @param show_label        Whether to show the label or not
     * @return                  The updated value of the text box
     *
     * @attribute suffix        labeled
     */
    string text_box(const string& label_text, const string& value, bool show_label);

    /**
     * Creates a text entry box at a specific position on screen.
     * Returns the updated value of the text box.
     *
     * Example usage:
     * ```c++
     * my_string = text_box("Name", my_string, rectangle_from(0,0,100,100));
     * ```
     *
     * @param label_text        Unique identifier for the text box (not drawn)
     * @param value             The current value of the text box
     * @param rect              The rectangle to display the button in
     * @return                  The updated value of the text box
     *
     * @attribute suffix        at_position
     */
    string text_box(const string& label_text, const string& value, const rectangle& rect);

    /**
     * Returns if the last created element was changed at all (such as dragged, typed in, etc)
     *
     * @return                   Whether the last created element was changed
     */
    bool last_element_changed();

    /**
     * Returns if the last created element was 'confirmed' (such as clicking a button, or hitting enter in a text box)
     *
     * @return                   Whether the last created element was confirmed
     */
    bool last_element_confirmed();

    /**
     * Sets the interface style to one of the presets in the interface_style enum.
     * @param style              The preset style to use
     */
    void set_interface_style(interface_style style);

    /**
     * Sets the interface style to one of the presets in the interface_style enum.
     * Also accepts a color used to customize the interface.
     * @param style              The preset style to use
     * @param clr                The color to style the interface after
     *
     * @attribute suffix        with_color
     */
    void set_interface_style(interface_style style, color clr);

    /**
     * A convenience function to set the majority of the interface's colors in one go.
     * Some colors will be automatically chosen based on the parameters (such as text color).
     * @param main_clr           The main color of the interface - also decides if the interface is light or dark mode
     * @param accent_clr         The color used to accent the interface - this will appear in highlighted areas
     * @param contrast           The contrast between the frames of elements/containers and their internal elements
     * @param accent_contrast    How strongly the accent color is used, for instance when highlighting elements
     * @param border_contrast    Simply the opacity of the borders
     */
    void set_interface_colors_auto(color main_clr, color accent_clr, float contrast, float accent_contrast, float border_contrast);

    /**
     * Sets the style of all interface shadows. Use a fully transparent color to disable them.
     * @param radius             The radius of the shadow's blur
     * @param clr                The color of the shadows (commonly black, but can do coloured and semi-transparent too)
     * @param offset             The offset in x/y coordinates of the shadows from their casting elements
     */
    void set_interface_shadows(int radius, color clr, point_2d offset);

    /**
     * Sets the interface's text color.
     * @param clr                The color to set text to
     */
    void set_interface_text_color(color clr);

    /**
     * Sets color of text drawn directly onto the main window
     * @param clr                The color to set text drawn on the main window to
     */
    void set_interface_root_text_color(color clr);

    /**
     * Sets the interface's border color.
     * @param clr                The color to set borders to
     */
    void set_interface_border_color(color clr);

    /**
     * Sets the main color of elements in the interface, and the contrast between their frame and internal pieces.
     * @param clr                The color of elements
     * @param contrast           The contrast between the frame of elements and their internal pieces (between 0 and 1)
     */
    void set_interface_element_color(color clr, float contrast);

    /**
     * Sets the color of accents in the interface, and the contrast of how strongly they appear when hovering/interacting.
     * @param clr                The color of accents
     * @param contrast           The strength of how much the accents show (between 0 and 1)
     */
    void set_interface_accent_color(color clr, float contrast);

    /**
     * Sets the style of panel's shadows. Use a fully transparent color to disable them.
     * @param radius             The radius of the shadow's blur
     * @param clr                The color of the shadows (commonly black, but can do coloured and semi-transparent too)
     * @param offset             The offset in x/y coordinates of the shadows from their casting elements
     */
    void set_interface_panel_shadows(int radius, color clr, point_2d offset);

    /**
     * Sets the style of element's shadows. Use a fully transparent color to disable them.
     * @param radius             The radius of the shadow's blur
     * @param clr                The color of the shadows (commonly black, but can do coloured and semi-transparent too)
     * @param offset             The offset in x/y coordinates of the shadows from their casting elements
     */
    void set_interface_element_shadows(int radius, color clr, point_2d offset);

    /**
     * Sets the spacing within the interface.
     * @param spacing            The distance between elements
     * @param padding            The padding within elements
     */
    void set_interface_spacing(int spacing, int padding);

    /**
     * A utility function to show a 'Style Panel', which will allows you to experiment with different interface styles.
     *
     * @param initial_rectangle The initial position/size the panel starts off in
     */
    void interface_style_panel(const rectangle& initial_rectangle);

    /**
     * Disables the interface temporarily. Elements created after this function will appear disabled and cannot be interacted with.
     */
    void disable_interface();

    /**
     * Re-enables the interface, reverses the effects of disabling the interface.
     */
    void enable_interface();

    /**
     * Returns if the interface is currently enabled or not.
     *
     * @return                   Whether the interface is currently enabled or not
     */
    bool interface_enabled();

#endif /* interface_hpp */
}
