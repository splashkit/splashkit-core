//
//  resources.cpp
//  splashkit
//
//  Created by Andrew Cain on 12/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#include "resources.h"
#include "utility_functions.h"

#include <stdio.h>
#include <unistd.h>
#include <iostream>

#ifdef __APPLE__
#include <CoreFoundation/CoreFoundation.h>
#endif

#ifdef WINDOWS
#include <windows.h>
#endif

// Appveyor MSYS hack...
#ifndef PATH_MAX
#define PATH_MAX 1024
#endif

#ifdef __linux__
#include <linux/limits.h>
#include <libgen.h>
#endif
namespace splashkit_lib
{
    // Free notifiers are called when resources are deleted.
    static vector<free_notifier *> _free_notifiers;

    static bool     _has_resources_path = false;
    static string   _resources_path = "";

    void set_resources_path(const string &path)
    {
        //    cout << "Setting path to: " << path << endl;
        _has_resources_path = true;
        _resources_path = path;
    }

    /// Try to set the resource path by exploring sub directories and parent
    /// directories of the supplied path.
    bool _try_set_resource_path(string path)
    {
        string tmpPath;

        // test in current location: cwd
        tmpPath = path_from( { path, "Resources" } );
        if (directory_exists(tmpPath))
        {
            set_resources_path(tmpPath);
            return true;
        }

        // in the parent directory: eg. bin
        tmpPath = path_from( { path, "..", "Resources"} );
        if (directory_exists(tmpPath))
        {
            set_resources_path(tmpPath);
            return true;
        }

        // in the parent's parent: bin/Debug
        tmpPath = path_from( { path, "..", "..", "Resources"});
        if (directory_exists(tmpPath))
        {
            set_resources_path(tmpPath);
            return true;
        }

        return false;
    }

    void _guess_resources_path()
    {
        string      path;
        char        cwd[PATH_MAX];

#ifdef __APPLE__
        char        bndlPath[PATH_MAX];
        CFBundleRef mainBundle = nullptr;
        CFURLRef    mainBundleURL = nullptr;
        CFStringRef cfStringRef = nullptr;
#else
        char        exePath[PATH_MAX];
#endif

        if(getcwd(cwd, PATH_MAX))
        {
            if ( _try_set_resource_path(cwd)) return;

#ifdef __APPLE__
            // search bundle
            mainBundle = CFBundleGetMainBundle();
            if (mainBundle)
            {
                mainBundleURL = CFBundleCopyBundleURL(mainBundle);
                if (mainBundleURL)
                {
                    // Release the main bundle when this goes out of scope...
                    auto deleteMainBundleURL = finally( [mainBundleURL] { CFRelease(mainBundleURL); } );

                    cfStringRef = CFURLCopyFileSystemPath(mainBundleURL, kCFURLPOSIXPathStyle);
                    if (cfStringRef)
                    {
                        CFStringGetCString(cfStringRef, bndlPath, PATH_MAX, kCFStringEncodingASCII);
                        CFRelease(cfStringRef);

                        // Default bundle location
                        path = string(bndlPath) + "/Contents/MacOS";
                        if ( _try_set_resource_path(path) )
                        {
                            return;
                        }
                    }
                }

            }

#elif __linux__
            if(readlink( "/proc/self/exe", exePath, PATH_MAX ))
            {
                // Strips the executable name from the path
                dirname(exePath);
                if( _try_set_resource_path(exePath) ) return;
            }

#elif WINDOWS
            if (GetModuleFileName( NULL, exePath, MAX_PATH ))
            {
                if(_try_set_resource_path(exePath))
                    return;
            }
#endif

            set_resources_path(cwd);
            return;
        }
    }

    string path_to_resources()
    {
        if ( ! _has_resources_path ) _guess_resources_path();
        return _resources_path;
    }

    string path_to_resources(resource_kind kind)
    {
        string path = path_to_resources();

        switch(kind)
        {
            case SOUND_RESOURCE:        return path_from({ path, "sounds" });
            case MUSIC_RESOURCE:        return path_from({ path, "sounds" });
            case BUNDLE_RESOURCE:       return path_from({ path, "bundles" });
            case IMAGE_RESOURCE:        return path_from({ path, "images" });
            case FONT_RESOURCE:         return path_from({ path, "fonts" });
            case ANIMATION_RESOURCE:    return path_from({ path, "animations" });
            case JSON_RESOURCE:         return path_from({ path, "json" });
            case SERVER_RESOURCE:       return path_from({ path, "server" });
            case DATABASE_RESOURCE:     return path_from({ path, "databases" });
            case OTHER_RESOURCE:        return path;
            default:
                LOG(WARNING) << "Attempting to get path to unknown resource kind.";
                return path;
        }
    }
    
    string path_to_resource(const string &filename, resource_kind kind)
    {
        return path_from( { path_to_resources(kind) }, filename );
    }

    void register_free_notifier(free_notifier *fn)
    {
        _free_notifiers.push_back(fn);
    }

    void deregister_free_notifier(free_notifier *handler)
    {
        if (not erase_from_vector(_free_notifiers, handler))
        {
            LOG(WARNING) << "Not able to deregister handler -- handler not registered.";
        }
    }

    void notify_of_free( void *resource )
    {
        for ( free_notifier *fn : _free_notifiers )
        {
            fn ( resource );
        }
    }
}
