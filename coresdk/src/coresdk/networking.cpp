#include <sstream>
#include <cmath>
#include <iomanip>

#include "easylogging++.h"

#include "networking.h"
#include "network_driver.h"
#include "utility_functions.h"

namespace splashkit_lib
{
    static map<string, connection> connections;
    static map<string, server_socket> server_sockets;
    static vector<message> messages;
    static int UDP_PACKET_SIZE = 1024;

    server_socket create_server(const string &name, unsigned short int port, connection_type protocol)
    {
        sk_network_connection *con = nullptr;
        if (protocol == TCP)
        {
            sk_open_tcp_connection(nullptr, port);
        }
        else if (protocol == UDP)
        {
            sk_open_udp_connection(port);
        }
        else
        {
            LOG(ERROR) << "Unknown protocol " << protocol << " passed to create_server";
        }

        server_socket socket = new sk_server_data;
        if (con->_socket && (con->kind == TCP || con->kind == UDP))
        {
            socket->id = SERVER_SOCKET_PTR;
            socket->name = name;
            socket->socket = con;
            socket->port = port;
            socket->new_connections = 0;
            socket->protocol = protocol;

            server_sockets.insert({name, socket});
        }

        return socket;
    }

    server_socket create_server(const string &name, unsigned short int port)
    {
        return create_server(name, port, TCP);
    }

    server_socket server_named(const string &name)
    {
        if (server_sockets.find(name) != server_sockets.end())
        {
            return server_sockets[name];
        }

        LOG(WARNING) << "server_named found no server named '" << name << "'.";

        return nullptr;
    }

    bool close_server(server_socket svr)
    {
        if (INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket passed to close_server";
            return false;
        }

        for(auto connection : svr->connections)
        {
            close_connection(connection);
        }

        // close the socket
        sk_close_connection(svr->socket);
        server_sockets.erase(svr->name);

        delete svr;

        return true;
    }

    bool close_server(const string &name)
    {
        return close_server(server_sockets[name]);
    }

    void close_all_servers()
    {
        for(auto const &pair : server_sockets)
        {
            close_server(pair.second);
        }
    }

    bool server_has_new_connection(const string &name)
    {
        return server_has_new_connection(server_sockets[name]);
    }

    bool server_has_new_connection(server_socket server)
    {
        if (INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Passed invalid pointer to server_has_new_connection";
            return false;
        }

        return server->new_connections > 0;
    }

    bool has_new_connections()
    {
        for(auto const &pair : server_sockets)
        {
            if (server_has_new_connection(pair.second))
            {
                return true;
            }
        }
        return false;
    }

    connection _create_connection(const string& name, connection_type protocol)
    {
        connection result = new sk_connection_data;
        result->id = CONNECTION_PTR;
        result->name = name;
        result->ip = 0;
        result->string_ip = "";
        result->port = 0;
        result->protocol = protocol;
        result->part_msg_data = "";
        result->open = true;
        result->socket->_socket = nullptr;
        result->socket->kind = UNKNOWN;
        return result;
    }

    bool _establish_connection(connection con, const string& host, unsigned short int port, connection_type protocol)
    {
        con->string_ip = host;
        con->port = port;
        con->protocol = protocol;

        if (protocol == TCP)
        {
            con->socket = sk_open_tcp_connection(host.c_str(), port);

            if (!con->socket->_socket)
            {
                return false;
            }

            con->ip = sk_network_address(con->socket);
        }
        else if (protocol == UDP)
        {
            con->socket = sk_open_udp_connection(port);
            con->ip = sk_network_address(con->socket);
        }
        else
        {
            LOG(ERROR) << "Invalid protocol passed to _establish_connection: " << protocol;
            return false;
        }

        return true;
    }

    connection open_connection(const string &host, unsigned short int port)
    {
        return open_connection(name_for_connection(host, port), host, port, TCP);
    }

    connection open_connection(const string &name, const string &host, unsigned short int port)
    {
        return open_connection(name, host, port, TCP);
    }

    connection open_connection(const string &name, const string &host, unsigned short int port, connection_type protocol)
    {
        connection con = _create_connection(name, protocol);

        if (_establish_connection(con, host, port, protocol))
        {
            connections.insert({name_for_connection(host, port), con});
            return con;
        }
        else
        {
            delete con;
            return nullptr;
        }
    }

