#!/bin/bash
if [[ $TRAVIS_OS_NAME == 'linux' ]]; then
    echo "Installing Linux Dependencies"
    sudo apt-get -qq update
    sudo apt-get install -y libegl1-mesa-dev libgles2-mesa-dev
    sudo apt-get install -y libflac-dev libwebp-dev libvorbis-dev libpng-dev
    sudo apt-get install -y libcurl4-openssl-dev libmikmod2-dev
    sudo apt-get install -y libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
else
    echo "Installing macOS Dependencies"
    # None!
fi
