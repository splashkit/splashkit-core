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
            server_request request = next_web_request(todo_list_service);
            string method = request_get_method(request);
            string uri = request_get_uri(request);

            if ( method == ")
        }
    }

    return 0;
}
