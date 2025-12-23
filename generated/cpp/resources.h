//
// SplashKit Generated Resources C++ Code
// DO NOT MODIFY
//

#ifndef __resources_h
#define __resources_h

#include <string>
#include <vector>
#include <cmath>
#include <cstdint>
using std::string;
using std::vector;
using std::to_string;

typedef enum {
    ANIMATION_RESOURCE,
    BUNDLE_RESOURCE,
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
/**
* Remove the function from the list of functions receiving notification
* of resource freeing.
* @param handler The function to remove
*
*/;
void deregister_free_notifier(free_notifier *handler);
/**
* Gets the path to a give file of a certain resource kind.
* @param filename The name of the file of the resource kind.
* @param kind The kind of resource you are loading.
* @return The full path to the resource.
*/;
string path_to_resource(const string &filename, resource_kind kind);
/**
* Returns the path to the resources folder for the SplashKit program. This
* will be auto detected at startup, but can be changed using
* `set_resources_path`.

* @return Path to SplashKit Resources folder.
*/;
string path_to_resources();
/**
* Returns the path to the folder containing a given resource kind. This is
* the path SplashkKit will search when you load a resource.
* @param kind The type of resource you want the path for.
* @return The path to the folder containing this kind of resource.
*/;
string path_to_resources(resource_kind kind);
/**
* Register a function to be called when any resource is freed.
* @param fn The function to be called when a resource is freed.
*
*/;
void register_free_notifier(free_notifier *fn);
/**
* Sets the path to the SplashKit resources folder. Resource paths are then
* located within this folder.
* @param path The file path to the SplashKit Resources folder.
*
*/;
void set_resources_path(const string &path);

#endif /* __resources_h */
