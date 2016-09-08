#include "window_manager.h"
#include "networking.h"

#include "assert.h"

#include <iostream>

#define TEST_IP "127.0.0.1"
#define TEST_IP_HEX "0x7F000001"

using namespace splashkit_lib;

void run_encoding_decoding_tests()
{
    // Incomplete ip address tests
    assert(ipv4_to_hex("127.0.0") == "0x7F000000");
    assert(ipv4_to_str(ipv4_to_dec("127.0.0")) == "127.0.0.0");
    assert(ipv4_to_str(ipv4_to_dec("127,0.0")) == "127.0.0.0");
    assert(ipv4_to_str(ipv4_to_dec("")) == "0.0.0.0");

    int too_small_int = 4000;
    assert(ipv4_to_str(too_small_int) == "0.0.15.160");

    // Complete ip address tests
    assert(ipv4_to_str(ipv4_to_dec(TEST_IP)) == TEST_IP);
    assert(dec_to_hex(ipv4_to_dec(TEST_IP)) == TEST_IP_HEX);
    assert(ipv4_to_hex(TEST_IP) == TEST_IP_HEX);
    assert(hex_str_to_ipv4(TEST_IP_HEX) == TEST_IP);
    assert(my_ip() == "127.0.0.1");
}

void run_networking_test()
{
    run_encoding_decoding_tests();
}