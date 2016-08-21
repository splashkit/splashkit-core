//
// Created by arm on 8/18/16.
//

#include "resources.h"
#include "web_server.h"

#include <iostream>

using namespace std;

void run_web_server_tests()
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

        cout << "Matching routes\n";
        if (request_get_uri(request).find("/stop") != string::npos)
        {
            cout << "Matched to the stop route\n";
            send_response(request, "Goodbye");
            running = false;
        }
        else
        {
            cout << "Sending request response.\n";
            send_response(request, "Hello World");
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