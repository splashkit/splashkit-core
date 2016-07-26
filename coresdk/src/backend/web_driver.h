//
//  SGSDL2Web.h
//  sgsdl2
//
//  Created by Andrew Cain on 1/05/2015.
//  Copyright (c) 2015 Andrew Cain. All rights reserved.
//

#ifndef __sgsdl2__SGSDL2Web__
#define __sgsdl2__SGSDL2Web__

#include "backend_types.h"

void sk_init_web();
void sk_finalise_web();

sk_http_response sk_http_post(const char *host, unsigned short port, const char *body);
sk_http_response sk_http_get(const char *host, unsigned short port);
sk_http_response sk_http_put(const char *host, unsigned short port, const char *body);
sk_http_response sk_http_delete(const char *host, unsigned short port, const char *body);
sk_http_response sk_http_make_request(sk_http_request request);


#endif /* defined(__sgsdl2__SGSDL2Web__) */
