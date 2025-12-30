/**
*  test_terminal.cpp
*  splashkit
*
*  Created by Andrew Cain on 8/10/16.
*  Copyright © 2016 Andrew Cain. All rights reserved.
*/

#include "terminal.h"
#include "utils.h"
#include <iostream>
#include "basics.h"
#include <cassert>

using namespace splashkit_lib;

void test_simple_terminal()
{
    write_line("Hello World! " + to_string(10));
    write_line("Hello World! " + to_string(3.1415, 2));
    write("Hello");
    write(" ");
    write("World!");
    write_line();
    write_line("Test character output");
    write('a');
    write_line();
    write_line('c');
    delay(1000);
}

void test_terminal_has_input()
{
    write_line("Testing terminal input...");
    write_line("You have 2 seconds to either type something or nothing");
    delay(2000);
    if (terminal_has_input()) {
        write_line("There is data waiting to be read");
    } else {
        write_line("All data has been read");
    }
}

void dec_to_bin()
{
    write_line("Testing decimal to binary conversion");

    // Basic cases
    assert(dec_to_bin(0) == "0");
    assert(dec_to_bin(1) == "1");
    assert(dec_to_bin(2) == "10");
    assert(dec_to_bin(10) == "1010");
    assert(dec_to_bin(123) == "1111011");
    assert(dec_to_bin(1025) == "10000000001");
    assert(dec_to_bin(255) == "11111111");
    assert(dec_to_bin(256) == "100000000");
    assert(dec_to_bin(1023) == "1111111111");
    assert(dec_to_bin(4096) == "1000000000000");

    // Powers of 2
    assert(dec_to_bin(4) == "100");
    assert(dec_to_bin(8) == "1000");
    assert(dec_to_bin(16) == "10000");
    assert(dec_to_bin(1024) == "10000000000");

    // High values (32-bit boundaries)
    assert(dec_to_bin(4294967295) == "11111111111111111111111111111111");
    assert(dec_to_bin(2147483648) == "10000000000000000000000000000000");

    // Mixed bits
    assert(dec_to_bin(123) == "1111011");
    assert(dec_to_bin(1025) == "10000000001");

    // Tests for inequality
    assert(dec_to_bin(0) != "1");
    assert(dec_to_bin(1) != "0");
    assert(dec_to_bin(2) != "11");
    assert(dec_to_bin(10) != "1011");
    assert(dec_to_bin(123) != "1111100");
    assert(dec_to_bin(1025) != "10000000010");
    assert(dec_to_bin(255) != "100000000");
    assert(dec_to_bin(256) != "100000001");
    assert(dec_to_bin(1023) != "10000000000");
    assert(dec_to_bin(4096) != "1000000000001");
    assert(dec_to_bin(4294967295) != "1000");
    assert(dec_to_bin(2147483648) != "1000001");
    assert(dec_to_bin(123456789) != "1110101");
    assert(dec_to_bin(1100) != "11110");

    int dec_input1 = 1330;
    string result1 = dec_to_bin(dec_input1);
    write_line("1023 in binary is " + result1);

    int dec_input2 = 293842;
    string result2 = dec_to_bin(dec_input2);
    write_line("293842 in binary is " + result2);

    write_line("All decimal to binary tests passed!");
    write_line("-------------------------------------");
}

