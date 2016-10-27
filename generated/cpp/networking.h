//
// SplashKit Generated Networking C++ Code
// DO NOT MODIFY
//

#ifndef __networking_h
#define __networking_h

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
string dec_to_hex(unsigned int a_dec);
string hex_str_to_ipv4(const string &a_hex);
string hex_to_dec_string(const string &a_hex);
unsigned int ipv4_to_dec(const string &a_ip);
string ipv4_to_hex(const string &a_ip);
string ipv4_to_str(unsigned int ip);
string my_ip();

#endif /* __networking_h */
