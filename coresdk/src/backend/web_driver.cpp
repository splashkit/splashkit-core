//
//  skWeb.cpp
//  sk
//
//  Created by Andrew Cain on 1/05/2015.
//  Copyright (c) 2015 Andrew Cain. All rights reserved.
//

#include "web_driver.h"
#include "core_driver.h"
#include "easylogging++.h"
#include "utility_functions.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <curl/curl.h>
namespace splashkit_lib
{
    struct request_stream
    {
        char *body;
        unsigned long at;
    };

    static size_t write_memory_callback(void *contents, size_t size, size_t nmemb, void *userp)
    {
        size_t realsize = size * nmemb;
        request_stream *mem = static_cast<request_stream *>(userp);

        mem->body = (char *)realloc(mem->body, mem->at + realsize + 1);
        if(mem->body == NULL) {
            /* out of memory! */
            LOG(ERROR) << "not enough memory (realloc returned NULL)";
            return 0;
        }

        memcpy(&(mem->body[mem->at]), contents, realsize);
        mem->at += realsize;
        mem->body[mem->at] = 0;

        return realsize;
    }

    size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
        size_t written;
        written = fwrite(ptr, size, nmemb, stream);
        return written;
    }

    /* NOTE: check note regarding reading if this does not work on Windows with libcurl as a
     DLL -- you MUST also provide a read callback with CURLOPT_READFUNCTION.
     Failing to do so will give you a crash since a DLL may not use the
     variable's memory when passed in to it from an app like this. */
    static size_t read_request_body(void *ptr, size_t size, size_t nmemb, void *stream)
    {
        // not actually a
        request_stream *request = static_cast<request_stream *>(stream);

        unsigned long str_len = strlen(request->body);

        if (str_len - request->at > 0)
        {
            size_t len = str_len - request->at;
            size_t max_read = nmemb * size;
            size_t to_read;

            if (max_read > len) to_read = len;
            else to_read = max_read;

            strncpy((char*)ptr, request->body + request->at, sizeof(char) * to_read);
            request->at += to_read;
            return to_read;
        }

        return 0;
    }

    void sk_init_web()
    {
        curl_global_init(CURL_GLOBAL_ALL);
    }

    void sk_finalise_web()
    {
        curl_global_cleanup();
    }

    http_status_code code_to_status(int code)
    {
        switch (code)
        {
            case 200: return HTTP_STATUS_OK;
            case 201: return HTTP_STATUS_CREATED;
            case 204: return HTTP_STATUS_NO_CONTENT;
            case 400: return HTTP_STATUS_BAD_REQUEST;
            case 401: return HTTP_STATUS_UNAUTHORIZED;
            case 403: return HTTP_STATUS_FORBIDDEN;
            case 404: return HTTP_STATUS_NOT_FOUND;
            case 405: return HTTP_STATUS_METHOD_NOT_ALLOWED;
            case 408: return HTTP_STATUS_REQUEST_TIMEOUT;
            case 500: return HTTP_STATUS_INTERNAL_SERVER_ERROR;
            case 501: return HTTP_STATUS_NOT_IMPLEMENTED;
            case 503: return HTTP_STATUS_SERVICE_UNAVAILABLE;

            default:
                return static_cast<http_status_code>(code);
        }
    }

    void _init_curl(CURL *curl_handle, const string &host, unsigned short port)
    {
        // specify URL to get
        curl_easy_setopt(curl_handle, CURLOPT_URL, host.c_str());

        // set port
        curl_easy_setopt(curl_handle, CURLOPT_PORT, port);

        curl_easy_setopt(curl_handle, CURLOPT_FOLLOWLOCATION, 1L);

        curl_easy_setopt(curl_handle, CURLOPT_SSL_VERIFYPEER, 0L);

        // some servers don't like requests that are made without a user-agent field, so we provide one
        curl_easy_setopt(curl_handle, CURLOPT_USERAGENT, "libcurl-agent/1.0");
    }

    struct curl_slist *_setup_curl_upload(CURL *curl_handle, const string &body, const vector<string> &headers)
    {
        // header list
        struct curl_slist *list = NULL;

        if (headers.size() > 0)
        {
            for (int i = 0; i < headers.size(); ++i)
            {
                list = curl_slist_append(list, headers[i].c_str());
            }
        }
        else
        {
            list = curl_slist_append(list, "Content-Type: application/json;charset=UTF8");
            list = curl_slist_append(list, "Accept: application/json, text/plain, */*");
        }
        
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, list);
        curl_easy_setopt(curl_handle, CURLOPT_POSTFIELDS, body.c_str());

        return list;
    }

    void _setup_curl_download(CURL *curl_handle, request_stream *result)
    {
        // send all data to this function
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, write_memory_callback);

        // pass in the result as the location to write to
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, (void *)result);
    }

    sk_http_response *_create_response(CURL *curl_handle, CURLcode res, request_stream &data)
    {
        // check for errors
        if(res != CURLE_OK)
        {
            LOG(ERROR) << curl_easy_strerror(res);
            return nullptr;
        }

        sk_http_response *result = new sk_http_response;

        result->id = HTTP_RESPONSE_PTR;

        long status;
        curl_easy_getinfo(curl_handle, CURLINFO_RESPONSE_CODE, &status);
        result->code = code_to_status((int)status);

        char *content_type;
        curl_easy_getinfo(curl_handle, CURLINFO_CONTENT_TYPE, &content_type);
        if (content_type)
            result->content_type = string(content_type);
        else
            result->content_type = "";

        /* cleanup curl stuff */
        curl_easy_cleanup(curl_handle);

        result->message = data.body;
        result->message_size = data.at;
        return result;
    }

    sk_http_response *sk_http_post(const string &host, unsigned short port, const string &body, const vector<string> &headers)
    {
        request_stream data_read = { nullptr, 0 };

        // init the curl session
        CURL *curl_handle = curl_easy_init();;
        CURLcode res;

        _init_curl(curl_handle, host, port);
        struct curl_slist *list = _setup_curl_upload(curl_handle, body, headers);
        _setup_curl_download(curl_handle, &data_read);

        // get it!
        res = curl_easy_perform(curl_handle);

        // free headers
        curl_slist_free_all(list);

        return _create_response(curl_handle, res, data_read);
    }

    sk_http_response *sk_http_get(const string &host, unsigned short port)
    {
        request_stream data_read = { nullptr, 0 };

        // init the curl session
        CURL *curl_handle = curl_easy_init();;
        CURLcode res;

        _init_curl(curl_handle, host, port);
        _setup_curl_download(curl_handle, &data_read);

        // get it!
        res = curl_easy_perform(curl_handle);

        return _create_response(curl_handle, res, data_read);
    }

    sk_http_response *sk_http_put(const string &host, unsigned short port, const string &body)
    {
        request_stream data_read = { nullptr, 0 };

        // init the curl session
        CURL *curl_handle = curl_easy_init();;
        CURLcode res;

        _init_curl(curl_handle, host, port);
        _setup_curl_download(curl_handle, &data_read);

        // header list
        struct curl_slist *list = NULL;
        list = curl_slist_append(list, "Content-Type: application/json;charset=UTF8");
        list = curl_slist_append(list, "Accept: application/json, text/plain, */*");
        curl_easy_setopt(curl_handle, CURLOPT_HTTPHEADER, list);

        /* we want to use our own read function */
        curl_easy_setopt(curl_handle, CURLOPT_READFUNCTION, read_request_body);

        /* enable uploading */
        curl_easy_setopt(curl_handle, CURLOPT_UPLOAD, 1L);

        request_stream data = { strdup(body.c_str()), 0 };

        /* now specify which pointer to pass to our callback */
        curl_easy_setopt(curl_handle, CURLOPT_READDATA, &data);

        /* Set the size of the file to upload */
        curl_easy_setopt(curl_handle, CURLOPT_INFILESIZE, (curl_off_t)strlen(data.body));

        /* Now run off and do what you've been told! */
        res = curl_easy_perform(curl_handle);

        free(data.body);

        // free headers
        curl_slist_free_all(list);

        return _create_response(curl_handle, res, data_read);
    }

    sk_http_response *sk_http_delete(const string &host, unsigned short port, const string &body)
    {
        request_stream data_read = { nullptr, 0 };

        // init the curl session
        CURL *curl_handle = curl_easy_init();;
        CURLcode res;

        
        //TODO: Add headers param
        _init_curl(curl_handle, host, port);
        struct curl_slist *list = _setup_curl_upload(curl_handle, body, {});
        _setup_curl_download(curl_handle, &data_read);

        curl_easy_setopt(curl_handle, CURLOPT_CUSTOMREQUEST, "DELETE");

        // get it!
        res = curl_easy_perform(curl_handle);

        // free headers
        curl_slist_free_all(list);

        return _create_response(curl_handle, res, data_read);
    }

    sk_http_response *sk_http_make_request(const sk_http_request &request)
    {
        internal_sk_init();

        switch (request.method)
        {
            case HTTP_GET_METHOD:
                return sk_http_get(request.uri, request.port);
            case HTTP_POST_METHOD:
                return sk_http_post(request.uri, request.port, request.body, request.headers);
            case HTTP_PUT_METHOD:
                return sk_http_put(request.uri, request.port, request.body);
            case HTTP_DELETE_METHOD:
                return sk_http_delete(request.uri, request.port, request.body);
            default:
                return nullptr;
        }
    }
}
