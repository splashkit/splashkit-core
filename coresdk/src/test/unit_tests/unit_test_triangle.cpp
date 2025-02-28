/*  Copyright (C) 2024 Hayley Hughes
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <vector>

#include "catch.hpp"

#include "types.h"
#include "triangle_geometry.h"
#include "rectangle_geometry.h"
#include "point_geometry.h"

using namespace splashkit_lib;

TEST_CASE("triangle and rectangle collision detection", "[triangle][rectangle]")
{
    triangle t = triangle_from(0, 0, 50, 100, 100, 0);

    SECTION("non-intersecting")
    {
        rectangle r = rectangle_from(200, 0, 50, 50);

        CHECK_FALSE(triangle_rectangle_intersect(t, r));
    }

    SECTION("rectangle intersects with triangle bounding box but not triangle itself")
    {
        rectangle r = rectangle_from(0, 90, 1, 1);

        CHECK_FALSE(triangle_rectangle_intersect(t, r));
    }

    SECTION("rectangle intersects with triangle")
    {
        SECTION("left side")
        {
            rectangle r = rectangle_from(50, 0, -100, 100);
            CHECK(triangle_rectangle_intersect(t, r));
        }
        
        SECTION("right side")
        {
            rectangle r = rectangle_from(50, 0, 100, 100);
            CHECK(triangle_rectangle_intersect(t, r));
        }
    }

    SECTION("rectangle inside triangle")
    {
        rectangle r = rectangle_from(45, 1, 10, 10);
        CHECK(triangle_rectangle_intersect(t, r));
    }

    SECTION("triangle point ordering")
    {
        vector<point_2d> triangle_points = {point_at(0, 0), point_at(50, 100), point_at(100, 0)};
        rectangle r = rectangle_from(0, 0, 50, 50);

        for (point_2d a : triangle_points) {
            for (point_2d b : triangle_points) {
                for (point_2d c : triangle_points) {
                    if (same_point(a, b) or same_point(a, c) or same_point(b, c)) continue;

                    triangle t = triangle_from(a, b, c);
                    CHECK(triangle_rectangle_intersect(t, r));
                }
            }
        }
    }
}