void bin_to_dec()
{
    write_line("Testing binary to decimal conversion");

    // Basic cases
    assert(bin_to_dec("0") == 0);
    assert(bin_to_dec("1") == 1);
    assert(bin_to_dec("10") == 2);
    assert(bin_to_dec("1010") == 10);
    assert(bin_to_dec("1111011") == 123);
    assert(bin_to_dec("10000000001") == 1025);
    assert(bin_to_dec("11111111") == 255);
    assert(bin_to_dec("100000000") == 256);
    assert(bin_to_dec("1111111111") == 1023);
    assert(bin_to_dec("1000000000000") == 4096);

    // Powers of 2
    assert(bin_to_dec("100") == 4);
    assert(bin_to_dec("1000") == 8);
    assert(bin_to_dec("10000") == 16);
    assert(bin_to_dec("10000000000") == 1024);

    // High values (32-bit boundaries)
    std::cout << bin_to_dec("10000000000000000000000000000000") << std::endl;
    assert(bin_to_dec("10000000000000000000000000000000") == 2147483648);

    // Mixed bits
    assert(bin_to_dec("1111011") == 123);
    assert(bin_to_dec("10000000001") == 1025);

    // Tests for inequality
    assert(bin_to_dec("0") != 1);
    assert(bin_to_dec("1") != 0);
    assert(bin_to_dec("10") != 3);
    assert(bin_to_dec("1010") != 11);
    assert(bin_to_dec("1111011") != 124);
    assert(bin_to_dec("10000000001") != 1026);
    assert(bin_to_dec("11111111") != 256);
    assert(bin_to_dec("100000000") != 257);
    assert(bin_to_dec("1111111111") != 1024);
    assert(bin_to_dec("1000000000000") != 4097);
    assert(bin_to_dec("10000000000000000000000000000000") != 2147483649);
    assert(bin_to_dec("abcde") != 2147483647);
    assert(bin_to_dec("a1b2b3i4f02") != 1234);

    string bin_input1 = "1111011";
    int result1 = bin_to_dec(bin_input1);
    write_line("1111011 in decimal is " + to_string(result1));

    string bin_input2 = "10000000001";
    int result2 = bin_to_dec(bin_input2);
    write_line("10000000001 in decimal is " + to_string(result2));

    write_line("All binary to decimal tests passed!");
    write_line("-------------------------------------");
}

void hex_to_bin()
{
    write_line("Testing hexadecimal to binary conversion");

    // Basic cases
    assert(hex_to_bin("0") == "0");
    assert(hex_to_bin("1") == "1");
    assert(hex_to_bin("A") == "1010");
    assert(hex_to_bin("F") == "1111");
    assert(hex_to_bin("10") == "00010000");
    assert(hex_to_bin("FF") == "11111111");
    assert(hex_to_bin("100") == "000100000000");
    assert(hex_to_bin("ABC") == "101010111100");
    assert(hex_to_bin("1234") == "0001001000110100");

    // Larger hexadecimal values
    assert(hex_to_bin("FFFF") == "1111111111111111");
    assert(hex_to_bin("FFFFFFFF") == "11111111111111111111111111111111");
    assert(hex_to_bin("1FFFFFF") == "0001111111111111111111111111");
    assert(hex_to_bin("ABCDEF") == "101010111100110111101111");

    // Tests for inequality
    assert(hex_to_bin("0") != "1");
    assert(hex_to_bin("1") != "0");
    assert(hex_to_bin("A") != "1011");
    assert(hex_to_bin("F") != "10000");
    assert(hex_to_bin("10") != "00010001");
    assert(hex_to_bin("FF") != "100000000");
    assert(hex_to_bin("100") != "000100000001");
    assert(hex_to_bin("ABC") != "101010111101");
    assert(hex_to_bin("1234") != "0001001000110101");
    assert(hex_to_bin("FFFF") != "11111111111111110");
    assert(hex_to_bin("FFFFFFFF") != "11111");
    assert(hex_to_bin("1FFFFFF") != "0111110");
    assert(hex_to_bin("GGGGGG") != "10101011110010");

    string hex_input1 = "ABCDEF";
    string result1 = hex_to_bin(hex_input1);
    write_line("ABCDEF in binary is " + result1);

    string hex_input2 = "1234";
    string result2 = hex_to_bin(hex_input2);
    write_line("1234 in binary is " + result2);

    write_line("All hexadecimal to binary tests passed!");
    write_line("-------------------------------------");
}

