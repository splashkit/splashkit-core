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
#include "json.h"

using namespace std;
using namespace splashkit_lib;

void run_twitter_test()
{
    json test = create_json();
    // generate_authorization_header(test);
    new_tweet("her");
}
