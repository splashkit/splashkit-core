/**
 * @header  camera
 * @author  Andrew Cain
 * @brief   SplashKit camera functionality allows you to move a virtual camera
 *          around in your world.
 *
 * Splashkit camera functionality allows you to move a virtual camera around in
 * your world. This camera projects to the users window, allowing you to
 * draw things to the screen in your world coordinates.
 *
 * @attribute group  camera
 * @attribute static camera
 */

#ifndef camera_hpp
#define camera_hpp

#include "geometry.h"
namespace splashkit_lib
{
    /**
     * Returns the x location of the camera in game coordinates. This represents
     * the left most x value shown on the screen, with the right of the screen
     * being at camera x + screen width.
     *
     * @returns The x location of the camera in game coordinates.
     *
     * @attribute getter x
     */
    double camera_x();

    /**
     * Returns the y location of the camera in game coordinates. This represents
     * the stop most y value shown on the screen, with bottom of screen being
     * at camera y + screen height.
     *
     * @returns The y location of the camera in game coordinates.
     *
     * @attribute getter y
     */
    double camera_y();

    /**
     * Change the X position of the camera to a specified world coordinate. This
     * will then be the new left most position of the screen within the world.
     *
     * @param x The new x coordinate for the camera
     *
     * @attribute setter x
     */
    void set_camera_x(double x);

    /**
     * Change the Y position of the camera to a specified world coordinate. This
     * will then be the new top most position of the screen within the world.
     *
     * @param y The new y coordinate for the camera
     *
     * @attribute setter y
     */
    void set_camera_y(double y);

    /**
     * Change the position of the camera to a specified world coordinate. This
     * will then be the new top left most position of the screen within the world.
     *
     * @param pos   The new location of the camera.
     *
     * @attribute setter position
     */
    void set_camera_position(point_2d pos);

    /**
     * Returns the position of the camera in game coordinates. This will be the
     * coordinate of the upper left corner of the screen.
     *
     * @returns The position of the camera as a point_2d.
     *
     * @attribute getter position
     */
    point_2d camera_position();

    /**
     * Returns the center of the screen in world coordinates.
     *
     * @returns The center of the screen in world coordinates.
     *
     * @attribute getter screen_center
     */
    point_2d screen_center();

    //---------------------------------------------------------------------------
    // World-To-Screen Translation
    //---------------------------------------------------------------------------

    /**
     * Translate a world x value to the current screen x value which is based on
     * the camera position.
     *
     * @param world_x   The value of the x coordinate to translate to screen.
     * @returns         The x location of the world coordinate on the screen.
     *
     * @attribute method to_screen_x
     */
    double to_screen_x(double world_x);

    /**
     * Translate a world y value to the current screen y value set by the camera.
     *
     * @param world_y   The value of the y coordinate to translate to screen.
     * @returns         The y location of the world coordinate on the screen.
     *
     * @attribute method to_screen_y
     */
    double to_screen_y(double world_y);

    /**
     * Convert the passed in world coordinates to screen coordinates.
     *
     * @param pt    The point to convert - this should be in world coordinates.
     * @returns     A point that represents pt in screen coordinates.
     *
     * @attribute suffix    point
     *
     * @attribute method to_screen
     */
    point_2d to_screen(const point_2d &pt);

    /**
     * Convert the rectangle in world coordinates to screen coordinates.
     *
     * @param rect  The rectangle to convert - this should be in world coordinates.
     * @returns     A rectangle that represents rect in screen coordinates.
     *
     * @attribute suffix    rectangle
     *
     * @attribute method to_screen
     */
    rectangle to_screen(const rectangle &rect);

    /**
     * Returns a vector that can transform points from world to screen coordinates.
     *
     * @returns A vector representing the distance and direction points need
     *          to move to map from world to screen coordinates.
     *
     * @attribute getter vector_world_to_screen
     */
    vector_2d vector_world_to_screen();

    /**
     * Returns a rectangle that represents the dimensions of the window.
     *
     * @returns     A rectangle representing the dimensions of the current window.
     *
     * @attribute getter screen_rectangle
     */
    rectangle screen_rectangle();

    /**
     * Returns a rectangle that represents the dimensions of the window based
     * on the camera.
     *
     * @param wind  The window
     * @returns     A rectangle representing the dimensions of the current window.
     *
     * @attribute class window
     * @attribute getter area
     */
    rectangle window_area(window wind);

    //---------------------------------------------------------------------------
    // Screen-To-World Translation
    //---------------------------------------------------------------------------

    /**
     * Translate a screen x value (based on the camera) to a world x value
     *
     * @param screen_x   The value of the x coordinate on screen to translate to
     *                   the world.
     * @returns         The x location of the screen coordinate in the world.
     *
     * @attribute method to_world_x
     */
    double to_world_x(double screen_x);

    /**
     * Translate a screen y value (based on the camera) to a world y value
     *
     * @param screen_y   The value of the y coordinate on screen to translate to
     *                   the world.
     * @returns         The y location of the screen coordinate in the world.
     *
     * @attribute method to_world_y
     */
    double to_world_y(double screen_y);

    /**
     * Converts the passed in point from screen coordinates to world coordinates.
     *
     * @param pt    The point in screen coordinates.
     * @returns     The same point in world coordinates.
     *
     * @attribute method to_world
     */
    point_2d to_world(const point_2d &pt);


