/**
* @header  twitter
* @author  Jake Renzella
* @brief   SplashKit provides functionality to post material to twitter
*
* @attribute group  social
* @attribute static twitter
 */


//
//  twitter.hpp
//  splashkit
//
//  Created by Jake Renzella on 19/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef twitter_hpp
#define twitter_hpp

#include "json.h"
#include "web_client.h"

#include <string>
using std::string;

#endif /* twitter_h */
namespace splashkit_lib
{
    string generate_signature();
    http_response new_tweet(json parameters);
}
