//
//  json.h
//  splashkit
//
//  Created by James Armstrong & Jake Renzella on 03/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef SPLASHKIT_JSON_CPP
#define SPLASHKIT_JSON_CPP

#include <string>
#include <vector>
#include <map>

#include <easylogging++.h>
#include <json.hpp>

#include "backend/core_driver.h"

using backend_json = nlohmann::json;
using namespace std;

struct sk_json
{
    backend_json data;
};

typedef struct sk_json *json;

json create_json() {
    internal_sk_init();

    return new sk_json;
};

json create_json(string json_string)
{
    json j = create_json();
    j->data = backend_json::parse(json_string);
    return j;
}

string json_to_string(json j)
{
    return j->data.dump(4);
};

json json_from_file(string filename)
{};

void json_to_file(json j)
{};

void json_add_string(json j, string key, string value)
{
    j->data[key] = value;
};

void json_add_number(json j, string key, int value)
{
    j->data[key] = value;
}

void json_add_number(json j, string key, double value)
{
    j->data[key] = value;
}

void json_add_array(json j, string key, int value[])
{
    j->data[key] = value;
}

void json_add_array(json j, string key, double value[])
{
    j->data[key] = value;
}

void json_add_array(json j, string key, bool value[])
{
    j->data[key] = value;
}

void json_add_array(json j, string key, string value[], int size)
{
    backend_json a;

    for (int i = 0; i < size; ++i)
    {
        a.push_back(value[i]);
    }

    j->data[key] = a;
}

void json_add_array(json j, string key, json value[])
{
    for (auto& e : j->data)
    {

    }

    j->data[key] = value;
}

void json_add_object(json j, string key, json object)
{
    j->data[key] = object->data;
}

string json_read_string(json j, string key)
{
    return j->data[key];
}

double json_read_number(json j, string key)
{
    return j->data[key];
}

void json_read_number(json j, string key, int &out)
{
    out = j->data[key];
}

void json_read_number(json j, string key, double &out)
{
    out = j->data[key];
}

void json_read_array(json j, string key, int out[])
{


    /*
    backend_json json_array = j->data[key];

    out = new int[json_array.size()];
    for (int i = 0; i < json_array.size(); ++i)
    {
        out[i] = json_array.at(i);
    }
     */
}

void json_read_array(json j, string key, double out[])
{
    backend_json json_array = j->data[key];

    out = new double[json_array.size()];
    for (int i = 0; i < json_array.size(); ++i)
    {
        out[i] = json_array.at(i);
    }
}

void json_read_array(json j, string key, bool out[])
{
    backend_json json_array = j->data[key];

    out = new bool[json_array.size()];
    for (int i = 0; i < json_array.size(); ++i)
    {
        out[i] = json_array.at(i);
    }
}

void json_read_array(json j, string key, string out[])
{
    backend_json json_array = j->data[key];

    out = new string[json_array.size()];
    for (int i = 0; i < json_array.size(); ++i)
    {
        out[i] = json_array.at(i);
    }
}

void json_read_array(json j, string key, json out[])
{
    backend_json json_array = j->data[key];


}

json json_read_object(json j, string key)
{
    json result = new sk_json;
    result->data = j->data[key];
    return result;
}

#endif //SPLASHKIT_JSON_CPP