void bin_to_hex()
{
    write_line("Testing binary to hexadecimal conversion");

    // Basic cases
    assert(bin_to_hex("0") == "0");
    assert(bin_to_hex("1") == "1");
    assert(bin_to_hex("1010") == "A");
    assert(bin_to_hex("1111") == "F");

    // Multi-bit binary conversions
    assert(bin_to_hex("00010000") == "10");
    assert(bin_to_hex("11111111") == "FF");
    assert(bin_to_hex("000100000000") == "100");
    assert(bin_to_hex("101010111100") == "ABC");
    assert(bin_to_hex("0001001000110100") == "1234");

    // Larger binary values
    assert(bin_to_hex("1111111111111111") == "FFFF");
    assert(bin_to_hex("11111111111111111111111111111111") == "FFFFFFFF");
    assert(bin_to_hex("0001111111111111111111111111") == "1FFFFFF");
    assert(bin_to_hex("101010111100110111101111") == "ABCDEF");

    // Tests for inequality
    assert(bin_to_hex("0") != "1");
    assert(bin_to_hex("1") != "0");
    assert(bin_to_hex("1010") != "B");
    assert(bin_to_hex("1111") != "10");
    assert(bin_to_hex("00010000") != "11");
    assert(bin_to_hex("11111111") != "100");
    assert(bin_to_hex("000100000000") != "101");
    assert(bin_to_hex("101010111100") != "ABD");
    assert(bin_to_hex("0001001000110100") != "1235");
    assert(bin_to_hex("1111111111111111") != "FFFFF");
    assert(bin_to_hex("11111111111111111111111111111111") != "FFFFFFFFF");
    assert(bin_to_hex("00445566") != "1FFFFF");
    assert(bin_to_hex("1abc332") != "ABCDEG");

    string bin_input1 = "1010101111001111";
    string result1 = bin_to_hex(bin_input1);
    write_line("1010101111001111 in hexadecimal is " + result1);

    string bin_input2 = "0001001000110100";
    string result2 = bin_to_hex(bin_input2);
    write_line("0001001000110100 in hexadecimal is " + result2);

    write_line("All binary to hexadecimal tests passed!");
}

void test_dec_to_oct()
{
    write_line("Testing decimal to octal conversion");
    // Basic cases
    assert(dec_to_oct(0) == "0");
    assert(dec_to_oct(8) == "10");
    assert(dec_to_oct(64) == "100");
    assert(dec_to_oct(123) == "173");
    assert(dec_to_oct(255) == "377");
    assert(dec_to_oct(1023) == "1777");
    assert(dec_to_oct(4095) == "7777");

    // Powers of 8
    assert(dec_to_oct(8) == "10");
    assert(dec_to_oct(64) == "100");
    assert(dec_to_oct(512) == "1000");

    // High values (32-bit boundaries)
    assert(dec_to_oct(4294967295) == "37777777777");
    assert(dec_to_oct(2147483648) == "20000000000");

    // Mixed bits
    assert(dec_to_oct(123) == "173");
    assert(dec_to_oct(1025) == "2001");

    // Tests for inequality
    assert(dec_to_oct(0) != "1");
    assert(dec_to_oct(1) != "0");
    assert(dec_to_oct(8) != "11");
    assert(dec_to_oct(64) != "101");
    assert(dec_to_oct(123) != "174");
    assert(dec_to_oct(255) != "400");
    assert(dec_to_oct(1023) != "2000");
    assert(dec_to_oct(4095) != "8000");
    assert(dec_to_oct(4294967295) != "40000000000");
    assert(dec_to_oct(2147483648) != "20000000001");
    assert(dec_to_oct(123456789) != "1234567");
    assert(dec_to_oct(987654321) != "7654321");

    int dec_input1 = 1330;
    string result1 = dec_to_oct(dec_input1);
    write_line("1330 in octal is " + result1);

    int dec_input2 = 293842;
    string result2 = dec_to_oct(dec_input2);
    write_line("293842 in octal is " + result2);

    write_line("All decimal to octal tests passed!");
    write_line("-------------------------------------");
}
void test_oct_to_dec()
{
    write_line("Testing octal to decimal conversion");

    // Basic cases
    assert(oct_to_dec("0") == 0);
    assert(oct_to_dec("10") == 8);
    assert(oct_to_dec("100") == 64);
    assert(oct_to_dec("173") == 123);
    assert(oct_to_dec("377") == 255);
    assert(oct_to_dec("1777") == 1023);
    assert(oct_to_dec("7777") == 4095);

    // Powers of 8
    assert(oct_to_dec("10") == 8);
    assert(oct_to_dec("100") == 64);
    assert(oct_to_dec("1000") == 512);

    // High values (32-bit boundaries)
    assert(oct_to_dec("37777777777") == 4294967295);
    assert(oct_to_dec("20000000000") == 2147483648);

    // Mixed bits
    assert(oct_to_dec("173") == 123);
    assert(oct_to_dec("2001") == 1025);

    // Tests for inequality
    assert(oct_to_dec("0") != 1);
    assert(oct_to_dec("1") != 0);
    assert(oct_to_dec("10") != 9);
    assert(oct_to_dec("100") != 65);
    assert(oct_to_dec("173") != 124);
    assert(oct_to_dec("377") != 256);
    assert(oct_to_dec("1777") != 1024);
    assert(oct_to_dec("7777") != 4096);
    assert(oct_to_dec("20000000000") != 2147483649);
    assert(oct_to_dec("abcde") != 2147483647);
    assert(oct_to_dec("a1b2b3i4f02") != 1234);

    string oct_input1 = "173";
    int result1 = oct_to_dec(oct_input1);
    write_line("173 in decimal is " + to_string(result1));

    string oct_input2 = "2001";
    int result2 = oct_to_dec(oct_input2);
    write_line("2001 in decimal is " + to_string(result2));

    write_line("All octal to decimal tests passed!");
    write_line("-------------------------------------");
}

