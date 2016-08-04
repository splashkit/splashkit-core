//
//  database_driver.cpp
//  splashkit
//
//  Created by Jake Renzella on 2/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include <sqlite3.h>
#include "utility_functions.h"
#include "database_driver.h"

sqlite3 *sqlite3_from_void(void *ptr)
{
    return static_cast<sqlite3*>(ptr);
}

sqlite3_stmt *sqlite3_stmt_from_void(void *ptr)
{
    return static_cast<sqlite3_stmt*>(ptr);
}

sk_database sk_open_database(string db_file_path)
{
    sk_database result;
    int rc;
    sqlite3 *data;

    rc = sqlite3_open_v2(db_file_path.c_str(), &data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);
    
    if (rc)
    {
        // fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(data);
    }
    result._data = data;
    
    return result;
}

int sk_close_database(sk_database db)
{
    int rc = sqlite3_close_v2(sqlite3_from_void(db._data));
    if (rc != SQLITE_OK)
    {
        raise_warning("Could not close database");
    }
    return rc;
}

sk_query_result sk_prepare_statement(sk_database db, string sql)
{
    const char* sql_char = sql.c_str();
    int size_sql_inc_null = static_cast<int>(strlen(sql_char) + 1);
    
    sqlite3 *data = sqlite3_from_void(db._data);
    sqlite3_stmt *statement;
    
    sk_query_result result = { NULL } ;
    
    result._result = sqlite3_prepare_v2(data, sql_char, size_sql_inc_null, &statement, nullptr);
    result._stmt = statement;
    
    if (result._result == SQLITE_OK)
    {
        result._result = sqlite3_step(statement);
    }
    
    return result;
}

bool sk_query_has_data(sk_query_result result)
{
    return result._result == SQLITE_ROW;
}

bool sk_query_success(sk_query_result result)
{
    return result._result == SQLITE_ROW || result._result == SQLITE_OK || result._result == SQLITE_DONE;
}

bool sk_query_get_next_row(sk_query_result result)
{
    if (result._result == SQLITE_ROW)
    {
        sqlite3_stmt *stmt = sqlite3_stmt_from_void(result._stmt);
        result._result = sqlite3_step(stmt);
        return true;
    }
    raise_warning("Attempt to read a row from a query without data");
    return false;
}

void sk_reset_query_statement(sk_query_result result)
{
    sqlite3_reset(sqlite3_stmt_from_void(result._stmt));
}

int sk_query_read_column_int(sk_query_result result, int col)
{
    if (result._result == SQLITE_ROW)
    {
        return sqlite3_column_int(sqlite3_stmt_from_void(result._stmt), col);
    }
    
    raise_warning("Failed to read column as int");
    return false;
}

double sk_query_read_column_double(sk_query_result result, int col)
{
    if (result._result == SQLITE_ROW)
    {
        return sqlite3_column_double(sqlite3_stmt_from_void(result._stmt), col);
    }
    
    raise_warning("Failed to read double from column");
    return false;
}

string sk_query_read_column_text(sk_query_result result, int col)
{
    if (result._result == SQLITE_ROW)
    {
        const unsigned char* data = sqlite3_column_text(sqlite3_stmt_from_void(result._stmt), col);
        return string(reinterpret_cast<const char *>(data));
    }
    raise_warning("Failed to read column as text");
    return "";
}

void sk_finalise_query(sk_query_result result)
{
    int rc = sqlite3_finalize(sqlite3_stmt_from_void(result._stmt));
    if (rc != SQLITE_OK)
    {
        raise_warning("Failed to finalise query statement");
    }
}


string sk_query_type_of_column(sk_query_result result, int col)
{
    if (result._result == SQLITE_ROW)
    {
        int data = sqlite3_column_type(sqlite3_stmt_from_void(result._stmt), col);
        
        switch(data)
        {
            case 1 :
                return "INTEGER";
                break;
            case 2 :
                return "FLOAT";
                break;
            case 3 :
                return "TEXT";
                break;
            case 5 :
                return "NULL";
                break;
            default :
                raise_warning("Unkown type in column");
        }
    }
    raise_warning("Failed to read type of column");
    return "";
}

bool sk_query_read_column_bool(sk_query_result result, int col)
{
    if (result._result == SQLITE_ROW)
    {
        return sqlite3_column_int(sqlite3_stmt_from_void(result._stmt), col) != 0;
    }
    
    raise_warning("Failed to read column as boolean");
    return false;
}