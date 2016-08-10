#!/bin/sh

echo "Building linux library and test program"

rm -rf ./out/linux
mkdir -p ./out/linux

CORE_SDK_PATH="../../coresdk"

ALL_SDL2_LIBS="-lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2_net -Wl,--no-undefined"

OTHER_LIB="-lpthread -lbz2 -lFLAC -lsmpeg2 -lvorbis -lz -lpng16 -lvorbisfile -lmikmod -logg -lwebp -lfreetype -lcurl -lsqlite3"

# echo $ALL_SDL2_LIBS

function build_test_program {
    echo "Compiling test program"
    g++ -std=c++1y ${CORE_SDK_PATH}/src/test/*.cpp -I${CORE_SDK_PATH}/src/coresdk \
    -I${CORE_SDK_PATH}/src/test \
    -I${CORE_SDK_PATH}/src/backend \
     -L./out/linux -lsplashkit \
     -lpthread \
     -g -o ./out/linux/runtests
}

function run_test_program {
    ./out/linux/runtests
}

function build_shared_library {
    echo "Creating shared library"
    g++ -shared -std=c++1y -o ./out/linux/libsplashkit.so -I${CORE_SDK_PATH}/src/coresdk/ -I${CORE_SDK_PATH}/src/backend/ ${CORE_SDK_PATH}/src/coresdk/*.cpp ${CORE_SDK_PATH}/src/backend/*.cpp ${ALL_SDL2_LIBS} ${OTHER_LIB} -fPIC


    echo "Fails without root: Installing library manually into /usr/lib"
    cp ./out/linux/libsplashkit.so /usr/lib/libsplashkit.so
}

if [[ $# -gt 0 ]]; then
    echo "Copying resources"
    cp -r ${CORE_SDK_PATH}/src/test/Resources ./out/linux
    
    arg="$1"
    case $arg in
        -test)
            build_test_program
            run_test_program
            shift
            ;;
        -all)
            build_shared_library
            build_test_program
            run_test_program
            shift
            ;;
        -library)
            build_shared_library
            shift
            ;;
    esac
else
    echo "You must provide one of the following arguments:"
    echo "  -test       Builds and runs the test program."
    echo "  -all        Builds the library and tests and runs the test program."
    echo "  -library    Builds the library."
fi