    void shut_connection(connection con)
    {
        if (con->open)
        {
            con->open = false;
            sk_close_connection(con->socket);
        }
    }

    connection retrieve_connection(const string &name, int idx)
    {
        return retrieve_connection(server_sockets[name], idx);
    }

    connection retrieve_connection(server_socket server, int idx)
    {
        return server->connections.size() > idx ? server->connections[idx] : nullptr;
    }

    void close_all_connections()
    {
        for(auto const &pair : connections)
        {
            close_connection(pair.second);
        }
    }

    bool close_connection(connection con) {
        if (INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(WARNING) << "Invalid pointer passed to close_connection";
            return false;
        }

        bool result = false;
        clear_messages(con);
        shut_connection(con);

        if (connections.find(con->name) != connections.end())
        {
            connections.erase(con->name);
            con->id = NONE_PTR;
            delete con;
            result = true;
        }
        else
        {
            for (auto sock : server_sockets)
            {
                server_socket s = sock.second;
                int idx = index_of(s->connections, con);

                if (idx > -1)
                {
                    result = true;
                    con->id = NONE_PTR;
                    delete con;
                    s->connections.erase(s->connections.begin() + idx);
                }
            }
        }


        return result;
    }

    bool close_connection(const string &name)
    {
        return close_connection(connections[name]);
    }

    int connection_count(const string &name)
    {
        return connection_count(server_sockets[name]);
    }

    int connection_count(server_socket server) {
        return server->connections.size();
    }

    unsigned int connection_ip(const string &name)
    {
        return connection_ip(connections[name]);
    }

    unsigned int connection_ip(connection a_connection) {
        return a_connection->ip;
    }

    connection connection_named(const string &name) {
        return connection();
    }

    bool is_connection_open(connection con) {
        return con->open;
    }

    bool is_connection_open(const string &name) {
        return is_connection_open(connections[name]);
    }

    bool accept_new_connection(server_socket server)
    {
        if (INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket passed to accept_new_connection";
            return false;
        }
        
        server->new_connections = 0;

        network_connection con = sk_accept_connection(server->socket);

        if (con->_socket && (con->kind == TCP))
        {
            int ip = sk_network_address(con);
            int port = sk_get_network_port(con);

            connection client = _create_connection(server->name + "->" + name_for_connection(ipv4_to_str(ip), port), TCP);
            client->ip = ip;
            client->port = port;
            client->socket = con;

            server->connections.push_back(client);
            server->new_connections = 1;

            return true;
        }

        return false;
    }


    bool accept_all_new_connections()
    {
        bool result = false;

        for (auto it = server_sockets.begin(); it != server_sockets.end(); ++it)
        {
            if (accept_new_connection(it->second))
            {
                result = true;
            }
        }

        return result;
    }

    unsigned short int connection_port(connection a_connection) {
        return a_connection->port;
    }

    unsigned short int connection_port(const string &name)
    {
        return connection_port(connections[name]);
    }

    connection last_connection(server_socket server) {
        if (server->connections.empty())
        {
            return nullptr;
        }
        return server->connections[server->connections.size() - 1];
    }

    connection last_connection(const string &name) {
        return last_connection(server_sockets[name]);
    }

    void reconnect(const string &name)
    {
        reconnect(connections[name]);
    }

    void reconnect(connection con)
    {
        string host = con->string_ip;
        unsigned short port = con->port;

        sk_close_connection(con->socket);
        con->open = _establish_connection(con, host, port, con->protocol);
    }

    void release_all_connections()
    {
        close_all_connections();
        close_all_servers();
    }

    connection message_connection(message msg)
    {
        return msg->connection;
    }

    int udp_packet_size()
    {
        return UDP_PACKET_SIZE;
    }

    void set_udp_packet_size(int udp_packet_size)
    {
        UDP_PACKET_SIZE = udp_packet_size;
    }

    void _enqueue_tcp_message(const string &message, connection con)
    {
        sk_message* m = new sk_message;
        m->id = MESSAGE_PTR;
        m->data = message;
        m->protocol = TCP;
        m->connection = con;
        m->host = con->string_ip;
        m->port = con->port;
        con->messages.push_back(m);
    }

