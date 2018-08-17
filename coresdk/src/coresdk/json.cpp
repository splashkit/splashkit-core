
//
//  json.cpp
//  splashkit
//
//  Created by James Armstrong & Jake Renzella on 03/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "json.h"
#include "json_driver.h"
#include "resources.h"
#include "core_driver.h"
#include "utils.h"

using std::ofstream;

namespace splashkit_lib
{
    static vector<json> objects;

    json create_json()
    {
        internal_sk_init();

        sk_json* j = new sk_json;
        j->id = JSON_PTR;
        objects.push_back(j);

        return j;
    };

    json create_json(string json_string)
    {
        json j = create_json();
        try
        {
            j->data = backend_json::parse(json_string);
        }
        catch(...)
        {
            LOG(ERROR) << "Invalid JSON string passed to create_json\n" << json_string;
        }

        return j;
    }

    void free_json(json j)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(WARNING) << "Passed invalid json object to free_json";
            return;
        }

        for (auto it = objects.begin(); it != objects.end();)
        {
            if (*it == j)
            {
                notify_of_free(j);

                sk_delete_json(*it);
                it = objects.erase(it);
                return;
            }
            else
            {
                ++it;
            }
        }
    }

    void free_all_json()
    {
        for (json j : objects)
        {
            sk_delete_json(j);
        }

        objects.clear();
    }

    string json_to_string(json j)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(WARNING) << "Passed invalid json object to json_to_string";
            return "";
        }

        return j->data.dump(4);
    };

    json json_from_string(const string &j_string)
    {
        return create_json(j_string);
    }

    json json_from_file(const string &filename)
    {
        string result = file_as_string(filename, JSON_RESOURCE);

        return json_from_string(result);
    };

    void json_to_file(json j, const string& filename)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(WARNING) << "Passed invalid json object to json_to_file";
            return;
        }

        string path = path_to_resource(filename, JSON_RESOURCE);
        string j_string = json_to_string(j);

        ofstream ofs(path);
        if (ofs.is_open())
        {
            ofs << j_string;
        }
        else
        {
            LOG(ERROR) << "Unable to open file at [" << path << "] for writing in json_to_file";
            return;
        }
    };

    void json_set_string(json j, string key, string value)
    {
        sk_json_add_value(j, key, value);
    };

    void json_set_number(json j, string key, float value)
    {
        sk_json_add_value(j, key, value);
    }

    void json_set_number(json j, string key, double value)
    {
        sk_json_add_value(j, key, value);
    }

    void json_set_number(json j, string key, int value)
    {
        sk_json_add_value(j, key, value);
    }

    void json_set_bool(json j, string key, bool value)
    {
        sk_json_add_value(j, key, value);
    }

    void json_set_object(json j, string key, json obj)
    {
        sk_json_add_value(j, key, obj->data);
    }

    void json_set_array(json j, string key, vector<string> value)
    {
        sk_json_add_value(j, key, value);
    }

    void json_set_array(json j, string key, vector<double> value)
    {
        sk_json_add_value(j, key, value);
    }

    void json_set_array(json j, string key, vector<bool> value)
    {
        sk_json_add_value(j, key, value);
    }

    void json_set_array(json j, string key, vector<json> value)
    {
        vector<backend_json> real;

        for (json frontend : value)
        {
            if (INVALID_PTR(frontend, JSON_PTR))
            {
                LOG(WARNING) << "Passed an invalid json object to json_add_x";
            }
            else
            {
                real.push_back(frontend->data);
            }
        }

        sk_json_add_value(j, key, real);
    }

    string json_read_string(json j, string key)
    {
        return sk_json_read_value<string>(j, key, backend_json::value_t::string);
    }

    float json_read_number(json j, string key)
    {
        return sk_json_read_value<float>(j, key, backend_json::value_t::number_float);
    }

    int json_read_number_as_int(json j, string key)
    {
        return sk_json_read_value<int>(j, key, backend_json::value_t::number_integer);
    }

    double json_read_number_as_double(json j, string key)
    {
        return sk_json_read_value<double>(j, key, backend_json::value_t::number_float);
    }

    bool json_read_bool(json j, string key)
    {
        return sk_json_read_value<bool>(j, key, backend_json::value_t::boolean);
    }

    json json_read_object(json j, string key)
    {
        auto backend_j = sk_json_read_value<backend_json>(j, key, backend_json::value_t::object);

        json result = create_json();
        result->data = backend_j;
        return result;
    }

    void json_read_array(json j, string key, vector<double>& out)
    {
        sk_json_read_array(j, key, out);
    }

    void json_read_array(json j, string key, vector<bool>& out)
    {
        sk_json_read_array(j, key, out);
    }

    void json_read_array(json j, string key, vector<string>& out)
    {
        sk_json_read_array(j, key, out);
    }

    void json_read_array(json j, string key, vector<json>& out)
    {
        vector<backend_json> real;
        sk_json_read_array(j, key, real);

        out.clear();

        for (backend_json rj : real)
        {
            json wj = create_json();
            wj->data = rj;
            out.push_back(wj);
        }
    }

    bool json_has_key(json j, string key)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(ERROR) << "Invalid json object passed to json_has_key";
            return false;
        }

        return j->data.count(key) > 0;
    }

    int json_count_keys(json j)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(ERROR) << "Invalid json object passed to json_count_keys";
            return 0;
        }

        return static_cast<int>(j->data.size());
    }

    json json_from_color(color clr)
    {
        json result = create_json();
        string color_string = color_to_string(clr);
        json_set_string(result, "color", color_string);
        return result;
    }

    color json_to_color(json j)
    {
        if (INVALID_PTR(j, JSON_PTR))
        {
            LOG(ERROR) << "Invalid json object passed to json_to_color";
            return COLOR_WHITE;
        }

        string color_string = json_read_string(j, "color");
        return string_to_color(color_string);
    }
}
