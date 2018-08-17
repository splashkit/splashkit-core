//
//  utility_functions.h
//  splashkit
//
//  Created by Andrew Cain on 29/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef utility_functions_h
#define utility_functions_h

#include "backend_types.h"

#include <string>
#include <initializer_list>
#include <algorithm>

#include <easylogging++.h>

using std::string;

namespace splashkit_lib
{
    // smallest positive value: less than that to be considered zero
#define EPS   0.01
    // and its square
#define EPSEPS 0.0001

    bool file_exists(string path);

    bool directory_exists(string path);

#define VALID_PTR(p,pkind) ( (p) and p->id == pkind )
#define INVALID_PTR(p,pkind) ( not VALID_PTR(p,pkind) )

#define ASSIGNED(ptr) ( ptr != nullptr )

#define MIN(a,b) ( a < b ? a : b )
#define MAX(a,b) ( a > b ? a : b )

    template <typename T>
    bool erase_from_vector(vector<T> &v, T value)
    {
        auto it = find (v.begin(), v.end(), value);
        if (it != v.end())
        {
            v.erase(it);
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    int index_of (vector<T> vec, T value)
    {
        auto result = find(vec.begin(), vec.end(), value);

        if ( result == vec.end() ) return -1;
        else return static_cast<int>(result - vec.begin());
    }

    template <typename K, typename V>
    bool key_of_value(const map<K,V> &map, const V &value, K &result)
    {
        auto find_result = std::find_if(std::begin(map),
                                        std::end(map),
                                        [&](const std::pair<K, V> &pair)
                                        {
                                            return pair.second == value;
                                        });

        if (find_result != std::end(map))
        {
            result = find_result->first;
            return true;
        }
        else
        {
            return false;
        }
    }

    template <typename T>
    void move_range(std::vector<T> & v, size_t start, size_t length, size_t dst)
    {
        const size_t final_dst = dst > start ? dst - length : dst;

        std::vector<T> tmp(v.begin() + start, v.begin() + start + length);
        v.erase(v.begin() + start, v.begin() + start + length);
        v.insert(v.begin() + final_dst, tmp.begin(), tmp.end());
    }

#define FREE_ALL_FROM_MAP(collection, ptr_kind, fn )\
size_t sz = collection.size();\
for(size_t i = 0; i < sz; i++)\
{\
auto resource = collection.begin()->second;\
if (VALID_PTR(resource, ptr_kind))\
{\
fn(resource);\
}\
else\
{\
LOG(WARNING) << "Splashkit contains invalid ##ptr_kind !";\
collection.erase(collection.begin());\
}\
}

#define FREE_ALL_FROM_VECTOR(collection, ptr_kind, fn )\
size_t sz = collection.size();\
for(size_t i = 0; i < sz; i++)\
{\
auto resource = *collection.begin();\
if (VALID_PTR(resource, ptr_kind))\
{\
fn(resource);\
}\
else\
{\
LOG(WARNING) << "Splashkit contains invalid ##ptr_kind !";\
collection.erase(collection.begin());\
}\
}


    string cat(std::initializer_list<string> list);

    string path_from(std::initializer_list<string> list, string filename = string(""));

    string path_to_user_home();

    // finally mechanism from: http://stackoverflow.com/questions/161177/does-c-support-finally-blocks-and-whats-this-raii-i-keep-hearing-about
    template <typename F>
    struct FinalAction
    {
        /// When constructed it is passed a clean function (type F)
        FinalAction(F f) : clean_{f} {}

        /// When this goes out of scope the clean function is run... unless it was disabled.
        ~FinalAction() { if(enabled_) clean_(); }

        /// Turn off the block to avoid calling the clean function
        void disable() { enabled_ = false; };

    private:
        /// The clean function of type F
        F clean_;
        bool enabled_{true};
    };

    // Constructor function using finally name. Builds a FinalAction value
    template <typename F>
    FinalAction<F> finally(F f)
    {
        return FinalAction<F>(f);
    }

    string trim(const string& str);
    void to_upper(string &str);

    pointer_identifier ptr_kind(void *p);

    _bitmap_data *to_bitmap_ptr(void *b);
    _window_data *to_window_ptr(void *w);

    sk_drawing_surface *to_surface_ptr(void *p);
    void xy_from_opts(const drawing_options &opts, double &x, double &y);

    void process_range(string value_in, vector<int> &result);

    string extract_delimited(int index, string value, char delim);
    string extract_delimited_with_ranges(int index, string value);

    int count_delimiter(string value, char delimiter);
    int count_delimiter_with_ranges(string value, char delimiter);

    int str_to_int(string str, bool allow_empty = true, int empty_value = 0);
    float str_to_float(string str, bool allow_empty = true, float empty_value = 0.0f);
    double str_to_double(string str, bool allow_empty = true, double empty_value = 0.0);
    
    bool try_str_to_int(string str, int &result);
    bool try_str_to_float(string str, float &result);
    bool try_str_to_double(string str, double &result);
    
    string to_lower (string str);
    
    double rad_to_deg(double radians);
    
    double deg_to_rad(double degrees);

    // Notify the listeners that a resource has been freed. Implemented in resources.
    void notify_of_free(void *resource);
}
#endif /* utility_functions_h */
