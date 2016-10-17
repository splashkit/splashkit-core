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

#include <string>
#include <map>
#include <vector>

namespace splashkit_lib
{
    http_response new_tweet(json parameters)
    {
        map<string, string> parameters_map = sk_json_to_map(parameters);
        
        parameters_map["http_method"] = "POST";
        parameters_map["http_url"] = "https://api.twitter.com/1.1/statuses/update.json";

        string post_content = "status=" + url_encode(parameters_map.at("status"));
        string url = parameters_map.at("http_url");
        
        vector<string> post_header {generate_authorization_header(parameters_map), "Content-Type: application/x-www-form-urlencoded"};

        http_response response = http_post(url, 443, post_content, post_header);
        return response;
    }
}
