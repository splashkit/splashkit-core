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
    
    query_result cursor;
    
    cursor = run_sql(db, "DROP TABLE t;");
    cursor = run_sql(db, "CREATE TABLE t(x INTEGER PRIMARY KEY ASC, y, z);");
    cursor = run_sql(db, "INSERT INTO t VALUES (10001, 20002, 30003);");
    
    cursor = run_sql(db, "select * from t");
    
    printf("data in index 0 should be 10001 and is: %d\n", query_column_for_int(cursor, 0));
    printf("data in index 1 should be 20002 and is: %d\n", query_column_for_int(cursor, 1));
    printf("data in index 2 should be 30003 and is: %d\n", query_column_for_int(cursor, 2));
    
    free_all_query_results();
}