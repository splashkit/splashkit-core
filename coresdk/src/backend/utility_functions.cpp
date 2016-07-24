//
//  utility_functions.cpp
//  splashkit
//
//  Created by Andrew Cain on 29/06/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "utility_functions.h"

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

