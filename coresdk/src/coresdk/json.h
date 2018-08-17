/**
 * @header  json
 * @author  James Armstrong
 * @author  Jake Renzella
 * @brief   SplashKit Json allows you to create and read JSON objects.
 *
 * Splashkit's JSON library allows you to easily create or read JSON objects and
 * manipulate them to/from a JSON string or from a file containing a JSON
 * string. Create a new JSON object with a call to `create_json()` and
 * read or write data to it by calling methods like
 * `json_add_string(json j, string key, string value)` and
 * `json_read_string(json j, string key)`.
 *
 * @attribute group  json
 * @attribute static json
 */

#ifndef SPLASHKIT_JSON_CPP
#define SPLASHKIT_JSON_CPP

#include <string>
#include <vector>

#include "types.h"

using std::string;
using std::vector;

namespace splashkit_lib
{

    /**
     * The `json` type is used to refer to objects in the JSON format that can be
     * manipulated by the SplashKit `json` functions and procedures.
     *
     *
     * All `json` objects are:
     *
     *
     *   - created with `create_json()` or `create_json(string s)` or
     *   `json_from_string(string s)` or `json_from_file(json j)`
     *
     *
     *   - and must be released using `free_json()` (to release a specific `json object)
     *   or `free_all_json()` (to release all loaded `json objects).
     *
     *
     * @attribute class json
     */
    typedef struct sk_json *json;

    /**
     * @brief Creates an empty `json` object.
     *
     * The empty `json` object returned can be filled with data and read by the
     * functions and procedures prefixed with `json_add_` and `json_read_`
     *
     * @returns Returns an empty `json` object.
     *
     * @attribute class       json
     * @attribute constructor true
     */
    json create_json();

    /**
     * @brief Creates a `json` object filled with JSON fields from `json_string`.
     *
     * `string json_string` must be valid JSON.
     * The `json` object returned can be filled with data and read by the functions
     * and procedures prefixed with `json_add_` and `json_read_`
     *
     * @param json_string The JSON formatted `string` to be converted to a `json` object.
     *
     * @returns Returns a `json` object filled with data from the parameter `string`.
     *
     * @attribute class       json
     * @attribute constructor true
     *
     * @attribute suffix  from_string
     */
    json create_json(string json_string);

    /**
     * Frees the SplashKit resources associated with the `json` object.
     *
     * @param j The `json` object whose resources should be released.
     *
     * @attribute class      json
     * @attribute destructor true
     * @attribute self j
     */
    void free_json(json j);

    /**
     * Releases all of the `json` objects which have been loaded.
     *
     * @attribute static json
     * @attribute method free_all
     */
    void free_all_json();

    /**
     * Writes the `json` object to a JSON string stored in `Resources/json/filename`.
     *
     * @param j The `json` object to be written to file.
     * @param filename The filename of the file to be stored in `Resources/json/`
     *
     * @attribute static json
     * @attribute method to_file
     */
    void json_to_file(json j, const string& filename);

    /**
     * Reads a `json` object from a JSON string stored in `Resources/json/filename`
     * and loads the data into the returned `json` object.
     *
     * @param filename The filename of the file to be written to `Resources/json/`.
     *
     * @returns Returns the `json` object loaded from the JSON file in `filename`.
     *
     * @attribute static json
     * @attribute method from_file
     */
    json json_from_file(const string& filename);

    /**
     * Converts and returns the `json` object as a `string`.
     *
     * @param j The `json` object to be converted to a `string`.
     *
     * @returns Returns the `json` object as a `string`.
     *
     * @attribute static json
     * @attribute method to_json_string
     */
    string json_to_string(json j);

    /**
     * Reads a `json` object from a `string` in the JSON format.
     *
     * @param j_string A `string` in the JSON format.
     *
     * @returns Returns a `json` object loaded with data from `string j_string`.
     *
     * @attribute static json
     * @attribute method from_json_string
     */
    json json_from_string(const string &j_string);

    /**
     * Adds a `string` value to the `json` object for the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_string
     * @attribute self j
     */
    void json_set_string(json j, string key, string value);

    /**
     * Adds a `float` value to the `json` object for the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_number
     * @attribute self j
     *
     * @attribute suffix  float
     */
    void json_set_number(json j, string key, float value);

    /**
     * Adds a `double` value to the `json` object for the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_number
     * @attribute self j
     *
     * @attribute suffix  double
     */
    void json_set_number(json j, string key, double value);

    /**
     * Adds an `int` value to the `json` object for the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_number
     * @attribute self j
     *
     * @attribute suffix  integer
     */
    void json_set_number(json j, string key, int value);

    /**
     * Adds a `bool` value to the `json` object for the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_bool
     * @attribute self j
     */
    void json_set_bool(json j, string key, bool value);

    /**
     * Adds a `json` object to the `json` object for the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param obj The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_object
     * @attribute self j
     */
    void json_set_object(json j, string key, json obj);

