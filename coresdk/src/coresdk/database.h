/**
 * @header Database
 * @author Jake Renzella
 * @brief SplashKit Database allows you to create, query and otherwise manipulate a database.
 *
 * SplashKit's database library allows you to easily create or load databases
 * and to perform queries on them. To get started with databases in SplashKit,
 * the first thinkg you need to do is to load or create a database file. You can
 * do this by calling the `open_database(string name)` function.
 *
 * @attribute static database
 */

#ifndef database_h
#define database_h

#include <string>
using namespace std;

/**
 * The `database` type is used to refer to databases that can be
 * manipulated by the SplashKit database code. Databases are:
 *
 *
 *   - opened with `open_database`,
 *
 *
 *   - and must be released using `free_database` (to release a specific
 *     database) or `delete_all_databases` (to release all loaded
 *     databases).
 *
 *
 * @attribute class database
 */
typedef struct sk_database *database;

/**
 * The `query_result` type is used to store the result of performing
 * a query on the database. It can:
 *
 *
 *   - show the success or failure of a query using `query_success`,
 *
 *
 *   - stores the data from queries which return data. This data is
 *     accessed using `query_column_for_bool`, `query_column_for_int`,
 *     `query_column_for_string` and `query_column_for_double`.
 *
 *
 * @attribute class query_result
 */
typedef struct sk_query_result *query_result;


/**
 * Determines if SplashKit has a database loaded for the supplied name.
 * This checks against all databases loaded, those loaded without a name
 * are assigned the filename as a default. If this returns `false`, you may
 * want to use `load_database` to load in a specific database and give
 * it the desired name.
 *
 * @param name The name of the database you want to check for.
 *             This will match the name you used when opening the database in open_database
 *
 * @returns Returns `true` if a database with the given `name` has
 *          has been loaded.
 */
bool has_database(string name);

/**
 * Retrieves a `database` that has been loaded into SplashKit.
 *
 * @param name The name of the database to return.
 *
 * @returns Returns the `database` that has been loaded with the specified
 *          `name` using `open_database`.
 */
database database_named(string name);

/**
 * Calculates the number of row changed in the database at the last time
 * a changing query was performed on the given database.
 *
 * @param db The database to check how many rows changed.
 *
 * @returns Returns the `int` which represents how many rows were changed
 *          in the database.
 *
 * @attribute class     database
 * @attribute method    rows_changed
 * @attribute self      db
 */
int rows_changed(database db);

/**
 * @brief Loads or creates, and returns a database
 *
 * The supplied `filename` is the name of the file of the database. The
 * supplied `name` indicates the name to use to refer to this `database`.
 * The `database` can then be retrieved by passing this `name` to
 * the `database_named` function.
 *
 * @param name      The name used to refer to the database.
 * @param filename  The filename used to locate the database to use.
 *
 * @returns A new `database` with the initialised values provided.
 *
 * @attribute class       database
 * @attribute constructor true
 */
database open_database(string name, string filename);

/**
 * Returns the `query_result` for the query passed into `sql`.
 *
 * @param db The database to perform `sql` on.
 * @param sql The sql statement to perform on `db`.
 *
 * @returns Returns the `query_result` which represents
 *          the result of perfoming `sql` on `db`.
 *
 * @attribute class   database
 * @attribute method  run_sql
 * @attribute self    db
 */
query_result run_sql(database db, string sql);

/**
 * Returns the `query_result` for the query passed into `sql`.
 *
 * @param database_name The string name of the database to perform `sql` on.
 * @param sql The sql statement to perform on the database at `database_name`.
 *
 * @returns Returns the `query_result` which represents
 * the result of perfoming `sql` on the database at `database_name`.
 *
 * @attribute unique  run_sql_from_name
 */
query_result run_sql(string database_name, string sql);

/**
 * Frees all of the databases which have been loaded.
 *
 * @attribute static query_result
 * @attribute method free_all
 */
void free_all_query_results();

