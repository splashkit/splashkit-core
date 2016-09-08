#ifndef SPLASHKIT_NETWORKING_H
#define SPLASHKIT_NETWORKING_H

#include <string>
#include "types.h"

using namespace std;

/**
 * @brief Converts a hexadecimal ipv4 string to standard ipv4 address string x.x.x.x
 *
 * The supplied hexadecimal string is translated into ipv4 standard address string
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

#endif //SPLASHKIT_NETWORKING_H
