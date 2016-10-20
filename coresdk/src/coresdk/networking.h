/**
 * @header  networking
 * @author  James Armstrong
 * @brief   SplashKit's network-related functions allow you to communicate data
 *          across networks.
 *
 * @attribute group networking
 * @attribute static networking
 */

#ifndef SPLASHKIT_NETWORKING_H
#define SPLASHKIT_NETWORKING_H

#include <string>
#include <vector>
#include <map>

#include "types.h"

using namespace std;
namespace splashkit_lib
{
    /**
     * The kind of protocol used for a server of connection.
     *
     * @constant TCP  Uses the TCP protocol. SplashKit can send messages of any
     *                size, and repackage it from you at the other end. Messages
     *                are reliably transferred.
     * @constant UDP  Uses the UDP protocol. SplashKit will send messages of up
     *                to 1024 bytes (by default). You need to handle packaging
     *                anything larger than this.
     * @constant UNKNOWN The protocol is unknown, usually due to the connection
     *                    or server being invalid or closed.
     */
    enum connection_type
    {
        TCP,
        UDP,
        UNKNOWN
    };

    /**
     * A message contains data that has been transferred between a client
     * connection and a server (or visa versa).
     *
     * @attribute class message
     */
    typedef struct sk_message *message;

    /**
     * A connection represents the communication channel from a client going to
     * a server. This can be used for the client and the server to send and
     * receive messages.
     *
     * @attribute class connection
     */
    typedef struct sk_connection_data *connection;

    /**
     * A server represents a network resource that clients can connect to. The
     * server will receive messages from all of the client connections, and can
     * be used to access the clients connected to the server.
     *
     * @attribute class server_socket
     */
    typedef struct sk_server_data *server_socket;

    // Server functions
    server_socket create_server(const string &name, unsigned short int port, connection_type protocol);
    server_socket create_server(const string &name, unsigned short int port);
    server_socket server_named(const string &name);
    bool close_server(server_socket svr);
    bool close_server(const string &name);
    void close_all_servers();
    bool server_has_new_connection(const string &name);
    bool server_has_new_connection(server_socket server);
    bool has_new_connections();

    unsigned int connection_count(const string &name);
    unsigned int connection_count(server_socket server);

    bool has_server(const string &name);

    bool accept_all_new_connections();
    bool accept_new_connection(server_socket server);
    bool server_has_connection(server_socket server, const string &name);

    connection last_connection(server_socket server);
    connection last_connection(const string &name);

    // Connection functions
    connection open_connection(const string &name, const string &host, unsigned short int port, connection_type protocol);
    connection open_connection(const string &name, const string &host, unsigned short int port);
    connection open_connection(const string &host, unsigned short int port);
    connection retrieve_connection(const string &name, int idx);
    connection retrieve_connection(server_socket server, int idx);
    void close_all_connections();
    bool close_connection(connection a_connection);
    bool close_connection(const string &name);

    connection connection_named(const string &name);
    bool has_connection(const string &name);

    unsigned int connection_ip(const string &name);
    unsigned int connection_ip(connection a_connection);

    bool is_connection_open(connection con);
    bool is_connection_open(const string &name);

    unsigned short int connection_port(connection a_connection);
    unsigned short int connection_port(const string &name);

    connection message_connection(message msg);
    void reconnect(const string &name);
    void reconnect(connection a_connection);
    void release_all_connections();

    // Message functions
    unsigned int udp_packet_size();
    void set_udp_packet_size(unsigned int udp_packet_size);
    void broadcast_message(const string &a_msg);
    void broadcast_message(const string &a_msg, const string &name);
    void broadcast_message(const string &a_msg, server_socket svr);
    void check_network_activity();
    void clear_messages(server_socket svr);
    void clear_messages(connection a_connection);
    void clear_messages(const string &name);
    void close_message(message msg);
    bool has_messages();
    bool has_messages(connection con);
    bool has_messages(server_socket svr);
    bool has_messages(const string &name);
    unsigned int message_count(connection a_connection);
    unsigned int message_count(const string &name);
    unsigned int message_count(server_socket svr);
    string message_data(message msg);
    vector<int8_t> message_data_bytes(message msg);
    string message_host(message msg);
    unsigned short int message_port(message msg);
    connection_type message_protocol(message msg);
    message read_message(connection a_connection);
    message read_message(const string &name);
    message read_message(server_socket svr);
    string read_message_data(connection a_connection);
    string read_message_data(server_socket svr);
    string read_message_data(const string &name);
    bool send_message_to(const string &a_msg, connection a_connection);
    bool send_message_to(const string &a_msg, const string &name);
    connection message_connection(message msg);

    // Utility functions
    string name_for_connection(const string host, const unsigned int port);

    /**
     * @brief Converts a hexadecimal ipv4 string to standard ipv4 address string x.x.x.x
     *
     * The supplied hexadecimal string is translated into ipv4 standard address string.
     * Function handles hex strings starting with or without 0x.
     * e.g. 127.0.0.1 from 0x7F000001
     *
     * @param a_hex hexadecimal ipv4 string to convert
     *
     * @returns standard ipv4 address using format X.X.X.X
     */
    string hex_str_to_ipv4(const string &a_hex);

    /**
     * @brief Converts a hexadecimal string to a decimal string
     *
     * The supplied hexadecimal string is converted into it's decimal representation
     * e.g. 7F into 127
     *
     * @param a_hex hexadecimal string to convert
     *
     * @returns decimal representation of supplied hex string
     */
    string hex_to_dec_string(const string &a_hex);

    /**
     * @brief Converts a decimal integer into a hexadecimal string
     *
     * Converts the supplied decimal integer into it's hexadecimal representation.
     * e.g. 0x7F000001 from 2130706433
     *
     * @param a_dec decimal to be converted to a hexadecimal number string
     *
     * @return hexadecimal representation of the supplied decimal integer
     */
    string dec_to_hex(unsigned int a_dec);

    /**
     * @brief Converts an ipv4 address string to hex representation
     *
     * Converts an ipv4 address into it's hexadecimal representation
     * e.g. 0x7F000001 from 127.0.0.1
     *
     * @param a_ip ip address to convert
     *
     * @return hexadecimal representation of ipc4 string
     */
    string ipv4_to_hex(const string& a_ip);

    /**
     * @brief Encodes ipv4 string into single integer
     *
     * Encodes the supplied ipv4 address string (in format X.X.X.X) into a single integer
     * e.g. 127.0.0.1 into 2130706433
     *
     * @param a_ip ipv4 address to encode
     *
     * @returns encoded ipv4 string
     */
    unsigned int ipv4_to_dec(const string &a_ip);

    /**
     * @brief Decodes an integer into it's ipv4 address representation
     *
     * Decodes the supplied unsigned 32 bit integer into it's ipv4 address form
     * e.g. 2130706433 into 127.0.0.1
     *
     * @param ip integer to be decoded
     *
     * @returns ipv4 address string in X.X.X.X format
     */
    string ipv4_to_str(unsigned int ip);

    /**
     * @brief Returns the ipv4 string for the current computer's ip
     *
     * Returns the ipv4 string of the localhost loopback for the current computer.
     *
     * @return ipv4 address string in X.X.X.X format
     */
    string my_ip();
}
#endif //SPLASHKIT_NETWORKING_H
