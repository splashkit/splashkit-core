//
// SplashKit Generated Networking C++ Code
// DO NOT MODIFY
//

#ifndef __networking_h
#define __networking_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

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
/**
* Accept new connections for all servers.

* @return True if there were accepted connections
*/
bool accept_all_new_connections();
/**
* Accept new connections for a server
* @param server The server to check
* @return True if a connection was accepted
*/
bool accept_new_connection(server_socket server);
/**
* Broadcast a message to all connections of a server.
* @param a_msg The message to send
* @param svr The server to send the message to.
*
*/
void broadcast_message(const string &a_msg, server_socket svr);
/**
* Broadcase a message to all of the connections.
* @param a_msg The message to send
*
*/
void broadcast_message(const string &a_msg);
/**
* Broadcast a message to all connections of a server.
* @param a_msg The message to send
* @param name The name of the server to send the message to.
*
*/
void broadcast_message(const string &a_msg, const string &name);
/**
* Check network activity, looking for new connections and messages.

*
*/
void check_network_activity();
/**
* Clear all of the messages from a server or connection with the supplied name.
* @param name The name of the connection or the server to clear.
*
*/
void clear_messages(const string &name);
/**
* Clear all of the messages from a connection.
* @param a_connection The connection
*
*/
void clear_messages(connection a_connection);
/**
* Clear all of the messages from a server.
* @param svr The server to clear the messages from
*
*/
void clear_messages(server_socket svr);
/**
* Close all of the connections you have opened. This does not close
* connections to servers.

*
*/
void close_all_connections();
/**
* Close all of the servers that are currently open.

*
*/
void close_all_servers();
/**
* Close the connection
* @param a_connection The connection to close
* @return True if this succeeds.
*/
bool close_connection(connection a_connection);
/**
* Close the connection
* @param name The name of the connection to close
* @return True if this succeeds.
*/
bool close_connection(const string &name);
/**
* Closes the message.
* @param msg The message to close
*
*/
void close_message(message msg);
/**
* Closes the server with the indicated name.
* @param name The name of the server to close
* @return True if the server was closed successfully
*/
bool close_server(const string &name);
/**
* Closes the server, all connections with clients will be shut and
* the port will be closed.
* @param svr The server to close
* @return True if the close was successful
*/
bool close_server(server_socket svr);
/**
* Returns the number of clients connected to a server.
* @param name The name of the server to check
* @return The number of connected clients
*/
unsigned int connection_count(const string &name);
/**
* Returns the number of clients connected to a server.
* @param server The server to check
* @return The number of connected clients
*/
unsigned int connection_count(server_socket server);
/**
* Gets the ip address of the passed in connection.
* @param a_connection The connection
* @return The ip addres of the connection
*/
unsigned int connection_ip(connection a_connection);
/**
* Gets the ip address of the connection with the supplied name.
* @param name The name of the connection
* @return The connection's ip address
*/
unsigned int connection_ip(const string &name);
/**
* Fetch the connection with the indicated name.
* @param name The name of the connection to fetch
* @return The connection with that name
*/
connection connection_named(const string &name);
/**
* Gets the port of the connection.
* @param a_connection The connection
* @return The port of the connection.
*/
unsigned short connection_port(connection a_connection);
/**
* Gets the part of the connection.
* @param name The name of the connection
* @return The port of the connection
*/
unsigned short connection_port(const string &name);
/**
* Creates a new TCP server that can accept connections from other programs.
* @param name The name used to access the Server in splashkit
* @param port The port that clients will use to connect to the server
* @return A new server with the indicated details
*/
server_socket create_server(const string &name, unsigned short port);
/**
* Creates a new server that can accept connections from other programs.
* @param name The name used to access the Server in splashkit
* @param port The port that clients will use to connect to the server
* @param protocol The protocol used by the server
* @return A new server with the indicated details
*/
server_socket create_server(const string &name, unsigned short port, connection_type protocol);
/**
* Converts the supplied decimal integer into it's hexadecimal representation.
* e.g. 0x7F000001 from 2130706433
* @param a_dec decimal to be converted to a hexadecimal number string
* @return hexadecimal representation of the supplied decimal integer
*/
string dec_to_hex(unsigned int a_dec);
/**
* Decodes the supplied unsigned 32-bit integer into its ipv4 address form
* e.g. 2130706433 into 127.0.0.1
* @param ip integer to be decoded
* @return ipv4 address string in X.X.X.X format
*/
string dec_to_ipv4(unsigned int ip);
/**
* Get the oldest new connections made to the server, and
* reduces the new connection count by 1.
* @param server The server to check
* @return The oldest new connection
*/
connection fetch_new_connection(server_socket server);
/**
* Does the connection with the supplied name exist?
* @param name The name of the connection to check.
* @return True if there is a connection with the supplied name
*/
bool has_connection(const string &name);
/**
* Checks if there are any messages waiting to be read.

* @return True if there are any messages waiting to be read
*/
bool has_messages();
/**
* Checks if a connection has messages waiting to be read.
* @param con The connection
* @return True if there are any messages on the connection.
*/
bool has_messages(connection con);
/**
* Checks if a server or connection has any messages.
* @param name The name of the server or connection to check.
* @return [description]
*/
bool has_messages(const string &name);
/**
* Checks if a server has any messages waiting to be read.
* @param svr The server to check
* @return True if there are messages on the server.
*/
bool has_messages(server_socket svr);
/**
* Checks if any of the servers have new connections.

* @return True if there is one or more servers with new connections.
*/
bool has_new_connections();
/**
* Checks if there is a server with the indicated name.
* @param name The name of the server to check
* @return True if there is a server with that name
*/
bool has_server(const string &name);
/**
* The supplied hexadecimal string is translated into ipv4 standard address string.
* Function handles hex strings starting with or without 0x.
* e.g. 127.0.0.1 from 0x7F000001
* @param a_hex hexadecimal ipv4 string to convert
* @return standard ipv4 address using format X.X.X.X
*/
string hex_str_to_ipv4(const string &a_hex);
/**
* The supplied hexadecimal string is converted into it's decimal representation
* e.g. 7F into 127
* @param a_hex hexadecimal string to convert
* @return decimal representation of supplied hex string
*/
string hex_to_dec_string(const string &a_hex);
/**
* Converts a hexadecimal representation of a MAC address back to its standard format.
* e.g. 01:23:45:67:89:AB from 0x0123456789AB
* @param hex_str hexadecimal string to convert
* @return MAC address as a string in the format XX:XX:XX:XX:XX:XX
*/
string hex_to_mac(const string &hex_str);
/**
* Encodes the supplied ipv4 address string (in format X.X.X.X) into a single integer
* e.g. 127.0.0.1 into 2130706433
* @param a_ip ipv4 address to encode
* @return encoded ipv4 string
*/
unsigned int ipv4_to_dec(const string &a_ip);
/**
* Converts an ipv4 address into it's hexadecimal representation
* e.g. 0x7F000001 from 127.0.0.1
* @param a_ip ip address to convert
* @return hexadecimal representation of ipc4 string
*/
string ipv4_to_hex(const string &a_ip);
/**
* Checks if the connection currently is open.
* @param con The connection
* @return True if the connection is open.
*/
bool is_connection_open(connection con);
/**
* Checks if the connection with the supplied name currently is open.
* @param name The name of the connection
* @return True if the connection is open.
*/
bool is_connection_open(const string &name);
/**
* 
* @param ip The string containing the IP address to validate
* @return bool Returns true if the string is a valid IPv4 address, false otherwise
*/
bool is_valid_ipv4(const string &ip);
/**
* Checks if the supplied MAC address is valid.
* @param mac_address MAC address to check
* @return true if the MAC address is valid
*/
bool is_valid_mac(const string &mac_address);
/**
* Gets the last client that connected to a server.
* @param name The name of the server to check
* @return The last connection made to that server
*/
connection last_connection(const string &name);
/**
* Gets the last client that connected to a server.
* @param server The server to check
* @return The last connection made to that server
*/
connection last_connection(server_socket server);
/**
* Converts a MAC address into its hexadecimal representation.
* e.g. 0x0123456789AB from 01:23:45:67:89:AB
* @param mac_address MAC address to convert
* @return hexadecimal representation of MAC address as a string
*/
string mac_to_hex(const string &mac_address);
/**
* Returns the connection that sent a message.
* @param msg The message
* @return The connection that sent the message
*/
connection message_connection(message msg);
/**
* Returns the number of messages on a server.
* @param svr The server to check
* @return The number of messages on the server
*/
unsigned int message_count(server_socket svr);
/**
* Returns the number of messages on a connection.
* @param a_connection The connection
* @return The number of messages to be read from the connection
*/
unsigned int message_count(connection a_connection);
/**
* Returns the number of messages on a server or connection.
* @param name The name of the server or connection
* @return The number of messages on the server or connection
*/
unsigned int message_count(const string &name);
/**
* Gets the body of a message as a string.
* @param msg The message to check
* @return The string body of the message
*/
string message_data(message msg);
/**
* Gets the body of a message as a list of bytes.
* @param msg The message to check
* @return The body of the message as bytes
*/
vector<int8_t> message_data_bytes(message msg);
/**
* Returns the host who made the message.
* @param msg The message to check
* @return The host who sent the message
*/
string message_host(message msg);
/**
* Returns the port used to send a message.
* @param msg The message to check
* @return The port of the message
*/
unsigned short message_port(message msg);
/**
* Returns the protocol used to send a message.
* @param msg The message to check
* @return The protocol used to sent the message
*/
connection_type message_protocol(message msg);
/**
* Returns the ipv4 string of the localhost loopback for the current computer.

* @return ipv4 address string in X.X.X.X format
*/
string my_ip();
/**
* Returns the name SplashKit would use for a connection made to a server
* from a host to a port.
* @param host The host name
* @param port The port
* @return The name SplashKit would use for this connection
*/
string name_for_connection(const string host, const unsigned int port);
/**
* Get the number of new connections made to the server.
* The count will increase as the server accepts new connections.
* The count decreases each time you fetch a new connection, or
* can be set to 0 if you reset the new connection count.
* @param server The server to check
* @return The number of new connections
*/
int new_connection_count(server_socket server);
/**
* Opens a TCP connection to a server using the supplied details.
* @param name The name for the connection
* @param host The address of the server
* @param port The server's port
* @return A new connection to the indicated server
*/
connection open_connection(const string &name, const string &host, unsigned short port);
/**
* Opens a connection to a server using the supplied details.
* @param name The name for the connection
* @param host The address of the server
* @param port The server's port
* @param protocol The protocol used to connect to the server
* @return A new connection to the indicated server
*/
connection open_connection(const string &name, const string &host, unsigned short port, connection_type protocol);
/**
* Read a message from the network (from a server or connection).

* @return The first message from the network.
*/
message read_message();
/**
* Reads the first message from the connection.
* @param a_connection A connection
* @return The first message read from the connection
*/
message read_message(connection a_connection);
/**
* Reads the first message from a connection or server.
* @param name The name of a connection or server
* @return The first message read from the connection or server
*/
message read_message(const string &name);
/**
* Reads the first message from the server.
* @param svr A server
* @return The first message read from the server
*/
message read_message(server_socket svr);
/**
* Read message data from a connection or server.
* @param name The name of the connection or server
* @return The data from the first message from the server or connection
*/
string read_message_data(const string &name);
/**
* Read message data from a connection.
* @param a_connection The connection
* @return The data from the first message on the connection
*/
string read_message_data(connection a_connection);
/**
* Read message data from a server.
* @param svr The server
* @return The data from the first message on the server
*/
string read_message_data(server_socket svr);
/**
* Attempt to reconnect the connection.
* @param a_connection The connection to reconnect
*
*/
void reconnect(connection a_connection);
/**
* Attempt to reconnect the connection.
* @param name The name of the connection to reconnect.
*
*/
void reconnect(const string &name);
/**
* Close and release the resources used by all of the connections.

*
*/
void release_all_connections();
/**
* Allows you to reset the new connection count to 0.
* (The connections are kept)
* @param server The server to check
*
*/
void reset_new_connection_count(server_socket server);
/**
* Get a connection from the server.
* @param name The name of the server
* @param idx The index of the connection
* @return The connection at the supplied index
*/
connection retrieve_connection(const string &name, int idx);
/**
* Get a connection from the server.
* @param server The server
* @param idx The index of the connection
* @return The connection at the supplied index
*/
connection retrieve_connection(server_socket server, int idx);
/**
* Send a message to the connection.
* @param a_msg The message to send
* @param a_connection The connection to send the message to
* @return True if the message sends.
*/
bool send_message_to(const string &a_msg, connection a_connection);
/**
* Send a message to the connection with the given name.
* @param a_msg The message to send
* @param name The name of the connection to send the message to
* @return True if the message sends
*/
bool send_message_to(const string &a_msg, const string &name);
/**
* Checks of there are new connections waiting for a server.
* @param name The name of the server to check
* @return True if the server has new connections
*/
bool server_has_new_connection(const string &name);
/**
* Checks of there are new connections waiting for a server.
* @param server The server to check
* @return True if the server has new connections
*/
bool server_has_new_connection(server_socket server);
/**
* Gets the server with the indicated name.
* @param name The name of the server to get
* @return The server
*/
server_socket server_named(const string &name);
/**
* Change the size of the UDP packets.
* @param udp_packet_size The new packet size.
*
*/
void set_udp_packet_size(unsigned int udp_packet_size);
/**
* Returns the size SplashKit is using for UDP packets.

* @return The size of UDP packets.
*/
unsigned int udp_packet_size();

#endif /* __networking_h */
