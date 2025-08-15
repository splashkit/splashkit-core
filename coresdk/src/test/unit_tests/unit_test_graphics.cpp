/**
 * Graphics Unit Tests
 */

#include "catch.hpp"

#include "graphics.h"
#include "window_manager.h"

using namespace splashkit_lib;

TEST_CASE("screen dimension utilities", "[screen_width][screen_height]")
{
    SECTION("check that screen width and screen height are correct")
    {
        window w = open_window("test window", 200, 100);

        REQUIRE(screen_width() == 200);
        REQUIRE(screen_height() == 100);

        close_window(w);
    }
}
