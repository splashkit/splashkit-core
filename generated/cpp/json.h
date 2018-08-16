//
// SplashKit Generated Json C++ Code
// DO NOT MODIFY
//

#ifndef __json_h
#define __json_h

#include "types.h"
#include "json.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _json_data;
typedef struct _json_data *json;
json create_json();
json create_json(string json_string);
void free_all_json();
void free_json(json j);
int json_count_keys(json j);
json json_from_color(color clr);
json json_from_file(const string &filename);
json json_from_string(const string &j_string);
bool json_has_key(json j, string key);
void json_read_array(json j, string key, vector<double> &out_result);
void json_read_array(json j, string key, vector<json> &out_result);
void json_read_array(json j, string key, vector<string> &out_result);
void json_read_array(json j, string key, vector<bool> &out_result);
bool json_read_bool(json j, string key);
float json_read_number(json j, string key);
double json_read_number_as_double(json j, string key);
int json_read_number_as_int(json j, string key);
json json_read_object(json j, string key);
string json_read_string(json j, string key);
void json_set_array(json j, string key, vector<string> value);
void json_set_array(json j, string key, vector<double> value);
void json_set_array(json j, string key, vector<bool> value);
void json_set_array(json j, string key, vector<json> value);
void json_set_bool(json j, string key, bool value);
void json_set_number(json j, string key, int value);
void json_set_number(json j, string key, double value);
void json_set_number(json j, string key, float value);
void json_set_object(json j, string key, json obj);
void json_set_string(json j, string key, string value);
color json_to_color(json j);
void json_to_file(json j, const string &filename);
string json_to_string(json j);

#endif /* __json_h */
