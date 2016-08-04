//
//  database.h
//  splashkit
//
//  Created by Jake Renzella on 2/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef database_h
#define database_h

#include <string>
using namespace std;

typedef struct _database *database;
typedef struct sk_query_result *query_result;

bool has_database(string name);

database database_named(string name);

database open_database(string name, string filename);

query_result run_sql(database db, string sql);

query_result run_sql(string database_name, string sql);

void free_all_query_results();

void free_query_result(query_result query);

void free_all_query_results();

void get_next_row(query_result result);

void reset_result_query(query_result result);

int query_column_for_int(query_result result, int col);

string query_column_for_string(query_result result, int col);

bool query_column_for_bool(query_result result, int col);

database open_database(string name, string filename);


#endif /* database_h */