/**
 * Releases the SplashKit resources associated with the query.
 *
 * @param query The `query_result` whose resources should be released.
 *
 * @attribute class query_result
 * @attribute self  query
 * @attribute destructor true
 */
void free_query_result(query_result query);

/**
 * Gets the next row available on a given `query_result`.
 *
 * @param result The `query_result` to move to the next row on.
 *
 * @returns Returns a `bool` which represents if there was a valid row of data to move to.
 *
 * @attribute class   query_result
 * @attribute method  get_next_row
 * @attribute self    result
 */
bool get_next_row(query_result result);

/**
 * Checks if a given `query_result` has a valid row of data.
 *
 * @param result The `query_result` to check for a valid row of data on.
 *
 * @returns Returns a `bool` which represents if there was a valid row of data.
 *
 * @attribute class   query_result
 * @attribute getter  has_row
 * @attribute self    result
 */
bool has_row(query_result result);

/**
 * Resets a query_result back to its initial state, ready to be re-executed.
 *
 * @param result The `query_result` to reset.
 *
 * @attribute class   query_result
 * @attribute method  reset
 * @attribute self    result
 */
void reset_query_result(query_result result);

/**
 * Queries a given column in the current row of the `query_result` for an integer.
 *
 * @param result The `query_result` to perform the query on.
 * @param col The column you would like to query data from.
 *
 * @returns Returns the `int` which is the data at that column.
 *
 * @attribute class   query_result
 * @attribute method  query_column_for_int
 * @attribute self    result
 */
int query_column_for_int(query_result result, int col);

/**
 * Queries a given column in the current row of the `query_result` for a double.
 *
 * @param result The `query_result` to perform the query on.
 * @param col The column you would like to query data from.
 *
 * @returns Returns the `double` which is the data at that column.
 *
 * @attribute class   query_result
 * @attribute method  query_column_for_double
 * @attribute self    result
 */
double query_column_for_double(query_result result, int col);

/**
 * Queries a given column in the current row of the `query_result` for a string.
 *
 * @param result The `query_result` to perform the query on.
 * @param col The column you would like to query data from.
 *
 * @returns Returns the `string` which is the data at that column.
 *
 * @attribute class   query_result
 * @attribute method  query_column_for_string
 * @attribute self    result
 */
string query_column_for_string(query_result result, int col);

/**
 * Queries a given column in the current row of the `query_result` for a bool.
 *
 * @param result The `query_result` to perform the query on.
 * @param col The column you would like to query data from.
 *
 * @returns Returns the `bool` which is the data at that column.
 *
 * @attribute class   query_result
 * @attribute method  query_column_for_bool
 * @attribute self    result
 */
bool query_column_for_bool(query_result result, int col);

/**
 * Queries a given column in the current row of the `query_result` for the data type at its postition.
 *
 * @param result The `query_result` to perform the query on.
 * @param col The column you would like to know the data type of
 *
 * @returns Returns a `string` which is the name of the data type being stored.
 * - Could return: `INTEGER`, `FLOAT`, `TEXT`, `NULL`.
 *
 * @attribute class   query_result
 * @attribute method  query_type_of_col
 * @attribute self    result
 */
string query_type_of_col(query_result result, int col);

/**
 * Checks if the most recent query at the given `query_result` was a success or failure.
 *
 * @param result The `query_result` to check the success of.
 *
 * @returns Returns whether or not the query was a success or failure represented as a `bool`.
 *
 * @attribute class   query_result
 * @attribute getter  successful
 */
bool query_success(query_result result);

/**
 * Frees the SplashKit resources associated with the database.
 *
 * @param db_to_close The `database` whose resources should be released.
 *
 * @attribute class       database
 * @attribute destructor  true
 */
void free_database(database db_to_close);

/**
 * Frees the SplashKit resources associated with the database at a given name.
 *
 * @param name_of_db_to_close The `string` denoting where the database is which should be released.
 *
 * @attribute unique  free_database_named
 */
void free_database(string name_of_db_to_close);

/**
 * Releases all of the databases which have been loaded.
 */
void free_all_databases();

#endif /* database_h */
