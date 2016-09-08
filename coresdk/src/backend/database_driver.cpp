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
#include <cstring>

#ifdef __linux__
#include <string.h>
#endif
namespace splashkit_lib
{
    sqlite3 *sqlite3_from_void(void *ptr)
    {
        return static_cast<sqlite3*>(ptr);
    }

    sqlite3_stmt *sqlite3_stmt_from_void(void *ptr)
    {
        return static_cast<sqlite3_stmt*>(ptr);
    }

    bool sk_open_database(string db_file_path, sk_database *result)
    {
        int rc;
        sqlite3 *data;

        rc = sqlite3_open_v2(db_file_path.c_str(), &data, SQLITE_OPEN_READWRITE | SQLITE_OPEN_CREATE, NULL);

        if (rc)
        {
            // fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(db));
            sqlite3_close(data);
            result->_data = nullptr;
            return false;
        }
        else
        {
            result->_data = data;
            return true;
        }
    }

    int sk_close_database(sk_database *db)
    {
        int rc = sqlite3_close_v2(sqlite3_from_void(db->_data));
        if (rc != SQLITE_OK)
        {
            LOG(WARNING) << "Could not close database";
        }
        return rc;
    }

    int sk_step_statement(sk_query_result *result)
    {
        sqlite3_stmt *stmt = sqlite3_stmt_from_void(result->_stmt);
        return result->_result = sqlite3_step(stmt);
    }

    sk_query_result sk_prepare_statement(sk_database *db, string sql)
    {
        const char* sql_char = sql.c_str();
        int size_sql_inc_null = static_cast<int>(strlen(sql_char) + 1);

        sqlite3 *data = sqlite3_from_void(db->_data);
        sqlite3_stmt *statement;

        sk_query_result result;

        result._result = sqlite3_prepare_v2(data, sql_char, size_sql_inc_null, &statement, nullptr);
        result._stmt = statement;
        result.id = QUERY_PTR;
        return result;
    }

    bool sk_query_has_data(sk_query_result *result)
    {
        return result->_result == SQLITE_ROW;
    }

    bool sk_query_success(sk_query_result *result)
    {
        return result->_result == SQLITE_ROW || result->_result == SQLITE_OK || result->_result == SQLITE_DONE;
    }

    int sk_rows_affected(sk_database *db)
    {
        return sqlite3_changes(sqlite3_from_void(db->_data));
    }

    bool sk_query_get_next_row(sk_query_result *result)
    {
        sk_step_statement(result);
        return sk_query_has_data(result);
    }

    void sk_reset_query_statement(sk_query_result *result)
    {
        sqlite3_reset(sqlite3_stmt_from_void(result->_stmt));
        sk_step_statement(result);
    }

    int sk_query_read_column_int(sk_query_result *result, int col)
    {
        if (result->_result == SQLITE_ROW)
        {
            return sqlite3_column_int(sqlite3_stmt_from_void(result->_stmt), col);
        }

        LOG(WARNING) << "Failed to read column as int";
        return 0;
    }

    double sk_query_read_column_double(sk_query_result *result, int col)
    {
        if (result->_result == SQLITE_ROW)
        {
            return sqlite3_column_double(sqlite3_stmt_from_void(result->_stmt), col);
        }

        LOG(WARNING) << "Failed to read double from column";
        return 0.0;
    }

    string sk_query_read_column_text(sk_query_result *result, int col)
    {
        if (result->_result == SQLITE_ROW)
        {
            const unsigned char* data = sqlite3_column_text(sqlite3_stmt_from_void(result->_stmt), col);
            return string(reinterpret_cast<const char *>(data));
        }
        LOG(WARNING) << "Failed to read column as text";
        return "";
    }

    void sk_finalise_query(sk_query_result *result)
    {
        int rc = sqlite3_finalize(sqlite3_stmt_from_void(result->_stmt));
        if (rc != SQLITE_OK)
        {
            LOG(WARNING) << "Failed to finalise query statement";
        }
    }

    string sk_query_type_of_column(sk_query_result *result, int col)
    {
        if (result->_result == SQLITE_ROW)
        {
            int data = sqlite3_column_type(sqlite3_stmt_from_void(result->_stmt), col);

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
                    LOG(WARNING) << "Unkown type in column";
            }
        }
        LOG(WARNING) << "Failed to read type of column";
        return "";
    }
    
    bool sk_query_read_column_bool(sk_query_result *result, int col)
    {
        if (result->_result == SQLITE_ROW)
        {
            return sqlite3_column_int(sqlite3_stmt_from_void(result->_stmt), col) != 0;
        }
        
        LOG(WARNING) << "Failed to read column as boolean";
        return false;
    }
}