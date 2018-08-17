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
#include <string>
#include <locale>
#include <algorithm>

#include <cstdlib>

#include <unistd.h>
#include <sys/types.h>

#ifndef WINDOWS
#include <pwd.h>
#else
#include <Windows.h>
#include <Shlobj.h>
#endif

using std::string;
using std::locale;

namespace splashkit_lib
{
#define PI 3.141592653589793238L

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

    string get_env_var(const string &name)
    {
        char * val = getenv( name.c_str() );
        return val == NULL ? string("") : string(val);
    }

    string path_to_user_home()
    {
#ifndef WINDOWS
        struct passwd *pw = getpwuid(getuid());
        return string(pw->pw_dir);
#else
        WCHAR path[MAX_PATH];
        if (SUCCEEDED(SHGetFolderPathW(NULL, CSIDL_PROFILE, NULL, 0, path)))
        {
            char ch[260];
            char DefChar = ' ';
            WideCharToMultiByte(CP_ACP,0,path,-1, ch,260,&DefChar, NULL);

            return string(ch);
        }
        else
        {
            return get_env_var("HOMEDRIVE") + get_env_var("HomePath");
        }
#endif
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

    string to_lower (string str)
    {
        string result = "";
        locale loc;

        for(auto elem : str)
            result += std::tolower(elem,loc);

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
        bool first = true;
        for ( string elem : list )
        {
            if(elem.find(PATH_SEP) == 0 and not first)
                elem.erase(0,1);
            result += elem;
            if(elem.find_last_of(PATH_SEP) < elem.length() - 1)
                result += PATH_SEP;

            first = false;
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
            LOG(WARNING) << "Attempted to access a Window that appears to be an invalid pointer\n";
            result = nullptr;
        }

        return result;
    }

    _bitmap_data *to_bitmap_ptr(void *b)
    {
        _bitmap_data *result = static_cast<_bitmap_data *>(b);

        if (result and (result->id != BITMAP_PTR) )
        {
            LOG(WARNING) << "Attempted to access a Bitmap that appears to be an invalid pointer\n";
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
            LOG(WARNING) << "Attempting to draw to a surface that does not exist.";
            return  nullptr;
        }
    }

    void xy_from_opts(const drawing_options &opts, double &x, double &y)
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

    string extract_delimited(int index, string value, char delimiter)
    {
        int at_index = 1; // 1 based
        int i;
        string result;

        for (i = 0; i < value.length(); i++)
        {
            if( at_index >= index ) break; // past delimeter
            if( value[i] == delimiter )
            {
                at_index++;
            }
        }

        for (; i < value.length(); i++)
        {
            if( value[i] != delimiter )
            {
                result += value[i];
            }
            else break;
        }

        return result;
    }

    string extract_delimited_with_ranges(int index, string value)
    {
        int i, count, start;
        bool in_range;

        //SetLength(result, 0);
        in_range = false;
        string result = "";
        count = 1; //1 is the first index... not 0

        // Find the start of this delimited range
        for ( i = 0; i < value.size(); i++)
        {
            if (count == index) break;

            if ((not in_range) and (value[i] == ','))
                count += 1;
            else if ((in_range) and (value[i] == ']'))
                in_range = false;
            else if ((not in_range) and (value[i] == '['))
                in_range = true;
        }

        if (count != index) return result;

        in_range = false;
        start = i;

        for (i = start; i < value.size(); i++)
        {
            if ((not in_range) and (value[i] == ','))
                break;
            else if ((in_range) and (value[i] == ']'))
                in_range = false;
            else if ((not in_range) and (value[i] == '['))
                in_range = true;

            result += value[i];
        }

        return result;
    }

    int count_delimiter(string value, char delimiter)
    {
        int count = 0;
        for_each(value.begin(), value.end(), [&](char ch){if(ch == delimiter) count++;});
        return count;
    }

    int count_delimiter_with_ranges(string value, char delimiter)
    {
        int i;
        bool in_range = false;
        int result = 0;

        for ( i = 0; i < value.size(); i++ )
        {
            if ((not in_range) and (value[i] == delimiter))
                result++;
            else if (value[i] == '[')
                in_range = true;
            else if (value[i] == ']')
                in_range = false;
        }

        return result;
    }

    bool try_str_to_int(string str, int &result)
    {
        char temp;  //used to check nothing comes after the int

        // scan the string, looking for a number ... followed by nothing
        // sscanf = string scan format
        //          This will "scan" the array of character in line.str (reads this)
        //          " " = skip any spaces
        //          "%d" = read an integer
        //          " " = skip any spaces
        //          "%c" = read a character
        // sscanf returns the number of things it read (0 to 2 in this case)
        //          Loop while this is not equal to 1
        //          0 = did not read a number at the start
        //          1 = read a number, but no character followed it
        //          2 = read a number and a character... like "1 fred" (1 is the number, f is the character)
        if ( sscanf(str.c_str(), " %d %c", &result, &temp) != 1 )
        {
            return false;
        }

        return true;
    }

    int str_to_int(string str, bool allow_empty, int empty_value)
    {
        int result;

        if (allow_empty and str.size() == 0) return empty_value;

        if ( ! try_str_to_int(str, result) )
        {
            // scan found a number followed by something... so its not a whole number
            LOG(WARNING) << "Attempted to convert " + str + " to an integer.";

            try
            {
                result = stoi(str);
            }
            catch (...)
            {
                result = empty_value;
            }
        }

        return result;
    }

    bool try_str_to_float(string str, float &result)
    {
        char temp;  //used to check nothing comes after the int

        // scan the string, looking for a number ... followed by nothing
        // sscanf = string scan format
        //          This will "scan" the array of character in line.str (reads this)
        //          " " = skip any spaces
        //          "%d" = read an integer
        //          " " = skip any spaces
        //          "%c" = read a character
        // sscanf returns the number of things it read (0 to 2 in this case)
        //          Loop while this is not equal to 1
        //          0 = did not read a number at the start
        //          1 = read a number, but no character followed it
        //          2 = read a number and a character... like "1 fred" (1 is the number, f is the character)
        if ( sscanf(str.c_str(), " %f %c", &result, &temp) != 1 )
        {
            return false;
        }

        return true;
    }

    float str_to_float(string str, bool allow_empty, float empty_value)
    {
        float result;

        if (allow_empty and str.size() == 0) return empty_value;

        if ( not try_str_to_float(str, result) )
        {
            // scan found a number followed by something... so its not a whole number
            LOG(WARNING) << "Attempted to convert " + str + " to an real number (float).";

            try
            {
                result = stof(str);
            }
            catch (...)
            {
                result = empty_value;
            }
        }

        return result;
    }

    bool try_str_to_double(string str, double &result)
    {
        char temp;  //used to check nothing comes after the int

        // scan the string, looking for a number ... followed by nothing
        // sscanf = string scan format
        //          This will "scan" the array of character in line.str (reads this)
        //          " " = skip any spaces
        //          "%d" = read an integer
        //          " " = skip any spaces
        //          "%c" = read a character
        // sscanf returns the number of things it read (0 to 2 in this case)
        //          Loop while this is not equal to 1
        //          0 = did not read a number at the start
        //          1 = read a number, but no character followed it
        //          2 = read a number and a character... like "1 fred" (1 is the number, f is the character)
        if ( sscanf(str.c_str(), " %lf %c", &result, &temp) != 1 )
        {
            return false;
        }

        return true;
    }

    double str_to_double(string str, bool allow_empty, double empty_value)
    {
        double result;

        if (allow_empty and str.size() == 0) return empty_value;

        if ( not try_str_to_double(str, result) )
        {
            // scan found a number followed by something... so its not a whole number
            LOG(WARNING) << "Attempted to convert " + str + " to an real number (double).";

            try
            {
                result = stod(str);
            }
            catch (...)
            {
                result = empty_value;
            }
        }

        return result;
    }

    void to_upper(string &str)
    {
        for (auto & c: str) c = toupper(c);
    }

    int sign(int value)
    {
        if (value < 0) return -1;
        return 1;
    }

    void process_range(string value_in, vector<int> &result)
    {
        int i, j, count, temp, low_part, high_part, dash_count;
        string part, value;
        
        value = trim(value_in);
        result.clear();
        
        if ((value[0] != '[') or (value[value.size() - 1] != ']'))
        {
            // is number?
            if (try_str_to_int(value, temp))
            {
                result.push_back(temp);
            }
            return; // not a range
        }
        
        value = value.substr(1, value.size() - 2);
        
        i = 0;
        count = count_delimiter(value, ',');
        
        while (i <= count)
        {
            part = trim(extract_delimited(i + 1, value, ','));
            
            if (try_str_to_int(part, temp))
            {
                //just "a" so...
                result.push_back(temp);
            }
            else //Should be range
            {
                dash_count = count_delimiter(part, '-');
                
                if ((dash_count == 1) or ((dash_count == 2) and (part[1] != '-'))) //a-b or a--b
                    low_part = str_to_int(extract_delimited(1, part, '-'));
                else //assume -a...
                    low_part = -str_to_int(extract_delimited(2, part, '-'));
                
                if (dash_count == 1) //a-b
                    high_part = str_to_int(extract_delimited(2, part, '-'));
                else if ((dash_count == 2) and (part[1] = '-')) //-a-b
                    high_part = str_to_int(extract_delimited(3, part, '-'));
                else if (dash_count == 3) //assume -a--b
                    high_part = -str_to_int(extract_delimited(4, part, '-')); //read last string
                else if (dash_count == 2) //assume a--b
                    high_part = -str_to_int(extract_delimited(3, part, '-'));
                else
                {
                    LOG(WARNING) << "Error in range.";
                    result.clear();
                    return;
                }
                
                for (j = 0; j <= abs(high_part - low_part); j++)
                {
                    //low_part + j * (-1 or +1)
                    result.push_back(low_part + (j * sign(high_part - low_part)));
                }
            }
            
            i++;
        }
    }
    
    double rad_to_deg(double radians)
    {
        return radians * 180 / PI;
    }
    
    double deg_to_rad(double degrees)
    {
        return degrees * PI / 180;
    }
}
