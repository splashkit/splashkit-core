#include "box2d/box2d.h"
#include <stdlib.h>
#include "sprites.h"
#include "graphics.h"
#include "input.h"
#include "physics.h"

int main(){
    
    
    using namespace splashkit_lib;
    auto window_to_show = open_window("Physics Collision Game", 800, 600);
    auto physics_context = Box2DContext{};

    auto blue_rect_bitmap = create_bitmap("blue_rect", 5, 5);
    fill_rectangle_on_bitmap(blue_rect_bitmap, COLOR_BLUE, {0, 0, 5, 5});

    auto body_def = physics_context.get_default_body_definition();
    body_def.type = b2_dynamicBody;
    body_def.gravityScale = 0.3f;

    for (size_t y_pos = 0; y_pos < 600; y_pos += 7)
    {
        for (size_t x_pos = 0; x_pos < 100; x_pos += 7)
        {
            sprite player = create_sprite(blue_rect_bitmap);
            sprite_set_position(player, {(float)x_pos + 300.0f, y_pos - 400.0f});
            auto player_body = physics_context.add_sprite_to_world(player, body_def);
        }
    }
    // player_body.second->ApplyLinearImpulseToCenter({-1.0f, 0.0f}, true);

    auto red_rect_bitmap = create_bitmap("red_rect", 50, 50);
    fill_rectangle_on_bitmap(red_rect_bitmap, COLOR_RED, {0, 0, 50, 50});

    sprite red = create_sprite(red_rect_bitmap);
    sprite_set_position(red, {350.0f, 400.0f});
    body_def.type = b2_staticBody;
    auto red_body = physics_context.add_sprite_to_world(red, body_def);

    bool quit = false;
    while(!quit){
        process_events();
        clear_screen(COLOR_WHITE);
        physics_context.step();


        // box2dWorld.world.Step(1.0f/60.0f, 6, 2);

        // auto groudExtents = groundBody->GetFixtureList()->GetAABB(0).GetExtents();
        // draw_rectangle(
        //     COLOR_BLACK,
        //     (groundBody->GetPosition().x - groudExtents.x) * box2dWorld.options.scale_x,
        //     (groundBody->GetPosition().y - groudExtents.y) * box2dWorld.options.scale_y,
        //     groudExtents.x * 2 * box2dWorld.options.scale_x,
        //     groudExtents.y * 2 * box2dWorld.options.scale_y, box2dWorld.options);

        // auto bodyExtents = body->GetFixtureList()->GetAABB(0).GetExtents();
        // // draw_rectangle(
        // //     COLOR_BLUE,
        // //     (body->GetPosition().x - bodyExtents.x) * box2dWorld.options.scale_x,
        // //     (body->GetPosition().y - bodyExtents.y) * box2dWorld.options.scale_y,
        // //     bodyExtents.x * 2 * box2dWorld.options.scale_x,
        // //     bodyExtents.y * 2 * box2dWorld.options.scale_y, box2dWorld.options);

        // sprite_set_position(player, {(body->GetPosition().x - bodyExtents.x) * box2dWorld.options.scale_x,
        //                              (body->GetPosition().y - bodyExtents.y) * box2dWorld.options.scale_y});

        // sprite_set_rotation(player, body->GetAngle()*(180.0f/M_PI));

        update_all_sprites();
        draw_all_sprites();

        if (key_down(ESCAPE_KEY)) {
                quit = true;
        }

        if (quit_requested()) {
            quit = true;
        }

        refresh_screen(60);
    }
    return 0;
}
