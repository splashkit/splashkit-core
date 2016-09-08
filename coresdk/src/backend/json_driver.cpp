//
//  json_driver.cpp
//  splashkit
//
//  Created by James Armstrong & Jake Renzella on 03/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "json_driver.h"
namespace splashkit_lib
{
    void sk_delete_json(json j)
    {
        if (VALID_PTR(j, JSON_PTR))
        {
            j->id = NONE_PTR;
            delete j;
        }
    }
}