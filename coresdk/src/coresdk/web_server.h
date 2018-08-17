/**
 * @header  web_server
 * @author  James Armstrong
 * @attribute group networking
 * @attribute static web_server
 */

#ifndef web_server_h_
#define web_server_h_

#include "types.h"
#include "json.h"

#include <string>
#include <vector>

using std::string;
using std::vector;

namespace splashkit_lib
{
    /**
     * The web server is able to listen for incomming requests, and you can then provide the response.
     *
     * @attribute class web_server
     */
    typedef struct sk_web_server *web_server;

    /**
     * The request contains the details of the resource the user is requesting.
     *
     * @attribute class http_request
     * @attribute no_destructor true
     */
    typedef struct sk_http_request *http_request;

    /**
     * The method token is used to indicate the kind of action to be performed
     * on the server. See [W3 specifications](https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html).
     *
     * @constant HTTP_GET_METHOD        A get method
     * @constant HTTP_POST_METHOD       A post method
     * @constant HTTP_PUT_METHOD        A put method
     * @constant HTTP_DELETE_METHOD     A delete method
     * @constant HTTP_OPTIONS_METHOD    An options method
     * @constant HTTP_TRACE_METHOD      A trace method
     * @constant UNKNOWN_HTTP_METHOD    A method not recognised by SplashKit
     */
    enum http_method
    {
        HTTP_GET_METHOD,
        HTTP_POST_METHOD,
        HTTP_PUT_METHOD,
        HTTP_DELETE_METHOD,
        HTTP_OPTIONS_METHOD,
        HTTP_TRACE_METHOD,
        UNKNOWN_HTTP_METHOD
    };

    /**
     * Starts the web server on a given port number.
     *
     * @param port  The port number to connect through.
     *
     * @returns     Returns a new `web_server` instance.
     *
     * @attribute class       web_server
     * @attribute constructor true
     */
    web_server start_web_server(unsigned short port);

    /**
     * Creates a new web server instance and starts it.
     *
     * @attribute constructor true
     * @attribute class       web_server
     *
     * @returns Returns a new `web_sever` instance.
     *
     * @attribute suffix  with_default_port
     */
    web_server start_web_server();

    /**
     * Returns true if the given `web_sever` has pending requests.
     *
     * @param server  The `web_server` to check for waiting requests.
     *
     * @returns Returns a `bool` denoting whether the `web_server` has pending requests.
     *
     * @attribute self  server
     * @attribute class web_server
     * @attribute getter has_incoming_requests
     */
    bool has_incoming_requests(web_server server);

    /**
     * Stops a given `web_server` instance.
     *
     * @param server  The server instance to stop.
     *
     * @attribute destructor  true
     * @attribute class       web_server
     * @attribute self        server
     * @attribute method      stop
     */
    void stop_web_server(web_server server);

    /**
     * Returns the next request on a given `web_server` instance
     *
     * @param server  The `web_server` to get the `http_request` from.
     *
     * @returns       Returns the next request on the given `web_server` instance.
     *
     * @attribute class web_server
     * @attribute self  server
     * @attribute getter next_web_request
     */
    http_request next_web_request(web_server server);

    /**
     * Sends a message to a given `http_request` with the specified content type.
     *
     * @param r             The `http_request` to send the response to
     * @param code          The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
     * @param message       The messsage, in the form of a `http_response`, to be sent.
     * @param content_type  The content type of the response.
     *
     * @attribute class http_request
     * @attribute self  r
     * @attribute method send_response
     *
     * @attribute suffix  with_status_and_content_type
     */
    void send_response(http_request r, http_status_code code, const string &message, const string &content_type);

    /**
     * Sends a message to a given `http_request` with the specified content type.
     *
     * @param r             The `http_request` to send the response to
     * @param code          The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
     * @param message       The messsage, in the form of a `http_response`, to be sent.
     *
     * @attribute class http_request
     * @attribute self  r
     * @attribute method send_response
     *
     * @attribute suffix  with_status
     */
    void send_response(http_request r, http_status_code code, const string &message);

    /**
     * Sends a message to a given `http_request`.
     *
     * @param r       The request to be sent.
     * @param message The message to be sent
     *
     * @attribute class http_request
     * @attribute method send_response
     */
    void send_response(http_request r, const string &message);

    /**
     * Send a JSON response to a given `http_request`
     *
     * @param r The request the response belongs to.
     * @param j The json to be sent.
     *
     * @attribute class http_request
     * @attribute method send_response
     *
     * @attribute suffix  json
     */
    void send_response(http_request r, json j);

    /**
     * Sends a response code to a given `http_request`.
     *
     * @param r             The `http_request` to send the response to
     * @param code          The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
     *
     * @attribute class http_request
     * @attribute self  r
     * @attribute method send_response
     *
     * @attribute suffix  json_with_status
     */
    void send_response(http_request r, http_status_code code);

    /**
     * Sends a response with no content to a `http_request`.
     *
     * @param r             The `http_request` to send the response to
     *
     * @attribute class http_request
     * @attribute self  r
     * @attribute method send_response
     *
     * @attribute suffix  empty
     */
    void send_response(http_request r);

    /**
     * Serves a file to the given `http_request`.
     *
     * @param r        The request which is asking for the resource.
     * @param filename The name of the file in Resources/server
     * @param content_type The type of content being send:
     *
     * @attribute class http_request
     * @attribute method send_file_response
     */
    void send_file_response(http_request r, const string &filename, const string &content_type);
    
