
//
//  interface.cpp
//  splashkit
//
//  Created by Sean Boettger on 22/03/2024.
//  Copyright © 2024 Sean Boettger. All rights reserved.
//

#include "interface.h"

#include "graphics.h"
#include "window_manager.h"
#include "utils.h"
#include "drawing_options.h"
#include "camera.h"

#include "utility_functions.h"

#include "interface_driver.h"
#include "graphics_driver.h"
#include "text_driver.h"
extern "C" {
#include "microui.h"
}

namespace splashkit_lib
{
    void* get_interface_ctx()
    {
        return sk_interface_get_context();
    }

    void draw_interface()
    {
        drawing_options opts = option_defaults();

        sk_drawing_surface *surface;

        surface = to_surface_ptr(opts.dest);

        mu_Context *ctx = (mu_Context *)get_interface_ctx();

        if (surface)
        {
            mu_Command *cmd = NULL;
            while (mu_next_command(ctx, &cmd))
            {
                switch (cmd->type)
                {
                    case MU_COMMAND_TEXT: sk_draw_text(surface, FONT_NAME, FONT_SIZE, cmd->text.pos.x, cmd->text.pos.y, cmd->text.str, {cmd->text.color.r/255.f, cmd->text.color.g/255.f, cmd->text.color.b/255.f, cmd->text.color.a/255.f});break;
                    case MU_COMMAND_RECT: sk_fill_aa_rect(surface, {cmd->rect.color.r/255.f, cmd->rect.color.g/255.f, cmd->rect.color.b/255.f, cmd->rect.color.a/255.f}, cmd->rect.rect.x, cmd->rect.rect.y, cmd->rect.rect.w, cmd->rect.rect.h); break;
                    case MU_COMMAND_ICON: /*To Do*/ break;//r_draw_icon(cmd->icon.id, cmd->icon.rect, cmd->icon.color); break;
                    case MU_COMMAND_CLIP: sk_set_clip_rect(surface, cmd->clip.rect.x, cmd->clip.rect.y, cmd->clip.rect.w, cmd->clip.rect.h); break;
                }
            }
        }
    }
}
