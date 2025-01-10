//
//  SGSDL2Network.h
//  sgsdl2
//
//  Created by Andrew Cain on 16/11/2014.
//  Copyright (c) 2014 Andrew Cain. All rights reserved.
//

#ifndef __sgsdl2__SGSDL2Network__
#define __sgsdl2__SGSDL2Network__

#include "backend_types.h"

namespace splashkit_lib
{
    void sk_network_init();

    sk_network_connection sk_open_udp_connection(unsigned short port);
    sk_network_connection sk_open_tcp_connection(const char *host, unsigned short port);

    int sk_send_bytes(sk_network_connection *con, char *buffer, unsigned long size);

    int sk_send_udp_message(sk_network_connection *con, const char *host, unsigned short port, const char *buffer, unsigned long size);
    void sk_read_udp_message(sk_network_connection *con, unsigned int *host, unsigned short *port, char *buffer, unsigned long *size);

    int sk_read_bytes(sk_network_connection *con, char *buffer, int size);

    void sk_close_connection(sk_network_connection *con);

    unsigned int sk_network_address(sk_network_connection *con);

    unsigned int sk_get_network_port(sk_network_connection *con);

    sk_network_connection sk_accept_connection(sk_network_connection &con);

    unsigned int sk_network_has_data();
    unsigned int sk_connection_has_data(sk_network_connection *con);
}
#endif /* defined(__sgsdl2__SGSDL2Network__) */
