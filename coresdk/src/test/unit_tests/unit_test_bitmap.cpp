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
        string filename = "cottage_door_and_window_199195.jpg", name = "cottage";
        int width = 500, height = 333;
        SECTION("can load bitmap")
        {
            REQUIRE(has_bitmap(name) == false);
            bmp = load_bitmap(name, filename);
            REQUIRE(bmp != nullptr);
            REQUIRE(has_bitmap(name) == true);
            REQUIRE(bitmap_valid(bmp) == true);
            REQUIRE(bitmap_width(bmp) == width);
            REQUIRE(bitmap_height(bmp) == height);
            REQUIRE(bitmap_name(bmp) == name);
            REQUIRE(bitmap_filename(bmp) == path_to_resource(filename, IMAGE_RESOURCE));
            REQUIRE(bitmap_named(name) == bmp);
        }
        SECTION("can free bitmap")
        {
            free_bitmap(bmp);
            REQUIRE(has_bitmap(name) == false);
        }
    }
    SECTION("can load and free multiple bitmaps")
    {
        bitmap bmp1, bmp2;
        string filename1 = "player.png", name1 = "player", filename2 = "ufo.png", name2 = "ufo";
        int width1 = 300, height1 = 42, width2 = 35, height2 = 33;
        SECTION("can load and create two bitmaps")
        {
            REQUIRE(has_bitmap(name1) == false);
            bmp1 = load_bitmap(name1, filename1);
            REQUIRE(bmp1 != nullptr);
            REQUIRE(has_bitmap(name1) == true);
            REQUIRE(bitmap_valid(bmp1) == true);
            REQUIRE(bitmap_width(bmp1) == 300);
            REQUIRE(bitmap_height(bmp1) == 42);
            REQUIRE(bitmap_name(bmp1) == name1);
            REQUIRE(bitmap_filename(bmp1) == path_to_resource(filename1, IMAGE_RESOURCE));
            REQUIRE(bitmap_named(name1) == bmp1);

            REQUIRE(has_bitmap(name2) == false);
            bmp2 = load_bitmap(name2, filename2);
            REQUIRE(bmp2 != nullptr);
            REQUIRE(has_bitmap(name2) == true);
            REQUIRE(bitmap_valid(bmp2) == true);
            REQUIRE(bitmap_width(bmp2) == 35);
            REQUIRE(bitmap_height(bmp2) == 33);
            REQUIRE(bitmap_name(bmp2) == name2);
            REQUIRE(bitmap_filename(bmp2) == path_to_resource(filename2, IMAGE_RESOURCE));
            REQUIRE(bitmap_named(name2) == bmp2);
        }
        SECTION("can free all bitmaps")
        {
            free_all_bitmaps();
            REQUIRE(has_bitmap(name1) == false);
            REQUIRE(has_bitmap(name2) == false);
        }
    }
}
