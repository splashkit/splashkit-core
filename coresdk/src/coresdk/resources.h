//
//  resources.hpp
//  splashkit
//
//  Created by Andrew Cain on 12/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef resources_hpp
#define resources_hpp

#include <string>

using namespace std;

enum resource_kind
{
    AUDIO_RESOURCE,
    ANIMATION_RESOURCE,
    DATABASE_RESOURCE,
    IMAGE_RESOURCE,
    FONT_RESOURCE,
    OTHER_RESOURCE
};

void set_resources_path(string path);
string path_to_resources();

string path_to_resources(resource_kind kind);

string path_to_resource(const string filename, resource_kind kind);

#endif /* resources_hpp */
