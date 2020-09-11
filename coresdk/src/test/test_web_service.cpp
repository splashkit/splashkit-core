//
//  test_web_service.cpp
//  splashkit
//
//  Created by James Armstrong http://github.com/jarmstrong
//

#include "window_manager.h"
#include "text.h"
#include "input.h"
#include "json.h"
#include "web_server.h"

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

static map<http_method, map<string, function<void(http_request, string)>>> routes;

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
    return string("<a href=\"") + uri + "\">" + stub + "</a>";
}

void root_route(http_request request, string uri)
{
    send_html_file_response(request, "index.html");
}

void names_get_routes(http_request request, string uri)
{
    vector<string> stubs = split_uri_stubs(uri);

    if (stubs.size() == 1)
    {
        string j = people_to_json();
        send_response(request, HTTP_STATUS_OK, j, "application/json");
    }
    else
    {
        try
        {
            int id = stoi(stubs[1]);
            string json_person = json_to_string(person_to_json(people.at(id)));
            send_response(request, HTTP_STATUS_OK, json_person, "application/json");
        } catch (...)
        {
            send_response(request, HTTP_STATUS_OK, "<h1>No ID exists.</h1>", "text/html");
        }
    }
}

void names_post_routes(http_request request, string uri)
{
    vector<string> stubs = split_uri_stubs(uri);

    if (stubs.size() == 1)
    {
        json p = json_from_string(request_body(request));
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

void names_delete_route(http_request request, string uri)
{
    vector<string> stubs = split_uri_stubs(uri);
    try
    {
        int id = stoi(stubs[1]);
        people.erase(people.begin() + id);
        send_response(request, "Person has now been deleted.");
    } catch(...)
    {
        send_response(request, HTTP_STATUS_OK, "<h1>No ID exists.</h1>", "text/html");
    }
}

void post_person_route(http_request request, string uri)
{
    send_html_file_response(request, "post.html");
}

void get_person_route(http_request request, string uri)
{
    send_html_file_response(request, "get.html");
}

void api_login_route(http_request request, string uri)
{
  send_response(request, HTTP_STATUS_OK, "Check your cookies", "text", {"Set-Cookie: user=admin"});
}

void add_routes()
{
    routes[HTTP_GET_METHOD].insert({"", root_route});

    routes[HTTP_GET_METHOD].insert({"login", api_login_route});

    routes[HTTP_GET_METHOD].insert({"names", names_get_routes});
    routes[HTTP_POST_METHOD].insert({"names", names_post_routes});
    routes[HTTP_DELETE_METHOD].insert({"names", names_delete_route});

    routes[HTTP_GET_METHOD].insert({"post_person", post_person_route});
    routes[HTTP_GET_METHOD].insert({"get_person", get_person_route});
}

void run_restful_web_service()
{
    auto server = start_web_server();

    add_person("Peter Jenkins", "39 Fifty Street", 15);
    add_person("Paul Peterson", "23 Fifty Street", 27);
    add_person("Jerry Smith", "1 Sixty Street", 55);

    add_routes();

    window w1 = open_window("Running Web Service.", 200, 100);
    draw_text("Close to end", COLOR_BLACK, 0, 0);
    refresh_window(w1);

    while ( not window_close_requested(w1))
    {
        process_events();

        if ( not has_incoming_requests(server)) continue;

        auto request = next_web_request(server);

        http_method method = request_method(request);

        string uri = request_uri(request);

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

    close_window(w1);
}