    void _enqueue_udp_message(vector<sk_message*> &messages, const char* msg, int size, unsigned int host, int port)
    {
        message m = new sk_message;
        m->id = MESSAGE_PTR;
        LOG(WARNING) << "potential error in _enqueue_udp_message: validate results and remove this warning if correct";
        //m->data = '';
        for (int i = 0; i < size - 1; ++i)
        {
            m->data[i] += msg[i];
        }
        m->protocol = UDP;
        m->connection = nullptr;
        m->host = ipv4_to_str(host);
        m->port = port;
        messages.push_back(m);
    }

    bool _read_udp_message_from(network_connection con, vector<message>& messages)
    {
        if (INVALID_PTR(con, NETWORK_CONNECTION_PTR))
        {
            LOG(WARNING) << "Invalid network_connection passed to _read_udp_message_from";
        }

        if (sk_connection_has_data(con) > 0)
        {
            char data[UDP_PACKET_SIZE];
            unsigned int times, size, host;
            unsigned short port;
            times = size = host = port = 0;

            do
            {
                size = UDP_PACKET_SIZE;
                host = 0;
                port = 0;

                sk_read_udp_message(con, &host, &port, data, &size);

                if ((size > 0) || (host > 0))
                {
                    _enqueue_udp_message(messages, data, size, host, port);
                }

                times += 1;
            }
            while ((size != 0) && (host != 0) || (times < 10));

            return true;
        }

        return false;
    }

    bool _extract_data(packet_data buffer, int received_count, connection con)
    {
        int buf_idx = 0;
        int msg_len = 0;
        string msg;
        int missing, got;
        bytes size;

        while (buf_idx < received_count)
        {
            if (con->msgLen > 0)
            {
                msg = con->part_msg_data;
                msg_len = con->msgLen - msg.length();
                con->msgLen = -1;
                con->part_msg_data = "";
            }
            else
            {
                msg = "";

                if ((PACKET_SIZE - buf_idx) < 4)
                {
                    missing = 4 - PACKET_SIZE - buf_idx;

                    for (int i = 0; i <= missing; ++i)
                    {
                        buffer[PACKET_SIZE - 4 + i] = buffer[buf_idx + i];

                        got = sk_read_bytes(con->socket, &buffer[PACKET_SIZE - missing], missing);

                        if (got != missing)
                        {
                            LOG(WARNING) << "Issue reading message size from network. Notify SplashKit team.";
                            return false;
                        }

                        buf_idx = PACKET_SIZE - 4;
                    }

                    size[0] = byte(buffer[buf_idx]);
                    size[1] = byte(buffer[buf_idx + 1]);
                    size[2] = byte(buffer[buf_idx + 2]);
                    size[3] = byte(buffer[buf_idx + 3]);

                    msg_len = (size[0] << 24 & 0xFF) + (size[1] << 16 & 0xFF) + (size[2] << 8 & 0xFF) + (size[3]);

                    buf_idx += 4;
                }

                for (buf_idx; buf_idx <= buf_idx + msg_len - 1; ++buf_idx)
                {
                    if ((buf_idx >= received_count) || (buf_idx > PACKET_SIZE))
                    {
                        con->part_msg_data = msg;
                        con->msgLen = msg_len;
                        return true;
                    }

                    msg += buffer[buf_idx];
                }

                _enqueue_tcp_message(msg, con);

                buf_idx += 1;
            }
        }

        return false;
    }

