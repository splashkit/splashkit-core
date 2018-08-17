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

const int SERVER1_PORT = 5000;
const int SERVER2_PORT = SERVER1_PORT + 1;

using namespace splashkit_lib;
using namespace std;

server_socket svr;
connection lConA, lConB, lTmp, lTmpA;
bool lMskReceived = false;
message msk;

void pause_test()
{
    cout << "Please enter to continue;";
    char input;
    cin >> input;
}

void check_messages()
{
    cout << "Checking for messages" << endl;
    check_network_activity();


    if (has_messages())
    {
        cout << "Reading messages received for client" << endl;
        while (has_messages(lConA))
        {
            msk = read_message(lConA);
            cout << " -> " << message_data(msk) << " from " << message_host(msk) << ":" << message_port(msk) << endl;
            close_message(msk);
        }

        cout << "Reading messages received for ToSvr client" << endl;
        while (has_messages("ToSvr"))
        {
            msk = read_message("ToSvr");
            cout << " -> " << message_data(msk) << " from " << message_host(msk) << ":" << message_port(msk) << endl;
            close_message(msk);
        }

        for (int i = 0; i < connection_count(svr); ++i)
        {
            lTmp = retrieve_connection(svr, i);
            if (has_messages(lTmp))
            {
                cout << " -> " << read_message_data(lTmp) << " from " << connection_port(lTmp) << endl;
            }
        }

        pause_test();
    }
    else
    {
        cout << "No messages received" << endl;
    }
}

void run_tcp_networking_test()
{
    cout << "Starting" << endl;

    svr = create_server("svr1", SERVER1_PORT);
    create_server("svr2", SERVER2_PORT);

    cout << "Listening on " << SERVER1_PORT << " and " << SERVER2_PORT << "." << endl;
    pause_test();

    //cout << "Attempting to open connection twice (should fail):  "<<  Assigned(CreateServer("svr3 " <<  SERVER2_PORT)));

    cout << "Connecting to Port (x2)  " <<  SERVER1_PORT << endl;
    lConA = open_connection("lConA", "127.0.0.1", SERVER1_PORT);
    open_connection("ToSvr", "127.0.0.1", SERVER1_PORT);

    cout << "ToSvr is open:  " <<  is_connection_open("ToSvr") << endl;
    cout << "Fred is open:  " <<  is_connection_open("Fred") << endl;

    check_network_activity();

    cout << "Are there new connections?  " <<  has_new_connections() << endl;
    cout << "New Connection to  " <<  SERVER1_PORT << ":  " <<  server_has_new_connection(svr) << endl;
    cout << " Number of connections:  " <<  connection_count(svr) << endl;

    lConB = last_connection(svr);

    check_network_activity();
    cout << "Are there new connections?  " <<  has_new_connections() << endl;
    cout << "New Connection to  " <<  SERVER1_PORT << ":  " <<  server_has_new_connection(svr) << endl;
    cout << " Number of connections:  " <<  connection_count(svr) << endl;

    pause_test();
    cout << "Checking for messages -- shouldn't be any" << endl;
    check_messages();

    cout << "Sending messages" << endl;
    send_message_to("To server --> from client", lConA);
    send_message_to("How are you :)", lConA);
    send_message_to("To server --> from named client", "ToSvr");
    send_message_to(string(509 - 4, '7'), lConA);
    send_message_to("1234567", lConA);
    send_message_to("0987654", lConA);
    send_message_to(string(876, 'A'), lConA);

    send_message_to(string(509 - 4, '7'), lConB);
    send_message_to("Hello Client", lConB);
    send_message_to(string(876, 'A'), lConB);

    pause_test();
    check_messages();
    check_messages();
    check_messages();

    cout << "Closing client -  " << close_connection(lConA) << endl;
    pause_test();

    cout << "Client still:  " << lConA << endl;
    cout << "Test message send (to closed client):  " << send_message_to(string("A", 876), lConB);

    pause_test();
    cout << "Test message send (expect false):  " << send_message_to(string("A", 876), lConB) << endl;

    cout << "Server still connected to client:  " << is_connection_open(retrieve_connection(svr, 0)) << endl;

    cout << "Closing server"
    "s client connection (should already by closed -- just testing):  " << close_connection(lConB) << endl;
    cout << "Server connections:  " << connection_count(svr) << endl;
    pause_test();

    cout << "Checking for activity" << endl;
    check_network_activity();

    cout << "Opening a new connection" << endl;

    lConA = open_connection("lConA1", "127.0.0.1", SERVER1_PORT);
    cout << "Reconnected:  " << lConA << endl;

    check_network_activity();
    lConB = last_connection(svr);
    cout << "Connections =  " << connection_count(svr) << endl;

    send_message_to("New connection --> to server", lConA);
    send_message_to("New connection --> to client", lConB);

    check_messages();

    cout << "Closing server:  " << close_server(svr) << endl;
    pause_test();

    cout << "Can connect to old server?  " << open_connection("oldsvr", "127.0.0.1", SERVER1_PORT) << endl;
    pause_test();

    cout << "Restarting server..." << endl;
    svr = create_server("svr1", SERVER1_PORT);

    reconnect(lConA);
    reconnect("ToSvr");

    check_network_activity();
    lConB = last_connection(svr);

    check_network_activity();

    broadcast_message("Hello Everyone");
    broadcast_message("Hello Everyone on svr", svr);

    send_message_to("Another message --> to server", lConA);
    send_message_to("Another message --> to client", lConB);
    send_message_to("Another message --> from named client", "ToSvr");
    send_message_to("Another message --> to named client", last_connection(svr));

    check_messages();
    check_messages();

    cout << "Close all" << endl;
    close_all_connections();
    close_all_servers();
}
