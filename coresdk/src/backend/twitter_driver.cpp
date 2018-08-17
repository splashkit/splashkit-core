//
//  twitter_driver.cpp
//  splashkit
//
//  Created by Jake Renzella on 20/09/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "twitter_driver.h"
#include "utility_functions.h"
#include "hmac.h"
#include "sha1.h"
#include <random>
#include <iomanip>

#ifdef __linux__
#include <string.h>
#endif

using std::random_device;
using std::mt19937;
using std::uniform_int_distribution;
using std::ostringstream;
using std::hex;
using std::uppercase;
using std::setw;
using std::nouppercase;
using std::to_string;

namespace splashkit_lib
{

    std::vector<char> HexToBytes(const std::string& hex)
    {
        std::vector<char> bytes;

        for (unsigned int i = 0; i < hex.length(); i += 2)
        {
            std::string byteString = hex.substr(i, 2);
            char byte = (char) strtol(byteString.c_str(), NULL, 16);
            bytes.push_back(byte);
        }

        return bytes;
    }

    static const std::string base64_chars =
    "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "abcdefghijklmnopqrstuvwxyz"
    "0123456789+/";


    std::string base64_encode(const unsigned char* bytes_to_encode, unsigned int in_len)
    {
        std::string ret;
        int i = 0;
        int j = 0;
        unsigned char char_array_3[3];
        unsigned char char_array_4[4];

        while (in_len--)
        {
            char_array_3[i++] = *(bytes_to_encode++);
            if (i == 3)
            {
                char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
                char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
                char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
                char_array_4[3] = char_array_3[2] & 0x3f;

                for(i = 0; (i <4) ; i++)
                {
                    ret += base64_chars[char_array_4[i]];
                }
                i = 0;
            }
        }

        if (i)
        {
            for(j = i; j < 3; j++)
            {
                char_array_3[j] = '\0';
            }

            char_array_4[0] = (char_array_3[0] & 0xfc) >> 2;
            char_array_4[1] = ((char_array_3[0] & 0x03) << 4) + ((char_array_3[1] & 0xf0) >> 4);
            char_array_4[2] = ((char_array_3[1] & 0x0f) << 2) + ((char_array_3[2] & 0xc0) >> 6);
            char_array_4[3] = char_array_3[2] & 0x3f;

            for (j = 0; (j < i + 1); j++)
            {
                ret += base64_chars[char_array_4[j]];
            }

            while((i++ < 3))
            {
                ret += '=';
            }
        }
        return ret;
    }

    string generate_nonce()
    {

        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(0, RAND_MAX);

        static const char alphanum[] =
        "0123456789"
        "!@#$%^&*"
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz";

        int stringLength = sizeof(alphanum) - 1;
        string result = "";
        for (int i = 0; i<32; i++)
        {
            result += alphanum[dis(gen) % stringLength];
        }

        return base64_encode((const unsigned char*)result.c_str(), 32);
    }

    string url_encode(const string &value)
    {
        ostringstream escaped;
        escaped.fill('0');
        escaped << hex;

        for (string::const_iterator i = value.begin(), n = value.end(); i != n; ++i) {
            string::value_type c = (*i);

            // Keep alphanumeric and other accepted characters intact
            if (isalnum(c) || c == '-' || c == '_' || c == '.' || c == '~') {
                escaped << c;
                continue;
            }

            // Any other characters are percent-encoded
            escaped << uppercase;
            escaped << '%' << setw(2) << int((unsigned char) c);
            escaped << nouppercase;
        }
        return escaped.str();
    }

    string generate_unix_timestamp()
    {
        std::time_t result = std::time(nullptr);
        return to_string(result);
    }

    string collect_parameters(map<string, string> parameters_map)
    {
        string result = "";
        for (map<string, string>::iterator i = parameters_map.begin(); i != parameters_map.end(); i++)
        {
            result += i->first + "=" + i->second;
            if (parameters_map.rbegin()->first != i->first)
            {
                result += "&";
            }
        }
        return result;
    }

    string generate_signature(map<string, string> parameters_map)
    {
        map<string, string> encoded_parameters_map;

        encoded_parameters_map.insert({url_encode("oauth_signature_method"), url_encode(parameters_map.at("oauth_signature_method"))});
        encoded_parameters_map.insert({url_encode("status"), url_encode(parameters_map.at("status"))});
        encoded_parameters_map.insert({url_encode("oauth_consumer_key"), url_encode(parameters_map.at("oauth_consumer_key"))});
        encoded_parameters_map.insert({url_encode("oauth_nonce"), url_encode(parameters_map.at("oauth_nonce"))});
        encoded_parameters_map.insert({url_encode("oauth_timestamp"), url_encode(parameters_map.at("oauth_timestamp"))});
        encoded_parameters_map.insert({url_encode("oauth_token"), url_encode(parameters_map.at("oauth_token"))});
        encoded_parameters_map.insert({url_encode("oauth_version"), url_encode(parameters_map.at("oauth_version"))});

        string http_method = parameters_map.at("http_method");
        string http_url = parameters_map.at("http_url");

        string parameter_string = collect_parameters(encoded_parameters_map);
        string signature_base_string = http_method + "&" + url_encode(http_url) + "&" + url_encode(parameter_string);

        string consumer_secret = parameters_map.at("oauth_consumer_secret");
        string oath_token_secret = parameters_map.at("oauth_token_secret");

        string signing_key = url_encode(consumer_secret) + "&" + url_encode(oath_token_secret);
        string sha1hmac = hmac<SHA1>(signature_base_string, signing_key);

        auto sha1hmac_hex_decoded = HexToBytes(sha1hmac);
        unsigned const char* to_encode = reinterpret_cast<unsigned const char*>(sha1hmac_hex_decoded.data());

        string encoded_result = base64_encode(to_encode, static_cast<unsigned int>(sha1hmac_hex_decoded.size()));
        return encoded_result;

    }

    string generate_authorization_header(map<string, string> parameters_map)
    {
        parameters_map["oauth_nonce"] = generate_nonce();
        parameters_map["oauth_signature_method"] = "HMAC-SHA1";
        parameters_map["oauth_timestamp"] = generate_unix_timestamp();
        parameters_map["oauth_version"] = "1.0";
        parameters_map["oauth_signature"] = generate_signature(parameters_map);

        string DST = "Authorization:OAuth ";
        DST += url_encode("oauth_consumer_key") + "=\"" + url_encode(parameters_map.at("oauth_consumer_key")) + "\", ";
        DST += url_encode("oauth_nonce") + "=\"" + url_encode(parameters_map.at("oauth_nonce")) + "\", ";
        DST += url_encode("oauth_signature") + "=\"" + url_encode(parameters_map.at("oauth_signature")) + "\", ";
        DST += url_encode("oauth_signature_method") + "=\"" + url_encode(parameters_map.at("oauth_signature_method")) + "\", ";
        DST += url_encode("oauth_timestamp") + "=\"" + url_encode(parameters_map.at("oauth_timestamp")) + "\", ";
        DST += url_encode("oauth_token") + "=\"" + url_encode(parameters_map.at("oauth_token")) + "\", ";
        DST += url_encode("oauth_version") + "=\"" + url_encode(parameters_map.at("oauth_version")) + "\"";

        return DST;
    }

}
