/**
 * Bitmap Unit Tests
 */

#include "catch.hpp"

#include "types.h"
#include "graphics.h"

using namespace splashkit_lib;

TEST_CASE("bitmap can be created and freed", "[bitmap]")
{
    SECTION("can detect non-existant bitamp has not been loaded")
    {
        bitmap no_bmp = load_bitmap("non_existent", "non_existent.jpg");
        REQUIRE(has_bitmap("non_existent") == false);
    }
    SECTION("can load and create bitmap")
    {
        bitmap bmp = load_bitmap("cottage", "cottage_door_and_window_199195.jpg");
        REQUIRE(has_bitmap("cottage") == true);
        REQUIRE(bitmap_valid(bmp) == true);
        REQUIRE(bitmap_width(bmp) == 500);
        REQUIRE(bitmap_height(bmp) == 333);
        SECTION("can free bitmap")
        {
            free_bitmap(bmp);
            REQUIRE(has_bitmap("cottage") == false);
        }
    }
    SECTION("can free all bitmaps")
    {
        bitmap bmp2, bmp3;
        SECTION("can load and create two bitmaps")
        {
            bmp2 = load_bitmap("player", "player.png");
            REQUIRE(has_bitmap("player") == true);
            REQUIRE(bitmap_valid(bmp2) == true);
            bmp3 = load_bitmap("ufo", "ufo.png");
            REQUIRE(has_bitmap("ufo") == true);
            REQUIRE(bitmap_valid(bmp3) == true);
        }
        SECTION("can free all bitmaps")
        {
            free_all_bitmaps();
            REQUIRE(has_bitmap("player") == false);
            REQUIRE(has_bitmap("ufo") == false);
        }
    }
}
