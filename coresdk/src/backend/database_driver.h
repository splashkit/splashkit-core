//
//  database_driver.h
//  splashkit
//
//  Created by Jake Renzella on 2/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef database_driver_h
#define database_driver_h

#include "sqlite3.h"
#include <string>
using namespace std;

typedef struct sk_database
{
    // private data used by backend
    sqlite3* _data;
} sk_database;

sk_database sk_load_database(string db_file_name);

#endif /* database_driver_h */