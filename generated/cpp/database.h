//
// SplashKit Generated Database C++ Code
// DO NOT MODIFY
//

#ifndef __database_h
#define __database_h

#include "database.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _database_data;
typedef struct _database_data *database;
struct _query_result_data;
typedef struct _query_result_data *query_result;
database database_named(string name);
void free_all_databases();
void free_all_query_results();
void free_database(database db_to_close);
void free_database(string name_of_db_to_close);
void free_query_result(query_result query);
bool get_next_row(query_result result);
bool has_database(string name);
bool has_row(query_result result);
database open_database(string name, string filename);
bool query_column_for_bool(query_result result, int col);
double query_column_for_double(query_result result, int col);
int query_column_for_int(query_result result, int col);
string query_column_for_string(query_result result, int col);
bool query_success(query_result result);
string query_type_of_col(query_result result, int col);
void reset_query_result(query_result result);
int rows_changed(database db);
query_result run_sql(database db, string sql);
query_result run_sql(string database_name, string sql);

#endif /* __database_h */
