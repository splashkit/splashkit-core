
//
//  utils.hpp
//  splashkit
//
//  Created by Andrew Cain on 23/07/2016.
//  Copyright © 2016 Andrew Cain. All rights reserved.
//

#ifndef utils_hpp
#define utils_hpp

#include "resources.h"

#include <iostream>
#include <string>

namespace splashkit_lib
{
    /// Puts the program to sleep for a specified number of
    /// milliseconds.
    ///
    void delay(unsigned int milliseconds);

    /// Gets the number of milliseconds that have passed since the progrma was started.
    ///
    unsigned int current_ticks();

    /**
     * Return a SplashKit resource of `resource_kind` with name `filename`
     * as a string.
     *
     * @param filename The filename of the resource.
     * @param kind The kind of resource.
     *
     * @returns The file loaded into a string.
     */
    string file_as_string(string filename, resource_kind kind);
}
#endif /* utils_hpp */