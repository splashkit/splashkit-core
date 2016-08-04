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
    
    cursor = run_sql(db, "DROP TABLE friends;");

    cursor = run_sql(db, "CREATE TABLE friends (id INTEGER PRIMARY KEY, name TEXT, age INTEGER, weight REAL, isStudent BOOL);");
    cursor = run_sql(db, "INSERT INTO friends VALUES (10001, \"Jake Renzella\", 21, 32.43, 1);");
    
    cursor = run_sql("test1", "select * from friends;");
    
    cout << "data in index 0 should be 10001 and is: " << query_column_for_int(cursor, 0) << endl;
    cout << "data in index 1 should be Jake Renzella and is: " << query_column_for_string(cursor, 1) << endl;
    cout << "data in index 2 should be 21 and is: " << query_column_for_int(cursor, 2) << endl;
    cout << "data in index 3 should be 32.43 and is: " << query_column_for_int(cursor, 3) << endl;
    cout << "data in index 4 should be true and is: " << query_column_for_bool(cursor, 4) << endl;
    
    free_all_query_results();
}