void test_octal_to_bin()
{
    write_line("Testing octal to binary conversion");

    // Basic cases
    assert(oct_to_bin("0") == "0");
    assert(oct_to_bin("1") == "1");
    assert(oct_to_bin("7") == "111");
    assert(oct_to_bin("10") == "1000");
    assert(oct_to_bin("12") == "1010");
    assert(oct_to_bin("77") == "111111");
    assert(oct_to_bin("100") == "1000000");
    assert(oct_to_bin("173") == "1111011");

    // Larger octal values
    assert(oct_to_bin("777") == "111111111");
    assert(oct_to_bin("1000") == "1000000000");
    assert(oct_to_bin("7777") == "111111111111");

    // Edge cases and boundary values
    assert(oct_to_bin("37777777777") == "11111111111111111111111111111111");
    assert(oct_to_bin("20000000000") == "10000000000000000000000000000000");

    // Tests for inequality
    assert(oct_to_bin("0") != "1");
    assert(oct_to_bin("1") != "0");
    assert(oct_to_bin("7") != "1000");
    assert(oct_to_bin("10") != "11");
    assert(oct_to_bin("12") != "1011");
    assert(oct_to_bin("77") != "1000000");
    assert(oct_to_bin("100") != "1000001");
    assert(oct_to_bin("173") != "1111100");
    assert(oct_to_bin("777") != "1000000000");
    assert(oct_to_bin("1000") != "1000000001");
    assert(oct_to_bin("7777") != "100000000000");
    assert(oct_to_bin("37777777777") != "10000000000000");
    assert(oct_to_bin("205550000") != "1000000001");

    string oct_input1 = "173";
    string result1 = oct_to_bin(oct_input1);
    write_line("173 in binary is " + result1);

    string oct_input2 = "7777";
    string result2 = oct_to_bin(oct_input2);
    write_line("7777 in binary is " + result2);

    write_line("All octal to binary tests passed!");
    write_line("-------------------------------------");
}

void test_bin_to_oct()
{
    write_line("Testing binary to octal conversion");

    // Basic cases
    assert(bin_to_oct("0") == "0");
    assert(bin_to_oct("1") == "1");
    assert(bin_to_oct("111") == "7");
    assert(bin_to_oct("1000") == "10");

    // Multi-bit binary numbers
    assert(bin_to_oct("1010") == "12");
    assert(bin_to_oct("111111") == "77");
    assert(bin_to_oct("1000000") == "100");
    assert(bin_to_oct("1111011") == "173");

    // Larger binary values
    assert(bin_to_oct("111111111") == "777");
    assert(bin_to_oct("1000000000") == "1000");
    assert(bin_to_oct("111111111111") == "7777");

    // Edge cases and boundary values
    assert(bin_to_oct("11111111111111111111111111111111") == "37777777777");
    assert(bin_to_oct("10000000000000000000000000000000") == "20000000000");

    // Tests for inequality
    assert(bin_to_oct("0") != "1");
    assert(bin_to_oct("1") != "0");
    assert(bin_to_oct("111") != "8");
    assert(bin_to_oct("1000") != "11");
    assert(bin_to_oct("1010") != "13");
    assert(bin_to_oct("111111") != "100");
    assert(bin_to_oct("1000000") != "101");
    assert(bin_to_oct("1111011") != "174");
    assert(bin_to_oct("111111111") != "1000");
    assert(bin_to_oct("1000000000") != "1001");
    assert(bin_to_oct("111111111111") != "10000");
    assert(bin_to_oct("1error1") != "40000000000");
    assert(bin_to_oct("1000077770") != "400097979701");

    string bin_input1 = "1111011";
    string result1 = bin_to_oct(bin_input1);
    write_line("1111011 in octal is " + result1);

    string bin_input2 = "111111111111";
    string result2 = bin_to_oct(bin_input2);
    write_line("111111111111 in octal is " + result2);

    write_line("All binary to octal tests passed!");
    write_line("-------------------------------------");
}

