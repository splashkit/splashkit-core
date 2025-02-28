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

#include "web_server.h"

using namespace splashkit_lib;

TEST_CASE("split uri stubs", "[web_server]")
{
    vector<string> empty;

    SECTION("can parse uri without path")
    {
       CHECK(split_uri_stubs("")  == empty);
       CHECK(split_uri_stubs("/") == (vector<string>) {""});
    }

    SECTION("can parse uri with path")
    {
       CHECK(split_uri_stubs("/one")      == (vector<string>) {"one"});
       CHECK(split_uri_stubs("/one/two/") == (vector<string>) {"one", "two"});
    }

    SECTION("can parse uri with arguments")
    {
       CHECK(split_uri_stubs("?foo=bar")      == empty);
       CHECK(split_uri_stubs("/one/?foo=bar") == (vector<string>) {"one"});
       CHECK(split_uri_stubs("/one?foo=bar")  == (vector<string>) {"one"});
    }
}

