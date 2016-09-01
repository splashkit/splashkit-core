/**
 * @header  bundles
 * @author  Andrew Cain
 * @brief   SplashKit resource bundles allow you to quickly and easily load a
 *          number of resources.
 *
 *  Supports the loading and freeing of game resource bundles. Resource types
 *  include images, sounds, music and animation files to name a few. Resource
 *  files must be saved in specific locations of a **Resources** folder for
 *  your game.
 *
 * @attribute static resource_bundle
 */

//
//  bundles.hpp
//  splashkit
//
//  Created by Andrew Cain on 29/08/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef bundles_h
#define bundles_h

#include <string>
using namespace std;

/**
 * Loads all of the resources in the resource bundle. The resource bundle is a
 * text file that describes the resources you want to load. These rescources
 * are then loaded when you call this procedure, and can all be released when
 * you call `release_resource_bundle`.
 *
 * Save the resource bundle text files into your projects **Resources** in the
 * **bundles** folder. Use the following as the format for each of the
 * resources.
 *
 * Start a line with a // to have it ignored when the bundle is loaded. This
 * can be used to add comments to your bundle.
 *
 * To load an **animation** use the format: ANIM,name,filename. For example, the
 * following will load an animation named "WalkingScript" that loads the
 * animation from "kermit.txt" in your games animation Resources.
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

#endif /* bundles_hpp */
