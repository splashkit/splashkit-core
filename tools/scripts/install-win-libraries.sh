#!/bin/bash

echo "This is just a start... need to complete the list!"
pacman -S git mingw-w64-x86_64-toolchain mingw-w64-x86_64-SDL2 mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-SDL2_image mingw-w64-x86_64-SDL2_ttf mingw-w64-x86_64-SDL2_net mingw-w64-x86_64-cmake make mingw-w64-x86_64-SDL2_mixer mingw-w64-x86_64-civetweb

echo "To check libraries used..."
ldd SplashKit.dll | grep mingw64 | sed 's/.*=> /cp /' - | sed 's/ (.*)/ ./' -