# Pacman Package for mingw

Note: Needs to be reviewed before using.

This directory contains the `PKGBUILD` file and `mingw-w64-x86_64-splashkit-1.0.0-1-x86_64.pkg.tar`
pacman package of the Splashkit C++ library.

## Overview

The `PKGBUILD` file contains the instructions that the pacman `make-pkg` command will use to create the pacman package.
Two main parts of this file are:

1. `build()`
2. `package()`

### build()

Commands in this section are used when the package is being made.
In this case it is used to clone the files from github into the `/src` directory of the package.

### package()

The commands located in this section are run when the user installs the package on there device.
Splashkit package creates the directories `/include/splashkit` & `/lib` within the `/msys64` directory.
Files from the `/src` file are copied into their needed locations.

Note: With the current `PKGBUILD` file you **will** be able to compile C++ programs that use the Splashkit library.
However, these files **will not** be able to run as the `PATH ENVIRONMENT` variable has not been set to use the
dependant `.dll` files.
This is the current roadblock stopping progression, Pacman packages run in a seperate instance so they are not given
the neccasery privellages to make these changes to my knowledge, nor the ability to access the `/msys64/home/<user>/` directory.

## Testing and Useful Commands

Ensure that all currently related splashkit files are uninstalled from the system before continuing.

### Making and Installing splashkit pacman package

1. Open msys64 terminal and if this is the first time creating a pacman package, run:`pacman -S --needed base-devel`.
2. Access a preffered directory using `cd`, create and enter a dir called `mingw-w64-splashkit`.
3. Within `/mingw-w64-splashkit` dir, add `PKGBUILD` file.
4. Run `makepkg-mingw --cleanbuild --syncdeps --force --noconfirm` to build the package from the `PKGBUILD` file.
5. Run `pacman -U *.pkg.tar.zst` to install the package.

This should have created the pacman package based off of the `PKGBUILD` file and then installed it onto the device.
To remove the package run `pacman -R mingw-w64-x86_64-splashkit` in the terminal and all associated file should be removed.

Note: When running the `make-pkg` command we will have current user permission, but not when installing the package with `pacman -U`.

### Compiling and Running Programs

With the installation complete, we are able to compile programs that depend on the Splashkit toolkit.
Using `clang++ <filename>.cpp -l splashkit -o <filename>` we are able to create an .exe file of out program:

As meantioned in [Overview](#overview) we will not be able to run the compiled file, due to the needed `.dll` not being registered by the systems `PATH ENVIRONMENT` variable.
The current solution is to run `bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh)`.
This is the install script located on the [skm](https://github.com/thoth-tech/skm) repository which installs the skm repo to `/msys64/home/<user>/.splashkit` and setting the `PATH ENVIRONMENT` variable to the needed locations.

After running the compiler and `bash <(curl -s https://raw.githubusercontent.com/splashkit/skm/master/install-scripts/skm-install.sh)` (only needs to be done once) the compiled file will succesfully run.

## Moving Forward

The main issue is not having the needed files within the systems `PATH ENVIRONMENT` variable by just using the pacman package.
Two ways of moving forward are:

1. Figuring out how to place the needed `.dll` files in a location that is already part of the systems `PATH ENVIRONMENT` variable.
2. How to install the repo into `/msys64/home/<user>/.splashkit` dir and adding that to the `PATH ENVIRONMENT` variable.
Both of these methods require more privelage then that which is given during the pacman installation.
