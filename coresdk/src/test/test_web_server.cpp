//
// Created by arm on 8/18/16.
//

#include "resources.h"
#include "web_server.h"

#include <iostream>

using namespace std;

bool handle_request(server_request r)
{
    string uri = request_get_uri(r);
    cout << "Matching routes for " << uri << "\n";
    if (uri.find("/stop") != string::npos)
    {
        cout << "Matched to the stop route\n";
        send_response(r, "Goodbye");
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
    web_server server = start_web_server("8080");

    bool running = true;
    while (running)
    {
        // Navigating to http://localhost:8080 will invoke begin_request_handler().
        cout << "Waiting for web request\n";
        server_request request = next_web_request(server);

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

    if (has_waiting_requests(server))
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
    auto server1 = start_web_server("8080");
    auto server2 = start_web_server("8081");

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

void run_web_server_tests()
{
    run_single_server_test();
    run_multiple_server_test();
}