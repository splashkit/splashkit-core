/**
 * Text and font Unit Tests
 */

#include <vector>

#include "catch.hpp"

#include "text.h"
#include "types.h"
#include "backend_types.h"
#include "utility_functions.h"

using namespace splashkit_lib;

TEST_CASE("can load system fonts", "[text]")
{
    font test;
    #ifndef __linux__
    test = load_font("Arial", "Arial");
    #else
    test = load_font("Arial", "DejaVuSans.ttf");
    #endif

    SECTION("can load arial")
    {
        REQUIRE(test != nullptr);
        REQUIRE(VALID_PTR(test, FONT_PTR));
    }
}
