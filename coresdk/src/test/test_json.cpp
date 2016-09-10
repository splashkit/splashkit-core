//
//  test_json.cpp
//  splashkit
//
//  Created by James Armstrong & Jake Renzella on 03/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef SPLASHKIT_TEST_JSON_H
#define SPLASHKIT_TEST_JSON_H

#include <vector>
#include <iostream>

#include "easylogging++.h"

#include "json.h"

using namespace splashkit_lib;
using namespace std;

json create_person()
{
    json person = create_json();

    json_add_string(person, "firstName", "John");
    json_add_string(person, "lastName", "Smith");

    json addresses = create_json();
    json_add_string(addresses, "streetAddress", "21 2nd Street");
    json_add_string(addresses, "city", "New York");
    json_add_string(addresses, "state", "NY");
    json_add_number(addresses, "postalCode", 10021);

    json_add_object(person, "addresses", addresses);

    vector<string> numbers = {"212 555-1234", "646 555-4567"};
    json_add_array(person, "phoneNumbers", numbers);

    json_add_bool(person, "pensioner", true);

    return person;
}

void test_to_string()
{
    json person = create_person();
    cout << json_to_string(person) << endl;
}

template <typename T>
void test(T expected, T actual)
{
    cout << "Expected: " << expected << " -> Actual: " << actual << endl;
}

void test_read_values(json person)
{
    test(string("John"), json_read_string(person, "firstName"));
    test(string("Smith"), json_read_string(person, "lastName"));

    json addresses = json_read_object(person, "addresses");
    test(string("21 2nd Street"), json_read_string(addresses, "streetAddress"));
    test(string("New York"), json_read_string(addresses, "city"));
    test(string("NY"), json_read_string(addresses, "state"));
    test<double>(10021, json_read_number(addresses, "postalCode"));

    vector<string> numbers;
    json_read_array(person, "phoneNumbers", numbers);
    test(string("212 555-1234"), numbers[0]);
    test(string("646 555-4567"), numbers[1]);

    test(true, json_read_bool(person, "pensioner"));
}

void save_person_to_file(string filename)
{
    json j = create_person();

    cout << "Saving person to Resources/json/" + filename << endl;
    json_to_file(j, filename);
}

json create_person_from_file(string filename)
{
    cout << "Reading " << filename << " from disk" << endl;
    json j = json_from_file(filename);
    return j;
}

void test_has_key(json person)
{
    LOG(DEBUG) << "Testing has key";
    test(true, json_has_key(person, "lastName"));
    test(false, json_has_key(person, "postalCode"));
    test(true, json_has_key(person, "addresses"));
    json addresses = json_read_object(person, "addresses");
    test(true, json_has_key(addresses, "postalCode"));

    LOG(DEBUG) << "Key count: " << json_count_keys(person);
}

void run_json_test()
{
    test_to_string();

    test_read_values(create_person());

    save_person_to_file("person.json");

    json person = create_person_from_file("person.json");
    cout << "Testing read for json from file" << endl;
    test_read_values(person);

    test_has_key(person);

    free_json(person);
    LOG(DEBUG) << "If you are seeing errors after this, things are working.";
    test_read_values(person);

    free_all_json();
}

#endif //SPLASHKIT_TEST_JSON_H
