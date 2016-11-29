//
//  skNetwork.cpp
//  sk
//
//  Created by Andrew Cain on 16/11/2014.
//  Copyright (c) 2014 Andrew Cain. All rights reserved.
//

#include "core_driver.h"
#include "network_driver.h"
#include "easylogging++.h"

#include <stdio.h>

#ifdef __linux__
#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#else
#include <SDL.h>
#include <SDL_net.h>
#endif

#include <string.h>
#include <stdlib.h>
namespace splashkit_lib
{
    // This set keeps track of all of the sockets to see if there is activity
    SDLNet_SocketSet _sockets; // allocate on setup of functions.

    void sk_network_init()
    {
        SDLNet_Init();
        _sockets = SDLNet_AllocSocketSet(1024);
        if(!_sockets)
        {
            printf("Error allocating network resources\n");
            exit(1);
        }
    }

    sk_network_connection sk_open_udp_connection(unsigned short port)
    {
        internal_sk_init();

        UDPsocket svr;

        sk_network_connection result;
        result.id = NETWORK_CONNECTION_PTR;
        result.kind = UNKNOWN;
        result._socket = nullptr;

        svr = SDLNet_UDP_Open(port);

        if (svr)
        {
            result.kind = UDP;
            result._socket = svr;
            SDLNet_UDP_AddSocket(_sockets, svr);
        }
        else
        {
            result.kind = UNKNOWN;
            result._socket = nullptr;
            LOG(ERROR) << "Failed to open UDP server on port " << port << ": " << SDLNet_GetError();
        }

        return result;
    }

    sk_network_connection sk_open_tcp_connection(const char *host, unsigned short port)
    {
        internal_sk_init();

        IPaddress addr;
        TCPsocket client;

        sk_network_connection result;
        result.id = NETWORK_CONNECTION_PTR;
        result.kind = UNKNOWN;
        result._socket = nullptr;

        if (SDLNet_ResolveHost(&addr, host, port) < 0)
            return result;

        client = SDLNet_TCP_Open(&addr);

        if (client)
        {
            result.kind = TCP;
            result._socket = client;
            if (host)
                SDLNet_TCP_AddSocket(_sockets, client);
        }
        else
        {
            result.kind = UNKNOWN;
            result._socket = nullptr;
            LOG(ERROR) << "SDLNet_TCP_Open: " << SDLNet_GetError();
        }

        return result;
    }

    int sk_send_bytes(sk_network_connection *con, char *buffer, unsigned long size)
    {
        // not entry point...
        //    printf("Sending %d\n", size);
        int sent = 0;
        if ((TCPsocket)con->_socket)
        {
            //printf("here -- %p\n", (TCPsocket)con->_socket);
            sent = SDLNet_TCP_Send((TCPsocket)con->_socket, buffer, static_cast<int>(size));
        }
        //    printf("Sent %d\n", sent);
        return sent;
    }

    int sk_send_udp_message(sk_network_connection *con, const char *host, unsigned short port, const char *buffer, unsigned long size)
    {
        // Not entry point.
        UDPpacket packet;
        SDLNet_ResolveHost(&packet.address, host, port);

        packet.len = static_cast<int>(size);
        packet.data = (Uint8*)buffer;
        return SDLNet_UDP_Send((UDPsocket)con->_socket, -1, &packet);
    }

    void sk_read_udp_message(sk_network_connection *con, unsigned int *host, unsigned short *port, char *buffer, unsigned long *size)
    {
        //    printf("Reading up to %d bytes\n", *size);

        UDPpacket *packet;
        packet = SDLNet_AllocPacket((int)*size);

        *size = 0;
        *host = 0;
        if ( SDLNet_UDP_Recv((UDPsocket)con->_socket, packet) > 0 )
        {
            //        printf("Read %d bytes\n", packet->len);

            *host = SDLNet_Read32(&packet->address.host);
            *port = SDLNet_Read16(&packet->address.port);

            if ( packet->len > 0 )
            {
                unsigned int buf_sz = sizeof(char) * (unsigned int)packet->len;
                memcpy(buffer, packet->data, buf_sz);
                *size = buf_sz;
            }
        }
        SDLNet_FreePacket(packet);
    }

    int sk_read_bytes(sk_network_connection *con, char *buffer, int size)
    {
        // not entry point
        return SDLNet_TCP_Recv((TCPsocket)con->_socket, buffer, size);
    }

    void sk_close_connection(sk_network_connection *con)
    {
        // not entry point
        if ( con->kind == TCP )
        {
            SDLNet_TCP_DelSocket(_sockets, (TCPsocket)con->_socket);
            SDLNet_TCP_Close((TCPsocket)con->_socket);
        }
        else
        {
            SDLNet_UDP_DelSocket(_sockets, (UDPsocket)con->_socket);
            SDLNet_UDP_Close((UDPsocket)con->_socket);
        }

        con->kind = UNKNOWN;
    }

    unsigned int sk_network_address(sk_network_connection *con)
    {
        IPaddress *remote;
        if (con->kind == TCP)
            remote = SDLNet_TCP_GetPeerAddress((TCPsocket)con->_socket);
        else
            remote = SDLNet_UDP_GetPeerAddress((UDPsocket)con->_socket, -1);
        return SDLNet_Read32(&remote->host);
    }

    unsigned int sk_get_network_port(sk_network_connection *con)
    {
        IPaddress *remote;
        if (con->kind == TCP)
            remote = SDLNet_TCP_GetPeerAddress((TCPsocket)con->_socket);
        else
            remote = SDLNet_UDP_GetPeerAddress((UDPsocket)con->_socket, -1);
        return SDLNet_Read16(&remote->port);
    }

    sk_network_connection sk_accept_connection(sk_network_connection &con)
    {
        sk_network_connection result;
        result._socket = NULL;
        result.kind = UNKNOWN;
        
        TCPsocket client;
        if ((client = SDLNet_TCP_Accept((TCPsocket)con._socket)) != NULL)
        {
            //        printf("Adding client %p\n", client);
            SDLNet_TCP_AddSocket(_sockets, client);
            result._socket = client;
            result.kind = TCP;
        }
        return result;
    }
    
    unsigned int sk_network_has_data()
    {
        internal_sk_init();
        if (SDLNet_CheckSockets(_sockets, 0) > 0) return 1;
        else return 0;
    }
    
    unsigned int sk_connection_has_data(sk_network_connection *con)
    {
        int got = SDLNet_SocketReady(con->_socket);
        
        //    printf("Checking %p %d\n", con->_socket, got);
        if (got > 0)
            return 1;
        else
            return 0;
    }
}
