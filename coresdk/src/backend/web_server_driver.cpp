//
//  web_server.cpp
//  splashkit
//
//  Created by James Armstrong on 21/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "web_server_driver.h"
#include "concurrency_utils.h"
#include "utility_functions.h"
#include "core_driver.h"

#include <iostream>
#include <cstring>

static map<string, sk_web_server*> servers;

struct _web_server_ctx_data
{
    string port;
};

static int begin_request_handler(struct mg_connection *conn)
{
    _web_server_ctx_data *user_data;
    user_data = static_cast<_web_server_ctx_data *>(mg_get_user_data(mg_get_context(conn)));
    if ( not user_data )
    {
        LOG(WARNING) << "Request handler called within invalid user data. Contact splashkit dev team.";
    }

    string port = user_data->port;
    if (servers.find(port) == servers.end())
    {
        LOG(WARNING) << "Request handler called on non-existent server";
        return -1;
    }

    const struct mg_request_info *request_info = mg_get_request_info(conn);

    sk_server_request *r = new sk_server_request;
    r->id = WEB_SERVER_REQUEST_PTR;
    r->uri = request_info->request_uri;

    servers.at(port)->request_queue.put(r); // Add request to concurrent queue
    r->control.acquire(); // Waits until user returns response.

    // Send HTTP reply to the client
    mg_printf(conn,
              "HTTP/1.1 200 OK\r\n"
              "Content-Type: %s\r\n"
              "Connection: close\r\n"
              "Content-Length: %lu\r\n" // Always set Content-Length
              "\r\n"
              "%s",
              r->response->content_type.c_str(),
              r->response->message.length(),
              r->response->message.c_str());

    r->response->response_sent.release();
    
    // Remove the request
    delete r;

    // Non-zero return means civetweb has replied to client
    return 1;
}

void sk_flush_request(sk_server_request *request)
{
    request->response = new sk_server_response;
    request->response->id = WEB_SERVER_RESPONSE_PTR;
    request->response->message = "Server is stopping.";
    request->control.release();
}

/*
 * Copy's and returns the request from the last_request object
 * and sets the variable to null so it can't be retrieved again.
 */
sk_server_request* sk_get_request(sk_web_server *server)
{
    sk_server_request* request;
    
    if ( server->last_request )
    {
        request = server->last_request;
        server->last_request = nullptr;
    }
    else
    {
        request = server->request_queue.take();
    }
    
    return request;
}

bool sk_has_waiting_requests(sk_web_server *server)
{
    // If we already have a request from the channel, get it.
    if (server->last_request)
    {
        return true;
    }

    // Try to get a new request from the queue and set the last request if one exists
    sk_server_request *request;
    bool success = server->request_queue.try_take(request);

    if (success)
    {
        server->last_request = request;
        return true;
    }

    return false;
}

sk_web_server* sk_start_web_server(string port)
{
    internal_sk_init();

    if (servers.find(port) != servers.end())
    {
        LOG(WARNING) << "Server already started on port " + port;
        return nullptr;
    }

    sk_web_server *server = new sk_web_server;
    server->id = WEB_SERVER_PTR;
    server->port = port;
    server->last_request = nullptr;

    // List of options. Last element must be NULL.
    const char *options[] = {"listening_ports", port.c_str(), NULL};

    _web_server_ctx_data *user_data = new _web_server_ctx_data();
    user_data->port = port;

    // Prepare callbacks structure. We have only one callback, the rest are NULL.
    memset(&server->callbacks, 0, sizeof(server->callbacks));
    server->callbacks.begin_request = &begin_request_handler;

    // Start the web server.
    server->ctx = mg_start(&server->callbacks, user_data, options);

    servers[port] = server;

    return server;
}

void sk_stop_web_server(sk_web_server *server)
{
    // Clear requests
    if (server->last_request)
    {
        sk_flush_request(server->last_request);
        delete server->last_request;
    }

    sk_server_request *request;
    while (server->request_queue.try_take(request))
    {
        sk_flush_request(request);
    }

    _web_server_ctx_data *user_data = static_cast<_web_server_ctx_data *>(mg_get_user_data(server->ctx));
    if ( user_data )
    {
        delete user_data;
    }

    mg_stop(server->ctx);

    auto it = servers.find(server->port);
    if (it != servers.end())
    {
        servers.erase(it);
    }
    else
    {
        LOG(WARNING) << "Tried to remove from servers map a server which did not exist.";
    }
}
