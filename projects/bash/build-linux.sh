#!/bin/sh

echo "Building linux library and test program"

rm -rf ./out/linux
mkdir -p ./out/linux

CORE_SDK_PATH="../../coresdk"

ALL_SDL2_LIBS="-lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2_net -Wl,--no-undefined"

OTHER_LIB="-lpthread -lbz2 -lFLAC -lsmpeg2 -lvorbis -lz -lpng16 -lvorbisfile -lmikmod -logg -lwebp -lfreetype -lcurl -lsqlite3"

# echo $ALL_SDL2_LIBS

echo "Creating shared library"
g++ -shared -std=c++1y -o ./out/linux/libsplashkit.so -I${CORE_SDK_PATH}/src/coresdk/ -I${CORE_SDK_PATH}/src/backend/ ${CORE_SDK_PATH}/src/coresdk/*.cpp ${CORE_SDK_PATH}/src/backend/*.cpp ${ALL_SDL2_LIBS} ${OTHER_LIB} -fPIC

echo "Compiling test program"
g++ -std=c++1y ${CORE_SDK_PATH}/src/test/*.cpp -I${CORE_SDK_PATH}/src/coresdk \
-I${CORE_SDK_PATH}/src/test \
-I${CORE_SDK_PATH}/src/backend \
 -L./out/linux -lsplashkit \
 -lpthread \
 -g -o ./out/linux/runtests

echo "Copying resources"
cp -r ${CORE_SDK_PATH}/src/test/Resources ./out/linux
