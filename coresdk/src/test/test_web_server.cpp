//
//  test_web_server.cpp
//  splashkit
//
//  Created by James Armstrong http://github.com/jarmstrong
//

#include "resources.h"
#include "web_server.h"
#include "json.h"

#include <iostream>
#include <functional>
#include <vector>


using namespace std;
using namespace splashkit_lib;

bool handle_request(http_request r)
{
    string uri = request_uri(r);
    cout << "Matching routes for " << uri << "\n";
    if (uri.find("/stop") != string::npos)
    {
        string user = request_query_parameter(r, "user", "");
        if ( user != "admin" )
        {
            send_response(r, "No auth for " + user + " to stop");
            return false;
        }
        cout << "Matched to the stop route\n";
        // do not send response on close, to test that you can still stop the server.
        // send_response(r, "Goodbye");
        return true;
    }
    else
    {
        cout << "Sending request response.\n";
        send_response(r, "Hello World");
        return false;
    }
}

void run_single_server_test()
{
    cout << "Starting web server on http://localhost:8080\n";
    web_server server = start_web_server(8080);

    bool running = true;
    while (running)
    {
        // Navigating to http://localhost:8080 will invoke begin_request_handler().
        cout << "Waiting for web request\n";
        http_request request = next_web_request(server);

        cout << "Received request checking if valid\n";
        if (request)
        {
            cout << "Request is valid.\n";
        }
        else
        {
            cout << "Request is invalid.\n";
        }

        if (handle_request(request))
        {
            running = false;
        }
    }

    if (has_incoming_requests(server))
    {
        cerr << "Still has requests...\n";
    }

    cout << "Closing the server.\n";
    stop_web_server(server);
    cout << "Server is closed.\n";
}

void run_multiple_server_test()
{
    cout << "Starting two localhost servers on 8080 and 8081\n";
    auto server1 = start_web_server(8080);
    auto server2 = start_web_server(8081);

    bool server1_up = true;
    bool server2_up = true;
    while (server1_up || server2_up)
    {
        if (server1_up)
        {
            cout << "Load http://localhost:8080 or .../stop\n";
            auto r1 = next_web_request(server1);

            if (handle_request(r1))
            {
                server1_up = false;
                cout << "Server 1 down\n";
            }
        }

        if (server2_up)
        {
            cout << "Load http://localhost:8081 or .../stop\n";
            auto r2 = next_web_request(server2);

            if (handle_request(r2))
            {
                server2_up = false;
                cout << "Server 2 down\n";
            }
        }
    }

    stop_web_server(server1);
    stop_web_server(server2);
}

json load_person()
{
    cout << "Reading " << "person.json" << " from disk" << endl;
    json j = json_from_file("person.json");
    return j;
}

void test_send_json_response()
{
    auto server = start_web_server();

    string json = json_to_string(load_person());

    bool running = true;
    while (running)
    {
        auto request = next_web_request(server);

        send_response(request, HTTP_STATUS_OK, json, "application/json");
    }
}

static vector<pair<string, function<void()>>> tests;

void add_tests()
{
    tests.push_back({"Single Server", run_single_server_test});
    tests.push_back({"Multiple Servers", run_multiple_server_test});
    tests.push_back({"Send JSON Response", test_send_json_response});
}

void run_web_server_tests()
{
    add_tests();

    cout << "=== Web Server Tests === \n";

    for (int i = 0; i < tests.size(); ++i)
    {
        auto test = tests[i];
        cout << i << ": " << test.first << "\n";
    }

    cout << "Select test to run: ";

    int option = 0;
    cin >> option;

    if (option >= 0 && option < tests.size())
    {
        tests[option].second();
    }
}
