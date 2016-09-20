//
//  twitter_driver.cpp
//  splashkit
//
//  Created by Jake Renzella on 20/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "twitter_driver.h"
#include "utility_functions.h"
#include <iomanip>

#ifdef __linux__
#include <string.h>
#endif

namespace splashkit_lib
{
    char* hextostr(const std::string& hexStr)
    {
        size_t len = hexStr.length();
        int k=0;
        if (len & 1) return NULL;
        
        char* output = new char[(len/2)+1];
        for (size_t i = 0; i < len; i+=2)
        {
            output[k++] = (((hexStr[i] >= 'A')? (hexStr[i] - 'A' + 10): (hexStr[i] - '0')) << 4) |
            (((hexStr[i+1] >= 'A')? (hexStr[i+1] - 'A' + 10): (hexStr[i+1] - '0')));
        }
        output[k] = '\0';
        return output;
    }
    
    static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
    
    
    std::string base64_encode(unsigned char const* bytes_to_encode, unsigned int in_len) {
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
