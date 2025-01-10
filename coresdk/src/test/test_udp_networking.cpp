//
//  test_udp_networking.cpp
//  splashkit
//
//  Ported by James Armstrong on 15/09/2016.
//

#include <iostream>

#include "easylogging++.h"

#include "networking.h"
#include "utils.h"

const int LISTEN_PORTB = 5000;

using namespace splashkit_lib;
using namespace std;

void pause_tcp_test()
{
    cout << "Please enter to continue;";
    char input;
    cin >> input;
}

void run_udp_networking_test()
{
    cout << "Listening for UDP connections on port " << LISTEN_PORTB << endl;
    server_socket server = create_server("MyServer", LISTEN_PORTB, UDP);
    pause_tcp_test();

    cout << "Creating connection to send data to server" << endl;
    connection to_server = open_connection("to_server", "127.0.0.1", LISTEN_PORTB, UDP);
    pause_tcp_test();

    cout << "Sending message to server" << endl;
    send_message_to("Hello UDP", to_server);
    delay(1000);

    cout << "Checking activity" << endl;
    check_network_activity();
    cout << "Server got message: " << has_messages(server) << endl;
    message msg = read_message(server);
    cout << "Message " << message_data(msg) << endl;
    pause_tcp_test();

    cout << "Sending message to client " << message_host(msg) << ":" << message_port(msg) << endl;
    connection to_client = open_connection("to_client", message_host(msg), message_port(msg), UDP);
    close_message(msg);

    cout << "Connection created" << endl;
    send_message_to("Hello Client", to_client);
    delay(100);
    check_network_activity();

    cout << "Client got message " << has_messages("to_server") << endl;
    cout << "Message " << read_message_data(to_server) << endl;

    close_connection(to_server);

    cout << "Closing UDP socket on port " << LISTEN_PORTB << endl;
    close_server(server);

    cout << "Close all" << endl;
    close_all_connections();
    close_all_servers();
}
