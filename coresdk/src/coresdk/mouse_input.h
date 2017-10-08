//
//  mouse_input.hpp
//  splashkit
//
//  Created by Andrew Cain on 15/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef mouse_input_h
#define mouse_input_h

#include "geometry.h"

/**
 * A mouse can have many different types of buttons. Most people know
 * about the simple Left and Right buttons, but there is also a Middle
 * button (sometimes part of a scoll wheel), and possible side buttons.
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
 */
vector_2d mouse_position_vector();

/**
 * Returns the current window position of the mouse as a `Point2D`
 */
point_2d mouse_position();

/**
 * Returns the current x value of the mouse's position.
 */
float mouse_x();

/**
 * Returns the current y value of the mouse's position.
 */
float mouse_y();

/**
 * Returns the amount of accumulated mouse movement, since the last time
 * `ProcessEvents` was called, as a `Vector`.
 */
vector_2d mouse_movement();

/**
 * Returns the amount the mouse wheel was scrolled since the last call
 * to `ProcessEvents`. The result is a vector containing the x and y
 * amounts scrolled. Scroll left generates a negative x, scroll right a
 * positive x. Scroll backward is negative y, scroll forward positive y.
 * Note that on MacOS the directions may be inverted by OS settings.
 */
vector_2d mouse_wheel_scroll();

/**
 * Returns ``true`` if the specified button is currently pressed down.
 */
bool mouse_down(mouse_button button);

/**
 * Returns ``true`` if the specified button is currently up.
 */
bool mouse_up(mouse_button button);

/**
 * Returns true if the specified button was clicked since the last time
 * `ProcessEvents` was called
 */
bool mouse_clicked(mouse_button button);

/**
 * Moves the mouse cursor to the specified screen location.
 */
void move_mouse(float x, float y);

/**
 * Moves the mouse cursor to the specified screen location.
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
 */
void show_mouse(bool show);

/**
 * Tells the mouse cursor to hide (no longer visible) if it is currently
 * showing. Use `ShowMouse` to make the mouse cursor visible again.
 */
void hide_mouse();

/**
 * Returns ``true`` if the mouse is currently visible, ``false`` if not.
 */
bool mouse_shown();

#endif /* mouse_input_h */
