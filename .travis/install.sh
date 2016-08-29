#!/bin/bash
if [[ $TRAVIS_OS_NAME == 'linux' ]]; then
    echo "Installing Linux Libraries"
    sudo apt-get install libsdl2-dev libsdl2-gfx-dev libsdl2-image-dev libsdl2-mixer-dev libsdl2-net-dev libsdl2-ttf-dev
    sudo apt-get install libcurl4-openssl-dev libmikmod2-dev
    sudo apt-get install libflac-dev libwebp-dev libvorbis-dev

    # Do not emulate the following on a typical ubuntu installthis will probably break things.
    wget http://mirrors.kernel.org/ubuntu/pool/universe/libp/libpng1.6/libpng16-16_1.6.20-2_amd64.deb
    sudo dpkg --force-depends -i libpng16-16_1.6.20-2_amd64.deb

    wget http://mirrors.kernel.org/ubuntu/pool/universe/libp/libpng1.6/libpng16-devtools_1.6.20-2_amd64.deb
    sudo dpkg --force-depends -i libpng16-devtools_1.6.20-2_amd64.deb

    wget http://mirrors.kernel.org/ubuntu/pool/universe/libp/libpng1.6/libpng16-dev_1.6.20-2_amd64.deb
    sudo dpkg --force-depends -i libpng16-dev_1.6.20-2_amd64.deb

    wget https://www.libsdl.org/projects/smpeg/release/smpeg2-2.0.0.tar.gz
    tar -xzvf smpeg2-2.0.0.tar.gz
    pushd smpeg2-2.0.0 && CFLAGS=-Wno-narrowing ./configure --prefix=/usr && make && sudo make install && popd
else
    echo "Installing OSX Libraries"
    #brew update
    #brew outdated cmake || brew upgrade cmake

    echo "Grabbing SDL dependencies"
    ./coresdk/external/setup.sh
fi
