//
// SplashKit Generated Web Server C++ Code
// DO NOT MODIFY
//

#ifndef __web_server_h
#define __web_server_h

#include "types.h"
#include "json.h"
#include "web_server.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _http_request_data;
typedef struct _http_request_data *http_request;
struct _web_server_data;
typedef struct _web_server_data *web_server;
typedef enum {
    HTTP_GET_METHOD,
    HTTP_POST_METHOD,
    HTTP_PUT_METHOD,
    HTTP_DELETE_METHOD,
    HTTP_OPTIONS_METHOD,
    HTTP_TRACE_METHOD,
    UNKNOWN_HTTP_METHOD
} http_method;
bool has_incoming_requests(web_server server);
bool is_delete_request_for(http_request request, const string &path);
bool is_get_request_for(http_request request, const string &path);
bool is_options_request_for(http_request request, const string &path);
bool is_post_request_for(http_request request, const string &path);
bool is_put_request_for(http_request request, const string &path);
bool is_request_for(http_request request, http_method method, const string &path);
bool is_trace_request_for(http_request request, const string &path);
http_request next_web_request(web_server server);
string request_body(http_request r);
bool request_has_query_parameter(http_request r, const string &name);
http_method request_method(http_request r);
string request_query_parameter(http_request r, const string &name, const string &default_value);
string request_query_string(http_request r);
string request_uri(http_request r);
vector<string> request_uri_stubs(http_request r);
void send_css_file_response(http_request r, const string &filename);
void send_file_response(http_request r, const string &filename, const string &content_type);
void send_html_file_response(http_request r, const string &filename);
void send_javascript_file_response(http_request r, const string &filename);
void send_response(http_request r);
void send_response(http_request r, const string &message);
void send_response(http_request r, http_status_code code);
void send_response(http_request r, http_status_code code, const string &message);
void send_response(http_request r, http_status_code code, const string &message, const string &content_type);
void send_response(http_request r, json j);
vector<string> split_uri_stubs(const string &uri);
web_server start_web_server();
web_server start_web_server(unsigned short port);
void stop_web_server(web_server server);

#endif /* __web_server_h */
