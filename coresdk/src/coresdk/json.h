/**
 * @header Json
 * @author James Armstrong
 * @author Jake Renzella
 * @brief SplashKit Json allows you to create and read JSON objects.
 *
 * Splashkit's JSON library allows you to easily create or read JSON objects and
 * manipulate them to/from a JSON string or from a file containing a JSON
 * string. Create a new JSON object with a call to `create_json()` and
 * read or write data to it by calling methods like
 * `json_add_string(json j, string key, string value)` and
 * `json_read_string(json j, string key)`.
 *
 * @attribute static json
 */

#ifndef SPLASHKIT_JSON_CPP
#define SPLASHKIT_JSON_CPP

#include <string>
#include <vector>

using namespace std;

/**
 * The `json` type is used to refer to JSON objects that can be
 * manipulated by the SplashKit json code.
 *
 * All `json` objects created must be released with `free_all_json()`
 * before the program ends.
 *
 * @attribute class json
 */
typedef struct sk_json *json;

json create_json();

json create_json(string json_string);

void free_json(json j);

void free_all_json();

void json_to_file(json j, const string& filename);

json json_from_file(const string& filename);

string json_to_string(json j);

json json_from_string(const string &j_string);

void json_add_string(json j, string key, string value);

void json_add_number(json j, string key, double value);

void json_add_bool(json j, string key, bool value);

void json_add_object(json j, string key, json object);

void json_add_array(json j, string key, vector<string> value);

void json_add_array(json j, string key, vector<double> value);

void json_add_array(json j, string key, vector<bool> value);

void json_add_array(json j, string key, vector<json> value);

double json_read_number(json j, string key);

string json_read_string(json j, string key);

bool json_read_bool(json j, string key);

json json_read_object(json j, string key);

void json_read_array(json j, string key, vector<double> &out);

void json_read_array(json j, string key, vector<json> &out);

void json_read_array(json j, string key, vector<string> &out);

void json_read_array(json j, string key, vector<bool> &out);

bool json_has_key(json j, string key);

#endif //SPLASHKIT_JSON_CPP
