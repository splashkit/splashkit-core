//
// SplashKit Generated Networking C++ Code
// DO NOT MODIFY
//

#ifndef __networking_h
#define __networking_h

#include "networking.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _connection_data;
typedef struct _connection_data *connection;
struct _message_data;
typedef struct _message_data *message;
struct _server_socket_data;
typedef struct _server_socket_data *server_socket;
typedef enum {
    TCP,
    UDP,
    UNKNOWN
} connection_type;
bool accept_all_new_connections();
bool accept_new_connection(server_socket server);
void broadcast_message(const string &a_msg, server_socket svr);
void broadcast_message(const string &a_msg);
void broadcast_message(const string &a_msg, const string &name);
void check_network_activity();
void clear_messages(const string &name);
void clear_messages(connection a_connection);
void clear_messages(server_socket svr);
void close_all_connections();
void close_all_servers();
bool close_connection(connection a_connection);
bool close_connection(const string &name);
void close_message(message msg);
bool close_server(const string &name);
bool close_server(server_socket svr);
unsigned int connection_count(const string &name);
unsigned int connection_count(server_socket server);
unsigned int connection_ip(connection a_connection);
unsigned int connection_ip(const string &name);
connection connection_named(const string &name);
unsigned short connection_port(connection a_connection);
unsigned short connection_port(const string &name);
server_socket create_server(const string &name, unsigned short port);
server_socket create_server(const string &name, unsigned short port, connection_type protocol);
string dec_to_hex(unsigned int a_dec);
connection fetch_new_connection(server_socket server);
bool has_connection(const string &name);
bool has_messages();
bool has_messages(connection con);
bool has_messages(const string &name);
bool has_messages(server_socket svr);
bool has_new_connections();
bool has_server(const string &name);
string hex_str_to_ipv4(const string &a_hex);
string hex_to_dec_string(const string &a_hex);
unsigned int ipv4_to_dec(const string &a_ip);
string ipv4_to_hex(const string &a_ip);
string ipv4_to_str(unsigned int ip);
bool is_connection_open(connection con);
bool is_connection_open(const string &name);
connection last_connection(const string &name);
connection last_connection(server_socket server);
connection message_connection(message msg);
unsigned int message_count(server_socket svr);
unsigned int message_count(connection a_connection);
unsigned int message_count(const string &name);
string message_data(message msg);
vector<int8_t> message_data_bytes(message msg);
string message_host(message msg);
unsigned short message_port(message msg);
connection_type message_protocol(message msg);
string my_ip();
string name_for_connection(const string host, const unsigned int port);
int new_connection_count(server_socket server);
connection open_connection(const string &name, const string &host, unsigned short port);
connection open_connection(const string &name, const string &host, unsigned short port, connection_type protocol);
message read_message();
message read_message(connection a_connection);
message read_message(const string &name);
message read_message(server_socket svr);
string read_message_data(const string &name);
string read_message_data(connection a_connection);
string read_message_data(server_socket svr);
void reconnect(connection a_connection);
void reconnect(const string &name);
void release_all_connections();
void reset_new_connection_count(server_socket server);
connection retrieve_connection(const string &name, int idx);
connection retrieve_connection(server_socket server, int idx);
bool send_message_to(const string &a_msg, connection a_connection);
bool send_message_to(const string &a_msg, const string &name);
bool server_has_new_connection(const string &name);
bool server_has_new_connection(server_socket server);
server_socket server_named(const string &name);
void set_udp_packet_size(unsigned int udp_packet_size);
unsigned int udp_packet_size();

#endif /* __networking_h */
