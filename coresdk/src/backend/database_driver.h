//
//  database_driver.h
//  splashkit
//
//  Created by Jake Renzella on 2/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef database_driver_h
#define database_driver_h

#include <string>
using namespace std;

struct sk_database
{
    // private data used by backend
    void* _data;
};

struct sk_query_result
{
    void *_stmt;
    int _result;
};

sk_database sk_load_database(string db_file_name);

sk_query_result sk_prepare_statement(sk_database db, string sql);

#endif /* database_driver_h */