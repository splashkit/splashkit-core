#include <sstream>
#include <cmath>
#include <iomanip>

#include "easylogging++.h"

#include "networking.h"
#include "network_driver.h"
#include "utility_functions.h"

using std::endl;
using std::stringstream;
using std::to_string;
using std::uppercase;
using std::hex;
using std::setw;
using std::setfill;

namespace splashkit_lib
{
    #define PACKET_SIZE 512
    static unsigned int UDP_PACKET_SIZE = 1024;


    typedef char packet_data[PACKET_SIZE];
    typedef unsigned char byte;

    static map<string, connection> _connections;
    static map<string, server_socket> _server_sockets;
    static vector<message> _messages;

    server_socket create_server(const string &name, unsigned short int port, connection_type protocol)
    {
        sk_network_connection con;
        if (protocol == TCP)
        {
            con = sk_open_tcp_connection(nullptr, port);
        }
        else if (protocol == UDP)
        {
            con = sk_open_udp_connection(port);
        }
        else
        {
            LOG(ERROR) << "Unknown protocol " << protocol << " passed to create_server";
        }

        if (con._socket && (con.kind == TCP || con.kind == UDP))
        {
            server_socket socket = new sk_server_data;
            socket->id = SERVER_SOCKET_PTR;
            socket->name = name;
            socket->socket = con;
            socket->port = port;
            socket->new_connections = 0;
            socket->protocol = protocol;

            _server_sockets.insert({name, socket});

            return socket;
        }

        LOG(ERROR) << "Failed to create server named " << name;
        return nullptr;
    }

    server_socket create_server(const string &name, unsigned short int port)
    {
        return create_server(name, port, TCP);
    }

    server_socket server_named(const string &name)
    {
        if (has_server(name))
        {
            return _server_sockets[name];
        }

        LOG(WARNING) << "No server named '" << name << "'.";
        return nullptr;
    }

    bool close_server(server_socket svr)
    {
        if (INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket passed to close_server";
            return false;
        }

        clear_messages(svr);

        for(auto connection : svr->connections)
        {
            close_connection(connection);
        }

        // close the socket
        sk_close_connection(&svr->socket);
        _server_sockets.erase(svr->name);

        svr->id = NONE_PTR;

        delete svr;

        return true;
    }

    bool close_server(const string &name)
    {
        return close_server(_server_sockets[name]);
    }

    void close_all_servers()
    {
        FREE_ALL_FROM_MAP( _server_sockets, SERVER_SOCKET_PTR, [] (server_socket svr) { close_server(svr); } );
    }

    bool has_server(const string &name)
    {
        return _server_sockets.count(name) > 0;
    }

    bool server_has_new_connection(const string &name)
    {
        return server_has_new_connection(server_named(name));
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
        for(auto const &pair : _server_sockets)
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
        //result->part_msg_data is empty
        result->expected_msg_len = -1;
        result->open = true;
        result->socket._socket = nullptr;
        result->socket.kind = UNKNOWN;

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
        }
        else if (protocol == UDP)
        {
            con->socket = sk_open_udp_connection(0);
        }
        else
        {
            LOG(ERROR) << "Invalid protocol passed to _establish_connection: " << protocol;
            return false;
        }

        if (!con->socket._socket)
        {
            return false;
        }

