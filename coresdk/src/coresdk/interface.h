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

#include "graphics.h"

#include <string>
using std::string;

#ifndef interface_hpp
#define interface_hpp
namespace splashkit_lib
{
    /**
     * Draws the user interface that has been created so far
     */
    void draw_interface();

    void set_interface_font(font fnt);
    void set_interface_font_size(int size);

    bool start_panel(const string& name, rectangle initial_rectangle);
    void end_panel(const string& name);

    bool start_popup(const string& name);
    void end_popup(const string& name);

    void open_popup(const string& name);

    void label(const string& label);
    bool button(const string& label);


#endif /* interface_hpp */
}
