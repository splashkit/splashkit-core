//
//  twitter_driver.cpp
//  splashkit
//
//  Created by Jake Renzella on 20/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "twitter_driver.h"
#include "utility_functions.h"
#include <random>
#include <iomanip>

#ifdef __linux__
#include <string.h>
#endif

namespace splashkit_lib
{
    
    std::vector<char> HexToBytes(const std::string& hex) {
        std::vector<char> bytes;
        
        for (unsigned int i = 0; i < hex.length(); i += 2) {
            std::string byteString = hex.substr(i, 2);
            char byte = (char) strtol(byteString.c_str(), NULL, 16);
            bytes.push_back(byte);
        }
        
        return bytes;
    }
    
    static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
    
    
    std::string base64_encode(const unsigned char* bytes_to_encode, unsigned int in_len) {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];
        
        while (in_len--) {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3) {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;
                
                for(i = 0; (i <4) ; i++)
                    ret += base64_chars[char_array_4[i]];
                i = 0;
            }
        }
        
        if (i)
        {
            for(j = i; j < 3; j++)
                char_array_3[j] = '\0';
            
            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;
            
            for (j = 0; (j < i + 1); j++)
                ret += base64_chars[char_array_4[j]];
            
            while((i++ < 3))
                ret += '=';
            
        }
        
        return ret;
    }
    
    string generate_nonce()
    {
        
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, RAND_MAX);
        
        static const char alphanum[] =
        "0123456789"
        "!@#$%^&*"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";
        
        int stringLength = sizeof(alphanum) - 1;
        string result = "";
        for (int i = 0; i<32; i++)
        {
            result += alphanum[dis(gen) % stringLength];

        }
        
        return base64_encode((const unsigned char*)result.c_str(), 32);
    }
    
    string url_encode(const string &value) {
        ostringstream escaped;
        escaped.fill('0');
        escaped << hex;
        
        for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
            string::value_type c = (*i);
            
            // Keep alphanumeric and other accepted characters intact
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
                continue;
            }
            
            // Any other characters are percent-encoded
            escaped << uppercase;
            escaped << '%' << setw(2) << int((unsigned char) c);
            escaped << nouppercase;
        }
        
        return escaped.str();
    }
}