    bool _check_connection_for_data(connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR) || !con->socket->_socket)
        {
            LOG(WARNING) << "Invalid connection or socket passed to _check_connection_for_data";
            return false;
        }

        if (sk_connection_has_data(con->socket) > 0)
        {
            bool got_data = true;
            int times = 0;
            do
            {
                if (con->protocol == TCP)
                {
                    packet_data buffer;
                    int received = sk_read_bytes(con->socket, buffer, 512);

                    if (received <= 0) {
                        // shut_connection
                        LOG(DEBUG) << "No data received in _c_c_for_data";
                        return false;
                    }

                    got_data = _extract_data(buffer, received, con);
                }
                else
                {
                    got_data = _read_udp_message_from(con->socket, con->messages);
                }

                times += 1;
            } while (got_data or times < 10);

            return true;
        }

        return false;
    }

    bool _check_udp_socket_for_data(server_socket socket)
    {
        if (VALID_PTR(socket, SERVER_SOCKET_PTR))
        {
            return _read_udp_message_from(socket->socket, socket->messages);
        }

        return false;
    }

    void check_network_activity()
    {
        accept_all_new_connections();
        bool got_data = true;

        while ((sk_network_has_data() > 0) && got_data)
        {
            got_data = false;

            for (auto it = server_sockets.begin(); it != server_sockets.end(); ++it)
            {
                server_socket s = it->second;
                if (s->protocol == TCP)
                {
                    for (int i = 0; i < s->connections.size(); ++i)
                    {
                        got_data = _check_connection_for_data(s->connections[i]) || got_data;
                    }
                }
                else
                {
                    got_data = _check_udp_socket_for_data(s) || got_data;
                }
            }

            for (auto it = connections.begin(); it != connections.end(); ++it)
            {
                got_data = _check_connection_for_data(it->second) || got_data;
            }
        }
    }

    void broadcast_message(const string &a_msg)
    {
        for(auto const& tcp_server: server_sockets)
        {
            broadcast_message(a_msg, tcp_server.second);
        }
        for (auto const& udp_connection: connections)
        {
            send_message_to(a_msg, udp_connection.second);
        }
    }

    void broadcast_message(const string &a_msg, const string &name)
    {
        broadcast_message(a_msg, server_sockets[name]);
    }

    void broadcast_message(const string &a_msg, server_socket svr)
    {
        if (INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket passed to broadcast message.";
            return;
        }

        for (auto const& tcp_connection: svr->connections)
        {
            send_message_to(a_msg, tcp_connection);
        }
    }

    void clear_messages(server_socket svr)
    {
        // TODO delete all messages
    }

    void clear_messages(connection a_connection)
    {
        // TODO delete all messages
    }

    void clear_messages(const string &name)
    {
        if (server_sockets.count(name))
        {
            clear_messages(server_sockets[name]);
        }
        else if (connections.count(name))
        {
            clear_messages(connections[name]);
        }
    }

    void close_message(message msg)
    {
        if (INVALID_PTR(msg, MESSAGE_PTR))
        {
            LOG(WARNING) << "Invalid message passed to close_message";
            return;
        }

        msg->id = NONE_PTR;
        delete msg;
    }

    bool has_messages()
    {
        for(auto &tcp_server: server_sockets)
        {
            if (has_messages(tcp_server.second))
            {
                return true;
            }
        }
        for (auto &udp_connection: connections)
        {
            if (has_messages(udp_connection.second))
            {
                return true;
            }
        }

        return false;
    }

    bool has_messages(connection con)
    {
        return con->messages.empty();
    }

    bool has_messages(server_socket svr)
    {
        return svr->messages.empty();
    }

    bool has_messages(const string &name)
    {
        return connections.count(name) ? connections[name]->messages.empty()
                                       : server_sockets[name]->messages.empty();
    }

    int message_count(connection a_connection)
    {
        return a_connection->messages.size();
    }

    int message_count(const string &name)
    {
        return connections.count(name) ? connections[name]->messages.size()
                                       : server_sockets[name]->messages.size();
    }

    int message_count(server_socket svr)
    {
        return svr->messages.size();
    }

    string message_data(sk_message msg)
    {
        return msg.data;
    }

    string message_host(sk_message msg)
    {
        return msg.host;
    }

    unsigned short int message_port(sk_message msg)
    {
        return msg.port;
    }

    connection_type message_protocol(sk_message msg)
    {
        return msg.protocol;
    }

    message read_message(connection a_connection)
    {
        return new sk_message;
    }

    message read_message(const string &name)
    {
        return new sk_message;
    }

    message read_message(server_socket svr)
    {
        return new sk_message();
    }

    string read_message_data(connection a_connection)
    {
        return std::__cxx11::string();
    }

    string read_message_data(server_socket svr)
    {
        return std::__cxx11::string();
    }

    string read_message_data(const string &name)
    {
        return std::__cxx11::string();
    }

    bool send_message_to(const string &msg, connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR) || !con->open)
        {
            LOG(WARNING) << "Invalid connection or closed connection passed to send_message_to";
            return false;
        }

        if (con->protocol == TCP)
        {
            LOG(WARNING) << "Bytes endianness might be wrong - use char array?";
            unsigned long n = msg.length();
            bytes size;
            size[0] = (n >> 24) & 0xFF;
            size[1] = (n >> 16) & 0xFF;
            size[2] = (n >> 8) & 0xFF;
            size[3] = n & 0xFF;

            int len = msg.size() + 4;
            char buffer[len];

            for (int i = 0; i < len - 1; ++i)
            {
                if (i < 4)
                {
                    buffer[i] = size[i];
                }
                else
                {
                    buffer[i] = byte(msg[i - 3]);
                }
            }

            if (sk_send_bytes(con->socket, buffer, len) == len)
            {
                return true;
            }
            else
            {
                shut_connection(con);
            }
        }
        else // UDP
        {
            if (msg.size() < 1024)
            {
                sk_send_udp_message(con->socket, con->string_ip.c_str(), con->port, msg.c_str(), msg.length());
                return true;
            }
        }

        return false;
    }

    bool send_message_to(const string &a_msg, const string &name)
    {
        if (connections.find(name) != connections.end())
        {
            return send_message_to(a_msg, connections[name]);
        }

        return false;
    }

    string name_for_connection(const string host, const unsigned int port)
    {
        stringstream str;
        str << host << ":" << port;
        return str.str();
    }

    string hex_str_to_ipv4(const string &a_hex)
    {
        stringstream ipv4_string;
        ipv4_string << hex_to_dec_string(a_hex.substr(2,2));
        ipv4_string << "." << hex_to_dec_string(a_hex.substr(4,2));
        ipv4_string << "."<< hex_to_dec_string(a_hex.substr(6,2));
        ipv4_string << "." << hex_to_dec_string(a_hex.substr(8,2));
        return ipv4_string.str();
    }

    string hex_to_dec_string(const string &a_hex)
    {
        int dec = 0;
        for (int i = 0; i < a_hex.length(); i++)
        {
            int c_val = 0;
            if (a_hex[i] - '0' < 10)
            {
                c_val = a_hex[i] - '0';
            }
            else if (a_hex[i] - 'A' < 6)
            {
                c_val = (a_hex[i] - 'A') + 10;
            }
            dec += c_val * pow(16, (a_hex.length() - i - 1));
        }
        return to_string(dec);
    }

    string dec_to_hex(unsigned int a_dec)
    {
        uint32_t dec = (uint32_t) a_dec;
        stringstream hex_string;
        hex_string << "0x" << uppercase << hex << dec;
        return hex_string.str();
    }

    unsigned int ipv4_to_dec(const string &a_ip)
    {
        string::size_type lastpos = 0;
        unsigned int result = 0;
        for(unsigned int i = 0; i < 4; i++)
        {
            string::size_type pos = a_ip.find('.', lastpos);
            string token = pos == -1 ? a_ip.substr(lastpos) : a_ip.substr(lastpos, pos - lastpos);

            result += (token == "" || (lastpos == 0 && i > 0) ? 0 : stoi(token) << (3 - i) * 8);
            lastpos = pos + 1;
        }

        return result;
    }

    string ipv4_to_hex(const string& a_ip)
    {
        string::size_type lastpos = 0;
        stringstream hex_string;
        hex_string << "0x";
        for(unsigned int i = 0; i < 4; i++)
        {
            string::size_type pos = a_ip.find('.', lastpos);
            string token = pos == -1 ? a_ip.substr(lastpos) : a_ip.substr(lastpos, pos - lastpos);

            hex_string << setw(2) << setfill('0') << uppercase << hex
            << (token == "" || (lastpos == 0 && i > 0) ? 0 : stoi(token));

            lastpos = pos + 1;
        }

        return hex_string.str();
    }

    string ipv4_to_str(unsigned int ip)
    {
        uint32_t ipaddr = (uint32_t) ip;
        stringstream ip_string;
        ip_string << ((ipaddr >> 24) & 0xFF) << ".";
        ip_string << ((ipaddr >> 16) & 0xFF) << ".";
        ip_string << ((ipaddr >> 8) & 0xFF) << ".";
        ip_string << (ipaddr & 0xFF);
        return ip_string.str();
    }
    
    string my_ip()
    {
        // TODO implement ip address resolution. Should return ip address of connected network if one exists.
        return "127.0.0.1";
    }
}