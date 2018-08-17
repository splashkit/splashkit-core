/**
 * @header  bundles
 * @author  Andrew Cain
 * @brief   SplashKit resource bundles allow you to quickly and easily load a
 *          number of resources in the `Resources` folder.
 *
 *  Supports the loading and freeing of game resource bundles. Resource types
 *  include images, sounds, music and animation files to name a few. Resource
 *  files must be saved in specific locations of a `Resources` folder for
 *  your game.
 *
 * @attribute group  resource_bundles
 * @attribute static resource_bundle
 */

#ifndef bundles_h
#define bundles_h

#include <string>
using std::string;

namespace splashkit_lib
{
    /**
     * Loads all of the resources in the resource bundle. The resource bundle is a
     * text file that describes the resources you want to load. These rescources
     * are then loaded when you call this procedure, and can all be released when
     * you call `release_resource_bundle`.
     *
     * Save the resource bundle text files into your projects `Resources` in the
     * `bundles` folder. Use the following as the format for each of the
     * resources.
     *
     * Start a line with a `//` to have it ignored when the bundle is loaded. This
     * can be used to add comments to your bundle.
     *
     *
     * -  To load an **animation** use the format:
     *
     *    ```
     *    ANIM,name,filename
     *    ```
     *
     *    For example, the following will load an animation named "WalkingScript" that
     *    loads the animation from "kermit.txt" in your games animation `Resources`.
     *
     *    ```
     *    ANIM,WalkingScript,kermit.txt
     *    ```
     *
     * -  To load a **bitmap** use the format: 
     *
     *    ```
     *    BMP,name,filename
     *    ```
     *
     *    For example, the following will load a bitmap named "Logo" using the
     *    "Logo.png" file.
     *
     *    ```
     *    BITMAP,Logo,logo.png
     *    ```
     *
     * -  To load a **bitmap** that has a number of cells, you can extend the
     *    bitmap format with the cell details. This has the format:
     *
     *    ```
     *    BMP,name,filename,cell-width,cell-height,columns,rows,count
     *    ```
     *
     *    The following will setup the "Player" bitmap to have cells that are 75
     *    pixels wide, and 42 pixels height. There are 4 columns in 1 row, giving
     *    a total of 4 cells.
     *
     *    ```
     *    BITMAP,Player,player.png,75,42,4,1,4
     *    ```
     *
     * -  To load a font use FONT,name,filename. For example, the following loads a
     *    font named "GameFont" that represents the "demolition.otf".
     *
     *    ```
     *    FONT,GameFont,demolition.otf
     *    ```
     *
     * -  To load music, use MUSIC,name,filename. The following loads "GameMusic"
     *    for the "magical_night.ogg" file.
     *
     *    ```
     *    MUSIC,GameMusic,magical_night.ogg
     *    ```
     *
     * -  To load a sound effect, use SOUND,name,filename. For example the following
     *    loads "error" from the "error.wav" file.
     *
     *    ```
     *    SOUND,error,error.wav
     *    ```
     *
     * -  To create a timer use TIMER,name. The following creates a timer named as
     *    "my timer".
     *
     *    ```
     *    TIMER,my timer
     *    ```
     *
     * -  You can also load another resource bundle using BUNDLE,name,filename.
     *    The following loads "another bundle" from the "another.txt" file.
     *
     *    ```
     *    BUNDLE,another bundle,another.txt
     *    ```
     *
     * @param name      The name of the bundle when it is loaded.
     * @param filename  The filename to load.
     */
    void load_resource_bundle(const string &name, const string &filename);

    /**
     * Returns true when the named resource bundle has already been loaded.
     *
     * @param name  The name of the resource bundle.
     * @returns     True when the bundle is already loaded.
     */
    bool has_resource_bundle(const string &name);

    /**
     * When you are finished with the resources in a bundle, you can free them all
     * by calling this procedure. It will free the resource bundle and all of the
     * associated resources.
     *
     * @param name  The name of the resource bundle to be freed
     */
    void free_resource_bundle(const string name);

    void free_all_resource_bundles();

#endif /* bundles_hpp */
}
