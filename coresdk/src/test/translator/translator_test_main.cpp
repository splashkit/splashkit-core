//
//  main.cpp
//  CaveEscapeFrontEndTest
//
//  Created by Alex on 9/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "splashkit.h"

#define GRAVITY 0.08
#define MAX_SPEED 5
#define JUMP_RECOVERY_BOOST 2
#define FOREGROUND_FOREROOF_POLE_SCROLL_SPEED -2
#define BACKGROUND_SCROLL_SPEED -1
#define NUM_POLES 4

struct pole_data
{
    bool score_limiter;
    sprite up_pole, down_pole;
};

struct background_data
{
    sprite foreroof, foreground, background;
};

enum player_state{MENU, PLAY};

typedef struct player
{
    sprite sprite_data;
    int score;
    bool is_dead;
    player_state state;
} player;

typedef struct game_data
{
    player player_data;
    background_data scene;
    pole_data poles_data[NUM_POLES];
} game_data;

player get_new_player()
{
    player result;

    result.sprite_data = create_sprite(bitmap_named("Player"), animation_script_named("PlayerAnimations"));
    sprite_set_x(result.sprite_data, screen_width() / 2 - sprite_width(result.sprite_data));
    sprite_set_y(result.sprite_data, screen_height() / 2);
    sprite_start_animation(result.sprite_data, "Fly");
    result.score = 0;
    result.is_dead = false;
    result.state = MENU;

    return result;
}

pole_data get_random_poles()
{
    pole_data result;

    result.up_pole = create_sprite(bitmap_named("UpPole"));
    result.down_pole = create_sprite(bitmap_named("DownPole"));
    sprite_set_x(result.up_pole, screen_width() + rnd(1200));
    sprite_set_y(result.up_pole, screen_height() - sprite_height(result.up_pole) -  rnd(bitmap_height(bitmap_named("Foreground"))) + 1);
    sprite_set_x(result.down_pole, sprite_x(result.up_pole));
    sprite_set_y(result.down_pole, rnd(bitmap_height(bitmap_named("Foreroof"))) + 1);
    sprite_set_dx(result.up_pole, FOREGROUND_FOREROOF_POLE_SCROLL_SPEED);
    sprite_set_dx(result.down_pole, FOREGROUND_FOREROOF_POLE_SCROLL_SPEED);
    result.score_limiter = true;

    return result;
}

background_data get_new_background()
{
    background_data result;

    result.background = create_sprite(bitmap_named("Background"));
    sprite_set_x(result.background, 0);
    sprite_set_y(result.background, 0);
    sprite_set_dx(result.background, BACKGROUND_SCROLL_SPEED);

    result.foreground = create_sprite(bitmap_named("Foreground"), animation_script_named("ForegroundAnimations"));
    sprite_set_x(result.foreground, 0);
    sprite_set_y(result.foreground, screen_height() - sprite_height(result.foreground));
    sprite_set_dx(result.foreground, FOREGROUND_FOREROOF_POLE_SCROLL_SPEED);
    sprite_start_animation(result.foreground, "Fire");

    result.foreroof = create_sprite(bitmap_named("Foreroof"));
    sprite_set_x(result.foreroof, 0);
    sprite_set_y(result.foreroof, 0);
    sprite_set_dx(result.foreroof, FOREGROUND_FOREROOF_POLE_SCROLL_SPEED);

    return result;
}

void handle_input(player &player_data)
{
    if (key_typed(SPACE_KEY) && (player_data.state = PLAY))
    {
        sprite_set_dy(player_data.sprite_data, sprite_dy(player_data.sprite_data) - JUMP_RECOVERY_BOOST);
    }
    else if (key_typed(SPACE_KEY))
    {
        player_data.state = PLAY;
    }
}

void check_for_collisions(game_data &game)
{
    int i;

    if (sprite_collision(game.player_data.sprite_data, game.scene.foreground) || sprite_collision(game.player_data.sprite_data, game.scene.foreroof))
    {
        game.player_data.is_dead = true;
        return;
    }

    for (i = 0; i < NUM_POLES; i++)
    {
        if (sprite_collision(game.player_data.sprite_data, game.poles_data[i].up_pole) || sprite_collision(game.player_data.sprite_data, game.poles_data[i].down_pole))
        {
            game.player_data.is_dead = true;
            return;
        }
    }
}

void reset_pole_data(pole_data &poles)
{
    free_sprite(poles.up_pole);
    free_sprite(poles.down_pole);
    poles = get_random_poles();
}

