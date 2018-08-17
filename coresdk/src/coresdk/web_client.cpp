//
//  web.cpp
//  splashkit
//
//  Created by Andrew Cain on 26/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "web_client.h"
#include "web_driver.h"
#include "utility_functions.h"
#include <fstream>
#include <cstdio>
#include <cstring>

#include "images.h"

#include "backend_types.h"

using std::ofstream;
using std::ios;

#ifdef WINDOWS
#include <Windows.h>
#endif
namespace splashkit_lib
{
    sk_http_response *make_request (http_method request_type, string uri, unsigned short port, string body, const vector<string> &headers)
    {
        sk_http_request request;

        request.id = HTTP_REQUEST_PTR;
        request.method = request_type;
        request.uri = uri;
        request.port = port;
        request.body = body;
        request.filename = "";
        request.headers = headers;

        return sk_http_make_request(request);
    }

    http_response http_get(const string &url, unsigned short port)
    {
        return make_request(HTTP_GET_METHOD, url, port, "", {});
    }

    http_response http_post(const string &url, unsigned short port, const string &body, const vector<string> &headers)
    {
        return make_request(HTTP_POST_METHOD, url, port, body, headers);
    }

    http_response http_post(const string &url, unsigned short port, string body)
    {
        return http_post(url, port, body, {});
    }

    void save_response_to_file(http_response response, string filename)
    {
        ofstream file(filename, ios::binary);
        file.write(response->message, response->message_size);
        file.close();
    }

    string http_response_to_string(http_response response)
    {
        if ( ! VALID_PTR(response, HTTP_RESPONSE_PTR))
        {
            LOG(WARNING) << "Attempt to convert invalid http response to a string";
            return "";
        }

        return string(response->message);
    }

    bool download_file(const string &name, const string &url, unsigned short port, string &path)
    {
        http_response response = http_get(url, port);

        if ( !response )
        {
            return false;
        }

        auto cleanup_response = finally( [&] { free_response(response); });

        if ( static_cast<int>(response->code) < 200 || static_cast<int>(response->code) >= 300 )
        {
            LOG(WARNING) << "Unable to download file from " << url << " got status " << response->code;
            return false;
        }

        char *tmpname;

#ifndef WINDOWS
        tmpname = strdup("/tmp/splashkit.file.XXXXXX");
        mkstemp(tmpname);
#else
        char fname[L_tmpnam];
        tmpnam (fname);
        char tmppath[261] = {0};
        GetTempPath(260, tmppath);

        tmpname = strdup(tmppath);
        string fpath = path_from({tmpname, fname});
        tmpname = strdup(fpath.c_str());
        LOG(WARNING) << tmpname;
#endif
        save_response_to_file(response, tmpname);

        path = string(tmpname);
        free(tmpname);

        return true;
    }

    bitmap download_bitmap(const string &name, const string &url, unsigned short port)
    {
        string path;
        if ( not download_file(name, url, port, path) )
        {
            return nullptr;
        }

        bitmap result = load_bitmap(name, path);
        remove(path.c_str()); // Delete the file
        return result;
    }

    font download_font(const string &name, const string &url, unsigned short port)
    {
        string path;
        if ( not download_file(name, url, port, path) )
        {
            return nullptr;
        }

        font result = load_font(name, path);
        if ( VALID_PTR(result, FONT_PTR) )
            result->was_downloaded = true; // ensure that font will delete file when it is released.
        return result;
    }

    sound_effect download_sound_effect(const string &name, const string &url, unsigned short port)
    {
        string path;
        if ( not download_file(name, url, port, path) )
        {
            return nullptr;
        }

        sound_effect result = load_sound_effect(name, path);
        remove(path.c_str()); // Delete the file
        return result;
    }

    music download_music(const string &name, const string &url, unsigned short port)
    {
        string path;
        if ( not download_file(name, url, port, path) )
        {
            return nullptr;
        }

        music result = load_music(name, path);
        remove(path.c_str()); // Delete the file
        return result;
    }

    void free_response (http_response response)
    {
        if ( VALID_PTR(response, HTTP_RESPONSE_PTR))
        {
            notify_of_free(response);
            response->id = NONE_PTR;
            if ( response->message )
            {
                delete(response->message);
            }
            delete(response);
        }
        else
        {
            LOG(WARNING) << "Attempting to delete a http response with an invalid pointer.";
        }
    }
}
