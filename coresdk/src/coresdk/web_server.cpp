//
//  web_server.cpp
//  splashkit
//
//  Created by James Armstrong on 21/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "utility_functions.h"
#include "web_server.h"
#include "web_client.h"
#include "web_server_driver.h"
#include "utils.h"

namespace splashkit_lib
{
    web_server start_web_server(unsigned short port)
    {
        return sk_start_web_server(port);
    }

    web_server start_web_server()
    {
        return start_web_server(8080);
    }

    bool has_incoming_requests(web_server server)
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

    http_request next_web_request(web_server server)
    {
        if (INVALID_PTR(server, WEB_SERVER_PTR))
        {
            LOG(WARNING) << "next_web_request called on an invalid server";
            return nullptr;
        }

        return sk_get_request(server);
    }

    void _send_response(http_request r, http_response resp)
    {
        if (INVALID_PTR(r, HTTP_REQUEST_PTR))
        {
            LOG(WARNING) << "send_response called on an invalid request";
            return;
        }
        else if (INVALID_PTR(resp, HTTP_RESPONSE_PTR))
        {
            LOG(WARNING) << "send_response called on an invalid response";
            return;
        }

        r->response = resp;
        r->control.release();
    }

    void send_response(http_request r, const string &message)
    {
        send_response(r, HTTP_STATUS_OK, message, "text/plain");
    }

    void send_response(http_request r, http_status_code code, const string &message, const string &content_type)
    {
        sk_http_response resp;

        resp.id = HTTP_RESPONSE_PTR;
        resp.message = strdup(message.c_str()); // copy to pass to non-const ref -- as this is used for sending and receiving data
        resp.message_size = message.size();
        resp.content_type = content_type;
        resp.code = code;

        _send_response(r, &resp);

        // Wait for sending thread to actually send the data...
        resp.response_sent.acquire();
        // Safe to delete
        delete resp.message;
    }

    void send_response(http_request r, http_status_code code, const string &message)
    {
        send_response(r, code, message, "text/html");
    }

    void send_response(http_request r, json j)
    {
        send_response(r, HTTP_STATUS_OK, json_to_string(j), "application/json");
    }

    void send_response(http_request r, http_status_code code)
    {
        send_response(r, code, "", "text/plain");
    }

    void send_response(http_request r)
    {
        send_response(r, HTTP_STATUS_NO_CONTENT, "", "text/plain");
    }

    void send_html_file_response(http_request r, const string &filename)
    {
        string extension = ".html";
        if (filename.size() > extension.size() &&
                filename.compare(filename.size() - extension.size(), extension.size(), extension) == 0)
        {
            string file = file_as_string(filename, SERVER_RESOURCE);

            send_response(r, HTTP_STATUS_OK, file, "text/html");
        }
        else
        {
            LOG(WARNING) << "send_html_file_response passed invalid html at " << filename;
            send_response(r, cat({"Invalid HTML file at ", path_to_resource(filename, SERVER_RESOURCE)}));
        }
    }

    string request_uri(http_request r)
    {
        if (INVALID_PTR(r, HTTP_REQUEST_PTR))
        {
            LOG(WARNING) << "Getting request uri with invalid request";
            return "";
        }

        return r->uri;
    }

    http_method request_method(http_request r)
    {
        if (INVALID_PTR(r, HTTP_REQUEST_PTR))
        {
            LOG(WARNING) << "Requesting http method on an invalid request";
            return UNKNOWN_HTTP_METHOD;
        }

        return r->method;
    }

    string request_body(http_request r)
    {
        if (INVALID_PTR(r, HTTP_REQUEST_PTR))
        {
            LOG(WARNING) << "Getting request body with invalid request";
            return "";
        }

        return r->body;
    }

    vector<string> request_uri_stubs(http_request r)
    {
        string uri = request_uri(r);
        return split_uri_stubs(uri);
    }

    vector<string> split_uri_stubs(const string &uri)
    {
        stringstream ss(uri);
        string stub;
        vector<string> result;

        while (getline(ss, stub, '/'))
        {
            result.push_back(stub);
        }

        // Remove "/" from the list of stubs if stubs > 1
        if (result.size() > 1)
        {
            result.erase(result.begin());
        }

        return result;
    }

    bool is_request_for(http_request request, http_method method, const string &path)
    {
        if ( request_method(request) != method ) return false;
        return request_uri(request) == path;
    }

    bool is_get_request_for(http_request request, const string &path)
    {
        return is_request_for(request, HTTP_GET_METHOD, path);
    }

    bool is_post_request_for(http_request request, const string &path)
    {
        return is_request_for(request, HTTP_POST_METHOD, path);
    }

    bool is_put_request_for(http_request request, const string &path)
    {
        return is_request_for(request, HTTP_PUT_METHOD, path);
    }

    bool is_delete_request_for(http_request request, const string &path)
    {
        return is_request_for(request, HTTP_DELETE_METHOD, path);
    }

    bool is_options_request_for(http_request request, const string &path)
    {
        return is_request_for(request, HTTP_OPTIONS_METHOD, path);
    }

    bool is_trace_request_for(http_request request, const string &path)
    {
        return is_request_for(request, HTTP_TRACE_METHOD, path);
    }
}
