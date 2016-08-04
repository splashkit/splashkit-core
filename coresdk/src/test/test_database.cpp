//
//  test_database.cpp
//  splashkit
//
//  Created by Jake Renzella on 3/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "test_database.hpp"
#include "database.h"
#include "utils_driver.h"
#include <iostream>
using namespace std;

void run_database_tests()
{
    open_database("test1", "test_database");
    database db = database_named("test1");
    
    bool result = has_database("test1");
    printf(result ? "Database Opened\n" : "Database Not Opened\n");
    
    run_sql(db, "CREATE TABLE t(x INTEGER PRIMARY KEY ASC, y, z);");
}