//
//  web_server.cpp
//  splashkit
//
//  Created by James Armstrong on 21/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "web_server_driver.h"
#include "concurrency_utils.h"

#include <iostream>
#include <cstring>

static sk_server_request* last_request = nullptr;
static channel<sk_server_request*> request_queue;

static int begin_request_handler(struct mg_connection *conn)
{
    const struct mg_request_info *request_info = mg_get_request_info(conn);

    sk_server_request *r = new sk_server_request;
    r->uri = request_info->request_uri;

    request_queue.put(r); // Add request to concurrent queue
    r->control.acquire(); // Waits until user returns response.

    // Send HTTP reply to the client
    mg_printf(conn,
              "HTTP/1.1 200 OK\r\n"
              "Content-Type: text/plain\r\n"
              "Content-Length: %d\r\n" // Always set Content-Length
              "\r\n"
              "%s",
              r->response->message.length(), r->response->message.c_str());

    // Remove the request
    delete r->response;
    delete r;

    // Non-zero return means civetweb has replied to client
    return 1;
}

void sk_flush_request(sk_server_request *request)
{
    request->response = new sk_server_response;
    request->response->message = "Server is stopping.";
    request->control.release();
}

/*
 * Copy's and returns the request from the last_request object
 * and sets it to null so it can't be retrieved again.
 */
sk_server_request* sk_get_request(sk_web_server *server)
{
    sk_server_request* request = last_request;
    last_request = nullptr;
    return request;
}

bool sk_has_waiting_requests(sk_web_server *server)
{
    // If we already have a request from the channel, get it.
    if (last_request)
    {
        return true;
    }

    // Try to get a new request from the queue and set the last request if one exists
    sk_server_request *request;
    bool success = request_queue.try_take(request);

    if (success)
    {
        last_request = request;
        return true;
    }

    return false;
}

sk_web_server* sk_start_web_server(string port)
{
    sk_web_server *server = new sk_web_server;

    // List of options. Last element must be NULL.
    const char *options[] = {"listening_ports", port.c_str(), NULL};

    // Prepare callbacks structure. We have only one callback, the rest are NULL.
    memset(&server->callbacks, 0, sizeof(server->callbacks));
    server->callbacks.begin_request = begin_request_handler;

    // Start the web server.
    server->ctx = mg_start(&server->callbacks, NULL, options);

    return server;
}

void sk_stop_web_server(sk_web_server *server)
{
    // Clear requests
    if (last_request)
    {
        sk_flush_request(last_request);
        delete last_request;
    }

    sk_server_request *request;
    while (request_queue.try_take(request))
    {
        sk_flush_request(request);
    }

    mg_stop(server->ctx);
}