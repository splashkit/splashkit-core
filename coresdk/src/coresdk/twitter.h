/**
* @header  twitter
* @author  Jake Renzella
* @brief   SplashKit provides functionality to post material to twitter
*
* @attribute group  social
* @attribute static twitter
 */

#ifndef twitter_hpp
#define twitter_hpp

#include "json.h"
#include "web_client.h"
#include <string>
using namespace std;

#endif /* twitter_h */
namespace splashkit_lib
{
    typedef struct _twitter_account *twitter_account;

    twitter_account load_twitter_account(const string &name, const string &filename);
    bool has_twitter_account(const string &name);
    twitter_account twitter_account_named(const string &name);

    http_response tweet(twitter_account account, const string &message);
}
