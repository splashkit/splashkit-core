
//
//  interface.cpp
//  splashkit
//
//  Created by Sean Boettger on 22/03/2024.
//  Copyright © 2024 Sean Boettger. All rights reserved.
//

#include "interface.h"

#include "utils.h"
#include "drawing_options.h"

#include "interface_driver.h"

namespace splashkit_lib
{

    void draw_interface()
    {
        drawing_options opts = option_defaults();

        sk_interface_draw(opts);
    }

    bool start_panel(const string& name, rectangle initial_rectangle)
    {
        bool open = sk_interface_start_panel(name, initial_rectangle);

        return open;
    }
    void end_panel(const string& name)
    {
        sk_interface_end_panel();
    }

    bool start_popup(const string& name)
    {
        bool open = sk_interface_start_popup(name);

        return open;
    }
    void end_popup(const string& name)
    {
        sk_interface_end_popup();
    }

    void open_popup(const string& name)
    {
        sk_interface_open_popup(name);
    }

    void label(const string& label)
    {
        sk_interface_label(label);
    }
    bool button(const string& label)
    {
        return sk_interface_button(label);
    }
}
