//
// SplashKit Generated Web C++ Code
// DO NOT MODIFY
//

#ifndef __web_h
#define __web_h

#include "music.h"
#include "sound.h"
#include "types.h"
#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

struct _http_response_data;
typedef struct _http_response_data *http_response;
/**
* Download an image from a web server and load it into SplashKit so that
* you can use it.
* @param name The name of the bitmap resource when it is loaded
* @param url The URL path to the image resoure
* @param port The port to connect to on the server
* @return The bitmap that was loaded
*/
bitmap download_bitmap(const string &name, const string &url, unsigned short port);
/**
* Download a font from a web server and load it into SplashKit so that
* you can use it.
* @param name The name of the font resource when it is loaded
* @param url The URL path to the font resoure
* @param port The port to connect to on the server
* @return The font that was loaded
*/
font download_font(const string &name, const string &url, unsigned short port);
/**
* Download a music file from a web server and load it into SplashKit so
* that you can use it.
* @param name The name of the music resource when it is loaded
* @param url The URL path to the music resoure
* @param port The port to connect to on the server
* @return The music that was loaded
*/
music download_music(const string &name, const string &url, unsigned short port);
/**
* Download a sound effect from a web server and load it into SplashKit so
* that you can use it.
* @param name The name of the sound effect resource when it is loaded
* @param url The URL path to the sound effect resoure
* @param port The port to connect to on the server
* @return The sound effect that was loaded
*/
sound_effect download_sound_effect(const string &name, const string &url, unsigned short port);
/**
* Free the response resource.
* @param response The response to free
*
*/
void free_response(http_response response);
/**
* Make a get request to access a resource on the internet.
* @param url The path to the resource, for example http://splashkit.io
* @param port The port on the server (80 for http, 443 for https)
* @return The response with all of the data received
*/
http_response http_get(const string &url, unsigned short port);
/**
* Post the supplied information to the indicated url with the given headers.
* @param url The url of the server to post the data to
* @param port The port to connect to on the server
* @param body The body of the message to post
* @param headers The headers of the request
* @return The response from the server
*/
http_response http_post(const string &url, unsigned short port, const string &body, const vector<string> &headers);
/**
* Post the supplied information to the indicated url.
* @param url The url of the server to post the data to
* @param port The port to connect to on the server
* @param body The body of the message to post
* @return The response from the server
*/
http_response http_post(const string &url, unsigned short port, string body);
/**
* Read the HTTP response and convert it to text
* @param response The response from the server
* @return The data from the response as text
*/
string http_response_to_string(http_response response);
/**
* Save the HTTP response downloaded into a file.
* @param response The response from the server
* @param path The path to the file where the response should be saved
*
*/
void save_response_to_file(http_response response, string path);

#endif /* __web_h */
