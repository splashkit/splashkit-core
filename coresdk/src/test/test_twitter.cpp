//
//  test_bundles.cpp
//  splashkit
//
//  Created by Andrew Cain on 29/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "twitter.h"
#include "utils.h"
#include <iostream>

using namespace std;
using namespace splashkit_lib;

void run_twitter_test()
{
    twitter_account account = load_twitter_account("jake", "twitter.json");
    tweet(account, "#hey hey so full! #killerkebabs #abrakebabra");
}
