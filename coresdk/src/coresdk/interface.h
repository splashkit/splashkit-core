/**
 * @header  interface
 * @author  Sean Boettger
 * @brief   SplashKit interface provides ability to create user interfaces
 *
 * SplashKit`s interface library provides various functions for creating
 * panels, and drawing interface elements such as buttons, text boxes, and more
 *
 * @attribute group  interface
 * @attribute static interface
 */

#ifndef interface_hpp
#define interface_hpp
namespace splashkit_lib
{
    /**
     * Draws the user interface that has been created so far
     */
    void draw_interface();

    // temporary
    void* get_interface_ctx();

#endif /* interface_hpp */
}
