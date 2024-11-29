/**
 * Geometry Unit Tests
 */

#include "catch.hpp"

#include "types.h"
#include "point_geometry.h"

using namespace splashkit_lib;

constexpr double EPSILON = 1.0E-13;

TEST_CASE("can perform circle geometry", "[geometry]")
{
   SECTION("can detect circle quad intersection")
   {
        circle c = circle_at(100.0, 100.0, 50.0);
        quad q = quad_from(rectangle_from(50.0, 50.0, 100.0, 100.0));
        REQUIRE(circle_quad_intersect(c, q));
        q = quad_from(rectangle_from(200.0, 200.0, 100.0, 100.0));
        REQUIRE_FALSE(circle_quad_intersect(c, q));
   }
}
TEST_CASE("can perform rectangle geometry", "[rectangle]")
{
    SECTION("can detect rectangle circle intersection")
    {
        rectangle r = rectangle_from(100.0, 100.0, 100.0, 100.0);
        circle c = circle_at(150.0, 150.0, 50.0);
        REQUIRE(rectangle_circle_intersect(r, c));
        c = circle_at(200.0, 200.0, 50.0);
        REQUIRE_FALSE(rectangle_circle_intersect(r, c));
    }
}
TEST_CASE("can perform triangle geometry", "[triangle]")
{
    SECTION("can detect triangle quad intersection")
    {
        triangle t = triangle_from(100.0, 100.0, 200.0, 100.0, 150.0, 150.0);
        quad q = quad_from(50.0, 50.0, 150.0, 50.0, 50.0, 150.0, 150.0, 150.0);
        REQUIRE(triangle_quad_intersect(t, q));
        q = quad_from(200.0, 200.0, 300.0, 200.0, 200.0, 300.0, 300.0, 300.0);
        REQUIRE_FALSE(triangle_quad_intersect(t, q));
    }
}
