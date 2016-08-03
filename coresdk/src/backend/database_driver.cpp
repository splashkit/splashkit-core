//
//  database_driver.cpp
//  splashkit
//
//  Created by Jake Renzella on 2/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "database_driver.h"

sk_database sk_load_database(string db_file_path)
{
    sk_database result;
    int rc;

    rc = sqlite3_open(db_file_path.c_str(), &result._data);
    if( rc )
    {
        // fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(result._data);
    }
    return result;
}