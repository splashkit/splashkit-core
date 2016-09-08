#ifndef SPLASHKIT_NETWORKING_H
#define SPLASHKIT_NETWORKING_H

#include <string>
#include "types.h"

using namespace std;

// TODO implement safety checks e.g. 7F000001 should fail or be handled but should fail for dec_to_hex()

/**
 * @brief Converts a hexadecimal ipv4 string to standard ipv4 address string x.x.x.x
 *
 * The supplied hexadecimal string is translated into ipv4 standard address string.
 * Function handles hex strings starting with or without 0x.
 * e.g. 127.0.0.1 from 0x7F000001
 *
 * @param a_hex hexadecimal ipv4 string to convert
 *
 * @returns standard ipv4 address using format X.X.X.X
 */
string hex_str_to_ipv4(const string &a_hex);

/**
 * @brief Converts a hexadecimal string to a decimal string
 *
 * The supplied hexadecimal string is converted into it's decimal representation
 * e.g. 7F into 127
 *
 * @param a_hex hexadecimal string to convert
 *
 * @returns decimal representation of supplied hex string
 */
string hex_to_dec_string(const string &a_hex);

/**
 * @brief Converts a decimal integer into a hexadecimal string
 *
 * Converts the supplied decimal integer into it's hexadecimal representation.
 * e.g. 0x7F000001 from 2130706433
 *
 * @param a_dec decimal to be converted to a hexadecimal number string
 *
 * @return hexadecimal representation of the supplied decimal integer
 */
string dec_to_hex(unsigned int a_dec);

/**
 * @brief Converts an ipv4 address string to hex representation
 *
 * Converts an ipv4 address into it's hexadecimal representation
 * e.g. 0x7F000001 from 127.0.0.1
 *
 * @param a_ip ip address to convert
 *
 * @return hexadecimal representation of ipc4 string
 */
string ipv4_to_hex(const string& a_ip);

/**
 * @brief Encodes ipv4 string into single integer
 *
 * Encodes the supplied ipv4 address string (in format X.X.X.X) into a single integer
 * e.g. 127.0.0.1 into 2130706433
 *
 * @param a_ip ipv4 address to encode
 *
 * @returns encoded ipv4 string
 */
unsigned int ipv4_to_dec(const string &a_ip);

/**
 * @brief Decodes an integer into it's ipv4 address representation
 *
 * Decodes the supplied unsigned 32 bit integer into it's ipv4 address form
 * e.g. 2130706433 into 127.0.0.1
 *
 * @param ip integer to be decoded
 *
 * @returns ipv4 address string in X.X.X.X format
 */
string ipv4_to_str(unsigned int ip);

/**
 * @brief Returns the ipv4 string for the current computer's ip
 *
 * Returns the ipv4 string of the localhost loopback for the current computer.
 *
 * @return ipv4 address string in X.X.X.X format
 */
string my_ip();

#endif //SPLASHKIT_NETWORKING_H
