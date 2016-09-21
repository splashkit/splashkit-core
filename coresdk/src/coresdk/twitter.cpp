//
//  twitter.cpp
//  splashkit
//
//  Created by Jake Renzella on 19/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//
#include "twitter.h"
#include "twitter_driver.h"
#include "web.h"
#include "json.h"

#include <sstream>
#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <vector>
#include <ctime>

namespace splashkit_lib
{
    string generate_unix_timestamp()
    {
        std::time_t result = std::time(nullptr);
        
        return to_string(result);
    }
    
    string collect_parameters(map<string, string> parameters_map)
    {
        string result = "";
        for (map<string, string>::iterator i = parameters_map.begin(); i != parameters_map.end(); i++)
        {
            result += i->first + "=" + i->second;
            if (parameters_map.rbegin()->first != i->first)
            {
                result += "&";
            }
        }
        return result;
    }
    
    string generate_signature(json parameters)
    {
        map<string, string> parameters_map;

        parameters_map.insert({url_encode("oauth_signature_method"), url_encode(json_read_string(parameters, "oauth_signature_method"))});
        parameters_map.insert({url_encode("status"), url_encode(json_read_string(parameters, "status"))});
        parameters_map.insert({url_encode("include_entities"), url_encode("true")});
        parameters_map.insert({url_encode("oauth_consumer_key"), url_encode(json_read_string(parameters, "oauth_consumer_key"))});
        parameters_map.insert({url_encode("oauth_nonce"), url_encode(json_read_string(parameters, "oauth_nonce"))});
        parameters_map.insert({url_encode("oauth_timestamp"), url_encode(json_read_string(parameters, "oauth_timestamp"))});
        parameters_map.insert({url_encode("oauth_token"), url_encode(json_read_string(parameters, "oauth_token"))});
        parameters_map.insert({url_encode("oauth_version"), url_encode(json_read_string(parameters, "oauth_version"))});

        string http_method = json_read_string(parameters, "http_method");
        string http_url = json_read_string(parameters, "http_url");
        
        string parameter_string = collect_parameters(parameters_map);

        string signature_base_string = http_method + "&" + url_encode(http_url) + "&" + url_encode(parameter_string);

        string consumer_secret = json_read_string(parameters, "oauth_consumer_secret");
        string oath_token_secret = json_read_string(parameters, "oauth_token_secret");

        string signing_key = url_encode(consumer_secret) + "&" + url_encode(oath_token_secret);

        std::string sha1hmac = hmac<SHA1>(signature_base_string, signing_key);

        auto sha1hmac_hex_decoded = HexToBytes(sha1hmac);
        auto to_encode = reinterpret_cast<unsigned const char*>(sha1hmac_hex_decoded.data());

        string encoded_result = base64_encode(to_encode, static_cast<unsigned int>(sha1hmac_hex_decoded.size()));
        return encoded_result;

    }

    string generate_authorization_header(json parameters)
    {
        // json_add_string(parameters, "oauth_consumer_key", "xvz1evFS4wEEPTGEFPHBog");                            //consumer key from twitter app api
        // json_add_string(parameters, "oauth_token", "370773112-GmHxMAgYyLbNEtIKZeRNFsMKPR9EyMZeS9weJAEb");       //given (oauth/access token)
        json_add_string(parameters, "oauth_nonce", generate_nonce());                                           //Uniquely generate this ourselves
        json_add_string(parameters, "oauth_signature_method", "HMAC-SHA1");                                     //generated
        json_add_string(parameters, "oauth_timestamp", generate_unix_timestamp());                                           //generated
        json_add_string(parameters, "oauth_version", "1.0");                                                    //generated
        json_add_string(parameters, "oauth_signature", generate_signature(parameters));                         //generated

        string DST = "OAuth ";
        DST += url_encode("oauth_consumer_key") + "=\"" + url_encode(json_read_string(parameters, "oauth_consumer_key")) + "\", ";
        DST += url_encode("oauth_nonce") + "=\"" + url_encode(json_read_string(parameters, "oauth_nonce")) + "\", ";
        DST += url_encode("oauth_signature") + "=\"" + url_encode(json_read_string(parameters, "oauth_signature")) + "\", ";
        DST += url_encode("oauth_signature_method") + "=\"" + url_encode(json_read_string(parameters, "oauth_signature_method")) + "\", ";
        DST += url_encode("oauth_timestamp") + "=\"" + url_encode(json_read_string(parameters, "oauth_timestamp")) + "\", ";
        DST += url_encode("oauth_token") + "=\"" + url_encode(json_read_string(parameters, "oauth_token")) + "\", ";
        DST += url_encode("oauth_version") + "=\"" + url_encode(json_read_string(parameters, "oauth_version")) + "\"";

        return DST;

    }

    void new_tweet(json parameters)
    {
        //parameters should have oauth_consumer_key, oauth_token, status NEEDS TO BE IN HERE
        json_add_string(parameters, "http_method", "POST");
        json_add_string(parameters, "http_url", "https://api.twitter.com/1.1/statuses/update.json");
        
        stringstream ss;

        string content = "status=" + json_read_string(parameters, "status");
        string url = json_read_string(parameters, "http_url");
        vector<string> headers;
        
        /*
        headers.push_back("Authorization:"
                                  "OAuth oauth_consumer_key=\"VlU5u3eZD8O9FLLjCJ7X7SZCm\", "
                                  "oauth_nonce=\"2f51578d75e905ec9da75bfadb0f894c\", "
                                  "oauth_signature=\"623Ji28W1v4eN6FIOzJhxobNvlo%3D\", "
                                  "oauth_signature_method=\"HMAC-SHA1\", "
                                  "oauth_timestamp=\"1474457494\", "
                                  "oauth_token=\"777822290318757888-ZTefOHbqKd1huzc7cf5BLDZwfT36rgG\", "
                                  "oauth_version=\"1.0\"");
         */
        headers.push_back(generate_authorization_header(parameters));
        headers.push_back("Content-Type: application/x-www-form-urlencoded");

        http_response response = http_post(url, 443, content, headers);

        cout << "response is: " << http_response_to_string(response) << endl;
    }
}
