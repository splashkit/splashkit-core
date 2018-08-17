/**
 * @header  resources
 * @author  Andrew Cain
 * @brief   SplashKit resource functions allow you to locate resources in a
 *          project's `Resources` folder.
 *
 * @attribute group  resources
 * @attribute static resources
 */

#ifndef resources_hpp
#define resources_hpp

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     * SplashKit is able to manage a number of different kinds of resources
     * for you.
     *
     * @constant ANIMATION_RESOURCE Animation scripts are loaded as Animation
     *                              resources. These are located in the projects
     *                              `Resources/animations` folder.
     * @constant BUNDLE_RESOURCE    Resource bundles contain lists of other
     *                              resources. These are located in the projects
     *                              `Resources/bundles` folder.
     * @constant DATABASE_RESOURCE  Database resources are located in the
     *                              `Resources/databases` folder.
     * @constant FONT_RESOURCE      Fonts resources are located in the
     *                              `Resources/fonts` folder.
     * @constant IMAGE_RESOURCE     Image resources are located in the
     *                              `Resources/images` folder.
     * @constant JSON_RESOURCE      JSON resources are located in the projects
     *                              `Resources/json` folder.
     * @constant MUSIC_RESOURCE     Music resources can be played as music, and
     *                              live in the program's `Resources/sounds`
     *                              folder.
     * @constant SERVER_RESOURCE    Server resources that can be sent as responses
     *                              to web server requests.
     * @constant SOUND_RESOURCE     Sound resources can be played as sound
     *                              effects, and live in the program's
     *                              `Resources/sounds` folder.
     * @constant TIMER_RESOURCE     Timer resources are not saved to file, but
     *                              can be created by SplashkKit resource
     *                              bundles.
     * @constant OTHER_RESOURCE     Other resources can be loaded, these will be
     *                              located directly in these project's
     *                              `Resources` folder.
     */
    enum resource_kind
    {
        ANIMATION_RESOURCE,
        BUNDLE_RESOURCE,
        DATABASE_RESOURCE,
        FONT_RESOURCE,
        IMAGE_RESOURCE,
        JSON_RESOURCE,
        SERVER_RESOURCE,
        MUSIC_RESOURCE,
        SOUND_RESOURCE,
        TIMER_RESOURCE,
        OTHER_RESOURCE
    };

    /**
     * The free notifier can be registered with the system. It is called every
     * time a resource is freed.
     *
     * @param pointer   The pointer to the resource that is being freed.
     */
    typedef void (free_notifier)(void *pointer);

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
     *
     * @attribute suffix for_kind
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

    /**
     * Register a function to be called when any resource is freed.
     *
     * @param fn The function to be called when a resource is freed.
     */
    void register_free_notifier(free_notifier *fn);

    /**
     * Remove the function from the list of functions receiving notification
     * of resource freeing.
     *
     * @param handler The function to remove
     */
    void deregister_free_notifier(free_notifier *handler);

}
#endif /* resources_hpp */