    /**
     * Adds an array of `string` values to the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_array
     * @attribute suffix of_string
     * @attribute self j
     */
    void json_set_array(json j, string key, vector<string> value);

    /**
     * Adds an array of `double` values to the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_array
     * @attribute suffix of_double
     * @attribute self j
     */
    void json_set_array(json j, string key, vector<double> value);

    /**
     * Adds an array of `bool` values to the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_array
     * @attribute suffix of_bool
     * @attribute self j
     */
    void json_set_array(json j, string key, vector<bool> value);

    /**
     * Adds an array of `json` object values to the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object where data will be inserted for the given key.
     * @param key The `string` key where data will be stored in the `json` object.
     * @param value The value to be inserted into the `json` object.
     *
     * @attribute class json
     * @attribute method add_array
     * @attribute suffix of_json
     * @attribute self j
     */
    void json_set_array(json j, string key, vector<json> value);

    /**
     * Reads a `float` value from the `json` object for the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     *
     * @returns Returns the `float` value stored at the `string` key.
     *
     * @attribute class json
     * @attribute method read_number
     * @attribute self j
     */
    float json_read_number(json j, string key);

    /**
     * Reads a `integer` value from the `json` object for the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     *
     * @returns Returns the `integer` value stored at the `string` key.
     *
     * @attribute class json
     * @attribute method read_integer
     * @attribute self j
     */
    int json_read_number_as_int(json j, string key);

    /**
     * Reads a `double` value from the `json` object for the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     *
     * @returns Returns the `double` value stored at the `string` key.
     *
     * @attribute class json
     * @attribute method read_double
     * @attribute self j
     */
    double json_read_number_as_double(json j, string key);

    /**
     * Reads a `string` value from the `json` object for the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     *
     * @returns Returns the `string` value stored at the `string` key.
     *
     * @attribute class json
     * @attribute method read_string
     * @attribute self j
     */
    string json_read_string(json j, string key);

    /**
     * Reads a `bool` value from the `json` object for the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     *
     * @returns Returns the `bool` value stored at the `string` key.
     *
     * @attribute class json
     * @attribute method read_bool
     * @attribute self j
     */
    bool json_read_bool(json j, string key);

    /**
     * Reads a `json` object value from the `json` object for the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     *
     * @returns Returns the `json` object value stored at the `string` key.
     *
     * @attribute class json
     * @attribute method read_object
     * @attribute self j
     */
    json json_read_object(json j, string key);

    /**
     * Reads an array of `double` values from the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     * @param out_result The array which will be filled with the data stored for `string` key.
     *
     * @attribute class json
     * @attribute method read_array
     * @attribute suffix of_double
     * @attribute self j
     */
    void json_read_array(json j, string key, vector<double> &out_result);

    /**
     * Reads an array of `json` object values from the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     * @param out_result The array which will be filled with the data stored for `string` key.
     *
     * @attribute class json
     * @attribute method read_array
     * @attribute suffix of_json
     * @attribute self j
     */
    void json_read_array(json j, string key, vector<json> &out_result);

    /**
     * Reads an array of `string` values from the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     * @param out_result The array which will be filled with the data stored for `string` key.
     *
     * @attribute class json
     * @attribute method read_array
     * @attribute suffix of_string
     * @attribute self j
     */
    void json_read_array(json j, string key, vector<string> &out_result);

    /**
     * Reads an array of `bool` values from the `json` object for
     * the given `string` key.
     *
     * @param j The `json` object from which data will be returned for the given key.
     * @param key The `string` key used to find data in the `json` object.
     * @param out_result The array which will be filled with the data stored for `string` key.
     *
     * @attribute class json
     * @attribute method read_array
     * @attribute suffix of_bool
     * @attribute self j
     */
    void json_read_array(json j, string key, vector<bool> &out_result);

    /**
     * Checks if the `json` object contains the given `string` key.
     *
     * @param j The `json` object to check for the given key.
     * @param key The `string` key to be checked.
     *
     * @returns Returns `true` if the `json j` object contains a key for `string` key.
     *
     * @attribute class json
     * @attribute method has_key
     * @attribute self j
     */
    bool json_has_key(json j, string key);

    /**
     * Returns the count of keys in the top-level `json` object.
     *
     * @param j The `json` object to count keys.
     *
     * @returns The count of keys in the top-level `json` object.
     *
     * @attribute class json
     * @attribute method count_keys
     * @attribute self j
     */
    int json_count_keys(json j);

    /**
     * Converts a `color` to a `json` object.
     *
     * @param clr The `color` to convert to `json`.
     *
     * @returns The `color` serialized into a `json` object.
     */
    json json_from_color(color clr);

    /**
     * Converts a `json` object to a `color` object.
     *
     * @param j The `json` to convert to a `color`.
     *
     * @returns The `color` deserialized from the `json` object.
     */
    color json_to_color(json j);
}
#endif //SPLASHKIT_JSON_CPP
