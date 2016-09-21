//
//  twitter.hpp
//  splashkit
//
//  Created by Jake Renzella on 19/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef twitter_hpp
#define twitter_hpp

#include <stdio.h>
//#include "/Users/jakerenzella/Repos/splashkit/coresdk/external/hash-library/hmac.h"
//#include "/Users/jakerenzella/Repos/splashkit/coresdk/external/hash-library/sha1.h"
#include <string>
using namespace std;

#endif /* twitter_h */
namespace splashkit_lib
{
    string generate_signature();
    void new_tweet(string status);
}