void test_oct_to_hex()
{
    write_line("Testing octal to hexadecimal conversion");

    // Basic cases
    assert(oct_to_hex("0") == "0");
    assert(oct_to_hex("1") == "1");
    assert(oct_to_hex("7") == "7");
    assert(oct_to_hex("10") == "8");
    assert(oct_to_hex("12") == "A");
    assert(oct_to_hex("77") == "3F");
    assert(oct_to_hex("100") == "40");
    assert(oct_to_hex("173") == "7B");

    // Larger octal values
    assert(oct_to_hex("777") == "1FF");
    assert(oct_to_hex("1000") == "200");
    assert(oct_to_hex("7777") == "FFF");
    assert(oct_to_hex("77777") == "7FFF");

    // Edge cases and boundary values
    assert(oct_to_hex("37777777777") == "FFFFFFFF");
    assert(oct_to_hex("20000000000") == "80000000");

    // Tests for inequality
    assert(oct_to_hex("0") != "1");
    assert(oct_to_hex("1") != "0");
    assert(oct_to_hex("7") != "8");
    assert(oct_to_hex("10") != "9");
    assert(oct_to_hex("12") != "B");
    assert(oct_to_hex("77") != "40");
    assert(oct_to_hex("100") != "41");
    assert(oct_to_hex("173") != "7C");
    assert(oct_to_hex("777") != "200");
    assert(oct_to_hex("1000") != "201");
    assert(oct_to_hex("7777") != "1000");
    assert(oct_to_hex("77777") != "8000");
    assert(oct_to_hex("37777777777") != "FFFFFFFFF");
    assert(oct_to_hex("20000000000") != "80000001");
    assert(oct_to_hex("abcde") != "80000000");
    assert(oct_to_hex("a1b2b3i4f02") != "80000001");

    string oct_input1 = "173";
    string result1 = oct_to_hex(oct_input1);
    write_line("173 in hexadecimal is " + result1);

    string oct_input2 = "7777";
    string result2 = oct_to_hex(oct_input2);
    write_line("7777 in hexadecimal is " + result2);

    write_line("All octal to hexadecimal tests passed!");
    write_line("-------------------------------------");
}

void test_hex_to_oct()
{
    write_line("Testing hexadecimal to octal conversion");

    // Basic cases
    assert(hex_to_oct("0") == "0");
    assert(hex_to_oct("1") == "1");
    assert(hex_to_oct("7") == "7");
    assert(hex_to_oct("8") == "10");

    // Multi-digit hex numbers
    assert(hex_to_oct("A") == "12");
    assert(hex_to_oct("3F") == "77");
    assert(hex_to_oct("40") == "100");
    assert(hex_to_oct("7B") == "173");

    // Larger hex values
    assert(hex_to_oct("1FF") == "777");
    assert(hex_to_oct("200") == "1000");
    assert(hex_to_oct("FFF") == "7777");
    assert(hex_to_oct("FFFF") == "177777");

    // Edge cases and boundary values
    assert(hex_to_oct("FFFFFFFF") == "37777777777");
    assert(hex_to_oct("80000000") == "20000000000");

    // Tests for inequality
    assert(hex_to_oct("0") != "1");
    assert(hex_to_oct("1") != "0");
    assert(hex_to_oct("7") != "8");
    assert(hex_to_oct("8") != "11");
    assert(hex_to_oct("A") != "13");
    assert(hex_to_oct("3F") != "100");
    assert(hex_to_oct("40") != "101");
    assert(hex_to_oct("7B") != "174");
    assert(hex_to_oct("1FF") != "1000");
    assert(hex_to_oct("200") != "1001");
    assert(hex_to_oct("FFF") != "10000");
    assert(hex_to_oct("FFFF") != "200000");
    assert(hex_to_oct("FFFFFFFF") != "40000000000");
    assert(hex_to_oct("80000000") != "40000000001");
    assert(hex_to_oct("abcde") != "40000000000");
    assert(hex_to_oct("a1b2b3i4f02") != "40000000001");

    string hex_input1 = "7B";
    string result1 = hex_to_oct(hex_input1);
    write_line("7B in octal is " + result1);

    string hex_input2 = "FFF";
    string result2 = hex_to_oct(hex_input2);
    write_line("FFF in octal is " + result2);

    write_line("All hexadecimal to octal tests passed!");
    write_line("-------------------------------------");
}

