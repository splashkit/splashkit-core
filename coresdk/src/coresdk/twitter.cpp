//
//  twitter.cpp
//  splashkit
//
//  Created by Jake Renzella on 19/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//
#include "twitter.h"
#include "twitter_driver.h"

#include "json.h"
#include "json_driver.h"

#include <iomanip>
#include <iostream>
#include <string>
#include <map>
#include <stdio.h>
#include <vector>


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
    
    string generate_signature(map<string, string> parameters_map)
    {
        map<string, string> encoded_parameters_map;

        encoded_parameters_map.insert({url_encode("oauth_signature_method"), url_encode(parameters_map.at("oauth_signature_method"))});
        encoded_parameters_map.insert({url_encode("status"), url_encode(parameters_map.at("status"))});
        encoded_parameters_map.insert({url_encode("oauth_consumer_key"), url_encode(parameters_map.at("oauth_consumer_key"))});
        encoded_parameters_map.insert({url_encode("oauth_nonce"), url_encode(parameters_map.at("oauth_nonce"))});
        encoded_parameters_map.insert({url_encode("oauth_timestamp"), url_encode(parameters_map.at("oauth_timestamp"))});
        encoded_parameters_map.insert({url_encode("oauth_token"), url_encode(parameters_map.at("oauth_token"))});
        encoded_parameters_map.insert({url_encode("oauth_version"), url_encode(parameters_map.at("oauth_version"))});

        string http_method = parameters_map.at("http_method");
        string http_url = parameters_map.at("http_url");
        string parameter_string = collect_parameters(encoded_parameters_map);
        string signature_base_string = http_method + "&" + url_encode(http_url) + "&" + url_encode(parameter_string);
        string consumer_secret = parameters_map.at("oauth_consumer_secret");
        string oath_token_secret = parameters_map.at("oauth_token_secret");
        string signing_key = url_encode(consumer_secret) + "&" + url_encode(oath_token_secret);

        string sha1hmac = hmac<SHA1>(signature_base_string, signing_key);

        auto sha1hmac_hex_decoded = HexToBytes(sha1hmac);
        unsigned const char* to_encode = reinterpret_cast<unsigned const char*>(sha1hmac_hex_decoded.data());

        string encoded_result = base64_encode(to_encode, static_cast<unsigned int>(sha1hmac_hex_decoded.size()));
        return encoded_result;

    }

    string generate_authorization_header(map<string, string> parameters_map)
    {
        parameters_map["oauth_nonce"] = generate_nonce();
        parameters_map["oauth_signature_method"] = "HMAC-SHA1";
        parameters_map["oauth_timestamp"] = generate_unix_timestamp();
        parameters_map["oauth_version"] = "1.0";
        parameters_map["oauth_signature"] = generate_signature(parameters_map);

        string DST = "Authorization:OAuth ";
        DST += url_encode("oauth_consumer_key") + "=\"" + url_encode(parameters_map.at("oauth_consumer_key")) + "\", ";
        DST += url_encode("oauth_nonce") + "=\"" + url_encode(parameters_map.at("oauth_nonce")) + "\", ";
        DST += url_encode("oauth_signature") + "=\"" + url_encode(parameters_map.at("oauth_signature")) + "\", ";
        DST += url_encode("oauth_signature_method") + "=\"" + url_encode(parameters_map.at("oauth_signature_method")) + "\", ";
        DST += url_encode("oauth_timestamp") + "=\"" + url_encode(parameters_map.at("oauth_timestamp")) + "\", ";
        DST += url_encode("oauth_token") + "=\"" + url_encode(parameters_map.at("oauth_token")) + "\", ";
        DST += url_encode("oauth_version") + "=\"" + url_encode(parameters_map.at("oauth_version")) + "\"";

        return DST;
    }

    http_response new_tweet(json parameters)
    {
        map<string, string> parameters_map = sk_json_to_map(parameters);
        
        parameters_map["http_method"] = "POST";
        parameters_map["http_url"] = "https://api.twitter.com/1.1/statuses/update.json";

        string status_content = "status=" + url_encode(parameters_map.at("status"));
        string url = parameters_map.at("http_url");
        
        vector<string> headers {generate_authorization_header(parameters_map), "Content-Type: application/x-www-form-urlencoded"};

        http_response response = http_post(url, 443, status_content, headers);
        return response;
    }
}
