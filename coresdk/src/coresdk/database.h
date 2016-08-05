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

int rows_changed(database db);

int rows_changed(query_result result);

database open_database(string name, string filename);

query_result run_sql(database db, string sql);

query_result run_sql(string database_name, string sql);

void free_all_query_results();

void free_query_result(query_result query);

bool get_next_row(query_result result);

bool has_row(query_result result);

void reset_query_result(query_result result);

int query_column_for_int(query_result result, int col);

double query_column_for_double(query_result result, int col);

string query_column_for_string(query_result result, int col);

bool query_column_for_bool(query_result result, int col);

string query_type_of_col(query_result result, int col);

bool query_success(query_result result);

database open_database(string name, string filename);

void free_database(database db_to_close);

void free_database(string name_of_db_to_close);

void free_all_databases();

#endif /* database_h */