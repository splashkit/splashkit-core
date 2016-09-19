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
#include "hmacsha1.c"

namespace splashkit_lib
{
    
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

        string consumer_secret = "JdmKx1uYTFB5RL3Whbg6pyppQXGKt2NrHtmWQgWID37fWDaadb"
        string oath_token_secret = "gHT5YN7biHTVhOpK4AT4tsxZRVODDNL92iiAT8igE2FUf"
        
        string signing key = consumer_secret + "&" + oath_token_secret;
        return "";
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
