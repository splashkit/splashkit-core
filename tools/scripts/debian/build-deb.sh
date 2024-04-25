#!/bin/bash

PKG_NAME=libsplashkit-dev_1.0.0_amd64
SK_ROOT=../../../
LIBSPLASHKIT_DIR=$SK_ROOT/tools/scripts/cmake/libsplashkit
SKM_OUT=$SK_ROOT/out/skm

# Build libSplashKit.so
pushd $LIBSPLASHKIT_DIR
cmake .
make -j$nprocs
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
dpkg-deb --build $PKG_NAME