void reset_player(player &player_data)
{
    free_sprite(player_data.sprite_data);
    player_data = get_new_player();
}

void reset_game(game_data &game)
{
    int i;

    reset_player(game.player_data);
    for (i = 0; i < NUM_POLES; i++)
    {
        reset_pole_data(game.poles_data[i]);
    }
}

void update_velocity(sprite player)
{
    sprite_set_dy(player, sprite_dy(player) + GRAVITY);

    if (sprite_dy(player) > MAX_SPEED)
    {
        sprite_set_dy(player, MAX_SPEED);
    }
    else if (sprite_dy(player) < -(MAX_SPEED))
    {
        sprite_set_dy(player, -(MAX_SPEED));
    }
}

void update_poles(pole_data &poles, player &player)
{
    update_sprite(poles.up_pole);
    update_sprite(poles.down_pole);

    if ((sprite_x(poles.up_pole) < sprite_x(player.sprite_data)) && (poles.score_limiter == true))
    {
        poles.score_limiter = false;
        player.score++;
    }

    if ((sprite_x(poles.up_pole) + sprite_width(poles.up_pole) < 0) && (sprite_x(poles.down_pole) + sprite_width(poles.down_pole) < 0))
    {
        reset_pole_data(poles);
    }
}

void update_poles_array(pole_data poles_array[], player &player)
{
    int i;

    for (i = 0; i < NUM_POLES; i++)
    {
        update_poles(poles_array[i], player);
    }
}

void update_background(background_data &scene)
{
    update_sprite(scene.foreground);
    update_sprite(scene.foreroof);
    update_sprite(scene.background);

    if (sprite_x(scene.foreground) <= -(sprite_width(scene.foreground) / 2))
    {
        sprite_set_x(scene.foreground, 0);
        sprite_set_x(scene.foreroof, 0);
    }
    if (sprite_x(scene.background) <= -(sprite_width(scene.background) / 2))
    {
        sprite_set_x(scene.background, 0);
    }
}

void update_player(player &player)
{
    if (player.state == PLAY)
    {
        update_velocity(player.sprite_data);
    }
    update_sprite(player.sprite_data);
}

void update_game(game_data &game)
{
    if ( not game.player_data.is_dead)
    {
        check_for_collisions(game);
        handle_input(game.player_data);
        update_background(game.scene);
        update_player(game.player_data);
        if (game.player_data.state == PLAY)
        {
            update_poles_array(game.poles_data, game.player_data);
        }
    }
    else
    {
        reset_game(game);
    }
}

void draw_poles(pole_data &poles)
{
    draw_sprite(poles.up_pole);
    draw_sprite(poles.down_pole);
}

void draw_poles_array(pole_data poles_array[])
{
    int i;

    for (i = 0; i < NUM_POLES; i++)
    {
        draw_poles(poles_array[i]);
    }
}

void draw_game(game_data &game)
{
    char str[15];

    sprintf(str, "%d", game.player_data.score);

    draw_sprite(game.scene.background);
    draw_poles_array(game.poles_data);
    draw_sprite(game.scene.foreroof);
    draw_sprite(game.scene.foreground);
    draw_sprite(game.player_data.sprite_data);
    if (game.player_data.state == PLAY)
    {
        draw_text(str, COLOR_WHITE, "GameFont", 21, 10, 0);
    }
    else if (game.player_data.state == MENU)
    {
        draw_bitmap(bitmap_named("Logo"), 0, 40);
        draw_text("PRESS SPACE!",
                  COLOR_WHITE,
                  "GameFont",
                  21,
                  180, 680);
    }
}

void set_up_game(game_data &game)
{
    int i;

    load_resource_bundle("CaveEscape", "cave_escape.txt");
    for (i = 0; i < NUM_POLES; i++)
    {
        game.poles_data[i] = get_random_poles();
    }
    game.player_data = get_new_player();
    game.scene = get_new_background();
    fade_music_in("GameMusic", -1, 15000);
}

int main()
{
    game_data game;

    open_window("Cave Escape", 432, 768);
    set_up_game(game);

    do
    {
        process_events();
        clear_screen(COLOR_WHITE);
        update_game(game);
        draw_game(game);
        refresh_screen();

    } while(!window_close_requested("Cave Escape"));
    
    free_resource_bundle("CaveEscape");
    close_window("Cave Escape");
}
