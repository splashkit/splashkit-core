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
    query_result cursor;
    
    open_database("test1", "test_database");
    database db = database_named("test1");
    
    bool result = has_database("test1");
    cout << (result ? "Database Opened\n\n" : "Database Not Opened\n\n");
    

    cursor = run_sql(db, "DROP TABLE friends;");

    cursor = run_sql(db, "CREATE TABLE friends (id INTEGER PRIMARY KEY, name TEXT, age INTEGER, weight REAL, isStudent BOOL);");
    cursor = run_sql(db, "INSERT INTO friends VALUES (10001, \"Jake Renzella\", 21, 32.43, 1);");
    cursor = run_sql(db, "INSERT INTO friends VALUES (20002, \"Andrew Cain\", 19, 42.43, 0);");
    
    cout << "Testing garbage query..." << endl;
    
    cursor = run_sql("test1", "garbage_queryfkdsafjkdls :(");
    result = query_success(cursor);
    cout << (result ? "Query successful\n" : "Query unsuccessful\n");
    
    cout << "Testing good query..." << endl;
    cursor = run_sql("test1", "select * from friends;");
    result = query_success(cursor);
    cout << (result ? "Query successful\n" : "Query unsuccessful\n");
    
    cout << endl << endl;
    
    cout << "data in index 0 should be 10001 and is: " << query_column_for_int(cursor, 0) << endl;
    cout << "data in index 1 should be Jake Renzella and is: " << query_column_for_string(cursor, 1) << endl;
    cout << "data in index 2 should be 21 and is: " << query_column_for_int(cursor, 2) << endl;
    cout << "data in index 3 should be 32.43 and is: " << query_column_for_double(cursor, 3) << endl;
    cout << "data in index 4 should be true and is: " << query_column_for_bool(cursor, 4) << endl << endl;
    
    cout << "data type in index 0 should be INTEGER and is: " << query_type_of_col(cursor, 0) << endl;
    cout << "data type in index 1 should be TEXT and is: " << query_type_of_col(cursor, 1) << endl;
    cout << "data type in index 2 should be INTEGER and is: " << query_type_of_col(cursor, 2) << endl;
    cout << "data type in index 3 should be FLOAT and is: " << query_type_of_col(cursor, 3) << endl;
    cout << "data type in index 4 should be BOOL(INTEGER) and is: " << query_type_of_col(cursor, 4) << endl << endl;
    
    get_next_row(cursor);
    
    cout << "data in index 0 should be 20002 and is: " << query_column_for_int(cursor, 0) << endl;
    cout << "data in index 1 should be Andrew Cain and is: " << query_column_for_string(cursor, 1) << endl;
    cout << "data in index 2 should be 19 and is: " << query_column_for_int(cursor, 2) << endl;
    cout << "data in index 3 should be 42.43 and is: " << query_column_for_double(cursor, 3) << endl;
    cout << "data in index 4 should be false and is: " << query_column_for_bool(cursor, 4) << endl << endl;
    
    cout << "data type in index 0 should be INTEGER and is: " << query_type_of_col(cursor, 0) << endl;
    cout << "data type in index 1 should be TEXT and is: " << query_type_of_col(cursor, 1) << endl;
    cout << "data type in index 2 should be INTEGER and is: " << query_type_of_col(cursor, 2) << endl;
    cout << "data type in index 3 should be FLOAT and is: " << query_type_of_col(cursor, 3) << endl;
    cout << "data type in index 4 should be BOOL(INTEGER) and is: " << query_type_of_col(cursor, 4) << endl << endl;
    
    
    free_all_query_results();
    
    cout << "closing database" << endl;
    free_database("test1");
    
    result = has_database("test1");
    cout << (result ? "Database Opened\n" : "Database Not Opened\n");
}