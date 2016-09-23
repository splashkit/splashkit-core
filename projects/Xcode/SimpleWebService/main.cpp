//
//  main.cpp
//  SimpleWebService
//
//  Created by Andrew Cain on 23/9/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "splashkit.h"
#include <vector>
using std::vector;
using std::to_string;

void send_todo_list(const vector<string> &todos, server_request request)
{
    json list = create_json();
    json_add_array(list, "todos", todos);
    send_response(request, OK, json_to_string(list), "application/json");
}

void add_todo(vector<string> &todo, server_request request)
{
    todos.push_back(request_body(request));
}

void process_request(vector<string> &todos)
{
    server_request request = next_web_request(todo_list_service);

    http_method method = request_method(request);
    string uri = request_uri(request);

    vector<string> stubs = split_uri_stubs(uri);

    if ( stubs[0] == "todos" )
    {
        switch( method )
        {
            HTTP_GET:
                send_todo_list(todo_list, request);
                break;
            HTTP_POST:
                add_todo(todo_list, request);
                break;
            default:
                break;
        }
    }
}

int main()
{
    vector<string> todo_list;
    web_server todo_list_service = start_web_server();

    open_window("Web Service Controller", 300, 300);

    while ( not quit_requested() )
    {
        process_events();

        draw_text("Todo count: " + to_string(todo_list.size()), COLOR_BLACK, 10, 0);
        draw_text("Close to quit server", COLOR_BLACK, 10, 20);

        refresh_screen();

        if ( has_waiting_requests(todo_list_service) )
        {
            process_request(todo_list);
        }
    }

    return 0;
}
