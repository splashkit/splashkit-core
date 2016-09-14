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
namespace splashkit_lib
{
    /**
     * A HTTP response is a resource that comes back from a HTTP request. This
     * may be the text related to a web page, or the data related to a resource.
     * Once you have used the response, you need to make sure to call
     * `free_response`.
     *
     * @attribute class http_response
     */
    typedef struct _http_response_data *http_response;

    http_response http_get(const string &url, unsigned short port);

    http_response http_post(const string &url, unsigned short port, string body);

    bitmap download_image(const string &name, const string &url, unsigned short port);

    string http_response_to_string(http_response response);
    void save_response_to_file(http_response response, string path);
    void free_response (http_response response);
}
#endif /* web_hpp */