    /**
     * Serves a HTML file to the given `http_request`.
     *
     * @param r        The request which is asking for the resource.
     * @param filename The name of the file in Resources/server
     *
     * @attribute class http_request
     * @attribute method send_html_file_response
     */
    void send_html_file_response(http_request r, const string &filename);

    /**
     * Serves a javascript file to the given `http_request`.
     *
     * @param r        The request which is asking for the resource.
     * @param filename The name of the file in Resources/server
     *
     * @attribute class http_request
     * @attribute method send_javascript_file_response
     */
    void send_javascript_file_response(http_request r, const string &filename);
    
    /**
     * Serves a css file to the given `http_request`.
     *
     * @param r        The request which is asking for the resource.
     * @param filename The name of the file in Resources/server
     *
     * @attribute class http_request
     * @attribute method send_css_file_response
     */
    void send_css_file_response(http_request r, const string &filename);
    
    /**
     * Returns the server URI of the client request.
     *
     * @param r A request object.
     *
     * @returns Returns the requested URI in the form of a string.
     *
     * @attribute class http_request
     * @attribute getter uri
     */
    string request_uri(http_request r);
    
    /**
     * Returns the URI query string of the client request.
     *
     * @param r A request object.
     *
     * @returns Returns the requested URI queries in the form of a string.
     *
     * @attribute class http_request
     * @attribute getter query_string
     */
    string request_query_string(http_request r);

    /**
     * Returns the value of a parameter from within the query string, or the supplied default
     * if no matching parameter is found.
     *
     * @param r A request object.
     * @param name The name of the parameter to fetch
     * @param default_value The value to return if the named parameter is not in the query string.
     *
     * @returns Returns value of the parameter from the query string, or the default value if the parameter is not found.
     *
     * @attribute class http_request
     * @attribute method query_parameter
     */
    string request_query_parameter(http_request r, const string &name, const string &default_value);
    
    /**
     * Returns true if the parameter exists in the query string.
     *
     * @param r A request object.
     * @param name The name of the parameter to check
     *
     * @returns True if the parameter exists in the user's request.
     *
     * @attribute class http_request
     * @attribute method has_query_parameter
     */
    bool request_has_query_parameter(http_request r, const string &name);

    /**
     * Returns the HTTP method of the client request.
     *
     * @param r A request object.
     *
     * @returns Returns the request method.
     *
     * @attribute class http_request
     * @attribute getter method
     */
    http_method request_method(http_request r);
    

    /**
     * Returns the body of the request.
     *
     * @param r A request object.
     *
     * @returns The body of the request.
     *
     * @attribute class http_request
     * @attribute getter body
     */
    string request_body(http_request r);

    /**
     * Returns an array of strings representing each stub of the URI.
     *
     * For example a request sent to http://localhost:8080/names/0 returns...
     *
     *      ["names", "0"]
     *
     * @param r The request for retrieving URI to split into stubs.
     *
     * @return The array of stubs as strings.
     *
     * @attribute class http_request
     * @attribute getter uri_stubs
     */
    vector<string> request_uri_stubs(http_request r);

    /**
     * Returns an array of strings representing each stub of the URI.
     *
     * For example a request sent to http://localhost:8080/names/0 returns...
     *
     *      ["names", "0"]
     *
     * @param uri The URI to split into stubs.
     *
     * @return The array of stubs as strings.
     */
    vector<string> split_uri_stubs(const string &uri);


    /**
     * Checks if a request is after a given resource.
     *
     * @param  request The request to check
     * @param  method  The kind of request
     * @param  path    The resource/route path
     * @return         True if the request is for the indicated method and path
     *
     * @attribute class http_request
     * @attribute method is_request_for
     */
    bool is_request_for(http_request request, http_method method, const string &path);

    /**
     * Checks if a request wants to get a given resource.
     *
     * @param  request The request to check
     * @param  path    The resource/route path
     * @return         True if the request is a HTTP GET request for `path`
     *
     * @attribute class http_request
     * @attribute method is_get_request_for
     */
    bool is_get_request_for(http_request request, const string &path);

    /**
     * Checks if a request wants to create (post) a given resource.
     *
     * @param  request The request to check
     * @param  path    The resource/route path
     * @return         True if the request is a HTTP POST request for `path`
     *
     * @attribute class http_request
     * @attribute method is_post_request_for
     */
    bool is_post_request_for(http_request request, const string &path);

    /**
     * Checks if a request wants to update (put) a given resource.
     *
     * @param  request The request to check
     * @param  path    The resource/route path
     * @return         True if the request is a HTTP PUT request for `path`
     *
     * @attribute class http_request
     * @attribute method is_put_request_for
     */
    bool is_put_request_for(http_request request, const string &path);

    /**
     * Checks if a request wants to delete a given resource.
     *
     * @param  request The request to check
     * @param  path    The resource/route path
     * @return         True if the request is a HTTP DELETE request for `path`
     *
     * @attribute class http_request
     * @attribute method is_delete_request_for
     */
    bool is_delete_request_for(http_request request, const string &path);

    /**
     * Checks if a request wants to check options for given resource.
     *
     * @param  request The request to check
     * @param  path    The resource/route path
     * @return         True if the request is a HTTP OPTIONS request for `path`
     *
     * @attribute class http_request
     * @attribute method is_options_request_for
     */
    bool is_options_request_for(http_request request, const string &path);

    /**
     * Checks if a request wants to trace a given resource.
     *
     * @param  request The request to check
     * @param  path    The resource/route path
     * @return         True if the request is a HTTP TRACE request for `path`
     *
     * @attribute class http_request
     * @attribute method is_trace_request_for
     */
    bool is_trace_request_for(http_request request, const string &path);
}
#endif /* web_server_h_ */
