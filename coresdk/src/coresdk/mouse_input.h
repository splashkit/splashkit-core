/**
 * @header mouse_input
 * @author Andrew Cain
 * @attribute group input
 */

#ifndef mouse_input_h
#define mouse_input_h

#include "geometry.h"
namespace splashkit_lib
{
    /**
     * A mouse can have many different types of buttons. Most people know
     * about the simple Left and Right buttons, but there is also a Middle
     * button (sometimes part of a scoll wheel), and possible side buttons.
     *
     * @constant NO_BUTTON          No mouse button
     * @constant LEFT_BUTTON        The left mouse button
     * @constant MIDDLE_BUTTON      The middle mouse button
     * @constant RIGHT_BUTTON       The right mouse button
     * @constant MOUSE_X1_BUTTON    The x1 mouse button
     * @constant MOUSE_X2_BUTTON    The x2 mouse button
     */
    enum mouse_button
    {
        NO_BUTTON,
        LEFT_BUTTON,
        MIDDLE_BUTTON,
        RIGHT_BUTTON,
        MOUSE_X1_BUTTON,
        MOUSE_X2_BUTTON
    };

    /**
     * Returns The current window position of the mouse as a `Vector`
     *
     * @returns The offset from the window origin to the mouse.
     */
    vector_2d mouse_position_vector();

    /**
     * Returns the current window position of the mouse as a `Point2D`
     *
     * @returns The position of the mouse in the current window.
     */
    point_2d mouse_position();

    /**
     * Returns the current x value of the mouse's position.
     *
     * @returns The distance of the mouse from the left edge of the current
     *          window location
     */
    float mouse_x();

    /**
     * Returns the current y value of the mouse's position.
     *
     * @returns The distance of the mouse from the top edge of the current
     *          window location
     */
    float mouse_y();

    /**
     * Returns the amount of accumulated mouse movement, since the last time
     * `process_events` was called, as a `vector_2d`.
     *
     * @returns The movement of the mouse since the last process events
     */
    vector_2d mouse_movement();

    /**
     * Returns the amount the mouse wheel was scrolled since the last call
     * to `process_events`. The result is a vector containing the x and y
     * amounts scrolled. Scroll left generates a negative x, scroll right a
     * positive x. Scroll backward is negative y, scroll forward positive y.
     * Note that on MacOS the directions may be inverted by OS settings.
     *
     * @returns The distance and direction of the mouse scroll since the last
     *          `process_events`
     */
    vector_2d mouse_wheel_scroll();

    /**
     * Returns `true` if the specified button is currently pressed down.
     *
     * @param button  The mouse button to check
     * @returns       True if the mouse button is down
     */
    bool mouse_down(mouse_button button);

    /**
     * Returns `true` if the specified button is currently up.
     *
     * @param button  The mouse button to check
     * @returns       True if the mouse button is up (i.e. not down)
     */
    bool mouse_up(mouse_button button);

    /**
     * Returns true if the specified button was clicked since the last time
     * `process_events` was called.
     *
     * @param button  The mouse button to check
     * @returns       True if the mouse button was clicked
     */
    bool mouse_clicked(mouse_button button);

    /**
     * Moves the mouse cursor to the specified screen location.
     *
     * @param x   The new x location of the mouse
     * @param y   The new y location of the mouse
     */
    void move_mouse(double x, double y);

    /**
     * Moves the mouse cursor to the specified screen location.
     *
     * @param point   The new location of the mouse
     *
     * @attribute suffix  to_point
     */
    void move_mouse(point_2d point);

    /**
     * Tells the mouse cursor to be visible if it was previously hidden with
     * by a `HideMouse` or `SetMouseVisible`(False) call.
     */
    void show_mouse();

    /**
     * Used to explicitly set the mouse cursors visible state (if it is showing
     * in the window or not) based on the show parameter.
     *
     * @param show  When true the mouse is shown, when false it is hidden
     *
     * @attribute suffix  with_boolean
     */
    void show_mouse(bool show);

    /**
     * Tells the mouse cursor to hide (no longer visible) if it is currently
     * showing. Use `ShowMouse` to make the mouse cursor visible again.
     */
    void hide_mouse();

    /**
     * Returns `true` if the mouse is currently visible, `false` if not.
     *
     * @return True if the mouse is shown.
     */
    bool mouse_shown();
}
#endif /* mouse_input_h */