void test_base64_encode()
{
    write_line("Testing Base64 encoding");

    // Basic cases
    assert(base64_encode("Man") == "TWFu");
    assert(base64_encode("M") == "TQ==");
    assert(base64_encode("Ma") == "TWE=");
    assert(base64_encode("any carnal pleasure.") == "YW55IGNhcm5hbCBwbGVhc3VyZS4=");

    // Edge cases
    assert(base64_encode("") == "");
    assert(base64_encode("A") == "QQ==");
    assert(base64_encode("BC") == "QkM=");
    assert(base64_encode("yes") == "eWVz");

    // Larger strings
    assert(base64_encode("Hello, World!") == "SGVsbG8sIFdvcmxkIQ==");
    assert(base64_encode("The quick brown fox jumps over the lazy dog") == "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==");

    // Tests for inequality
    assert(base64_encode("Man") != "TQ==");
    assert(base64_encode("M") != "TWFu");
    assert(base64_encode("Ma") != "YW55IGNhcm5hbCBwbGVhc3VyZS4=");
    assert(base64_encode("any carnal pleasure.") != "TWE=");
    assert(base64_encode("") != "QQ==");
    assert(base64_encode("A") != "QkM=");
    assert(base64_encode("BC") != "eWVz");
    assert(base64_encode("yes") != "SGVsbG8sIFdvcmxkIQ==");
    assert(base64_encode("Hello, World!") != "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==");
    assert(base64_encode("The quick brown fox jumps over the lazy dog") != "SGVsbG8sIFdvcmxkIQ==");

    string input1 = "Hello, World!";
    string result1 = base64_encode(input1);
    write_line("Hello, World! in Base64 is " + result1);

    string input2 = "The quick brown fox jumps over the lazy dog";
    string result2 = base64_encode(input2);
    write_line("The quick brown fox jumps over the lazy dog in Base64 is " + result2);

    write_line("All Base64 encoding tests passed!");
    write_line("-------------------------------------");
}

void test_base64_decode()
{
    write_line("Testing Base64 decoding");

    // Basic cases
    assert(base64_decode("TWFu") == "Man");
    assert(base64_decode("TQ==") == "M");
    assert(base64_decode("TWE=") == "Ma");
    assert(base64_decode("YW55IGNhcm5hbCBwbGVhc3VyZS4=") == "any carnal pleasure.");

    // Edge cases
    assert(base64_decode("") == "");
    assert(base64_decode("QQ==") == "A");
    assert(base64_decode("QkM=") == "BC");
    assert(base64_decode("eWVz") == "yes");

    // Larger strings
    assert(base64_decode("SGVsbG8sIFdvcmxkIQ==") == "Hello, World!");
    assert(base64_decode("VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==") == "The quick brown fox jumps over the lazy dog");

    // Tests for inequality
    assert(base64_decode("TQ==") != "Man");
    assert(base64_decode("TWFu") != "M");
    assert(base64_decode("YW55IGNhcm5hbCBwbGVhc3VyZS4=") != "Ma");
    assert(base64_decode("TWE=") != "any carnal pleasure.");
    assert(base64_decode("QQ==") != "");
    assert(base64_decode("QkM=") != "A");
    assert(base64_decode("eWVz") != "BC");
    assert(base64_decode("SGVsbG8sIFdvcmxkIQ==") != "yes");
    assert(base64_decode("VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==") != "Hello, World!");
    assert(base64_decode("SGVsbG8sIFdvcmxkIQ==") != "The quick brown fox jumps over the lazy dog");

    string input1 = "SGVsbG8sIFdvcmxkIQ==";
    string result1 = base64_decode(input1);
    write_line("SGVsbG8sIFdvcmxkIQ== in Base64 is " + result1);

    string input2 = "VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw==";
    string result2 = base64_decode(input2);
    write_line("VGhlIHF1aWNrIGJyb3duIGZveCBqdW1wcyBvdmVyIHRoZSBsYXp5IGRvZw== in Base64 is " + result2);

    write_line("All Base64 decoding tests passed!");
    write_line("-------------------------------------");
}

