//
// SplashKit Generated Json C++ Code
// DO NOT MODIFY
//

#ifndef __json_h
#define __json_h

#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _json_data;
typedef struct _json_data *json;
/**
* The empty `json` object returned can be filled with data and read by the
* functions and procedures prefixed with `json_add_` and `json_read_`

* @return Returns an empty `json` object.
*/
json create_json();
/**
* `string json_string` must be valid JSON.
* The `json` object returned can be filled with data and read by the functions
* and procedures prefixed with `json_add_` and `json_read_`
* @param json_string The JSON formatted `string` to be converted to a `json` object.
* @return Returns a `json` object filled with data from the parameter `string`.
*/
json create_json(string json_string);
/**
* Releases all of the `json` objects which have been loaded.

*
*/
void free_all_json();
/**
* Frees the SplashKit resources associated with the `json` object.
* @param j The `json` object whose resources should be released.
*
*/
void free_json(json j);
/**
* Returns the count of keys in the top-level `json` object.
* @param j The `json` object to count keys.
* @return The count of keys in the top-level `json` object.
*/
int json_count_keys(json j);
/**
* Converts a `color` to a `json` object.
* @param clr The `color` to convert to `json`.
* @return The `color` serialized into a `json` object.
*/
json json_from_color(color clr);
/**
* Reads a `json` object from a JSON string stored in `Resources/json/filename`
* and loads the data into the returned `json` object.
* @param filename The filename of the file to be written to `Resources/json/`.
* @return Returns the `json` object loaded from the JSON file in `filename`.
*/
json json_from_file(const string &filename);
/**
* Reads a `json` object from a `string` in the JSON format.
* @param j_string A `string` in the JSON format.
* @return Returns a `json` object loaded with data from `string j_string`.
*/
json json_from_string(const string &j_string);
/**
* Checks if the `json` object contains the given `string` key.
* @param j The `json` object to check for the given key.
* @param key The `string` key to be checked.
* @return Returns `true` if the `json j` object contains a key for `string` key.
*/
bool json_has_key(json j, string key);
/**
* Reads an array of `double` values from the `json` object for
* the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @param out_result The array which will be filled with the data stored for `string` key.
*
*/
void json_read_array(json j, string key, vector<double> &out_result);
/**
* Reads an array of `json` object values from the `json` object for
* the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @param out_result The array which will be filled with the data stored for `string` key.
*
*/
void json_read_array(json j, string key, vector<json> &out_result);
/**
* Reads an array of `string` values from the `json` object for
* the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @param out_result The array which will be filled with the data stored for `string` key.
*
*/
void json_read_array(json j, string key, vector<string> &out_result);
/**
* Reads an array of `bool` values from the `json` object for
* the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @param out_result The array which will be filled with the data stored for `string` key.
*
*/
void json_read_array(json j, string key, vector<bool> &out_result);
/**
* Reads a `bool` value from the `json` object for the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @return Returns the `bool` value stored at the `string` key.
*/
bool json_read_bool(json j, string key);
/**
* Reads a `float` value from the `json` object for the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @return Returns the `float` value stored at the `string` key.
*/
float json_read_number(json j, string key);
/**
* Reads a `double` value from the `json` object for the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @return Returns the `double` value stored at the `string` key.
*/
double json_read_number_as_double(json j, string key);
/**
* Reads a `integer` value from the `json` object for the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @return Returns the `integer` value stored at the `string` key.
*/
int json_read_number_as_int(json j, string key);
/**
* Reads a `json` object value from the `json` object for the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @return Returns the `json` object value stored at the `string` key.
*/
json json_read_object(json j, string key);
/**
* Reads a `string` value from the `json` object for the given `string` key.
* @param j The `json` object from which data will be returned for the given key.
* @param key The `string` key used to find data in the `json` object.
* @return Returns the `string` value stored at the `string` key.
*/
string json_read_string(json j, string key);
/**
* Adds an array of `string` values to the `json` object for
* the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_array(json j, string key, vector<string> value);
/**
* Adds an array of `double` values to the `json` object for
* the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_array(json j, string key, vector<double> value);
/**
* Adds an array of `bool` values to the `json` object for
* the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_array(json j, string key, vector<bool> value);
/**
* Adds an array of `json` object values to the `json` object for
* the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_array(json j, string key, vector<json> value);
/**
* Adds a `bool` value to the `json` object for the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_bool(json j, string key, bool value);
/**
* Adds an `int` value to the `json` object for the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_number(json j, string key, int value);
/**
* Adds a `double` value to the `json` object for the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_number(json j, string key, double value);
/**
* Adds a `float` value to the `json` object for the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_number(json j, string key, float value);
/**
* Adds a `json` object to the `json` object for the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param obj The value to be inserted into the `json` object.
*
*/
void json_set_object(json j, string key, json obj);
/**
* Adds a `string` value to the `json` object for the given `string` key.
* @param j The `json` object where data will be inserted for the given key.
* @param key The `string` key where data will be stored in the `json` object.
* @param value The value to be inserted into the `json` object.
*
*/
void json_set_string(json j, string key, string value);
/**
* Converts a `json` object to a `color` object.
* @param j The `json` to convert to a `color`.
* @return The `color` deserialized from the `json` object.
*/
color json_to_color(json j);
/**
* Writes the `json` object to a JSON string stored in `Resources/json/filename`.
* @param j The `json` object to be written to file.
* @param filename The filename of the file to be stored in `Resources/json/`
*
*/
void json_to_file(json j, const string &filename);
/**
* Converts and returns the `json` object as a `string`.
* @param j The `json` object to be converted to a `string`.
* @return Returns the `json` object as a `string`.
*/
string json_to_string(json j);

#endif /* __json_h */
