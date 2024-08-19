/**
 * Bitmap Unit Tests
 */

#include "catch.hpp"

#include "types.h"
#include "graphics.h"
#include "resources.h"

using namespace splashkit_lib;

TEST_CASE("bitmaps can be created and freed", "[bitmap]")
{
    SECTION("can detect non-existent bitmap")
    {
        REQUIRE(has_bitmap("non_existent") == false);
        bitmap no_bmp = load_bitmap("non_existent", "non_existent.jpg");
        REQUIRE(no_bmp == nullptr);
        REQUIRE(has_bitmap("non_existent") == false);
    }
    SECTION("can load and free bitmap")
    {
        bitmap bmp;
        SECTION("can load bitmap")
        {
            REQUIRE(has_bitmap("cottage") == false);
            bmp = load_bitmap("cottage", "cottage_door_and_window_199195.jpg");
            REQUIRE(bmp != nullptr);
            REQUIRE(has_bitmap("cottage") == true);
            REQUIRE(bitmap_valid(bmp) == true);
            REQUIRE(bitmap_width(bmp) == 500);
            REQUIRE(bitmap_height(bmp) == 333);
            REQUIRE(bitmap_name(bmp) == "cottage");
            REQUIRE(bitmap_filename(bmp) == path_to_resource("cottage_door_and_window_199195.jpg", IMAGE_RESOURCE));
            REQUIRE(bitmap_named("cottage") == bmp);
        }
        SECTION("can free bitmap")
        {
            free_bitmap(bmp);
            REQUIRE(has_bitmap("cottage") == false);
        }
    }
    SECTION("can load and free multiple bitmaps")
    {
        bitmap bmp, bmp2;
        SECTION("can load and create two bitmaps")
        {
            REQUIRE(has_bitmap("player") == false);
            bmp = load_bitmap("player", "player.png");
            REQUIRE(bmp != nullptr);
            REQUIRE(has_bitmap("player") == true);
            REQUIRE(bitmap_valid(bmp) == true);
            REQUIRE(bitmap_width(bmp) == 300);
            REQUIRE(bitmap_height(bmp) == 42);
            REQUIRE(bitmap_name(bmp) == "player");
            REQUIRE(bitmap_filename(bmp) == path_to_resource("player.png", IMAGE_RESOURCE));
            REQUIRE(bitmap_named("player") == bmp);
            REQUIRE(has_bitmap("ufo") == false);
            bmp2 = load_bitmap("ufo", "ufo.png");
            REQUIRE(bmp2 != nullptr);
            REQUIRE(has_bitmap("ufo") == true);
            REQUIRE(bitmap_valid(bmp2) == true);
            REQUIRE(bitmap_width(bmp2) == 35);
            REQUIRE(bitmap_height(bmp2) == 33);
            REQUIRE(bitmap_name(bmp2) == "ufo");
            REQUIRE(bitmap_filename(bmp2) == path_to_resource("ufo.png", IMAGE_RESOURCE));
            REQUIRE(bitmap_named("ufo") == bmp2);
        }
        SECTION("can free all bitmaps")
        {
            free_all_bitmaps();
            REQUIRE(has_bitmap("player") == false);
            REQUIRE(has_bitmap("ufo") == false);
        }
    }
}
