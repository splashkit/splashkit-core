#include "catch.hpp"

#include "networking.h"

using namespace splashkit_lib;

constexpr unsigned short int PORT = 3000;
const string TEST_IP = "http://localhost";

TEST_CASE("can create a server", "[networking]")
{
    const string SERVER_NAME = "test_server";

    SECTION("can create a UDP server")
    {
        server_socket server = create_server(SERVER_NAME, PORT, UDP);
        REQUIRE(server != nullptr);
        REQUIRE(has_server(SERVER_NAME));
        SECTION ("can get a server by name")
        {
            server_socket server2 = server_named(SERVER_NAME);
            REQUIRE(server2 == server);
        }
        SECTION("can close a server")
        {
            REQUIRE(close_server(server));
        }
    }
    SECTION("can create a TCP server")
    {
        server_socket server = create_server(SERVER_NAME, PORT, TCP);
        REQUIRE(server != nullptr);
        REQUIRE(has_server(SERVER_NAME));
        SECTION ("can get a server by name")
        {
            server_socket server2 = server_named(SERVER_NAME);
            REQUIRE(server2 == server);
        }
        SECTION("can close a server")
        {
            REQUIRE(close_server(server));
        }
    }
}
TEST_CASE("can communicate with server", "[networking]")
{
    SECTION("can communicate with a TCP server")
    {
        const string SERVER_NAME = "test_server";
        const string MESSAGE = "Hello";
        
        server_socket server = create_server(SERVER_NAME, PORT, TCP);
        REQUIRE(server != nullptr);
        SECTION("can send a message to a server")
        {
            connection conn = open_connection(SERVER_NAME, TEST_IP, PORT, TCP);
            REQUIRE(conn != nullptr);

            REQUIRE(has_new_connections());
            REQUIRE(server_has_new_connection(server));
            REQUIRE(server_has_new_connection(SERVER_NAME));
            REQUIRE(connection_count(server) == 0);
            REQUIRE(connection_count(SERVER_NAME) == 0);
            REQUIRE(new_connection_count(server) == 1);

            connection fethed_conn = fetch_new_connection(server);
            REQUIRE(fethed_conn == conn);

            REQUIRE(!has_new_connections());
            REQUIRE(!server_has_new_connection(server));
            REQUIRE(!server_has_new_connection(SERVER_NAME));
            REQUIRE(connection_count(server) == 1);
            REQUIRE(connection_count(SERVER_NAME) == 1);
            REQUIRE(new_connection_count(server) == 0);

            REQUIRE(send_message_to(MESSAGE, conn));
            close_connection(conn);
            SECTION("UDP server can receive a message")
            {
                message mes = read_message(server);
                REQUIRE(mes != nullptr);
                REQUIRE(message_data(mes) == MESSAGE);
                REQUIRE(message_protocol(mes) == TCP);
                REQUIRE(message_connection(mes) == fethed_conn);
                REQUIRE(message_host(mes) == TEST_IP);
                REQUIRE(message_port(mes) == PORT);
            }
        }
    }
}