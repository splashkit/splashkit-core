
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
    void* get_interface_ctx()
    {
        return sk_interface_get_context();
    }

    void draw_interface()
    {
        drawing_options opts = option_defaults();

        sk_interface_draw(opts);
    }
}
