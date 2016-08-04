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

sk_database sk_open_database(string db_file_name);

int sk_close_database(sk_database db);

sk_query_result sk_prepare_statement(sk_database db, string sql);

bool sk_query_has_data(sk_query_result result);

bool sk_query_success(sk_query_result result);

bool sk_query_get_next_row(sk_query_result result);

void sk_reset_query_statement(sk_query_result result);

int sk_query_read_column_int(sk_query_result result, int col);

string sk_query_read_column_text(sk_query_result result, int col);

void sk_finalise_query(sk_query_result result);

bool sk_query_read_column_bool(sk_query_result result, int col);

#endif /* database_driver_h */