//
// SplashKit Generated Web Server C++ Code
// DO NOT MODIFY
//

#ifndef __web_server_h
#define __web_server_h

#include "json.h"
#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

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
/**
* Returns true if the given `web_sever` has pending requests.
* @param server The `web_server` to check for waiting requests.
* @return Returns a `bool` denoting whether the `web_server` has pending requests.
*/
bool has_incoming_requests(web_server server);
/**
* Checks if a request wants to delete a given resource.
* @param request The request to check
* @param path The resource/route path
* @return True if the request is a HTTP DELETE request for `path`
*/
bool is_delete_request_for(http_request request, const string &path);
/**
* Checks if a request wants to get a given resource.
* @param request The request to check
* @param path The resource/route path
* @return True if the request is a HTTP GET request for `path`
*/
bool is_get_request_for(http_request request, const string &path);
/**
* Checks if a request wants to check options for given resource.
* @param request The request to check
* @param path The resource/route path
* @return True if the request is a HTTP OPTIONS request for `path`
*/
bool is_options_request_for(http_request request, const string &path);
/**
* Checks if a request wants to create (post) a given resource.
* @param request The request to check
* @param path The resource/route path
* @return True if the request is a HTTP POST request for `path`
*/
bool is_post_request_for(http_request request, const string &path);
/**
* Checks if a request wants to update (put) a given resource.
* @param request The request to check
* @param path The resource/route path
* @return True if the request is a HTTP PUT request for `path`
*/
bool is_put_request_for(http_request request, const string &path);
/**
* Checks if a request is after a given resource.
* @param request The request to check
* @param method The kind of request
* @param path The resource/route path
* @return True if the request is for the indicated method and path
*/
bool is_request_for(http_request request, http_method method, const string &path);
/**
* Checks if a request wants to trace a given resource.
* @param request The request to check
* @param path The resource/route path
* @return True if the request is a HTTP TRACE request for `path`
*/
bool is_trace_request_for(http_request request, const string &path);
/**
* Returns the next request on a given `web_server` instance
* @param server The `web_server` to get the `http_request` from.
* @return Returns the next request on the given `web_server` instance.
*/
http_request next_web_request(web_server server);
/**
* Returns the body of the request.
* @param r A request object.
* @return The body of the request.
*/
string request_body(http_request r);
/**
* Returns true if the parameter exists in the query string.
* @param r A request object.
* @param name The name of the parameter to check
* @return True if the parameter exists in the user's request.
*/
bool request_has_query_parameter(http_request r, const string &name);
/**
* Returns the headers of the request.
* @param r A request object.
* @return The headers of the request.
*/
vector<string> request_headers(http_request r);
/**
* Returns the HTTP method of the client request.
* @param r A request object.
* @return Returns the request method.
*/
http_method request_method(http_request r);
/**
* Returns the value of a parameter from within the query string, or the supplied default
* if no matching parameter is found.
* @param r A request object.
* @param name The name of the parameter to fetch
* @param default_value The value to return if the named parameter is not in the query string.
* @return Returns value of the parameter from the query string, or the default value if the parameter is not found.
*/
string request_query_parameter(http_request r, const string &name, const string &default_value);
/**
* Returns the URI query string of the client request.
* @param r A request object.
* @return Returns the requested URI queries in the form of a string.
*/
string request_query_string(http_request r);
/**
* Returns the server URI of the client request.
* @param r A request object.
* @return Returns the requested URI in the form of a string.
*/
string request_uri(http_request r);
/**
* Returns an array of strings representing each stub of the URI.
* 
* For example a request sent to `http://localhost:8080/names/0` returns...
* 
* ["names", "0"]
* @param r The request for retrieving URI to split into stubs.
* @return The array of stubs as strings.
*/
vector<string> request_uri_stubs(http_request r);
/**
* Serves a css file to the given `http_request`.
* @param r The request which is asking for the resource.
* @param filename The name of the file in Resources/server
*
*/
void send_css_file_response(http_request r, const string &filename);
/**
* Serves a file to the given `http_request`.
* @param r The request which is asking for the resource.
* @param filename The name of the file in Resources/server
* @param content_type The type of content being send:
*
*/
void send_file_response(http_request r, const string &filename, const string &content_type);
/**
* Serves a HTML file to the given `http_request`.
* @param r The request which is asking for the resource.
* @param filename The name of the file in Resources/server
*
*/
void send_html_file_response(http_request r, const string &filename);
/**
* Serves a javascript file to the given `http_request`.
* @param r The request which is asking for the resource.
* @param filename The name of the file in Resources/server
*
*/
void send_javascript_file_response(http_request r, const string &filename);
/**
* Sends a response with no content to a `http_request`.
* @param r The `http_request` to send the response to
*
*/
void send_response(http_request r);
/**
* Sends a message to a given `http_request`.
* @param r The request to be sent.
* @param message The message to be sent
*
*/
void send_response(http_request r, const string &message);
/**
* Sends a response code to a given `http_request`.
* @param r The `http_request` to send the response to
* @param code The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
*
*/
void send_response(http_request r, http_status_code code);
/**
* Sends a message to a given `http_request` with the specified content type.
* @param r The `http_request` to send the response to
* @param code The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
* @param message The messsage, in the form of a `http_response`, to be sent.
*
*/
void send_response(http_request r, http_status_code code, const string &message);
/**
* Sends a message to a given `http_request` with the specified content type.
* @param r The `http_request` to send the response to
* @param code The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
* @param message The messsage, in the form of a `http_response`, to be sent.
* @param content_type The content type of the response.
*
*/
void send_response(http_request r, http_status_code code, const string &message, const string &content_type);
/**
* Sends a message to a given `http_request` with the specified content type.
* @param r The `http_request` to send the response to
* @param code The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
* @param message The messsage, in the form of a `http_response`, to be sent.
* @param content_type The content type of the response.
* @param headers The response headers
*
*/
void send_response(http_request r, http_status_code code, const string &message, const string &content_type, const vector<string> &headers);
/**
* Send a JSON response to a given `http_request`
* @param r The request the response belongs to.
* @param j The json to be sent.
*
*/
void send_response(http_request r, json j);
/**
* Returns an array of strings representing each stub of the URI.
* 
* For example a request sent to `http://localhost:8080/names/0` returns...
* 
* ["names", "0"]
* @param uri The URI to split into stubs.
* @return The array of stubs as strings.
*/
vector<string> split_uri_stubs(const string &uri);
/**
* Creates a new web server listening for connections on port 8080.

* @return Returns a new `web_sever` instance.
*/
web_server start_web_server();
/**
* Starts the web server on a given port number.
* @param port The port number to connect through.
* @return Returns a new `web_server` instance.
*/
web_server start_web_server(unsigned short port);
/**
* Stops a given `web_server` instance.
* @param server The server instance to stop.
*
*/
void stop_web_server(web_server server);

#endif /* __web_server_h */
