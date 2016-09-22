/**
 * JSON Unit Tests
 *
 * Created by James Armstrong http://github.com/jarmstrong
 */

#include <vector>

#include "catch.hpp"

#include "types.h"
#include "json.h"
#include "color.h"

using namespace splashkit_lib;

json create_person()
{
    json person = create_json();

    json_set_string(person, "firstName", "John");
    json_set_string(person, "lastName", "Smith");

    json addresses = create_json();
    json_set_string(addresses, "streetAddress", "21 2nd Street");
    json_set_string(addresses, "city", "New York");
    json_set_string(addresses, "state", "NY");
    json_set_number(addresses, "postalCode", 10021);

    json_set_object(person, "addresses", addresses);

    vector<string> numbers = {"212 555-1234", "646 555-4567"};
    json_set_array(person, "phoneNumbers", numbers);

    json_set_bool(person, "pensioner", true);

    return person;
}

TEST_CASE("json can be created and read", "[json]")
{
    json person = create_person();

    SECTION("can read strings from json")
    {
        REQUIRE(json_read_string(person, "firstName") == "John");
        REQUIRE(json_read_string(person, "lastName") == "Smith");
    }

    SECTION("can read from nested json objects")
    {
        json addresses = json_read_object(person, "addresses");

        REQUIRE(json_read_string(addresses, "streetAddress") == "21 2nd Street");
        REQUIRE(json_read_string(addresses, "city") == "New York");
        REQUIRE(json_read_string(addresses, "state") == "NY");
        REQUIRE(json_read_number_as_int(addresses, "postalCode") == 10021);

        vector<string> validation_numbers { "212 555-1234", "646 555-4567" };
        vector<string> numbers;
        json_read_array(person, "phoneNumbers", numbers);

        REQUIRE(validation_numbers.size() == numbers.size());

        for (int i = 0; i < validation_numbers.size(); ++i)
        {
            REQUIRE(validation_numbers[i] == numbers[i]);
        }

        REQUIRE(json_read_bool(person, "pensioner") == true);
    }

    SECTION("json can be converted to other forms")
    {
        SECTION("json can be written to/from string")
        {
            string json_string = json_to_string(person);
            json j = json_from_string(json_string);

            REQUIRE(json_read_string(j, "firstName") == "John");
        }

        SECTION("json can be written to/from file")
        {
            string filename = "person.json";
            json_to_file(person, filename);
            json j = json_from_file(filename);

            REQUIRE(json_read_string(j, "firstName") == "John");
        }
    }

    SECTION("can check if key exists in json")
    {
        REQUIRE(json_has_key(person, "firstName"));
        REQUIRE(json_has_key(person, "addresses"));
        json addresses = json_read_object(person, "addresses");
        REQUIRE(json_has_key(addresses, "postalCode"));

        SECTION("json_has_key will not search nested objects")
        {
            REQUIRE(json_has_key(person, "postalCode") == false);
        }

        REQUIRE(json_count_keys(person) == 5);
    }

    SECTION("can convert colors to/from json in hex form")
    {
        color clr = COLOR_BRIGHT_GREEN;
        json j = json_from_color(clr);

        REQUIRE(json_has_key(j, "color"));
        REQUIRE("#00ff00ff" == json_read_string(j, "color"));

        color deserialized_clr = json_to_color(j);

        REQUIRE("#00ff00ff" == color_to_string(deserialized_clr));
    }

    free_json(person);
    free_all_json();
}