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

using std::vector;
using std::map;

namespace splashkit_lib
{
    static map<string, database> _databases;
    static vector<query_result> _queries_vector;

    bool has_database(string name)
    {
        return _databases.count(name) > 0;
    }

    database database_named(string name)
    {
        if (has_database(name))
        {
            return _databases[name];
        }
        else
        {
            return nullptr;
        }
    }

    int rows_changed(database db)
    {
        if ( INVALID_PTR(db, DATABASE_PTR))
        {
            LOG(WARNING) << "Attempting to access rows changes on invalid database.";
            return 0;
        }

        return sk_rows_affected(db);
    }

    query_result run_sql(database db, string sql)
    {
        if ( INVALID_PTR(db, DATABASE_PTR))
        {
            LOG(WARNING) << "Attempting to run query on invalid database.";
            return nullptr;
        }

        sk_query_result temp_result = sk_prepare_statement(db, sql);

        query_result result = new sk_query_result();
        *result = temp_result;

        sk_step_statement(result);

        _queries_vector.push_back(result);

        return result;
    }
    
    string error_message(query_result query)
    {
        if ( INVALID_PTR(query, QUERY_PTR))
        {
            return "Attempting to get error message for invalid query result";
        }
        
        return sk_db_error_message(query);
    }

    query_result run_sql(string database_name, string sql)
    {
        return run_sql(database_named(database_name), sql);
    }

    void free_query_result(query_result query)
    {
        if ( INVALID_PTR(query, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to free invalid query.";
            return;
        }

        notify_of_free(query);

        vector<query_result>::iterator it;

        it = find (_queries_vector.begin(), _queries_vector.end(), query);
        if (it != _queries_vector.end())
        {
            auto index = std::distance(_queries_vector.begin(), it);
            sk_finalise_query(_queries_vector.at(index));
            _queries_vector.erase(it);
            delete(query);
        }
        else
        {
            LOG(WARNING) << "Not able to remove query as it is not found in _queries_vector\n";
        }
    }

    void free_all_query_results()
    {
        FREE_ALL_FROM_VECTOR(_queries_vector, QUERY_PTR, free_query_result);
        _queries_vector.clear();
    }

    bool get_next_row(query_result result)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to get next row.";
            return false;
        }
        if ( INVALID_PTR(result->_database, DATABASE_PTR))
        {
            LOG(WARNING) << "Attempting to get next row when database has been closed for this query";
            return false;
        }
        
        return sk_query_get_next_row(result);
    }

    bool has_row(query_result result)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to check has row.";
            return false;
        }

        return sk_query_has_data(result);
    }

    int query_column_count(query_result db_result)
    {
        if ( INVALID_PTR(db_result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query for column count.";
            return 0;
        }

        return sk_column_count(db_result);
    }

    void reset_query_result(query_result result)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to reset.";
            return;
        }
        if ( INVALID_PTR(result->_database, DATABASE_PTR))
        {
            LOG(WARNING) << "Attempting to reset query when database has been closed";
            return;
        }

        sk_reset_query_statement(result);
    }

    int query_column_for_int(query_result result, int col)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to read row.";
            return 0;
        }

        return sk_query_read_column_int(result, col);
    }

    double query_column_for_double(query_result result, int col)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to read row.";
            return 0;
        }

        return sk_query_read_column_double(result, col);
    }

    string query_column_for_string(query_result result, int col)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to read row.";
            return "";
        }

        return sk_query_read_column_text(result, col);
    }

    bool query_column_for_bool(query_result result, int col)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to read row.";
            return false;
        }

        return sk_query_read_column_bool(result, col);
    }

    string query_type_of_col(query_result result, int col)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to read row.";
            return "";
        }

        return sk_query_type_of_column(result, col);
    }

    bool query_success(query_result result)
    {
        if ( INVALID_PTR(result, QUERY_PTR))
        {
            LOG(WARNING) << "Attempting to access invalid query to read row.";
            return 0;
        }
        return sk_query_success(result);
    }

    database open_database(string name, string filename)
    {
        if (has_database(name)) return database_named(name);

        string file_path = path_to_resource(filename, DATABASE_RESOURCE);

        database result = new sk_database();

        if ( not sk_open_database(file_path, result) )
        {
            LOG(WARNING) << "Failed to open database " + file_path;
            delete result;
            return nullptr;
        }

        result->id = DATABASE_PTR;
        result->filename = file_path;
        result->name = name;

        _databases[name] = result;
        return result;
    }

    void free_database(database db_to_close)
    {
        if (VALID_PTR(db_to_close, DATABASE_PTR))
        {
            notify_of_free(db_to_close);

            _databases.erase(db_to_close->name);
            sk_close_database(db_to_close);
            db_to_close->id = NONE_PTR;  // ensure future use of this pointer will fail...
            delete(db_to_close);
        }
        else
        {
            LOG(WARNING) << "Delete sound effect called without valid sound effect";
        }
    }

    void free_database(string name_of_db_to_close)
    {
        free_database(database_named(name_of_db_to_close));
    }

    void free_all_databases()
    {
        FREE_ALL_FROM_MAP(_databases, DATABASE_PTR, free_database);
    }
}
