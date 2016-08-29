//
//  bundles.cpp
//  splashkit
//
//  Created by Andrew Cain on 29/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "bundles.h"

#include "types.h"
#include "resources.h"
#include "utility_functions.h"

#include <map>
#include <vector>
#include <iostream>
#include <fstream>

struct bundled_resource
{
    resource_kind kind;
    string name;
};

struct resource_bundle
{
    string                      name;
    string                      filename;
    vector<bundled_resource>    resources;
};

static map<string, resource_bundle> _resource_bundles;


bool has_resource_bundle(const string &name)
{
    return _resource_bundles.count(name) > 0;
}

resource_kind string_to_resource_kind(const string &txt)
{
    string kind = txt;
    to_upper(kind);
    
    if ( kind == "BUNDLE" ) return BUNDLE_RESOURCE;
    else if ( kind == "BITMAP") return IMAGE_RESOURCE;
    else if ( kind == "TIMER" ) return TIMER_RESOURCE;
    else if ( kind == "SOUND" ) return SOUND_RESOURCE;
    else if ( kind == "MUSIC" ) return MUSIC_RESOURCE;
    else if ( kind == "FONT"  ) return FONT_RESOURCE;
    else if ( kind == "ANIM"  ) return ANIMATION_RESOURCE;
    else return OTHER_RESOURCE;
}

void load_resource_bundle(const string &name, const string &filename)
{
    if ( has_resource_bundle(name) )
    {
        raise_warning("Attempting to load resource bundle twice.");
        return;
    }

    string path = path_to_resource(filename, BUNDLE_RESOURCE);

    if ( ! file_exists(path) )
    {
        raise_warning(cat({ "Unable to locate bundle file for ", name, " (", path, ")"}));
        return;
    }

    int line_no = 0;
    string line;
    ifstream input(path);

    resource_bundle result;

    auto process_line = [&]()
    {
        //resource_kind kind = string_to_resource_kind(extract_delimited(1, line, ','));
        
        return;
    };

    while (getline(input, line))
    {
        line_no = line_no + 1;

        line = trim(line);
        if (line.length() == 0) continue;  //skip empty lines
        if (line.substr(0,2) == "//") continue; //skip lines starting with //

        process_line();
    }
}