        con->ip = sk_network_address(&con->socket);

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
            _connections.insert({name, con});
            return con;
        }
        else
        {
            LOG(ERROR) << "Could not establish connection at open_connection after calling _establish_connection";
            delete con;
            return nullptr;
        }
    }

    void shut_connection(connection con)
    {
        if ( INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(WARNING) << "Attempting to shut invalid connection";
            return;
        }

        if (con->open)
        {
            con->open = false;
            sk_close_connection(&con->socket);
        }
    }

    bool has_connection(const string &name)
    {
        return _connections.count(name) > 0;
    }

    connection retrieve_connection(const string &name, int idx)
    {
        return retrieve_connection(server_named(name), idx);
    }

    connection retrieve_connection(server_socket server, int idx)
    {
        if ( INVALID_PTR(server, SERVER_SOCKET_PTR) )
        {
            LOG(WARNING) << "Attempting to get connection from invalid server";
            return nullptr;
        }

        return server->connections.size() > idx ? server->connections[idx] : nullptr;
    }

    void close_all_connections()
    {
        FREE_ALL_FROM_MAP(_connections, CONNECTION_PTR, [] (connection con) { close_connection(con); });
    }

    bool close_connection(connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(WARNING) << "Invalid pointer passed to close_connection";
            return false;
        }

        bool result = false;
        clear_messages(con);
        shut_connection(con);

        if (_connections.find(con->name) != _connections.end())
        {
            _connections.erase(con->name);
            con->id = NONE_PTR;
            delete con;
            result = true;
        }
        else
        {
            for (auto sock : _server_sockets)
            {
                server_socket s = sock.second;
                int idx = index_of(s->connections, con);

                if (idx > -1)
                {
                    if ( idx >= s->connections.size() - s->new_connections )
                    {
                        s->new_connections--;
                    }
                    
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
        return close_connection(connection_named(name));
    }

    unsigned int connection_count(const string &name)
    {
        return connection_count(server_named(name));
    }

    unsigned int connection_count(server_socket server)
    {
        if ( INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Attempting to count connections of invalid server socket";
            return 0;
        }

        return static_cast<unsigned int>(server->connections.size());
    }

    unsigned int connection_ip(const string &name)
    {
        return connection_ip(connection_named(name));
    }

    unsigned int connection_ip(connection a_connection)
    {
        if ( INVALID_PTR(a_connection, CONNECTION_PTR) )
        {
            LOG(WARNING) << "Attempting to get ip of invalid connection";
            return 0;
        }
        return a_connection->ip;
    }

    connection connection_named(const string &name)
    {
        if ( has_connection(name))
        {
            return _connections[name];
        }

        LOG(WARNING) << "No connection exists for name: " << name << endl;
        return nullptr;
    }

    bool is_connection_open(connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(WARNING) << "Invalid connection passed to is_connection_open";
            return false;
        }

        return con->open;
    }

    bool is_connection_open(const string &name)
    {
        return is_connection_open(connection_named(name));
    }
    
    int new_connection_count(server_socket server)
    {
        if (INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket for number of new connections";
            return 0;
        }
        
        return server->new_connections;
    }
    
    connection fetch_new_connection(server_socket server)
    {
        if (INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket for fetching new connection";
            return nullptr;
        }
        
        if ( server->new_connections == 0 || server->connections.size() == 0 ) return nullptr;
        
        connection result;
        if ( server->new_connections > server->connections.size() )
            result = server->connections[0];
        else
            result = *(server->connections.end() - server->new_connections);
        
        server->new_connections--;
        return result;
    }
    
    void reset_new_connection_count(server_socket server)
    {
        if (INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket for reset new connection count";
            return;
        }
        
        server->new_connections = 0;
    }

    bool accept_new_connection(server_socket server)
    {
        if (INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Invalid server_socket passed to accept_new_connection";
            return false;
        }

        sk_network_connection con = sk_accept_connection(server->socket);

        if (con._socket && (con.kind == TCP))
        {
            int ip = sk_network_address(&con);
            int port = sk_get_network_port(&con);

            connection client = _create_connection(server->name + "->" + name_for_connection(ipv4_to_str(ip), port), TCP);
            client->ip = ip;
            client->string_ip = ipv4_to_str(ip);
            client->port = port;
            client->socket = con;

            server->connections.push_back(client);
            server->new_connections++;

            return true;
        }

        return false;
    }


    bool accept_all_new_connections()
    {
        bool result = false;

        for (auto it : _server_sockets)
        {
            if (accept_new_connection(it.second))
            {
                result = true;
            }
        }

        return result;
    }

    unsigned short int connection_port(connection a_connection)
    {
        if ( INVALID_PTR(a_connection, CONNECTION_PTR))
        {
            LOG(WARNING) << "Attempting to get port of invalid connection";
            return 0;
        }
        return a_connection->port;
    }

    unsigned short int connection_port(const string &name)
    {
        return connection_port(connection_named(name));
    }

    connection last_connection(server_socket server)
    {
        if ( INVALID_PTR(server, SERVER_SOCKET_PTR))
        {
            LOG(WARNING) << "Attempting to get last connection from invalid server socket";
            return nullptr;
        }

        if (server->connections.empty())
        {
            return nullptr;
        }
        return server->connections[server->connections.size() - 1];
    }

    connection last_connection(const string &name)
    {
        return last_connection(server_named(name));
    }

    void reconnect(const string &name)
    {
        reconnect(connection_named(name));
    }

    void reconnect(connection con)
    {
        if ( INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(WARNING) << "Attempting to reconnect invalid connection";
            return;
        }

        string host = con->string_ip;
        unsigned short port = con->port;

        sk_close_connection(&con->socket);
        con->open = _establish_connection(con, host, port, con->protocol);
    }

    void release_all_connections()
    {
        close_all_connections();
        close_all_servers();
    }

    connection message_connection(message msg)
    {
        if ( INVALID_PTR(msg, MESSAGE_PTR))
        {
            LOG(WARNING) << "Attempting to get connection of invalid message";
            return nullptr;
        }

        return msg->connection;
    }

    unsigned int udp_packet_size()
    {
        return UDP_PACKET_SIZE;
    }

    void set_udp_packet_size(unsigned int udp_packet_size)
    {
        UDP_PACKET_SIZE = udp_packet_size;
    }

    void _enqueue_tcp_message(const vector<int8_t> &message, connection con)
    {
        sk_message* m = new sk_message;

        m->id = MESSAGE_PTR;
        m->data = message;
        m->protocol = TCP;
        m->connection = con;
        m->host = con->string_ip;
        m->port = con->port;

        con->messages.push_back(m);
        con->expected_msg_len = -1;
        con->part_msg_data.clear();
    }

    void _enqueue_udp_message(vector<sk_message*> &messages, const char* msg, unsigned long size, unsigned int host, int port)
    {
        message m = new sk_message;
        m->id = MESSAGE_PTR;
        for (int i = 0; i < size; ++i)
        {
            m->data.push_back(msg[i]);
        }
        m->protocol = UDP;
        m->connection = nullptr;
        m->host = ipv4_to_str(host);
        m->port = port;
        messages.push_back(m);
    }

    bool _read_udp_message_from(sk_network_connection con, vector<message>& messages)
    {
        if (sk_connection_has_data(&con) > 0)
        {
            char data[UDP_PACKET_SIZE];
            unsigned long size;
            unsigned int times, host;
            unsigned short port;
            times = size = host = port = 0;

            do
            {
                size = UDP_PACKET_SIZE;
                host = 0;
                port = 0;

                sk_read_udp_message(&con, &host, &port, data, &size);

                if ((size > 0) || (host > 0))
                {
                    _enqueue_udp_message(messages, data, size, host, port);
                }

                times += 1;
            }
            while (((size != 0) && (host != 0)) || (times < 10));

            return true;
        }

        return false;
    }

    bool _extract_data(packet_data buffer, int received_count, connection con)
    {
        int buf_idx = 0;
        unsigned long msg_len = 0;
        vector<int8_t> msg;
        int missing, got;
        byte size[4];

        while (buf_idx < received_count) // there is data to read...
        {
            // Work out the message length...
            if (con->expected_msg_len > 0)   // we are part way though a message...
            {
                msg = con->part_msg_data;                              // get the part
                msg_len = con->expected_msg_len - msg.size();      // How much left to read...
                con->expected_msg_len = -1;                          // Reset length of message to "no message"
                con->part_msg_data.clear();                            // Reset part of message
            }
            else // This is a new message... get its size.
            {
                msg.clear();

                if ((received_count - buf_idx) < 4) // if there are less than 4 bytes for the start of this message...
                {
                    // How much do we have?
                    missing = 4 - (received_count - buf_idx);

                    // Move back to give space for 4 values... we must know size!
                    for (int i = 0; i < 4 - missing; ++i) // move back the ones we have...
                    {
                        buffer[received_count - 4 + i] = buffer[buf_idx + i]; // copy back over
                    }

                    // read the missing bytes
                    got = sk_read_bytes(&con->socket, &buffer[received_count - missing], missing);

                    if (got != missing)
                    {
                        LOG(WARNING) << "Issue reading message size from network. Notify SplashKit team.";
                        return false;
                    }

                    buf_idx = received_count - 4;
                }

                size[0] = byte(buffer[buf_idx]);
                size[1] = byte(buffer[buf_idx + 1]);
                size[2] = byte(buffer[buf_idx + 2]);
                size[3] = byte(buffer[buf_idx + 3]);

                msg_len = (size[0] << 24) + (size[1] << 16) + (size[2] << 8) + (size[3]);

                buf_idx += 4;
            }

            unsigned long end_msg = buf_idx + msg_len;
            for (; buf_idx < end_msg; ++buf_idx)
            {
                if ((buf_idx >= received_count) || (buf_idx > PACKET_SIZE))
                {
                    con->part_msg_data = msg;
                    con->expected_msg_len = msg_len;
                    return true;
                }

                msg.push_back(buffer[buf_idx]);
            }

            _enqueue_tcp_message(msg, con);
        }

        return false;
    }

    bool _check_connection_for_data(connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR) || !con->socket._socket)
        {
            LOG(WARNING) << "Invalid connection or socket passed to _check_connection_for_data";
            return false;
        }

        if (sk_connection_has_data(&con->socket) > 0)
        {
            bool got_data = true; // are we expecting more data?
            int times = 0;
            do
            {
                if (con->protocol == TCP)
                {
                    packet_data buffer;
                    int received = sk_read_bytes(&con->socket, buffer, 512);

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
            } while (got_data and times < 10);

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

            for (auto it = _server_sockets.begin(); it != _server_sockets.end(); ++it)
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

            for (auto it = _connections.begin(); it != _connections.end(); ++it)
            {
                got_data = _check_connection_for_data(it->second) || got_data;
            }
        }
    }

    void broadcast_message(const string &a_msg)
    {
        for(auto const& tcp_server: _server_sockets)
        {
            broadcast_message(a_msg, tcp_server.second);
        }
        for (auto const& udp_connection: _connections)
        {
            send_message_to(a_msg, udp_connection.second);
        }
    }

    void broadcast_message(const string &a_msg, const string &name)
    {
        broadcast_message(a_msg, server_named(name));
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
        if ( INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            return;
        }

        svr->messages.clear();
    }

    void clear_messages(connection a_connection)
    {
        if ( INVALID_PTR(a_connection, CONNECTION_PTR))
        {
            return;
        }

        a_connection->messages.clear();
    }

    void clear_messages(const string &name)
    {
        if (has_server(name))
        {
            clear_messages(server_named(name));
        }
        else if (has_connection(name))
        {
            clear_messages(connection_named(name));
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
        for(auto &tcp_server: _server_sockets)
        {
            if (has_messages(tcp_server.second))
            {
                return true;
            }
        }
        for (auto &udp_connection: _connections)
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
        if (INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(ERROR) << "Invalid connection passed to has_messages";
            return false;
        }

        return !con->messages.empty();
    }

    bool has_messages(server_socket svr)
    {
        if (INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            LOG(ERROR) << "Invalid server_socket passed to has_messages";
            return false;
        }

        if ( !svr->messages.empty() )
        {
            return true;
        }

        for(connection con : svr->connections)
        {
            if (has_messages(con))
            {
                return true;
            }
        }

        return false;
    }

    bool has_messages(const string &name)
    {
        if (has_connection(name))
            return has_messages(connection_named(name));
        else if ( has_server(name))
            return has_messages(server_named(name));
        else
        {
            LOG(WARNING) << "Attempt to check messages for name that is neither a server nor a connection";
            return 0;
        }
    }

    unsigned int message_count(const string &name)
    {
        if ( has_connection(name) )
            return message_count(connection_named(name));
        else if ( has_server(name) )
            return message_count(server_named(name));
        else
        {
            LOG(WARNING) << "Attempt to get message count for name that is neither a server nor a connection";
            return 0;
        }
    }

    unsigned int message_count(connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(ERROR) << "Invalid connection passed to get message count";
            return -1;
        }

        return static_cast<unsigned int>(con->messages.size());
    }

    unsigned int message_count(server_socket svr)
    {
        if (INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            LOG(ERROR) << "Invalid message passed to get message host";
            return -1;
        }

        return static_cast<unsigned int>(svr->messages.size());
    }

    string message_data(message msg)
    {
        if (INVALID_PTR(msg, MESSAGE_PTR))
        {
            LOG(ERROR) << "Invalid message passed to get message data";
            return "";
        }

        string result = "";

        for(char ch : msg->data) result += ch;

        return result;
    }

    vector<int8_t> message_data_bytes(message msg)
    {
        if (INVALID_PTR(msg, MESSAGE_PTR))
        {
            LOG(ERROR) << "Invalid message passed to get message data";
            vector<int8_t> result;
            return result;
        }

        return msg->data;
    }

    string message_host(message msg)
    {
        if (INVALID_PTR(msg, MESSAGE_PTR))
        {
            LOG(ERROR) << "Invalid message passed to get message host";
            return "";
        }

        return msg->host;
    }

    unsigned short int message_port(message msg)
    {
        if (INVALID_PTR(msg, MESSAGE_PTR))
        {
            LOG(ERROR) << "Invalid message passed to get message port";
            return 0;
        }

        return msg->port;
    }

    connection_type message_protocol(message msg)
    {
        if (INVALID_PTR(msg, MESSAGE_PTR))
        {
            LOG(ERROR) << "Invalid message passed to get message protocol";
            return UNKNOWN;
        }

        return msg->protocol;
    }

    message _pop_message(vector<message> &messages)
    {
        message first = messages.front();
        messages.erase(messages.begin());
        return first;
    }

    message read_message(connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(ERROR) << "Invalid message passed to read message";
            return nullptr;
        }

        return _pop_message(con->messages);
    }

    message read_message(const string &name)
    {
        return read_message(connection_named(name));
    }

    message read_message(server_socket svr)
    {
        if (INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            LOG(ERROR) << "Invalid message passed to read_message";
            return nullptr;
        }

        for (int i = 0; i < connection_count(svr); ++i)
        {
            connection con = retrieve_connection(svr, i);
            if (has_messages(con))
            {
                return read_message(con);
            }
        }

        if (svr->messages.size() > 0)
        {
            return _pop_message(svr->messages);
        }

        return nullptr;
    }
    
    message read_message()
    {
        for(auto const& tcp_server: _server_sockets)
        {
            if ( has_messages(tcp_server.second) )
                return read_message(tcp_server.second);
        }
        for (auto const& con: _connections)
        {
            if ( con.second->messages.size() > 0 )
                return read_message(con.second);
        }
        
        return nullptr;
    }
    

    string read_message_data(connection con)
    {
        if (INVALID_PTR(con, CONNECTION_PTR))
        {
            LOG(ERROR) << "Invalid connection passed to read_message_data";
            return "";
        }

        message msg = read_message(con);
        string result = "";
        if (VALID_PTR(msg, MESSAGE_PTR))
        {
            result = message_data(msg);
            close_message(msg);
        }
        else
        {
            LOG(ERROR) << "Invalid message received in read_message_data";
        }

        return result;
    }

    string read_message_data(server_socket svr)
    {
        if (INVALID_PTR(svr, SERVER_SOCKET_PTR))
        {
            LOG(ERROR) << "Invalid connection passed to read_message_data";
            return "";
        }

        message msg = read_message(svr);
        string result = "";
        if (VALID_PTR(msg, MESSAGE_PTR))
        {
            result = message_data(msg);
            close_message(msg);
        }
        else
        {
            LOG(ERROR) << "Invalid message received in read_message_data";
        }

        return result;
    }

    string read_message_data(const string &name)
    {
        message msg = read_message(name);
        string result = "";
        if (VALID_PTR(msg, MESSAGE_PTR))
        {
            result = message_data(msg);
            close_message(msg);
        }
        else
        {
            LOG(ERROR) << "Invalid message received in read_message_data";
        }

        return result;
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
            unsigned long n = msg.length();
            byte size[4];
            size[0] = (n >> 24) & 0xFF;
            size[1] = (n >> 16) & 0xFF;
            size[2] = (n >> 8) & 0xFF;
            size[3] = n & 0xFF;

            unsigned long len = msg.size() + 4;
            char buffer[len];

            for (int i = 0; i < len; ++i)
            {
                if (i < 4)
                {
                    buffer[i] = size[i];
                }
                else
                {
                    buffer[i] = byte(msg[i - 4]);
                }
            }

            if (sk_send_bytes(&con->socket, buffer, len) == len)
            {
                return true;
            }
            else
            {
                LOG(DEBUG) << "Shutting the connection as no bytes sent";
                shut_connection(con);
            }
        }
        else // UDP
        {
            if (msg.size() < 1024)
            {
                sk_send_udp_message(&con->socket, con->string_ip.c_str(), con->port, msg.c_str(), msg.length());
                return true;
            }
            else
            {
                LOG(ERROR) << "Cannot send messages longer than 1024 bytes using UDP -- message ignored";
            }
        }

        return false;
    }

    bool send_message_to(const string &a_msg, const string &name)
    {
        return send_message_to(a_msg, connection_named(name));
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
