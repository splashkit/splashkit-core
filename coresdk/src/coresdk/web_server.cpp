//
//  web_server.cpp
//  splashkit
//
//  Created by James Armstrong on 21/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "web_server.h"
#include "web_server_driver.h"

web_server start_web_server(string port)
{
    return sk_start_web_server(port);
}

web_server start_web_server()
{
    return start_web_server("8080");
}

bool has_waiting_requests(web_server server)
{
    return sk_has_waiting_requests(server);
}

void stop_web_server(web_server server)
{
    sk_stop_web_server(server);
}

server_request next_web_request(web_server server)
{
    if (has_waiting_requests(server))
    {
        return sk_get_request(server);
    }

    while (!has_waiting_requests(server)) { } // Add a proper wait here?

    return sk_get_request(server);
}

void send_response(server_request r, server_response resp)
{
    r->response = resp;
    r->control.release();
}

void send_response(server_request r, string message)
{
    server_response resp = new sk_server_response;
    resp->message = message;

    send_response(r, resp);
}

string request_get_uri(server_request r)
{
    return r->uri;
}