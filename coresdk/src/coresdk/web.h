//
//  web.hpp
//  splashkit
//
//  Created by Andrew Cain on 26/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef web_hpp
#define web_hpp

#include "types.h"

#include <string>
using namespace std;

typedef struct _http_request_data *http_request;
typedef struct _http_response_data *http_response;

http_response http_get(string url, unsigned short port);

bitmap download_image(string name, string url, unsigned short port);

string http_response_to_string(http_response response);
void save_response_to_file(http_response response, string path);
void free_response (http_response response);

#endif /* web_hpp */
