#ifndef SPLASHKIT_NETWORKING_H
#define SPLASHKIT_NETWORKING_H

#include <string>
#include <vector>
#include <map>
#include "types.h"
#include "backend_types.h

using namespace std;
namespace splashkit_lib
{
    typedef char packet_data[512];
    typedef byte bytes[4];
    static int UDP_PACKET_SIZE = 1024;

    static map<string, sk_connection> connections;
    static map<string, sk_server_socket> server_sockets;
    //static vector<sk_message> messages;

    // Server functions
    sk_server_socket& create_server(const string &name, unsigned short int port);
    sk_server_socket& create_server(const string &name, unsigned short int port, sk_connection_type protocol);
    sk_server_socket server_named(const string &name);
    bool close_server(sk_server_socket &svr);
    bool close_server(const string &name);
    void close_all_servers();
    bool server_has_new_connection(const string &name);
    bool server_has_new_connection(sk_server_socket& server);
    bool has_new_connections();

    // Connection functions
    sk_connection open_connection(const string &host, unsigned short int port);
    sk_connection open_connection(const string &name, const string &host, unsigned short int port);
    sk_connection open_connection(const string &name, const string &host, unsigned short int port, sk_connection_type protocol);
    sk_connection retrieve_connection(const string &name, int idx);
    sk_connection retrieve_connection(sk_server_socket server, int idx);
    void close_all_connections();
    bool close_connection(sk_connection &a_connection);
    bool close_connection(const string &name);
    int connection_count(const string &name);
    int connection_count(sk_server_socket server);
    unsigned int connection_ip(const string &name);
    unsigned int connection_ip(sk_connection a_connection);
    sk_connection connection_named(const string &name);
    bool is_connection_open(sk_connection con);
    bool is_connection_open(const string &name);
    unsigned short int connection_port(sk_connection a_connection);
    unsigned short int connection_port(const string &name);
    sk_connection last_connection(sk_server_socket server);
    sk_connection last_connection(const string &name);
    sk_connection message_connection(sk_message msg);
    void reconnect(const string &name);
    void reconnect(sk_connection a_connection);

    // Message functions
    void broadcast_message(const string &a_msg);
    void broadcast_message(const string &a_msg, const string &name);
    void broadcast_message(const string &a_msg, sk_server_socket svr);
    void check_network_activity();
    void clear_messages(sk_server_socket svr);
    void clear_messages(sk_connection a_connection);
    void clear_messages(const string &name);
    void free_message(sk_message msg);
    bool has_messages();
    bool has_messages(sk_connection con);
    bool has_messages(sk_server_socket svr);
    bool has_messages(const string &name);
    int message_count(sk_connection a_connection);
    int message_count(const string &name);
    int message_count(sk_server_socket svr);
    string message_data(sk_message msg);
    string message_host(sk_message msg);
    unsigned short int message_port(sk_message msg);
    sk_connection_type message_protocol(sk_message msg);
    sk_message read_message(sk_connection a_connection);
    sk_message read_message(const string &name);
    sk_message read_message(sk_server_socket svr);
    string read_message_data(sk_connection a_connection);
    string read_message_data(sk_server_socket svr);
    string read_message_data(const string &name);
    bool send_message_to(const string &a_msg, sk_connection a_connection);
    bool send_message_to(const string &a_msg, const string &name);
    sk_connection message_connection(sk_message msg);

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
