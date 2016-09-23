/**
 * @header Web Server
 * @author James Armstrong
 * @brief
 *
 * @attribute static web_server
 */

#ifndef web_server_h_
#define web_server_h_

#include "types.h"
#include "json.h"

#include <string>
#include <vector>

using namespace std;

namespace splashkit_lib
{
    /**
     * @attribute class web_server
     */
    typedef struct sk_web_server *web_server;

    /**
     * @attribute class server_request
     */
    typedef struct sk_server_request *server_request;

    /**
     * @attribute class server_response
     */
    typedef struct sk_server_response *server_response;

    /**
     * The method token is used to indicate the kind of action to be performed
     * on the server. See [w3 specifications](https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html).
     *
     * @constant HTTP_GET_METHOD       A get method
     * @constant HTTP_POST_METHOD      A get method
     * @constant HTTP_PUT_METHOD       A get method
     * @constant HTTP_DELETE_METHOD    A get method
     * @constant UNKNOWN_HTTP_METHOD A get method
     */
    enum http_method
    {
        HTTP_GET_METHOD,
        HTTP_POST_METHOD,
        HTTP_PUT_METHOD,
        HTTP_DELETE_METHOD,
        UNKNOWN_HTTP_METHOD
    };

    /**
     * Starts the web server on a given port number.
     *
     * @param port  The port number to connect through.
     *
     * @returns     Returns a new `web_server` instance.
     *
     * @attribute constructor true
     * @attribute class       web_server
     */
    web_server start_web_server(string port);

    /**
     * Creates a new web server instance and starts it.
     *
     * @attribute constructor true
     * @attribute class       web_server
     * @attribute method      start
     *
     * @returns Returns a new `web_sever` instance.
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
     * @param server  The `web_server` to get the `server_request` from.
     *
     * @returns       Returns the next request on the given `web_server` instance.
     *
     * @attribute class web_server
     * @attribute self  server
     */
    server_request next_web_request(web_server server);

    /**
     * Sends a message to a given `server_request` with the specified content type.
     *
     * @param r             The `server_request` to send the response to
     * @param code          The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
     * @param message       The messsage, in the form of a `server_response`, to be sent.
     * @param content_type  The content type of the response.
     *
     * @attribute class server_request
     * @attribute self  r
     */
    void send_response(server_request r, http_status_code code, string message, string content_type);

    /**
     * Sends a message to a given `server_request` with the specified content type.
     *
     * @param r             The `server_request` to send the response to
     * @param code          The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
     * @param message       The messsage, in the form of a `server_response`, to be sent.
     *
     * @attribute class server_request
     * @attribute self  r
     */
    void send_response(server_request r, http_status_code code, string message);

    /**
     * Sends a message to a given `server_request`.
     *
     * @param r       The request to be sent.
     * @param message The message to be sent
     *
     * @attribute class server_response
     */
    void send_response(server_request r, string message);

    /**
     * Send a JSON response to a given `server_request`
     *
     * @param r The request the response belongs to.
     * @param j The json to be sent.
     *
     * @attribute class server_response
     */
    void send_response(server_request r, json j);

    /**
     * Sends a response code to a given `server_request`.
     *
     * @param r             The `server_request` to send the response to
     * @param code          The [HTTP status code](See https://en.wikipedia.org/wiki/List_of_HTTP_status_codes) to be sent.
     *
     * @attribute class server_request
     * @attribute self  r
     */
    void send_response(server_request r, http_status_code code);

    /**
     * Sends a response with no content to a `server_request`.
     *
     * @param r             The `server_request` to send the response to
     *
     * @attribute class server_request
     * @attribute self  r
     */
    void send_response(server_request r);

    /**
     * Serves a HTML file to the given `server_request`.
     *
     * @param r        The request to be sent.
     * @param filename The name of the file in Resources/server
     *
     * @attribute class server_response
     */
    void send_html_file_response(server_request r, string filename);

    /**
     * Returns the server URI of the client request.
     *
     * @param r A request object.
     *
     * @returns Returns the requested URI in the form of a string.
     */
    string request_uri(server_request r);

    /**
     * Returns the HTTP method of the client request.
     *
     * @param r A request object.
     *
     * @returns Returns the request method.
     */
    http_method request_method(server_request r);

    /**
     * Returns the body of the request.
     *
     * @param r A request object.
     *
     * @returns The body of the request.
     */
    string request_body(server_request r);

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
     */
    vector<string> request_uri_stubs(server_request r);

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
     */
    bool route_matches(server_request request, http_method method, const string &path);
}
#endif /* web_server_h_ */
