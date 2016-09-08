//
//  SGSDL2Network.h
//  sgsdl2
//
//  Created by Andrew Cain on 16/11/2014.
//  Copyright (c) 2014 Andrew Cain. All rights reserved.
//

#ifndef __sgsdl2__SGSDL2Network__
#define __sgsdl2__SGSDL2Network__
namespace splashkit_lib
{
    enum sk_connection_kind
    {
        SGCK_UNKNOWN = 0,
        SGCK_TCP = 1,
        SGCK_UDP = 2
    };

    struct sk_network_connection
    {
        sk_connection_kind kind;

        // private data used by the backend
        void * _socket;
    };

    void sk_network_init();
}
#endif /* defined(__sgsdl2__SGSDL2Network__) */
