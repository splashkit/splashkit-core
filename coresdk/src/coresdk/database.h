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

bool has_database(string name);

database database_named(string name);

database open_database(string name, string filename);

void run_sql(database db, string sql);

#endif /* database_h */
