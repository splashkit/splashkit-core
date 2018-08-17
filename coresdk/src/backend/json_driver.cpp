//
//  json_driver.cpp
//  splashkit
//
//  Created by James Armstrong & Jake Renzella on 03/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "json_driver.h"

namespace splashkit_lib
{
    void sk_delete_json(json j)
    {
        if (VALID_PTR(j, JSON_PTR))
        {
            j->id = NONE_PTR;
            delete j;
        }
    }

    string json_type_to_string(backend_json::value_t type)
    {
        switch(type)
        {
            case nlohmann::detail::value_t::null: return "null";
            case nlohmann::detail::value_t::object: return "object";
            case nlohmann::detail::value_t::array: return "array";
            case nlohmann::detail::value_t::string: return "string";
            case nlohmann::detail::value_t::boolean: return "boolean";
            case nlohmann::detail::value_t::number_integer: return "number_integer";
            case nlohmann::detail::value_t::number_unsigned: return "number_unsigned";
            case nlohmann::detail::value_t::number_float: return "number_float";
            case nlohmann::detail::value_t::discarded: return "discarded";
            default: return "unknown";
        }
    }
}