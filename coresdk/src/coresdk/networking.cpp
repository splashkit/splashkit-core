#include <sstream>
#include <cmath>
#include "networking.h"

string hex_str_to_ipv4(const string &a_hex) {
    stringstream ipv4_string;
    ipv4_string << hex_to_dec_string(a_hex.substr(2,2));
    ipv4_string << "." << hex_to_dec_string(a_hex.substr(4,2));
    ipv4_string << "."<< hex_to_dec_string(a_hex.substr(6,2));
    ipv4_string << "." << hex_to_dec_string(a_hex.substr(8,2));
    return ipv4_string.str();
}

string hex_to_dec_string(const string &a_hex) {
    int dec = 0;
    for (int i = 0; i < a_hex.length(); i++) {
        int c_val = 0;
        if (a_hex[i] - '0' < 10)
        {
            c_val = a_hex[i] - '0';
        }
        else if (a_hex[i] - 'A' < 6)
        {
            c_val = (a_hex[i] - 'A') + 10;
        }
        dec += c_val * pow(16, (a_hex.length() - i - 1));
    }
    return to_string(dec);
}

unsigned int ipv4_to_dec(const string &a_ip) {
    string::size_type lastpos = 0;
    unsigned int result = 0;
    for(unsigned int i = 0; i < 4; i++)
    {
        string::size_type pos = a_ip.find('.', lastpos);
        string token = pos == -1 ? a_ip.substr(lastpos) : a_ip.substr(lastpos, pos - lastpos);

        result += stoi(token) << (3 - i) * 8;
        lastpos = pos + 1;
    }

    return result;
}

string ipv4_to_str(uint32_t ip) {
    stringstream ip_string;
    ip_string << ((ip >> 24) & 0xFF) << ".";
    ip_string << ((ip >> 16) & 0xFF) << ".";
    ip_string << ((ip >> 8) & 0xFF) << ".";
    ip_string << (ip & 0xFF);
    return ip_string.str();
}
