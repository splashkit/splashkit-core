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
using Catch::Matchers::WithinRel;

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

TEST_CASE("json can be created and read with different number types", "[json][json_read_number][json_read_number_as_double]")
{
    json number_types = create_json();
    
    SECTION("can read values correctly")
    {
        json_set_number(number_types, "float", 21.2f);
        REQUIRE_THAT(json_read_number(number_types, "float"), WithinRel(21.2f));
        json_set_number(number_types, "double", 30.1);
        REQUIRE_THAT(json_read_number_as_double(number_types, "double"), WithinRel(30.1));
    }
    
    SECTION("handles non-existent keys")
    {
        REQUIRE_FALSE(json_has_key(number_types, "nonExistent"));
        REQUIRE(json_read_number(number_types, "nonExistent") == 0.0f);
        REQUIRE(json_read_number_as_double(number_types, "nonExistent") == 0.0);
    }

    SECTION("handles reading non-numeric types")
    {
        json_set_string(number_types, "string", "21.2");
        REQUIRE(json_read_number(number_types, "nonNumericString") == 0.0f);
        REQUIRE(json_read_number_as_double(number_types, "nonNumericString") == 0.0);
    }

    SECTION("correctly handles very large numbers")
    {
        // Handles largest possible float
        float max_f = std::numeric_limits<float>::max();
        json_set_number(number_types, "maxFloat", max_f);
        REQUIRE_THAT(json_read_number(number_types, "maxFloat"), WithinRel(max_f));

        // Handles largest possible double
        double max_d = std::numeric_limits<double>::max();
        json_set_number(number_types, "maxDouble", max_d);
        REQUIRE_THAT(json_read_number_as_double(number_types, "maxDouble"), WithinRel(max_d));
    }

    SECTION("correctly handles very small numbers")
    {
        // Handles smallest possible float
        float min_f = std::numeric_limits<float>::min();
        json_set_number(number_types, "minFloat", min_f);
        REQUIRE_THAT(json_read_number(number_types, "minFloat"), WithinRel(min_f));

        // Handles smallest possible double
        double min_d = std::numeric_limits<double>::min();
        json_set_number(number_types, "minDouble", min_d);
        REQUIRE_THAT(json_read_number_as_double(number_types, "minDouble"), WithinRel(min_d));
    }
    
    free_json(number_types);
}
