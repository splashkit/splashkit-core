//
//  utility_functions.cpp
//  splashkit
//
//  Created by Andrew Cain on 29/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "utility_functions.h"

#include "camera.h"

#include <sys/stat.h>
#include <iostream>

using namespace std;

template <typename T>
bool is_valid_pointer(T ptr, pointer_identifier id)
{
    return ptr && ptr->id == id;
}

bool file_exists(const string path)
{
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0);
}

bool directory_exists(const string path)
{
    struct stat buffer;
    return (stat (path.c_str(), &buffer) == 0) and ( (buffer.st_mode & S_IFDIR) != 0);
}

string directory_of(const string filename)
{
    size_t found;
    found = filename.find_last_of("/\\");
    return filename.substr(0, found);
}

void raise_warning( string message )
{
    cerr << message << endl;
}

string cat(std::initializer_list<string> list)
{
    string result("");
    
    for ( string elem : list )
    {
        result += elem;
    }
    
    return result;
}

string path_from(std::initializer_list<string> list, string filename)
{
#ifdef WINDOWS
#define PATH_SEP "\\"
#else
#define PATH_SEP "/"
#endif
    
    string result("");
    
    for ( string elem : list )
    {
        result += elem;
        if(elem.find_last_of(PATH_SEP) < elem.length() - 1)
             result += PATH_SEP;
    }
    
    return result + filename;
}

struct unknown_data {
    pointer_identifier id;
};

pointer_identifier ptr_kind(void *p)
{
    unknown_data *ptr;
    
    ptr = static_cast<unknown_data *>(p);
    
    if (ptr)
        return ptr->id;
    else
        return NONE_PTR;
}

_window_data *to_window_ptr(void *w)
{
    _window_data *result = static_cast<_window_data *>(w);
    
    if (result and (result->id != WINDOW_PTR) )
    {
        raise_warning("Attempted to access a Window that appears to be an invalid pointer\n");
        result = nullptr;
    }
    
    return result;
}

_bitmap_data *to_bitmap_ptr(void *b)
{
    _bitmap_data *result = static_cast<_bitmap_data *>(b);
    
    if (result and (result->id != BITMAP_PTR) )
    {
        raise_warning("Attempted to access a Bitmap that appears to be an invalid pointer\n");
        result = nullptr;
    }
    
    return result;
}

sk_drawing_surface *to_surface_ptr(void *p)
{
    pointer_identifier id;
    _window_data *w;
    _bitmap_data *b;
    
    id = ptr_kind(p);
    
    if (id == WINDOW_PTR)
    {
        w = to_window_ptr(p);
        return &w->image.surface;
    }
    else if (id == BITMAP_PTR)
    {
        b = to_bitmap_ptr(p);
        return &b->image.surface;
    }
    else
    {
        raise_warning("Attempting to draw to a surface that does not exist.");
        return  nullptr;
    }
}

void xy_from_opts(drawing_options &opts, float &x, float &y)
{
    // check cases where drawn without camera...
    switch (opts.camera)
    {
        case DRAW_TO_SCREEN:
            return;
        case DRAW_TO_WORLD:
            break;
        case DRAW_DEFAULT:
            pointer_identifier id = ptr_kind(opts.dest);
            if (id != WINDOW_PTR) return;
            break;
    }
    
    // update location using camera
    x = to_screen_x(x);
    y = to_screen_y(y);
}
