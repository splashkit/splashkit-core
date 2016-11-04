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
#include "resources.h"

#include <string>
#include <map>
#include <vector>

namespace splashkit_lib
{
    struct _twitter_account
    {
        pointer_identifier id;
        json account_details;
    };

    static map<string, twitter_account> _twitter_accounts;

    bool has_twitter_account(const string &name)
    {
        return _twitter_accounts.count(name) > 0;
    }

    twitter_account twitter_account_named(const string &name)
    {
        if ( has_twitter_account(name) )
            return _twitter_accounts[name];
        else
        {
            string filename = path_to_resource(name, JSON_RESOURCE);

            if ( file_exists(filename) or file_exists(name) )
                return load_twitter_account(name, name);
            return nullptr;
        }
    }

    twitter_account load_twitter_account(const string &name, const string &filename)
    {
        if ( has_twitter_account(name) ) return twitter_account_named(name);

        string file_path = filename;

        if ( ! file_exists(file_path) )
        {
            file_path = path_to_resource(filename, JSON_RESOURCE);

            if ( ! file_exists(file_path) )
            {
                LOG(WARNING) << cat({ "Unable to locate file for twitter account ", name, " (", file_path, ")"});
                return nullptr;
            }
        }

        twitter_account result = new _twitter_account;

        result->id = TWITTER_PTR;
        result->account_details = json_from_file(filename);

        _twitter_accounts[name] = result;

        return result;
    }

    http_response tweet(twitter_account account, const string &message)
    {
        if ( INVALID_PTR(account, TWITTER_PTR) )
        {
            LOG(WARNING) << "Invalid twitter account for tweet";
            return nullptr;
        }

        map<string, string> parameters_map = sk_json_to_map(account->account_details);
        
        parameters_map["http_method"] = "POST";
        parameters_map["http_url"] = "https://api.twitter.com/1.1/statuses/update.json";

        string post_content = "status=" + url_encode(message);
        string url = parameters_map.at("http_url");

        vector<string> post_header {
            generate_authorization_header(parameters_map),
            "Content-Type: application/x-www-form-urlencoded"
        };

        http_response response = http_post(url, 443, post_content, post_header);
        return response;
    }
}
