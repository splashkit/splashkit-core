# Debian Package for Linux

Note: Needs to be reviewed before using.

This directory contains files and scripts for building a Debian binary package
(.deb) of the splashkit C++ library.

**TL;DR:** run `./build-deb.sh` inside this directory to build the deb file.

This directory contains the following files

## build-deb.sh

This script assembles a debian package using the following steps.

1. Build the Splashkit C++ library (if not already)
2. Construct the required directory structure
3. Copy the control, copyright, libSplashKit.so debian-binary and splashkit.h
   files to the correct locations (See Note)
4. Assemble the deb file

Note: The resulting directory can be used with `dpkg-deb --build` however that
requires the script to be running on a debian system. Therefore the build
script assembles the deb manually using tar and ar, meaning that one can run
the script on any unix like operating system.

### Dependencies

The `build-deb.sh` script depends on the following

- **bash**
- **tar**: should be already installed on any unix like OS
- **ar**: provided by the GNU binutils package (e.g. `apt install binutils`)

## control

This is a Debian *binary* control file. This states the package name, version,
author and depenencies.

## copyright

This file contains the licencing information for the splashkit project.

## splashkit.h

When installing the splashkit headers, the package installs them to
`/usr/include/splashkit`, however by default compilers will only search the
`/usr/include` directory and will not recurse into the splashkit sub directory.
However we don't want to just dump all of splashkit's headers into the
`/usr/include` directory as it would make splashkit significantly harder to
later uninstall. Therefore we need a header in `/usr/include` that prorgams can
include which itself will include `/usr/include/splashkit/splashkit.h/`.

## debian-binary

A simple text file which states the version of the debian binary format. Should
contain `2.0`.
