//
//  test_web_service.cpp
//  splashkit
//
//  Created by James Armstrong http://github.com/jarmstrong
//

#include "json.h"
#include "web_server.h"
#include "utility_functions.h"

#include "easylogging++.h"

#include <string>
#include <sstream>
#include <vector>
#include <iostream>
#include <exception>


using namespace std;
using namespace splashkit_lib;

struct person
{
    string name;
    string address;
    double age;
};

static vector<person> people;

static map<http_method, map<string, function<void(server_request, string)>>> routes;

json person_to_json(person p)
{
    json j = create_json();
    json_set_string(j, "name", p.name);
    json_set_string(j, "address", p.address);
    json_set_number(j, "age", p.age);
    return j;
}

person json_to_person(json j)
{
    person p;
    p.name = json_read_string(j, "name");
    p.address = json_read_string(j, "address");
    p.age = json_read_number(j, "age");
    return p;
}

void add_person(string name, string address, int age)
{
    person p;
    p.name = name;
    p.address = address;
    p.age = age;
    people.push_back(p);
}

string people_to_json()
{
    vector<json> peoples;
    for (person p : people)
    {
        json j = person_to_json(p);
        peoples.push_back(j);
    }

    json result = create_json();
    json_set_array(result, "people", peoples);
    return json_to_string(result);
}

/**
 * POST
 * GET
 * PUT
 * DELETE
 */

/**
 * / -> list of end points
 * /people -> list of names (GET ALL PEOPLE, POST ADD PERSON)
 * /people/:id  -> a single name (PUT, GET, DELETE)
 */

string get_url_link(string stub, string uri)
{
    return cat({"<a href=\"", uri, "\">", stub, "</a>"});
}

void root_route(server_request request, string uri)
{
    send_html_file_response(request, "index.html");
}

void names_get_routes(server_request request, string uri)
{
    vector<string> stubs = split_uri_stubs(uri);

    if (stubs.size() == 1)
    {
        string j = people_to_json();
        send_response(request, OK, j, "application/json");
    }
    else
    {
        try
        {
            int id = stoi(stubs[1]);
            string json_person = json_to_string(person_to_json(people.at(id)));
            send_response(request, OK, json_person, "application/json");
        } catch (...)
        {
            send_response(request, OK, "<h1>No ID exists.</h1>", "text/html");
        }
    }
}

void names_post_routes(server_request request, string uri)
{
    vector<string> stubs = split_uri_stubs(uri);

    if (stubs.size() == 1)
    {
        json p = json_from_string(request->body);
        if (json_count_keys(p) != 0)
        {
            people.push_back(json_to_person(p));
            send_response(request, "Person addition success.");
        }
        else
        {
            send_response(request, "Invalid or empty JSON received.");
        }
    }
    else
    {
        send_response(request, "Person addition failed.");
    }
}

void names_delete_route(server_request request, string uri)
{
    vector<string> stubs = split_uri_stubs(uri);
    try
    {
        int id = stoi(stubs[1]);
        people.erase(people.begin() + id);
        send_response(request, "Person has now been deleted.");
    } catch(...)
    {
        send_response(request, OK, "<h1>No ID exists.</h1>", "text/html");
    }
}

void post_person_route(server_request request, string uri)
{
    send_html_file_response(request, "post.html");
}

void get_person_route(server_request request, string uri)
{
    send_html_file_response(request, "get.html");
}

void add_routes()
{
    routes[HTTP_GET].insert({"", root_route});

    routes[HTTP_GET].insert({"names", names_get_routes});
    routes[HTTP_POST].insert({"names", names_post_routes});
    routes[HTTP_DELETE].insert({"names", names_delete_route});

    routes[HTTP_GET].insert({"post_person", post_person_route});
    routes[HTTP_GET].insert({"get_person", get_person_route});
}

void run_restful_web_service()
{
    auto server = start_web_server();

    add_person("Peter Jenkins", "39 Fifty Street", 15);
    add_person("Paul Peterson", "23 Fifty Street", 27);
    add_person("Jerry Smith", "1 Sixty Street", 55);

    add_routes();

    bool running = true;
    while (running)
    {
        auto request = next_web_request(server);

        http_method method = request_get_method(request);

        string uri = request_get_uri(request);

        if (uri.find("favicon.ico") != string::npos)
        {
            continue;
        }

        vector<string> stubs = split_uri_stubs(uri);

        auto it = routes[method].find(stubs[0]);
        if (it != routes[method].end())
        {
            LOG(DEBUG) << "Route matched for " << uri;
            it->second(request, uri);
        }
        else
        {
            LOG(DEBUG) << "No route matched for " << uri;
            send_response(request, "No route matching.");
        }
    }
}
