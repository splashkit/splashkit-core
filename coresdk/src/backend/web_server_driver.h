//
//  web_server.h
//  splashkit
//
//  Created by James Armstrong on 21/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//


#ifndef __sgsdl2__SGSDL2WebServer__
#define __sgsdl2__SGSDL2WebServer__

#include "backend_types.h"

namespace splashkit_lib
{
    void sk_flush_request(sk_http_request *request);

    sk_http_request* sk_get_request(sk_web_server *server);

    bool sk_has_waiting_requests(sk_web_server *server);

    sk_web_server* sk_start_web_server(unsigned short port);

    void sk_stop_web_server(sk_web_server *server);
}
#endif /* defined(__sgsdl2__SGSDL2WebServer__) */
