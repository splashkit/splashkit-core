//
//  twitter.cpp
//  splashkit
//
//  Created by Jake Renzella on 19/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "twitter.h"
#include "web.h"
#include "json.h"
#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include "/Users/jakerenzella/Repos/splashkit/coresdk/external/hmacsha1.c"

namespace splashkit_lib
{
    
    static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";
    
    
   // static inline bool is_base64(unsigned char c) {
  //      return (isalnum(c) || (c == '+') || (c == '/'));
  //  }
    
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
    
    
    string generate_signature()
    {
        map<string, string> parameters_map;
        string result = "";
        
        json signature = create_json("twitter signature");
        
        json_add_string(signature, "http_method", "POST");
        json_add_string(signature, "http_url", "https://api.twitter.com/1/statuses/update.json");
        
        parameters_map.insert({url_encode("oauth_signature_method"), url_encode("HMAC-SHA1")});
        parameters_map.insert({url_encode("status"), url_encode("Hello Ladies + Gentlemen, a signed OAuth request!")});
        parameters_map.insert({url_encode("include_entities"), url_encode("true")});
        parameters_map.insert({url_encode("oauth_consumer_key"), url_encode("xvz1evFS4wEEPTGEFPHBog")});
        parameters_map.insert({url_encode("oauth_nonce"), url_encode("kYjzVBB8Y0ZFabxSWbWovY3uYSQ2pTgmZeNu2VS4cg")});
        parameters_map.insert({url_encode("oauth_signature_method"), url_encode("HMAC-SHA1")});
        parameters_map.insert({url_encode("oauth_timestamp"), url_encode("1318622958")});
        parameters_map.insert({url_encode("oauth_token"), url_encode("370773112-GmHxMAgYyLbNEtIKZeRNFsMKPR9EyMZeS9weJAEb")});
        parameters_map.insert({url_encode("oauth_version"), url_encode("1.0")});
        
        for (map<string, string>::iterator i = parameters_map.begin(); i != parameters_map.end(); i++)
        {
            result += i->first + "=" + i->second;
            if (parameters_map.rbegin()->first != i->first)
            {
                result += "&";
            }
        }
        
        json_add_string(signature, "param_collection", result);
        
        string http_method = json_read_string(signature, "http_method");
        string http_url = url_encode(json_read_string(signature, "http_url"));
        string parameter_string = url_encode(json_read_string(signature, "param_collection"));
        
        string signature_base_string = http_method + "&" + http_url + "&" + parameter_string;
        //unsigned char* signature_base_string_charstar = (unsigned char *)(signature_base_string.c_str());
        
        unsigned char *signature_base_string_charstar=new unsigned char[signature_base_string.length()+1];
        strcpy((char *)signature_base_string_charstar,signature_base_string.c_str());

        string consumer_secret = "kAcSOqF21Fu85e7zjz7ZN2U4ZRhfV3WpwPAoE3Z7kBw";
        string oath_token_secret = "LswwdoUaIvS8ltyTt5jkRh4J50vUPVVHtR2YPi5kE";
        
        string signing_key = consumer_secret + "&" + oath_token_secret;
        
        unsigned char *signing_key_charstar=new unsigned char[signing_key.length()+1];
        strcpy((char *)signing_key_charstar,signing_key.c_str());
        
        //unsigned char *signing_key_charstar = (unsigned char *)(signing_key.c_str());
        unsigned char digest[20];
        
        hmac_sha1(
                    signing_key_charstar,
                    static_cast< int >(strlen((char*)signing_key_charstar)),
                    signature_base_string_charstar,
                    static_cast< int >(strlen((char*)signature_base_string_charstar)),
                    digest
                  );
        

        string encoded_result = base64_encode(static_cast<unsigned char const*>(digest), 20);
        return encoded_result;
    }
    
    void generate_header(json parameters)
    {
        json header = create_json("twitter header");
        json_add_string(header, "oauth_consumer_key", "xvz1evFS4wEEPTGEFPHBog");    //consumer key from twitter app api
        json_add_string(header, "oauth_nonce", "xvz1evFS4wEEPTGEFPHBog");           //Uniquely generate this ourselves
        json_add_string(header, "oauth_signature", generate_signature());           //The signature beast
        
    }
    
    void authenticate()
    {
        
    }
    
    void new_tweet(string status)
    {
        json http_request = create_json("http request");
        
        json_add_string(http_request, "status", status);
        json_add_string(http_request, "url", "https://api.twitter.com/1/statuses/update.json");
        
    
       // response = http_post("https://api.twitter.com/1.1/statuses/update.json?status=Posting%20from%20%40SplashKit&display_coordinates=false HTTP/1.1", 8080, string body);
    }
}
