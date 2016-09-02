#!/bin/bash
if [[ $TRAVIS_OS_NAME == 'linux' ]]; then
    echo "Installing Linux Dependencies"
    sudo apt-get install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
    sudo apt-get install libcurl4-openssl-dev libmikmod2-dev
    sudo apt-get install libflac-dev libwebp-dev libvorbis-dev libpng-dev
else
    echo "Installing macOS Dependencies"
    # None!
fi
