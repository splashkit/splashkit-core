#!/bin/sh

echo "Ensure you run this from the mingw 32 shell of Msys2"

rm -rf ../../out/win32
mkdir -p ../../out/win32
mkdir -p ./out/win32

CORE_SDK_PATH="../../coresdk"

ALL_SDL2_LIBS="-L${CORE_SDK_PATH}/lib/win32 -L/mingw32/lib -L/usr/lib -lSDL2main -Wl,--no-undefined"

DLLS=`cd ../../coresdk/lib/win32;ls -d *.dll | awk -F . '{split($1,patharr,"/"); idx=1; while(patharr[idx+1] != "") { idx++ } printf("../../coresdk/lib/win32/%s.dll ", patharr[idx]) }'`

# echo $DLLS

INC_SDL="-I/mingw32/include -I/mingw32/include/libpng16 -I${CORE_SDK_PATH}/external/SDL/include -I${CORE_SDK_PATH}/external/SDL_gfx -I${CORE_SDK_PATH}/external/SDL_image -I${CORE_SDK_PATH}/external/SDL_mixer -I${CORE_SDK_PATH}/external/SDL_net -I${CORE_SDK_PATH}/external/SDL_ttf -I${CORE_SDK_PATH}/lib/win_inc -I${CORE_SDK_PATH}/external/sqlite -I${CORE_SDK_PATH}/external/civetweb/include -I${CORE_SDK_PATH}/external/easyloggingpp -I${CORE_SDK_PATH}/external/json"

# echo $ALL_SDL2_LIBS

#echo "Creating shared library"
#g++ -m32 ${INC_SDL} -L/mingw32/bin -Wl,-Bdynamic ${DLLS} -shared -DBUILDING_DLL -DWINDOWS -std=c++11 -o ./out/win32/libSplashKit-32.dll -L/mingw32/lib -I${CORE_SDK_PATH}/src/coresdk/ -I${CORE_SDK_PATH}/src/backend/ ${CORE_SDK_PATH}/src/coresdk/*.cpp ${CORE_SDK_PATH}/src/backend/*.cpp ${ALL_SDL2_LIBS} ${OTHER_LIB} -Wl,--out-implib,./out/win32/libSplashKit-32.dll.a -static-libstdc++ -static-libgcc


echo "Copying in dlls"
cp ${CORE_SDK_PATH}/lib/win32/*.dll ../../out/win32

echo "Compiling splashkit dll"
g++ ${INC_SDL} -shared -L/mingw32/bin ${DLLS} -DWINDOWS -std=c++14 -L/mingw32/lib -I${CORE_SDK_PATH}/src/coresdk/ -I${CORE_SDK_PATH}/src/backend/ ${CORE_SDK_PATH}/src/coresdk/*.cpp ${CORE_SDK_PATH}/src/backend/*.cpp ${ALL_SDL2_LIBS} \
-I${CORE_SDK_PATH}/src/coresdk \
-I${CORE_SDK_PATH}/src/test \
 -L../../out/win32 \
 -static-libstdc++ -static-libgcc \
 -Wl,-Bstatic -lstdc++ -lpthread \
 -g -o ../../out/win32/libsplashkit.dll

echo "Compiling test program"
g++ -DWINDOWS -std=c++14 \
  -I${CORE_SDK_PATH}/src/coresdk/ -I${CORE_SDK_PATH}/src/test/ -I${CORE_SDK_PATH}/external/easyloggingpp/ \
  ${CORE_SDK_PATH}/src/test/*.cpp \
  -L../../out/win32 \
  -static-libstdc++ -static-libgcc \
  -Wl,-Bstatic -lstdc++ -lpthread \
  -g -o ./out/win32/RunTests.exe

echo "Copying resources"
cp -r ${CORE_SDK_PATH}/src/test/Resources ./out/win32
cp ../../out/win32/*.dll ./out/win32/
