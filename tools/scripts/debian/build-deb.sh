#!/bin/bash

PKG_NAME=libsplashkit-dev_1.0.0_amd64
SK_ROOT=../../../
SKM_OUT=$SK_ROOT/out/skm

# Build libSplashKit.so
pushd $SK_ROOT/tools/scripts/cmake/libsplashkit
cmake .
make install
popd

# Setup deb directory structure
mkdir -p $PKG_NAME/DEBIAN \
    $PKG_NAME/usr/lib \
    $PKG_NAME/usr/include/splashkit \
    $PKG_NAME/usr/share/doc/libsplashkit-dev

cp control $PKG_NAME/DEBIAN
cp copyright $PKG_NAME/usr/share/doc/libsplashkit-dev
cp splashkit.h $PKG_NAME/usr/include

cp $SK_ROOT/README.md $PKG_NAME/usr/share/doc/libsplashkit-dev

cp $SKM_OUT/lib/linux/libSplashKit.so $PKG_NAME/usr/lib
cp $SKM_OUT/g++/include/* $PKG_NAME/usr/include/splashkit

# Build package

# The resulting directory $PKG_NAME can be used with `dpkg-deb --build` however
# that requires the script to be running on a debian system. The following
# builds the deb manually using tar and ar.

tar -C $PKG_NAME -cJf data.tar.xz usr
tar -C $PKG_NAME/DEBIAN -cJf control.tar.xz control

ar r $PKG_NAME.deb debian-binary control.tar.xz data.tar.xz
