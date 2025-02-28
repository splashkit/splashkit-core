#include "catch.hpp"

#include "networking.h"

using namespace splashkit_lib;

TEST_CASE("can create a server", "[networking]")
{
    constexpr unsigned short int PORT = 3000;

    SECTION("can create a UDP server")
    {
        const string SERVER_NAME = "test_server";

        server_socket server = create_server(SERVER_NAME, PORT, UDP);
        REQUIRE(server != nullptr);
        REQUIRE(has_server(SERVER_NAME));

        SECTION("can close a server")
        {
            REQUIRE(close_server(server));
        }
    }
    SECTION("can create a TCP server")
    {
        const string SERVER_NAME = "test_server_2";

        server_socket server = create_server(SERVER_NAME, PORT, TCP);
        REQUIRE(server != nullptr);
        REQUIRE(has_server(SERVER_NAME));
        SECTION("can close a server")
        {
            REQUIRE(close_server(server));
        }
    }
    SECTION("can check for non-existent server")
    {
        REQUIRE_FALSE(has_server("non_existent_server"));
    }
}
TEST_CASE("can communicate with server", "[networking]")
{
    close_all_servers();
    close_all_connections();

    constexpr unsigned short int PORT = 3001;
    const string TEST_IP = "localhost";
    SECTION("can communicate with a TCP server")
    {
        const string SERVER_NAME = "test_server_3";
        const string CONNECTION_NAME = "test_connection";
        server_socket server;

        SECTION("can create server with no connections")
        {
            server = create_server(SERVER_NAME, PORT, TCP);
            REQUIRE(server != nullptr);
            REQUIRE(has_server(SERVER_NAME));

            REQUIRE_FALSE(has_connection(CONNECTION_NAME));
            REQUIRE(connection_count(server) == 0);
            REQUIRE(new_connection_count(server) == 0);
            REQUIRE_FALSE(server_has_new_connection(server));
            REQUIRE_FALSE(server_has_new_connection(SERVER_NAME));
            REQUIRE_FALSE(has_new_connections());
        }

        connection conn = open_connection(CONNECTION_NAME, TEST_IP, PORT, TCP);
        REQUIRE(conn != nullptr);

        REQUIRE(accept_new_connection(server));
        REQUIRE(has_connection(CONNECTION_NAME));
        REQUIRE(connection_count(server) == 1);

        connection last_conn = last_connection(server);

        REQUIRE(is_connection_open(conn));

        REQUIRE(close_server(server));
    }
    SECTION("can communicate with a UDP server")
    {
        const string SERVER_NAME = "test_server_4";
        const string CONNECTION_NAME = "test_connection_2";

        server_socket server;
        SECTION("can create server with no connections")
        {
            server = create_server(SERVER_NAME, PORT, UDP);

            REQUIRE(server != nullptr);
            REQUIRE(has_server(SERVER_NAME));

            REQUIRE_FALSE(has_connection(CONNECTION_NAME));
            REQUIRE(connection_count(server) == 0);
            REQUIRE(new_connection_count(server) == 0);
            REQUIRE_FALSE(server_has_new_connection(server));
            REQUIRE_FALSE(server_has_new_connection(SERVER_NAME));
        }

        connection conn = open_connection(CONNECTION_NAME, TEST_IP, PORT, UDP);
        REQUIRE(conn != nullptr);

        REQUIRE(has_connection(CONNECTION_NAME));

        connection last_conn = last_connection(server);
        REQUIRE(is_connection_open(conn));

        REQUIRE(close_server(server));
    }
    SECTION("can check for non-existant connection")
    {
        REQUIRE_FALSE(has_connection("non_existent_connection"));
    }

    close_all_servers();
    close_all_connections();
}
TEST_CASE("can convert network data")
{
    SECTION("Testing hex_str_to_ipv4: can convert hexidecimal to ipv4")
    {
        REQUIRE(hex_str_to_ipv4("0x7F000001") == "127.0.0.1");
        REQUIRE(hex_str_to_ipv4("0x00000000") == "0.0.0.0");
        REQUIRE(hex_str_to_ipv4("0x00000000000000") == "0.0.0.0");
        REQUIRE(hex_str_to_ipv4("0xFFFFFFFF") == "255.255.255.255");
        REQUIRE_THROWS(hex_str_to_ipv4(""));
        REQUIRE_THROWS(hex_str_to_ipv4("0x"));
        REQUIRE_THROWS(hex_str_to_ipv4("error"));
    }
    SECTION("Testing hex_to_dec_string: can convert hexadecimal to decimal string")
    {
        REQUIRE(hex_to_dec_string("0x7F") == "127");
        REQUIRE(hex_to_dec_string("0x00") == "0");
        REQUIRE(hex_to_dec_string("0xFF") == "255");
        REQUIRE(hex_to_dec_string("") == "0");
        REQUIRE(hex_to_dec_string("0x") == "0");
        REQUIRE(hex_to_dec_string("0xGG") == "0");
        REQUIRE(hex_to_dec_string("error") == "0");
    }
    SECTION("Testing dec_to_hex: can convert decimal to hexadecimal string")
    {
        REQUIRE(dec_to_hex(127) == "0x7F");
        REQUIRE(dec_to_hex(ipv4_to_dec("127.0.0.1")) == "0x7F000001");
        REQUIRE(dec_to_hex(0) == "0x0");
        REQUIRE(dec_to_hex(255) == "0xFF");
        REQUIRE(dec_to_hex(256) == "0x100");
    }
    SECTION("Testing ipv4_to_hex: can convert ipv4 to hexidecimal")
    {
        REQUIRE(ipv4_to_hex("127.0.0.1") == "0x7F000001");
        REQUIRE(ipv4_to_hex("255.255.255.255") == "0xFFFFFFFF");
        REQUIRE(ipv4_to_hex("0.0.0.0") == "0x00000000");
        REQUIRE(ipv4_to_hex("....") == "0x00000000");
        REQUIRE(ipv4_to_hex("") == "0x00000000");
        REQUIRE_THROWS(ipv4_to_hex("a.b.c.d"));
        REQUIRE_THROWS(ipv4_to_hex("error"));
    }
    SECTION("Testing ipv4_to_dec: can convert ipv4 to decimal")
    {
        REQUIRE(ipv4_to_dec("127.0.0.1") == 2130706433);
        REQUIRE(ipv4_to_dec("0.0.0.0") == 0);
        REQUIRE(ipv4_to_dec("255.255.255.255") == 4294967295);
        REQUIRE(ipv4_to_dec("....") == 0);
        REQUIRE_THROWS(ipv4_to_dec("a.b.c.d"));
        REQUIRE_THROWS(ipv4_to_dec("error"));
    }
    SECTION("Testing dec_to_ipv4: can convert decimal to ipv4")
    {
        REQUIRE(dec_to_ipv4(2130706433) == "127.0.0.1");
        REQUIRE(dec_to_ipv4(ipv4_to_dec("127,0.0")) == "127.0.0.0");
        REQUIRE(dec_to_ipv4(0) == "0.0.0.0");
        REQUIRE(dec_to_ipv4(ipv4_to_dec("")) == "0.0.0.0");
        REQUIRE(dec_to_ipv4(4294967295) == "255.255.255.255");
    }
    SECTION("Testing name_for_connection: can create name for connection")
    {
        REQUIRE(name_for_connection("splashkit.com", 3000) == "splashkit.com:3000");
        REQUIRE(name_for_connection("localhost", 3200) == "localhost:3200");
        REQUIRE(name_for_connection("", 0) == ":0");
    }
    SECTION("Testing my_ip: can get local ip address")
    {
        REQUIRE(my_ip() == "127.0.0.1");
    }
    SECTION("Testing is_valid_ipv4: can check valid ip address")
    {
        // Valid IP addresses
        REQUIRE(is_valid_ipv4("192.168.1.1"));          // Common private IP
        REQUIRE(is_valid_ipv4("127.0.0.1"));            // Localhost
        REQUIRE(is_valid_ipv4("8.8.8.8"));              // Google DNS
        REQUIRE(is_valid_ipv4("255.255.255.255"));      // Maximum values
        REQUIRE(is_valid_ipv4("0.0.0.0"));              // Minimum values
        REQUIRE(is_valid_ipv4("172.16.254.1"));         // Valid class B private IP
        REQUIRE(is_valid_ipv4("10.0.0.1"));             // Valid class A private IP

        // Invalid IP addresses
        REQUIRE_FALSE(is_valid_ipv4("256.1.2.3"));       // First octet > 255
        REQUIRE_FALSE(is_valid_ipv4("1.256.2.3"));       // Second octet > 255
        REQUIRE_FALSE(is_valid_ipv4("1.2.256.3"));       // Third octet > 255
        REQUIRE_FALSE(is_valid_ipv4("1.2.3.256"));       // Fourth octet > 255
        REQUIRE_FALSE(is_valid_ipv4("192.168.1"));       // Missing octet
        REQUIRE_FALSE(is_valid_ipv4("192.168.1.1.1"));   // Too many octets
        REQUIRE_FALSE(is_valid_ipv4("192.168.1."));      // Trailing dot
        REQUIRE_FALSE(is_valid_ipv4(".192.168.1"));      // Leading dot
        REQUIRE_FALSE(is_valid_ipv4("192.168..1"));      // Empty octet
        REQUIRE_FALSE(is_valid_ipv4("192.168.1.1a"));    // Invalid character
        REQUIRE_FALSE(is_valid_ipv4(""));                // Empty string
        REQUIRE_FALSE(is_valid_ipv4("abc.def.ghi.jkl")); // Letters
        REQUIRE_FALSE(is_valid_ipv4("192,168,1,1"));     // Wrong separator
    }
}