void test_is_binary()
{
    // Valid binary strings
    assert(is_binary("0"));
    assert(is_binary("1"));
    assert(is_binary("101010"));
    assert(is_binary("0000"));
    assert(is_binary("1111"));

    // Invalid binary strings
    assert(!is_binary(""));
    assert(!is_binary("102"));
    assert(!is_binary("ABC"));
    assert(!is_binary("1A1"));

    write_line("All binary validation tests passed!");
    write_line("-------------------------------------");
}

void test_is_hex()
{
    // Valid hexadecimal strings
    assert(is_hex("0"));
    assert(is_hex("F"));
    assert(is_hex("10"));
    assert(is_hex("1A2B3C"));
    assert(is_hex("abcdef"));
    assert(is_hex("ABCDEF"));
    assert(is_hex("1234567890ABCDEF"));

    // Invalid hexadecimal strings
    assert(!is_hex(""));
    assert(!is_hex("G"));
    assert(!is_hex("1G2"));
    assert(!is_hex("XYZ123"));

    write_line("All hexadecimal validation tests passed!");
    write_line("-------------------------------------");
}

void test_is_octal()
{
    // Valid octal strings
    assert(is_octal("0"));
    assert(is_octal("7"));
    assert(is_octal("10"));
    assert(is_octal("1234567"));
    assert(is_octal("0000"));

    // Invalid octal strings
    assert(!is_octal(""));
    assert(!is_octal("8"));
    assert(!is_octal("9"));
    assert(!is_octal("78"));
    assert(!is_octal("123A456"));

    write_line("All octal validation tests passed!");
    write_line("-------------------------------------");
}

void test_calculate_square_root()
{
    write_line("Testing square root calculation");

    // Basic cases
    assert(square_root(0) == 0);
    assert(square_root(1) == 1);
  //  assert(square_root(4) == 2);
    assert(square_root(9) == 3);
    assert(square_root(16) == 4);
    assert(square_root(25) == 5);
    assert(square_root(100) == 10);

    // Tests for inequality
    assert(square_root(0) != 1);
    assert(square_root(1) != 0);
    assert(square_root(4) != 3);
    assert(square_root(9) != 4);
    assert(square_root(16) != 5);
    assert(square_root(25) != 6);
    assert(square_root(100) != 11);

    double input1 = 49;
    double result1 = square_root(input1);
    write_line("Square root of 49 is " + to_string(result1));

    double input2 = 81;
    double result2 = square_root(input2);
    write_line("Square root of 81 is " + to_string(result2));

    double input3 = 83;
    double result3 = square_root(input3);
    write_line("Square root of 83 is " + to_string(result3));

    write_line("All square root calculation tests passed!");
    write_line("-------------------------------------");
}

void test_calculate_is_prime()
{
    write_line("Testing prime number calculation");

    // Basic cases
    assert(is_prime_number(2));
    assert(is_prime_number(3));
    assert(is_prime_number(5));
    assert(is_prime_number(7));
    assert(is_prime_number(11));
    assert(is_prime_number(13));
    assert(is_prime_number(17));
    assert(is_prime_number(19));
    assert(is_prime_number(23));
    assert(is_prime_number(29));

    // Non-prime numbers
    assert(!is_prime_number(0));
    assert(!is_prime_number(1));
    assert(!is_prime_number(4));
    assert(!is_prime_number(6));
    assert(!is_prime_number(8));
    assert(!is_prime_number(9));
    assert(!is_prime_number(10));
    assert(!is_prime_number(12));
    assert(!is_prime_number(14));
    assert(!is_prime_number(15));

    // Larger prime numbers
    assert(is_prime_number(101));
    assert(is_prime_number(103));
    assert(is_prime_number(107));
    assert(is_prime_number(109));
    assert(is_prime_number(113));

    // Tests for inequality
    assert(!is_prime_number(0));
    assert(!is_prime_number(1));
    assert(!is_prime_number(4));
    assert(!is_prime_number(6));
    assert(!is_prime_number(8));
    assert(!is_prime_number(9));
    assert(!is_prime_number(10));
    assert(!is_prime_number(12));
    assert(!is_prime_number(14));
    assert(!is_prime_number(15));

    write_line("All prime number calculation tests passed!");
    write_line("-------------------------------------");
}

