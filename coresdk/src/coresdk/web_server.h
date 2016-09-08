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

#include <string>

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
    bool has_waiting_requests(web_server server);

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
     * Sends a message to a given `server_request`.
     *
     * @param r     The `server_request` to send the response to
     * @param resp  The messsage, in the form of a `server_response`, to be sent.
     *
     * @attribute class server_request
     * @attribute self  r
     */
    void send_response(server_request r, server_response resp);

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
     * Requests a URI from the web server.
     *
     * @param r The request to be sent.
     *
     * @returns Returns the requested URI in the form of a string.
     */
    string request_get_uri(server_request r);
    
#endif /* web_server_h_ */
}