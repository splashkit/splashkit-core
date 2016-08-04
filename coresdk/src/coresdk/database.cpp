//
//  database.cpp
//  splashkit
//
//  Created by Jake Renzella on 2/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "database.h"
#include "database_driver.h"
#include "resources.h"
#include "backend_types.h"
#include "utility_functions.h"

#include <vector>
#include <algorithm>
#include <iostream>
#include <map>

using namespace std;

static map<string, database> _databases;
static vector<query_result> _queries_vector;

struct _database
{
    pointer_identifier id;
    sk_database database;
    string filename, name;
};

bool has_database(string name)
{
    return _databases.count(name) > 0;
}

database database_named(string name)
{
    if (has_database(name))
        return _databases[name];
    else
        return nullptr;
}

query_result run_sql(database db, string sql)
{
    sk_query_result temp_result = sk_prepare_statement(db->database, sql);

    query_result result = new sk_query_result();
    *result = temp_result;
    
    _queries_vector.push_back(result);
    
    return result;
}

query_result run_sql(string database_name, string sql)
{
    return run_sql(database_named(database_name), sql);
}

void free_query_result(query_result query)
{
    std::vector<query_result>::iterator it;
    
    it = find (_queries_vector.begin(), _queries_vector.end(), query);
    if (it != _queries_vector.end())
    {
        auto index = std::distance(_queries_vector.begin(), it);
        sk_finalise_query(*_queries_vector.at(index));
        _queries_vector.erase(it);
        //delete(query);
    }
    else
    {
        raise_warning("Not able to remove query as it is not found in _queries_vector\n");
    }
}

void free_all_query_results()
{
    
    auto it = std::begin(_queries_vector);
    
    while (it != std::end(_queries_vector))
    {
        auto index = std::distance(_queries_vector.begin(), it);
        free_query_result(_queries_vector.at(index));
    }

    _queries_vector.clear();
}

void get_next_row(query_result result)
{
    sk_query_get_next_row(*result);
}

void reset_result_query(query_result result)
{
    sk_reset_query_statement(*result);
}

int query_column_for_int(query_result result, int col)
{
    return sk_query_read_column_int(*result, col);
}

string query_column_for_string(query_result result, int col)
{
    return sk_query_read_column_text(*result, col);
}

bool query_column_for_bool(query_result result, int col)
{
    return sk_query_read_column_bool(*result, col);
}

database open_database(string name, string filename)
{
    if (has_database(name)) return database_named(name);
    
    string file_path = path_to_resource(filename, DATABASE_RESOURCE);
    
    database result = new _database();
    
    result->id = DATABASE_PTR;
    result->filename = file_path;
    result->name = name;
    result->database = sk_open_database(file_path);
    
    // Unable to load database
    if ( ! result->database._data )
    {
        result->id = NONE_PTR;
        delete result;
        raise_warning ( cat({ "Error loading database ", name, " at (", file_path, ")"}) );
        return nullptr;
    }
    
    _databases[name] = result;
    return result;
}