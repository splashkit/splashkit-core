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
using namespace std;

#include <initializer_list>

void raise_warning( string message );

bool file_exists(string path);

bool directory_exists(string path);

#define VALID_PTR(p,pkind) ( (p) and p->id == pkind )
#define INVALID_PTR(p,pkind) ( not VALID_PTR(p,pkind) )

#define ASSIGNED(ptr) ( ptr != nullptr )


string cat(std::initializer_list<string> list);

string path_from(std::initializer_list<string> list, string filename = string(""));

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

pointer_identifier ptr_kind(void *p);

_bitmap_data *to_bitmap_ptr(void *b);
_window_data *to_window_ptr(void *w);

sk_drawing_surface *to_surface_ptr(void *p);
void xy_from_opts(drawing_options &opts, float &x, float &y);

void process_range(string value_in, vector<int> &result);

string extract_delimited(int index, string value, char delim);
string extract_delimited_with_ranges(int index, string value);

int count_delimiter(string value, char delimiter);
int count_delimiter_with_ranges(string value, char delimiter);

int str_to_int(string str, bool allow_empty = true, int empty_value = 0);
float str_to_float(string str, bool allow_empty = true, float empty_value = 0.0f);
float str_to_double(string str, bool allow_empty = true, double empty_value = 0.0);

bool try_str_to_int(string str, int &result);
bool try_str_to_float(string str, float &result);
bool try_str_to_double(string str, double &result);

string to_lower (string str);

#endif /* utility_functions_h */