void test_calculate_gcd()
{
    write_line("Testing GCD calculation");

    // Basic cases
    assert(greatest_common_divisor(0, 0) == 0);
    assert(greatest_common_divisor(1, 0) == 1);
    assert(greatest_common_divisor(0, 1) == 1);
    assert(greatest_common_divisor(1, 1) == 1);
    assert(greatest_common_divisor(12, 8) == 4);
    assert(greatest_common_divisor(54, 24) == 6);
    assert(greatest_common_divisor(48, 18) == 6);
    assert(greatest_common_divisor(101, 103) == 1);

    // Edge cases
    assert(greatest_common_divisor(0, 5) == 5);
    assert(greatest_common_divisor(5, 0) == 5);
    assert(greatest_common_divisor(7, 1) == 1);
    assert(greatest_common_divisor(1, 7) == 1);

    // Tests for inequality
    assert(greatest_common_divisor(12, 8) != 5);
    assert(greatest_common_divisor(54, 24) != 7);
    assert(greatest_common_divisor(48, 18) != 5);
    assert(greatest_common_divisor(101, 103) != 2);

    int input1_a = 56, input1_b = 98;
    int result1 = greatest_common_divisor(input1_a, input1_b);
    write_line("GCD of 56 and 98 is " + to_string(result1));

    int input2_a = 48, input2_b = 180;
    int result2 = greatest_common_divisor(input2_a, input2_b);
    write_line("GCD of 48 and 180 is " + to_string(result2));

    write_line("All GCD calculation tests passed!");
    write_line("-------------------------------------");
}

void test_calculate_lcm()
{
    write_line("Testing LCM calculation");

    // Basic cases
    assert(least_common_multiple(0, 0) == 0);
    assert(least_common_multiple(1, 0) == 0);
    assert(least_common_multiple(0, 1) == 0);
    assert(least_common_multiple(1, 1) == 1);
    assert(least_common_multiple(12, 8) == 24);
    assert(least_common_multiple(54, 24) == 216);
    assert(least_common_multiple(48, 18) == 144);
    assert(least_common_multiple(101, 103) == 10403);

    // Edge cases
    assert(least_common_multiple(0, 5) == 0);
    assert(least_common_multiple(5, 0) == 0);
    assert(least_common_multiple(7, 1) == 7);
    assert(least_common_multiple(1, 7) == 7);

    // Tests for inequality
    assert(least_common_multiple(12, 8) != 25);
    assert(least_common_multiple(54, 24) != 217);
    assert(least_common_multiple(48, 18) != 145);
    assert(least_common_multiple(101, 103) != 10404);

    int input1_a = 21, input1_b = 6;
    int result1 = least_common_multiple(input1_a, input1_b);
    write_line("LCM of 21 and 6 is " + to_string(result1));

    int input2_a = 15, input2_b = 20;
    int result2 = least_common_multiple(input2_a, input2_b);
    write_line("LCM of 15 and 20 is " + to_string(result2));

    write_line("All LCM calculation tests passed!");
    write_line("-------------------------------------");
}

void run_terminal_test()
{
    test_simple_terminal();
    test_terminal_has_input();
    dec_to_bin();
    bin_to_dec();
    hex_to_bin();
    bin_to_hex();
    test_dec_to_oct();
    test_oct_to_dec();
    test_octal_to_bin();
    test_bin_to_oct();
    test_oct_to_hex();
    test_hex_to_oct();
    test_base64_encode();
    test_base64_decode();
    test_is_binary();
    test_is_hex();
    test_is_octal();
    test_calculate_square_root();
    test_calculate_is_prime();
    test_calculate_gcd();
    test_calculate_lcm();
}
