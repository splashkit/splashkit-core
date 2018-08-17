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

using std::to_string;

namespace splashkit_lib
{
    static map<unsigned short, sk_web_server*> servers;

    struct _web_server_ctx_data
    {
        unsigned short port;
    };

    static int begin_request_handler(struct mg_connection *conn)
    {
        _web_server_ctx_data *user_data;
        user_data = static_cast<_web_server_ctx_data *>(mg_get_user_data(mg_get_context(conn)));
        if ( not user_data )
        {
            LOG(WARNING) << "Request handler called within invalid user data. Contact splashkit dev team.";
            return -1;
        }

        unsigned short port = user_data->port;
        if (servers.count(port) == 0)
        {
            LOG(WARNING) << "Request handler called on non-existent server";
            return -1;
        }

        const struct mg_request_info *request_info = mg_get_request_info(conn);

        sk_http_request *r = new sk_http_request;
        r->id = HTTP_REQUEST_PTR;
        r->uri = request_info->request_uri ? request_info->request_uri : "" ;
        r->query_string = request_info->query_string ? request_info->query_string : "";
        r->filename = "";

        if ( strncmp(request_info->request_method, "GET", 4) == 0 )
        {
            r->method = HTTP_GET_METHOD;
        }
        else if ( strncmp(request_info->request_method, "PUT", 4) == 0 )
        {
            r->method = HTTP_PUT_METHOD;
        }
        else if ( strncmp(request_info->request_method, "POST", 5) == 0 )
        {
            r->method = HTTP_POST_METHOD;
        }
        else if ( strncmp(request_info->request_method, "DELETE", 7) == 0 )
        {
            r->method = HTTP_DELETE_METHOD;
        }
        else if ( strncmp(request_info->request_method, "OPTIONS", 8) == 0 )
        {
            r->method = HTTP_OPTIONS_METHOD;
        }
        else if ( strncmp(request_info->request_method, "TRACE", 6) == 0 )
        {
            r->method = HTTP_TRACE_METHOD;
        }
        else
        {
            LOG(ERROR) << "Http request got unknown method: " << request_info->request_method << ". Please report as issue to SplashKit dev team.";
            r->method = UNKNOWN_HTTP_METHOD;
        }

        if (r->method == HTTP_POST_METHOD or r->method == HTTP_PUT_METHOD)
        {
            char post_data[10240];
            int post_data_len;
            post_data_len = mg_read(conn, post_data, sizeof(post_data));

            r->body = string(post_data);
        }

        servers[port]->request_queue.put(r); // Add request to concurrent queue
        r->control.acquire(); // Waits until user returns response.

        // Send HTTP reply to the client
        mg_printf(conn,
                  "HTTP/1.1 %d\r\n"
                  "Content-Type: %s\r\n"
                  "Connection: close\r\n"
                  "Content-Length: %lu\r\n" // Always set Content-Length
                  "\r\n"
                  "%s",
                  r->response->code,
                  r->response->content_type.c_str(),
                  r->response->message_size,
                  r->response->message);

        r->response->response_sent.release();

        // Remove the request
        r->id = NONE_PTR;
        delete r;

        // Non-zero return means civetweb has replied to client
        return 1;
    }

    void sk_flush_request(sk_http_request *request)
    {
        request->response = new sk_http_response;

        request->response->id = HTTP_RESPONSE_PTR;
        request->response->message = nullptr;
        request->response->message_size = 0;
        request->response->code = HTTP_STATUS_SERVICE_UNAVAILABLE;
        request->response->content_type = "text/plain";

        request->control.release();
    }

    /*
     * Copy's and returns the request from the last_request object
     * and sets the variable to null so it can't be retrieved again.
     */
    sk_http_request* sk_get_request(sk_web_server *server)
    {
        sk_http_request* request;

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
        sk_http_request *request;
        bool success = server->request_queue.try_take(request);

        if (success)
        {
            server->last_request = request;
            return true;
        }

        return false;
    }

    sk_web_server* sk_start_web_server(unsigned short port)
    {
        internal_sk_init();

//        LOG(DEBUG) << "Starting a web server on port " << port;

        if (servers.find(port) != servers.end())
        {
            LOG(WARNING) << "Server already started on port " << port;
            return nullptr;
        }

        sk_web_server *server = new sk_web_server;
        server->id = WEB_SERVER_PTR;
        server->port = port;
        server->last_request = nullptr;

        string port_str = to_string(port);

        // List of options. Last element must be NULL.
        const char *options[] = {"listening_ports", port_str.c_str(), NULL};

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
        
        sk_http_request *request;
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
}
