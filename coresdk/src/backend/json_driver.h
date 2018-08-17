//
//  json_driver.h
//  splashkit
//
//  Created by James Armstrong & Jake Renzella on 03/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef SPLASHKIT_JSON_DRIVER_H
#define SPLASHKIT_JSON_DRIVER_H

#include "json.h"
#include "backend_types.h"
#include "utility_functions.h"
#include "json.hpp"

#include <string>
#include <vector>
#include <functional>

using backend_json = nlohmann::json;
using std::string;
using std::vector;
using std::make_pair;

namespace splashkit_lib
{
    struct sk_json
    {
        pointer_identifier id;
        backend_json data;
    };

    void sk_delete_json(json j);

    string json_type_to_string(backend_json::value_t type);

    template <typename T>
    void sk_json_add_value(json j, string key, T value)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(WARNING) << "Passed an invalid json object to json_add_x";
            return;
        }

        j->data[key] = value;
    }

    inline bool is_type_number(backend_json::value_t type)
    {
        return (type == backend_json::value_t::number_float ||
                type == backend_json::value_t::number_integer ||
                type == backend_json::value_t::number_unsigned);
    }

    template<typename T>
    T sk_json_read_value(json j, string key, backend_json::value_t type)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(ERROR) << "Invalid json pointer passed to json_read_x";
            return T();
        }

        backend_json temp = j->data[key];

        if ((temp.type() != type) &&
            !(is_type_number(temp.type()) && is_type_number(type)))
        {
            LOG(ERROR) << "JSON key value is not expected in sk_json_read_value. Has type " << json_type_to_string(j->data[key].type());
            return T();
        }

        return j->data[key];
    }

    template <typename T>
    void sk_json_read_array(json j, string key, vector<T>& out)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(WARNING) << "Passed an invalid json object to json_add_array";
            return;
        }

        if (!j->data[key].is_array())
        {
            LOG(ERROR) << "JSON key value is not an array. Has type " << json_type_to_string(j->data[key].type());
            return;
        }
        
        out.clear();
        
        backend_json json_array = j->data[key];
        
        for (T e : json_array) {
            out.push_back(e);
        }
    }

    inline map<string, string> sk_json_to_map(json j)
    {
        map<string, string> result;

        backend_json bj = j->data;
        for (auto it = bj.begin(); it != bj.end(); ++it)
        {
            if (!it.value().is_string())
            {
                LOG(ERROR) << "Key not a string in map";
            }
            else
            {
                result.insert(make_pair<string, string>(it.key(), it.value()));
            }
        }

        return result;
    };
}
#endif //SPLASHKIT_JSON_DRIVER_H
