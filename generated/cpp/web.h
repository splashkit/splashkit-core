//
// SplashKit Generated Web C++ Code
// DO NOT MODIFY
//

#ifndef __web_h
#define __web_h

#include "music.h"
#include "sound.h"
#include "types.h"
#include "web.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

struct _http_response_data;
typedef struct _http_response_data *http_response;
bitmap download_bitmap(const string &name, const string &url, unsigned short port);
font download_font(const string &name, const string &url, unsigned short port);
music download_music(const string &name, const string &url, unsigned short port);
sound_effect download_sound_effect(const string &name, const string &url, unsigned short port);
void free_response(http_response response);
http_response http_get(const string &url, unsigned short port);
http_response http_post(const string &url, unsigned short port, const string &body, const vector<string> &headers);
http_response http_post(const string &url, unsigned short port, string body);
string http_response_to_string(http_response response);
void save_response_to_file(http_response response, string path);

#endif /* __web_h */
