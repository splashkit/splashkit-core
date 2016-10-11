//
//  main.cpp
//  SimpleWebService
//
//  Created by Andrew Cain on 23/9/16.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "splashkit.h"
#include <string>
using std::to_string;

void process_request(web_server message_service, string &message)
{
    http_request request = next_web_request(message_service);

    if ( is_get_request_for(request, "/message") )
    {
        send_response(request, message);
    }
    else if ( is_put_request_for(request, "/message") )
    {
        message = request_body(request);
        send_response(request);
    }
    else if ( is_get_request_for(request, "/index.html") )
    {
        send_html_file_response(request, "message_index.html");
    }
    else
    {
        send_response(request, HTTP_STATUS_BAD_REQUEST, "Unknown request");
    }
}

int main()
{
    string message = "Get started with SplashKit";

    web_server message_service = start_web_server();

    open_window("Quote of the Day Controller", 300, 100);

    while ( not quit_requested() )
    {
        process_events();
        clear_screen();

        draw_text(message, COLOR_BLACK, 10, 10);
        draw_text("Activity:", COLOR_BLACK, 10, 30);
        draw_text("Close to quit server", COLOR_BLACK, 10, 60);

        refresh_screen();

        if ( has_incoming_requests(message_service) )
        {
            fill_rectangle(COLOR_GREEN, 80, 30, 10, 10);
            refresh_screen();
            process_request(message_service, message);
            delay(150);
        }
    }

    return 0;
}
