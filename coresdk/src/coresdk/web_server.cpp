//
//  web_server.cpp
//  splashkit
//
//  Created by James Armstrong on 21/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "utility_functions.h"
#include "web_server.h"
#include "web_server_driver.h"

web_server start_web_server(string port)
{
    LOG(DEBUG) << "Starting a web server on port " << port;
    return sk_start_web_server(port);
}

web_server start_web_server()
{
    return start_web_server("8080");
}

bool has_waiting_requests(web_server server)
{
    if (INVALID_PTR(server, WEB_SERVER_PTR))
    {
        LOG(WARNING) << "has_waiting_requests called on an invalid server";
        return false;
    }

    return sk_has_waiting_requests(server);
}

void stop_web_server(web_server server)
{
    if (INVALID_PTR(server, WEB_SERVER_PTR))
    {
        LOG(WARNING) << "stop_web_server called on an invalid server";
        return;
    }

    sk_stop_web_server(server);
}

server_request next_web_request(web_server server)
{
    if (INVALID_PTR(server, WEB_SERVER_PTR))
    {
        LOG(WARNING) << "next_web_request called on an invalid server";
        return nullptr;
    }

    return sk_get_request(server);
}

void send_response(server_request r, server_response resp)
{
    if (INVALID_PTR(r, WEB_SERVER_REQUEST_PTR))
    {
        LOG(WARNING) << "send_response called on an invalid request";
        return;
    }
    else if (INVALID_PTR(resp, WEB_SERVER_RESPONSE_PTR))
    {
        LOG(WARNING) << "send_response called on an invalid response";
        return;
    }

    r->response = resp;
    r->control.release();
}

void send_response(server_request r, string message, string content_type)
{
    server_response resp = new sk_server_response;
    resp->id = WEB_SERVER_RESPONSE_PTR;
    resp->message = message;
    resp->content_type = content_type;

    send_response(r, resp);

    resp->response_sent.acquire();
    delete resp;
}

void send_response(server_request r, string message)
{
    send_response(r, message, "text/plain");
}

string request_get_uri(server_request r)
{
    if (INVALID_PTR(r, WEB_SERVER_REQUEST_PTR))
    {
        LOG(WARNING) << "request_get_uri called on an invalid request";
        return "";
    }

    return r->uri;
}