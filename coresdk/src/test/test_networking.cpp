#include "window_manager.h"
#include "input.h"
#include "networking.h"

#include "assert.h"

#include <iostream>

#define TEST_IP "127.0.0.1"
#define TEST_IP_HEX "0x7F000001"

void run_encoding_decoding_tests()
{
    assert(ipv4_to_str(ipv4_to_dec(TEST_IP)) == TEST_IP);
    assert(hex_str_to_ipv4(TEST_IP_HEX) == TEST_IP);
}

void run_networking_test()
{
    run_encoding_decoding_tests();
}