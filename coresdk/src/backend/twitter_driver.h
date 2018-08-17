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
#include <map>

using std::string;
using std::vector;
using std::map;

namespace splashkit_lib
{
    string url_encode(const string &value);
    string generate_authorization_header(map<string, string> parameters_map);
}

#endif /* twitter_driver_h */
