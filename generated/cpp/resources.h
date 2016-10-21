//
// SplashKit Generated Resources C++ Code
// DO NOT MODIFY
//

#ifndef __resources_h
#define __resources_h

#include "resources.h"
#include <string>
#include <vector>
using std::string;
using std::vector;

typedef enum {
    ANIMATION_RESOURCE,
    BUNDLE_RESOURCE,
    DATABASE_RESOURCE,
    FONT_RESOURCE,
    IMAGE_RESOURCE,
    JSON_RESOURCE,
    MUSIC_RESOURCE,
    SERVER_RESOURCE,
    SOUND_RESOURCE,
    TIMER_RESOURCE,
    OTHER_RESOURCE
} resource_kind;
typedef void (free_notifier)(void *pointer);
void deregister_free_notifier(free_notifier *handler);
string path_to_resource(const string &filename, resource_kind kind);
string path_to_resources();
string path_to_resources(resource_kind kind);
void register_free_notifier(free_notifier *fn);
void set_resources_path(const string &path);

#endif /* __resources_h */
