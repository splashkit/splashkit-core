//
//  web_server.h
//  splashkit
//
//  Created by James Armstrong on 21/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef web_server_h_
#define web_server_h_

#include "types.h"

#include <string>

using namespace std;

typedef struct sk_web_server *web_server;
typedef struct sk_server_request *server_request;
typedef struct sk_server_response *server_response;

web_server start_web_server(string port);

web_server start_web_server();

bool has_waiting_requests(web_server server);

void stop_web_server(web_server server);

server_request next_web_request(web_server server);

void send_response(server_request r, server_response resp);

void send_response(server_request r, string message);

string request_get_uri(server_request r);

#endif /* web_server_h_ */
