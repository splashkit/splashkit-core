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
namespace splashkit_lib
{
    /**
     * SplashKit is able to manage a number of different kinds of resources
     * for you.
     */
    enum resource_kind
    {
        /**
         * Sound resources can be played as sound effects, and live in the
         * program's Resources/sounds folder.
         */
        SOUND_RESOURCE,

        /**
         * Music resources can be played as music, and live in the
         * program's Resources/sounds folder.
         */
        MUSIC_RESOURCE,

        /**
         * Animation scripts are loaded as Animation resources. These are
         * located in the projects Resources/animations folder.
         */
        ANIMATION_RESOURCE,

        /**
         * Resource bundles contain lists of other resources. These are
         * located in the projects Resources/bundles folder.
         */
        BUNDLE_RESOURCE,

        /**
         * Database resources are located in Resources/databases folder.
         */
        DATABASE_RESOURCE,

        /**
         * Image resources are located in Resources/images.
         */
        IMAGE_RESOURCE,

        /**
         * Fonts resources are located in Resources/fonts.
         */
        FONT_RESOURCE,

        /**
         * Timer resources are not saved to file, but can be created by
         * SplashkKit resource bundles.
         */
        TIMER_RESOURCE,

        /**
         * Json resources are located in the projects Resources/json folder.
         */
        JSON_RESOURCE,

        /**
         * Other resources can be loaded, these will be located directly in these
         * project's Resources folder.
         */
        OTHER_RESOURCE
    };

    /**
     * Sets the path to the SplashKit resources folder. Resource paths are then
     * located within this folder.
     *
     * @param path The file path to the SplashKit Resources folder.
     */
    void set_resources_path(const string &path);

    /**
     * Returns the path to the resources folder for the SplashKit program. This
     * will be auto detected at startup, but can be changed using
     * `set_resources_path`.
     *
     * @return Path to SplashKit Resources folder.
     */
    string path_to_resources();

    /**
     * Returns the path to the folder containing a given resource kind. This is
     * the path SplashkKit will search when you load a resource.
     *
     * @param  kind The type of resource you want the path for.
     * @return      The path to the folder containing this kind of resource.
     */
    string path_to_resources(resource_kind kind);

    /**
     * Gets the path to a give file of a certain resource kind.
     *
     * @param  filename The name of the file of the resource kind.
     * @param  kind     The kind of resource you are loading.
     * @return          The full path to the resource.
     */
    string path_to_resource(const string &filename, resource_kind kind);

}
#endif /* resources_hpp */