    //---------------------------------------------------------------------------
    // Screen tests
    //---------------------------------------------------------------------------

    /**
     * Tests if the rectangle is on the screen.
     *
     * @param  rect The rectangle to check.
     * @returns     True if any part of the rectangle is on the screen.
     *
     * @attribute method rect_on_screen
     */
    bool rect_on_screen(const rectangle &rect);

    /**
     * Tests if the point is on the screen.
     *
     * @param  pt   The point to check.
     * @returns     True if the point is on the screen.
     *
     * @attribute method point_on_screen
     */
    bool point_on_screen(const point_2d &pt);

    /**
     * Tests if the rectangle is within the bounds of the window.
     *
     * @param  wind The window to check
     * @param  rect The rectangle to check.
     * @returns     True if any part of the rectangle is in the window.
     *
     * @attribute method rect_in_window
     */
    bool rect_in_window(window wind, const rectangle &rect);

    /**
     * Tests if the point is in the window.
     *
     * @param  wind The window to check
     * @param  pt   The point to check.
     * @returns     True if the point is on the screen.
     *
     * @attribute method point_in_window
     */
    bool point_in_window(window wind, const point_2d &pt);



    //---------------------------------------------------------------------------
    // Camera movement
    //---------------------------------------------------------------------------

    /**
     * Move the camera view to a world location specified by the x and y values.
     * This will be the new top left corner of the screen.
     *
     * @param x The new camera x location
     * @param y The new camera y location
     *
     * @attribute method move_to
     */
    void move_camera_to(double x, double y);

    /**
     * Move the camera view (screen top left) to a specified point in the world.
     * This will be the new top left corner of the screen.
     *
     * @param pt The new camera location
     *
     * @attribute suffix    point
     * @attribute method    move_to
     */
    void move_camera_to(const point_2d &pt);

    /**
     * Move the camera (offset its world x and y values) using the specified
     * dx (change in x) and dy (change in x) values.
     *
     * @param dx The amount to move the camera along the x axis.
     * @param dy The amount to move the camera along the y axis.
     *
     * @attribute method move_by
     */
    void move_camera_by(double dx, double dy);

    /**
     * Move the camera (offset its world x and y values) using the specified
     * vector. For example, if you move the camera by the same speed vector of
     * a sprite the camera will "track" (be locked on to) the sprite as it moves.
     *
     * @param offset The amount to move the camera.
     *
     * @attribute suffix    vector
     * @attribute method    move_by
     */
    void move_camera_by(const vector_2d &offset);

    /**
     * Set the camera view to be centered over the specific sprite. The offset
     * vector allows you to move the sprite from the direct center of the screen.
     *
     * @param s        The sprite to track.
     * @param offset_x An additional offset added to the camera, allowing you to
     *                 position the sprite offset from the center of the screen.
     * @param offset_y An additional offset added to the camera, allowing you to
     *                 position the sprite offset from the center of the screen.
     *
     * @attribute method center_on
     */
    void center_camera_on(sprite s, double offset_x, double offset_y);

    /**
     * Set the camera view to be centered over a list of sprites. The offset
     * vector allows you to move the sprites from the direct center of the screen.
     *
     * @param s        A vector of sprites to track.
     * @param offset_x An additional offset added to the camera, allowing you to
     *                 position the sprites offset from the center of the screen.
     * @param offset_y An additional offset added to the camera, allowing you to
     *                 position the sprites offset from the center of the screen.
     */
    void center_camera_on(vector<sprite> s, double offset_x, double offset_y);

    /**
     * Set the camera view to be centered over an array of sprites. The offset
     * vector allows you to move the sprites from the direct center of the screen.
     *
     * @param s        An array of sprites to track.
     * @param size     The size of the sprite array.
     * @param offset_x An additional offset added to the camera, allowing you to
     *                 position the sprites offset from the center of the screen.
     * @param offset_y An additional offset added to the camera, allowing you to
     *                 position the sprites offset from the center of the screen.
     */
    void center_camera_on(sprite s[],int size , double offset_x, double offset_y);

    /**
     * Set the camera view to be centered over an array of sprites. The offset
     * vector allows you to move the sprites from the direct center of the screen.
     *
     * @param s        An array of sprites to track.
     * @param size     The size of the sprite array.
     * @param offset   The amount to offset the camera, allowing you to position
     *                 the sprites away from the center of the screen.
     */
    void center_camera_on(sprite s[], int size, const vector_2d &offset);

    /**
     * Set the camera view to be centered over a vector of sprites. The offset
     * vector allows you to move the sprites from the direct center of the screen.
     *
     * @param s        A vector of sprites to track.
     * @param offset   The amount to offset the camera, allowing you to position
     *                 the sprites away from the center of the screen.
     */
    void center_camera_on(vector<sprite> s, const vector_2d &offset);

    /**
     * Set the camera view to be centered over the specific sprite. The offset
     * vector allows you to move the sprite from the direct center of the screen.
     *
     * @param s        The sprite to track.
     * @param offset   The amount to offset the camera, allowing you to position
     *                 the sprite away from the center of the screen.
     *
     * @attribute suffix    vector
     * @attribute method center_on
     */
    void center_camera_on(sprite s, const vector_2d &offset);


#endif /* camera_hpp */
}
