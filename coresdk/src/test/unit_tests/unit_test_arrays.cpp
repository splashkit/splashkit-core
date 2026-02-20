#include "catch.hpp"

#include "terminal.h"
#include "basics.h"
using namespace splashkit_lib;

#include "splashkit-arrays.h"

#include <string>

using std::string;

namespace
{
    fixed_array<int, 5> build_fixed_sequence()
    {
        fixed_array<int, 5> arr(0);
        arr[0] = 10;
        arr[1] = 20;
        arr[4] = 30;
        return arr;
    }

    int fixed_first_plus_last(fixed_array<int, 5> arr)
    {
        return arr[0] + arr[arr.length() - 1];
    }

    void fixed_write_first(fixed_array<int, 5>& arr, int value)
    {
        arr[0] = value;
    }

    dynamic_array<int> build_dynamic_sequence()
    {
        dynamic_array<int> arr;
        arr.add(1);
        arr.add(2);
        arr.add(3);
        return arr;
    }

    int dynamic_sum(dynamic_array<int> arr)
    {
        int result = 0;
        for (int i = 0; i < arr.length(); ++i)
        {
            result += arr[i];
        }
        return result;
    }

    void dynamic_append(dynamic_array<int>& arr, int value)
    {
        arr.add(value);
    }

    struct lifetime_tracker
    {
        static int live_count;
        static int constructions;
        static int destructions;

        int value;

        lifetime_tracker(int v = 0) : value(v)
        {
            constructions++;
            live_count++;
        }

        lifetime_tracker(const lifetime_tracker& other) : value(other.value)
        {
            constructions++;
            live_count++;
        }

        ~lifetime_tracker()
        {
            destructions++;
            live_count--;
        }
    };

    int lifetime_tracker::live_count = 0;
    int lifetime_tracker::constructions = 0;
    int lifetime_tracker::destructions = 0;

    void reset_lifetime_counters()
    {
        lifetime_tracker::live_count = 0;
        lifetime_tracker::constructions = 0;
        lifetime_tracker::destructions = 0;
    }
}

TEST_CASE("fixed_array basic operations", "[arrays][fixed]")
{
    fixed_array<int, 5> arr;
    REQUIRE(arr.length() == 5);

    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;

    REQUIRE(arr[0] == 10);
    REQUIRE(arr[1] == 20);
    REQUIRE(arr[2] == 30);
}

TEST_CASE("fixed_array helpers and safety methods", "[arrays][fixed]")
{
    fixed_array<int, 5> arr(7);
    REQUIRE(arr[0] == 7);
    REQUIRE(arr[1] == 7);
    REQUIRE(arr[2] == 7);
    REQUIRE(arr[3] == 7);
    REQUIRE(arr[4] == 7);

    fill(arr, 2);
    REQUIRE(arr[0] == 2);
    REQUIRE(arr[1] == 2);
    REQUIRE(arr[2] == 2);

    set(arr, 1, 11);
    REQUIRE(get(arr, 1) == 11);
    REQUIRE(length(arr) == 5);

    int value = 0;
    REQUIRE(try_get(arr, 1, value));
    REQUIRE(value == 11);
    REQUIRE_FALSE(try_get(arr, 10, value));

    REQUIRE(try_set(arr, 2, 9));
    REQUIRE(arr[2] == 9);
    REQUIRE_FALSE(try_set(arr, 10, 9));

}

TEST_CASE("fixed_array validates index", "[arrays][fixed]")
{
    fixed_array<int, 2> arr;
    REQUIRE_THROWS_AS(arr.get(-1), array_invalid_index);
    REQUIRE_THROWS_AS(arr.get(2), array_invalid_index);
}

TEST_CASE("fixed_array supports copy, pass and return", "[arrays][fixed]")
{
    fixed_array<int, 5> original = build_fixed_sequence();
    fixed_array<int, 5> copied = original;

    copied[0] = 99;
    REQUIRE(original[0] == 10);
    REQUIRE(copied[0] == 99);

    fixed_write_first(original, 7);
    REQUIRE(original[0] == 7);
    REQUIRE(fixed_first_plus_last(original) == 37);
}

