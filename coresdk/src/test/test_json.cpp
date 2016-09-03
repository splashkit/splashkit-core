//
// Created by arm on 9/4/16.
//

#ifndef SPLASHKIT_TEST_JSON_H
#define SPLASHKIT_TEST_JSON_H

#include "json.h"
#include <easylogging++.h>

void run_json_test()
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

    string numbers[] = {"212 555-1234", "646 555-4567"};
    json_add_array(person, "phoneNumbers", numbers, 2);

    LOG(DEBUG) << json_to_string(person);
}

#endif //SPLASHKIT_TEST_JSON_H
