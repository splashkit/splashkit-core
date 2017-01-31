#!/bin/sh

APP_PATH=`echo $0 | awk '{split($0,patharr,"/"); idx=1; while(patharr[idx+1] != "") { if (patharr[idx] != "/") {printf("%s/", patharr[idx]); idx++ }} }'`
APP_PATH=`cd "$APP_PATH"; pwd`
cd "$APP_PATH"

SK_ROOT="../../"
SK_ROOT=`cd "$SK_ROOT"; pwd`
SK_SRC="${SK_ROOT}/coresdk/src"
SK_EXT="${SK_ROOT}/coresdk/external"
SK_LIB="${SK_ROOT}/coresdk/lib"

SK_GENERATED="${SK_ROOT}/generated"
SK_BIN="${SK_ROOT}/bin"
SK_OUT="${SK_ROOT}/out"
SK_TOOLS="${SK_ROOT}/tools"

SK_CMAKE_CLIB="${SK_TOOLS}/scripts/cmake/libsplashkit"
SK_CMAKE_CPP="${SK_TOOLS}/scripts/cmake/splashkitcpp"
SK_CMAKE_FPC="${SK_TOOLS}/scripts/cmake/splashkitpas"
SK_CMAKE_PYTHON="${SK_TOOLS}/scripts/cmake/splashkit-python"
SK_CMAKE_CSHARP="${SK_TOOLS}/scripts/cmake/splashkit-csharp"


cd ../../out/splashkit-macos
git checkout develop
git pull
cd ../splashkit-windows
git checkout develop
git pull
cd "$APP_PATH"

read -p "Regenerate SplashKit? [y,n] " doit
case $doit in
  y|Y) GENERATE_LIB=true ;;
  n|N) echo ; echo "Skipping generation" ;;
  *) exit -1 ;;
esac

if [[ `uname` == MINGW* ]]; then
  read -p "Delete cmake cache? [y,n] " doit
  case $doit in
    y|Y) DELETE_CMAKE_CACHE=true ;;
    n|N) echo ; echo "Keeping cache" ;;
    *) exit -1 ;;
  esac
fi

if [[ $GENERATE_LIB ]]; then
  echo
  echo "Running Translator"
  echo
  sleep 0.5
  ${SK_ROOT}/tools/translator/translate --no-color --verbose -o ${SK_GENERATED} -i ${SK_ROOT} -g clib,cpp,pascal,python,csharp -w ${SK_GENERATED}/translator_cache.json -r ${SK_GENERATED}/translator_cache.json
fi

function do_make {
  sleep 0.5
  if [[ ${DELETE_CMAKE_CACHE} ]]; then
    ./clean.sh
  fi
  cmake -DCMAKE_OSX_ARCHITECTURES="x86_64;i386" -G "Unix Makefiles" .
  make
  if [ $? != 0 ]; then echo "Error compiling"; exit 1; fi

  make install
  if [ $? != 0 ]; then echo "Error installing"; exit 1; fi
}

echo
echo "Building -- clib"
echo
cd "${SK_CMAKE_CLIB}"
do_make

echo
echo "Building -- cpp adapter"
echo
cd "${SK_CMAKE_CPP}"
do_make

echo
echo "Building -- pascal adapter"
echo
cd "${SK_CMAKE_FPC}"
do_make

echo
echo "Building -- C# adapter"
echo
cd "${SK_CMAKE_CSHARP}"
do_make


cd "${APP_PATH}"

if [[ `uname` == MINGW* ]]; then
  rm ${SK_OUT}/splashkit-windows/lib/*.a
fi