TEST_CASE("dynamic_array basic operations", "[arrays][dynamic]")
{
    dynamic_array<int> arr;
    REQUIRE(arr.length() == 0);
    REQUIRE(arr.capacity() == 0);

    arr.add(10);
    arr.add(20);
    arr.add(30);

    REQUIRE(arr.length() == 3);
    REQUIRE(arr.capacity() >= arr.length());
    REQUIRE(arr[0] == 10);
    REQUIRE(arr[2] == 30);
}

TEST_CASE("dynamic_array set/get and free helper variants", "[arrays][dynamic]")
{
    dynamic_array<string> arr;
    arr.add("Hello");
    add(arr, "world");
    set(arr, 1, "world!");
    get(arr, 1) += "!";

    REQUIRE(arr[1] == "world!!");
    REQUIRE(get(arr, 0) == "Hello");
}

TEST_CASE("dynamic_array size-changing and insertion helpers", "[arrays][dynamic]")
{
    dynamic_array<int> arr;
    add(arr, 4);
    add(arr, 4);
    add(arr, 4);
    REQUIRE(arr.length() == 3);
    REQUIRE(arr[0] == 4);
    REQUIRE(arr[1] == 4);
    REQUIRE(arr[2] == 4);

    resize(arr, 5, 8);
    REQUIRE(arr.length() == 5);
    REQUIRE(arr[3] == 8);
    REQUIRE(arr[4] == 8);

    resize(arr, 2);
    REQUIRE(arr.length() == 2);

    insert(arr, 1, 99);
    REQUIRE(arr.length() == 3);
    REQUIRE(arr[1] == 99);

    remove_at(arr, 1);
    REQUIRE(arr.length() == 2);
    REQUIRE(arr[0] == 4);
    REQUIRE(arr[1] == 4);

    clear(arr);
    REQUIRE(is_empty_array(arr));
}

TEST_CASE("dynamic_array non-throwing helpers", "[arrays][dynamic]")
{
    dynamic_array<int> arr;
    add(arr, 10);
    add(arr, 10);

    int value = 0;
    REQUIRE(try_get(arr, 1, value));
    REQUIRE(value == 10);
    REQUIRE_FALSE(try_get(arr, 5, value));

    REQUIRE(try_set(arr, 1, 55));
    REQUIRE(arr[1] == 55);
    REQUIRE_FALSE(try_set(arr, 5, 55));
}

TEST_CASE("dynamic_array validates index and size", "[arrays][dynamic]")
{
    dynamic_array<int> arr;
    REQUIRE_THROWS_AS(arr.get(0), array_invalid_index);

    arr.add(5);
    REQUIRE_THROWS_AS(arr.get(-1), array_invalid_index);
    REQUIRE_THROWS_AS(arr.get(5), array_invalid_index);
    REQUIRE_THROWS_AS(arr.insert(3, 10), array_invalid_index);

    REQUIRE_THROWS_AS(arr.resize(-1), array_invalid_size);
}

TEST_CASE("dynamic_array lifetime handling", "[arrays][dynamic]")
{
    reset_lifetime_counters();

    {
        dynamic_array<lifetime_tracker> arr;
        for (int i = 0; i < 5; ++i)
        {
            arr.add(lifetime_tracker(i));
        }

        REQUIRE(lifetime_tracker::live_count == 5);

        arr.remove(2);
        REQUIRE(lifetime_tracker::live_count == 4);

        arr.remove(0);
        arr.remove(0);
        arr.remove(0);
        arr.remove(0);
        REQUIRE(lifetime_tracker::live_count == 0);
    }

    REQUIRE(lifetime_tracker::live_count == 0);
    REQUIRE(lifetime_tracker::constructions == lifetime_tracker::destructions);
}

TEST_CASE("dynamic_array supports copy, pass and return", "[arrays][dynamic]")
{
    dynamic_array<int> original = build_dynamic_sequence();
    dynamic_array<int> copied = original;

    copied[0] = 99;
    REQUIRE(original[0] == 1);
    REQUIRE(copied[0] == 99);

    dynamic_append(original, 4);
    REQUIRE(original.length() == 4);
    REQUIRE(dynamic_sum(original) == 10);
}
