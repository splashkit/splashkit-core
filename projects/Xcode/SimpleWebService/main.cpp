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
    json_set_array(list, "todos", todos);
    send_response(request, list);
}

void add_todo(vector<string> &todos, server_request request)
{
    todos.push_back(request_body(request));
    send_response(request, OK, "Todo Added");
}

void process_request(web_server todo_list_service, vector<string> &todos)
{
    server_request request = next_web_request(todo_list_service);

    string uri = request_uri(request);

    vector<string> stubs = split_uri_stubs(uri);

    if ( stubs[0] == "todos" )
    {
        http_method method = request_method(request);

        switch( method )
        {
            case HTTP_GET_METHOD:
                send_todo_list(todos, request);
                break;
            case HTTP_POST_METHOD:
                add_todo(todos, request);
                break;
            default:
                send_response(request, BAD_REQUEST, "Unknown request");
                break;
        }
    }
    else if ( stubs[0] == "index.html" )
    {
        send_html_file_response(request, "todo_index.html");
    }
    else
    {
        send_response(request, NOT_FOUND, "Unknown request");
    }
}

int main()
{
    vector<string> todo_list;
    todo_list.push_back("Get started with SplashKit");

    web_server todo_list_service = start_web_server();

    open_window("Web Service Controller", 300, 300);

    while ( not quit_requested() )
    {
        process_events();
        clear_screen();

        draw_text("Todo count: " + to_string(todo_list.size()), COLOR_BLACK, 10, 0);
        draw_text("Close to quit server", COLOR_BLACK, 10, 20);

        refresh_screen();

        if ( has_waiting_requests(todo_list_service) )
        {
            fill_rectangle(COLOR_GREEN, 280, 0, 20, 20);
            refresh_screen();
            process_request(todo_list_service, todo_list);
            delay(50);
        }
    }

    return 0;
}
