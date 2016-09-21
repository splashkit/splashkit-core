//
//  twitter_driver.hpp
//  splashkit
//
//  Created by Jake Renzella on 20/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef twitter_driver_h
#define twitter_driver_h

#include <stdio.h>
#include <string>
#include <vector>
using namespace std;

namespace splashkit_lib
{
    char* hextostr(const std::string& hexStr);
    std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len);
    string url_encode(const string &value);
    string generate_nonce();
    void hex2bin(const char* src, char* target);
    std::vector<char> HexToBytes(const std::string& hex);
    
}

#endif /* twitter_driver_h */
