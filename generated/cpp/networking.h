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
void close_all_connections();
void close_all_servers();
bool close_connection(connection a_connection);
bool close_connection(const string &name);
void close_message(message msg);
bool close_server(const string &name);
bool close_server(server_socket svr);
unsigned int connection_count(const string &name);
unsigned int connection_count(server_socket server);
server_socket create_server(const string &name, unsigned short port);
server_socket create_server(const string &name, unsigned short port, connection_type protocol);
string dec_to_hex(unsigned int a_dec);
bool has_new_connections();
bool has_server(const string &name);
string hex_str_to_ipv4(const string &a_hex);
string hex_to_dec_string(const string &a_hex);
unsigned int ipv4_to_dec(const string &a_ip);
string ipv4_to_hex(const string &a_ip);
string ipv4_to_str(unsigned int ip);
connection last_connection(const string &name);
connection last_connection(server_socket server);
string my_ip();
connection open_connection(const string &name, const string &host, unsigned short port);
connection open_connection(const string &name, const string &host, unsigned short port, connection_type protocol);
connection retrieve_connection(const string &name, int idx);
connection retrieve_connection(server_socket server, int idx);
bool server_has_new_connection(const string &name);
bool server_has_new_connection(server_socket server);
server_socket server_named(const string &name);

#endif /* __networking_h */
