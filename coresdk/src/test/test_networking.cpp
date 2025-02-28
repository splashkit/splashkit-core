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

void is_valid_ip_test()
{
    // Valid IP addresses - should return true
    assert(is_valid_ipv4("192.168.1.1") == true);     // Common private IP
    assert(is_valid_ipv4("127.0.0.1") == true);       // Localhost
    assert(is_valid_ipv4("8.8.8.8") == true);         // Google DNS
    assert(is_valid_ipv4("255.255.255.255") == true); // Maximum values
    assert(is_valid_ipv4("0.0.0.0") == true);         // Minimum values
    assert(is_valid_ipv4("172.16.254.1") == true);    // Valid class B private IP
    assert(is_valid_ipv4("10.0.0.1") == true);        // Valid class A private IP

    // Invalid IP addresses - should return false
    assert(is_valid_ipv4("256.1.2.3") == false);       // First octet > 255
    assert(is_valid_ipv4("1.256.2.3") == false);       // Second octet > 255
    assert(is_valid_ipv4("1.2.256.3") == false);       // Third octet > 255
    assert(is_valid_ipv4("1.2.3.256") == false);       // Fourth octet > 255
    assert(is_valid_ipv4("192.168.1") == false);       // Missing octet
    assert(is_valid_ipv4("192.168.1.1.1") == false);   // Too many octets
    assert(is_valid_ipv4("192.168.1.") == false);      // Trailing dot
    assert(is_valid_ipv4(".192.168.1") == false);      // Leading dot
    assert(is_valid_ipv4("192.168..1") == false);      // Empty octet
    assert(is_valid_ipv4("192.168.1.1a") == false);    // Invalid character
    assert(is_valid_ipv4("") == false);                // Empty string
    assert(is_valid_ipv4("abc.def.ghi.jkl") == false); // Letters
    assert(is_valid_ipv4("192,168,1,1") == false);     // Wrong separator

    std::cout << "All IP validation tests passed!" << std::endl;
    std::cout << "-------------------------------------" << std::endl;
}

void run_networking_test()
{
    run_encoding_decoding_tests();
    is_valid_ip_test();
}