/**
 * Sprites Unit Tests
 */

#include "catch.hpp"

#include "sprites.h"
#include "images.h"

using namespace splashkit_lib;

constexpr int ROCKET_WIDTH = 36, ROCKET_HEIGHT = 72,
    FROG_WIDTH = 294, FROG_HEIGHT = 422,
        BACKGROUND_WIDTH = 864, BACKGROUND_HEIGHT = 769;

bitmap rocket_bmp, frog_bmp, background_bmp;

TEST_CASE("bitmaps can be created", "[bitmap]")
{
    rocket_bmp = load_bitmap("rocket_sprt", "rocket_sprt.png");
    REQUIRE(bitmap_valid(rocket_bmp));
    REQUIRE(rocket_bmp != nullptr);
    REQUIRE(bitmap_width(rocket_bmp) == ROCKET_WIDTH);
    REQUIRE(bitmap_height(rocket_bmp) == ROCKET_HEIGHT);
    frog_bmp = load_bitmap("frog", "frog.png");
    REQUIRE(bitmap_valid(frog_bmp));
    REQUIRE(frog_bmp != nullptr);
    REQUIRE(bitmap_width(frog_bmp) == FROG_WIDTH);
    REQUIRE(bitmap_height(frog_bmp) == FROG_HEIGHT);
    background_bmp = load_bitmap("background", "background.png");
    REQUIRE(bitmap_valid(background_bmp));
    REQUIRE(background_bmp != nullptr);
    REQUIRE(bitmap_width(background_bmp) == BACKGROUND_WIDTH);
    REQUIRE(bitmap_height(background_bmp) == BACKGROUND_HEIGHT);
}
TEST_CASE("sprites can be created and freed", "[sprite]")
{
    SECTION("can detect non-existent sprite")
    {
        REQUIRE_FALSE(has_sprite("non_existent"));
        bitmap non_bmp = bitmap_named("non_existent");
        REQUIRE(non_bmp == nullptr);
        REQUIRE_FALSE(has_sprite("non_existent"));
        sprite no_sprite = create_sprite("non-existent", non_bmp);
        REQUIRE_FALSE(has_sprite("non_existent"));
    }
    SECTION("can create and free sprite")
    {
        REQUIRE_FALSE(has_sprite("rocket"));
        sprite sprt = create_sprite("rocket", rocket_bmp);
        REQUIRE(has_sprite("rocket"));
        free_sprite(sprt);
        REQUIRE_FALSE(has_sprite("rocket"));
    }
    SECTION("can create and free sprite with animation")
    {
        animation_script kermit = load_animation_script("kermit", "kermit.txt");
        REQUIRE(has_animation_script("kermit"));
        REQUIRE_FALSE(has_sprite("frog"));
        sprite sprt = create_sprite("frog", frog_bmp, kermit);
        REQUIRE(has_sprite("frog"));
        free_sprite(sprt);
        REQUIRE_FALSE(has_sprite("frog"));
        free_animation_script(kermit);
        REQUIRE_FALSE(has_animation_script("kermit"));
    }
    SECTION("can free multiple sprites")
    {
        REQUIRE_FALSE(has_sprite("rocket"));
        sprite sprt = create_sprite("rocket", rocket_bmp);
        REQUIRE(has_sprite("rocket"));
        sprite sprt2 = create_sprite("rocket2", rocket_bmp);
        REQUIRE(has_sprite("rocket2"));
        free_all_sprites();
        REQUIRE_FALSE(has_sprite("rocket"));
        REQUIRE_FALSE(has_sprite("rocket2"));
    }
}
TEST_CASE("sprite dimensions can be retrieved", "[sprite]")
{
    sprite sprt = create_sprite("rocket", rocket_bmp);
    REQUIRE(sprite_width(sprt) == ROCKET_WIDTH);
    REQUIRE(sprite_height(sprt) == ROCKET_HEIGHT);
    free_sprite(sprt);
}
TEST_CASE("sprite default matrix is correct", "[sprite]")
{
    sprite sprt = create_sprite("rocket", rocket_bmp);
    matrix_2d m = sprite_location_matrix(sprt);
    rectangle r = sprite_collision_rectangle(sprt);
    matrix_2d translation = translation_matrix(r.x, r.y);
    REQUIRE(m.elements[0][0] == translation.elements[0][0]);
    REQUIRE(m.elements[0][1] == translation.elements[0][1]);
    REQUIRE(m.elements[0][2] == translation.elements[0][2]);
    REQUIRE(m.elements[1][0] == translation.elements[1][0]);
    REQUIRE(m.elements[1][1] == translation.elements[1][1]);
    REQUIRE(m.elements[1][2] == translation.elements[1][2]);
    REQUIRE(m.elements[2][0] == translation.elements[2][0]);
    REQUIRE(m.elements[2][1] == translation.elements[2][1]);
    REQUIRE(m.elements[2][2] == translation.elements[2][2]);
}
TEST_CASE("sprite can be moved", "[sprite]")
{
    sprite sprt = create_sprite("rocket", rocket_bmp);
    REQUIRE(has_sprite("rocket"));

    SECTION("initial position is (0, 0)")
    {
        REQUIRE(sprite_x(sprt) == 0.0);
        REQUIRE(sprite_y(sprt) == 0.0);
    }
    SECTION("can set sprite position")
    {
        sprite_set_x(sprt, 100.0);
        sprite_set_y(sprt, 200.0);
        point_2d pos = sprite_position(sprt);
        REQUIRE(pos.x == 100.0);
        REQUIRE(pos.y == 200.0);
        REQUIRE(sprite_x(sprt) == 100.0);
        REQUIRE(sprite_y(sprt) == 200.0);
    }
    SECTION("can set sprite position with point")
    {
        sprite_set_position(sprt, point_at(300.0, 400.0));
        point_2d pos = sprite_position(sprt);
        REQUIRE(pos.x == 300.0);
        REQUIRE(pos.y == 400.0);
        REQUIRE(sprite_x(sprt) == 300.0);
        REQUIRE(sprite_y(sprt) == 400.0);
        sprite_set_position(sprt, point_at(0.0, 0.0));
        pos = sprite_position(sprt);
        REQUIRE(pos.x == 0.0);
        REQUIRE(pos.y == 0.0);
        REQUIRE(sprite_x(sprt) == 0.0);
        REQUIRE(sprite_y(sprt) == 0.0);

        SECTION("can set sprite position to extreme values")
        {
            sprite_set_position(sprt, point_at(__DBL_MAX__, -__DBL_MAX__));
            pos = sprite_position(sprt);
            REQUIRE(pos.x == __DBL_MAX__);
            REQUIRE(pos.y == -__DBL_MAX__);
            REQUIRE(sprite_x(sprt) == __DBL_MAX__);
            REQUIRE(sprite_y(sprt) == -__DBL_MAX__);
            sprite_set_position(sprt, point_at(__DBL_MIN__, -__DBL_MIN__));
            pos = sprite_position(sprt);
            REQUIRE(pos.x == __DBL_MIN__);
            REQUIRE(pos.y == -__DBL_MIN__);
            REQUIRE(sprite_x(sprt) == __DBL_MIN__);
            REQUIRE(sprite_y(sprt) == -__DBL_MIN__);
        }
    }
    SECTION("can move sprite by anchor point")
    {
        sprite_set_move_from_anchor_point(sprt, true);
        sprite_set_anchor_point(sprt, point_at(30.0, 50.0));
        move_sprite_to(sprt, 500.0, 500.0);
        REQUIRE(sprite_x(sprt) == 500.0 - 30.0);
        REQUIRE(sprite_y(sprt) == 500.0 - 50.0);
    }
    SECTION("can move sprite from origin")
    {
        sprite_set_move_from_anchor_point(sprt, false);
        move_sprite_to(sprt, 10.0, 20.0);
        REQUIRE(sprite_x(sprt) == 10.0);
        REQUIRE(sprite_y(sprt) == 20.0);
    }
    SECTION("can get center point of sprite")
    {
        SECTION("sprite dimensions can be retrieved")
        {
            REQUIRE(sprite_width(sprt) == ROCKET_WIDTH);
            REQUIRE(sprite_height(sprt) == ROCKET_HEIGHT);
        }
        point_2d pos = sprite_position(sprt);
        point_2d center = center_point(sprt);
        REQUIRE(center.x == pos.x + ROCKET_WIDTH / 2.0);
        REQUIRE(center.y == pos.y + ROCKET_HEIGHT / 2.0);
    }
    free_sprite(sprt);
}
TEST_CASE("can check sprite intersection", "[sprite]")
{
    sprite sprt = create_sprite("background", background_bmp);
    REQUIRE(has_sprite("background"));
    sprite_set_move_from_anchor_point(sprt, false);
    sprite sprt2 = create_sprite("background_2", background_bmp);
    REQUIRE(has_sprite("background_2"));
    sprite_set_move_from_anchor_point(sprt2, false);

    SECTION("can check AABB collision")
    {
        sprite_set_collision_kind(sprt, AABB_COLLISIONS);
        sprite_set_collision_kind(sprt2, AABB_COLLISIONS);
        sprite_set_position(sprt, point_at(100.0, 100.0));
        sprite_set_position(sprt2, point_at(1300.0, 1300.0));
        REQUIRE_FALSE(sprite_collision(sprt, sprt2));
        REQUIRE_FALSE(sprite_rectangle_collision(sprt, sprite_collision_rectangle(sprt2)));
        sprite_set_position(sprt2, point_at(100.0, 100.0));
        REQUIRE(sprite_collision(sprt, sprt2));
        REQUIRE(sprite_rectangle_collision(sprt, sprite_collision_rectangle(sprt2)));

        SECTION("can detect small intersection")
        {
            sprite_set_position(sprt2, point_at(0.0, 0.0));
            sprite_set_position(sprt, point_at(sprite_width(sprt2), 0.0));
            REQUIRE_FALSE(sprite_collision(sprt, sprt2));
            REQUIRE_FALSE(sprite_rectangle_collision(sprt, sprite_collision_rectangle(sprt2)));
            sprite_set_position(sprt, point_at(sprite_width(sprt2) - 1.0, 0.0));

            rectangle r = sprite_collision_rectangle(sprt);
            REQUIRE(r.height == BACKGROUND_HEIGHT);
            REQUIRE(r.width == BACKGROUND_WIDTH);
            REQUIRE(r.x == 863.0);
            REQUIRE(r.y == 0.0);
            REQUIRE(sprite_collision_bitmap(sprt) == background_bmp);
            REQUIRE(sprite_current_cell(sprt) == 0);

            rectangle r2 = sprite_collision_rectangle(sprt2);
            REQUIRE(r2.height == 769.0);
            REQUIRE(r2.width == 864.0);
            REQUIRE(r2.x == 0.0);
            REQUIRE(r2.y == 0.0);
            REQUIRE(sprite_collision_bitmap(sprt2) == background_bmp);
            REQUIRE(sprite_current_cell(sprt2) == 0);

            REQUIRE(sprite_collision(sprt, sprt2));
            REQUIRE(rectangles_intersect(sprite_collision_rectangle(sprt), sprite_collision_rectangle(sprt2)));

            quad q1, q2;
            q1 = quad_from(bitmap_cell_rectangle(sprite_collision_bitmap(sprt)), sprite_location_matrix(sprt));
            q2 = quad_from(sprite_collision_rectangle(sprt2));
            REQUIRE(quads_intersect(q1, q2));

            REQUIRE(bitmap_rectangle_collision(sprite_collision_bitmap(sprt), sprite_current_cell(sprt),
                sprite_location_matrix(sprt), sprite_collision_rectangle(sprt2)));

            REQUIRE(sprite_rectangle_collision(sprt, sprite_collision_rectangle(sprt2)));
        }
    }
    SECTION("can check pixel collision")
    {
        sprite_set_collision_kind(sprt, PIXEL_COLLISIONS);
        sprite_set_collision_kind(sprt2, PIXEL_COLLISIONS);
        sprite_set_position(sprt, point_at(100.0, 100.0));
        sprite_set_position(sprt2, point_at(1500.0, 1500.0));
        REQUIRE_FALSE(sprite_collision(sprt, sprt2));
        sprite_set_position(sprt2, point_at(100.0, 100.0));
        REQUIRE(sprite_collision(sprt, sprt2));
    }
    SECTION("can check sprite intersection with bitmap")
    {
        sprite_set_collision_kind(sprt, PIXEL_COLLISIONS);
        sprite_set_position(sprt, point_at(100.0, 100.0));
        REQUIRE_FALSE(sprite_bitmap_collision(sprt, frog_bmp, 0, 1500.0, 1500.0));
        REQUIRE(sprite_bitmap_collision(sprt, frog_bmp, 0, 100.0, 100.0));
    }
    SECTION("can check sprite intersection with point")
    {
        sprite_set_collision_kind(sprt2, AABB_COLLISIONS);
        sprite_set_move_from_anchor_point(sprt2, false);
        sprite_set_position(sprt2, point_at(0.0, 0.0));
        REQUIRE_FALSE(sprite_point_collision(sprt2, point_at(2000.0, 2000.0)));
        REQUIRE(sprite_point_collision(sprt2, point_at(400.0, 400.0)));
        REQUIRE_FALSE(sprite_point_collision(sprt2, point_at(0.0, 0.0)));

        point_2d pt1 = point_at(0.1, 0.1);
        circle c = sprite_collision_circle(sprt2);
        point_2d center = center_point(sprt2);
        REQUIRE(c.center.x == center.x);
        REQUIRE(c.center.y == center.y);
        REQUIRE(c.radius == sqrt(pow(BACKGROUND_WIDTH / 2.0, 2.0) + pow(BACKGROUND_HEIGHT / 2.0, 2.0)));
        REQUIRE(point_in_circle(pt1, c));
        REQUIRE(sprite_point_collision(sprt2, pt1));

        point_2d pt2 = point_at(0.000001, 0.000001);
        REQUIRE(point_in_circle(pt2, sprite_collision_circle(sprt2)));
        REQUIRE(sprite_point_collision(sprt2, pt2));

        //REQUIRE(sprite_point_collision(sprt2, point_at(__DBL_MIN__, __DBL_MIN__)));
    }
    free_sprite(sprt);
    free_sprite(sprt2);
}
TEST_CASE("bitmaps can be freed", "[bitmap]")
{
    free_bitmap(rocket_bmp);
    REQUIRE_FALSE(has_bitmap("rocket_sprt"));
    free_bitmap(frog_bmp);
    REQUIRE_FALSE(has_bitmap("frog"));
    free_bitmap(background_bmp);
    REQUIRE_FALSE(has_bitmap("background"));
}

// sprite pack, calls for sprites, sprite functions