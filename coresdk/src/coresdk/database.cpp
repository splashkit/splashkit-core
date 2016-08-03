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

#include <iostream>
#include <map>

using namespace std;

static map<string, database> _databases;

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

database load_database(string name, string filename)
{
    if (has_database(name)) return database_named(name);
    
    string file_path = path_to_resource(filename, DATABASE_RESOURCE);
    
    if ( ! file_exists(file_path) )
    {
        raise_warning(cat({ "Unable to locate database file for ", name, " (", file_path, ")"}));
        return nullptr;
    }
    
    database result = new _database();
    
    result->id = DATABASE_PTR;
    result->filename = file_path;
    result->name = name;
    result->database = sk_load_database(file_path);
    
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