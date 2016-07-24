//
//  utility_functions.hpp
//  splashkit
//
//  Created by Andrew Cain on 29/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef utility_functions_hpp
#define utility_functions_hpp

#include "backend_types.h"

#include <string>
using namespace std;

#include <initializer_list>

void raise_warning( string message );

bool file_exists(string path);

bool directory_exists(string path);

#define VALID_PTR(p,pkind) ( (p) and p->id == pkind )

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

pointer_identifier ptr_kind(void *p);

_bitmap_data *to_bitmap_ptr(void *b);
_window_data *to_window_ptr(void *w);

sk_drawing_surface *to_surface_ptr(void *p);
void xy_from_opts(drawing_options &opts, float &x, float &y);


#endif /* utility_functions_hpp */
