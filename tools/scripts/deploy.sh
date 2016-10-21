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

SK_CMAKE_CLIB="${SK_TOOLS}/scripts/deploy/libsplashkit"
SK_CMAKE_CPP="${SK_TOOLS}/scripts/deploy/splashkitcpp"

read -p "Regenerate SplashKit? [y,n] :" doit
case $doit in
  y|Y) GENERATE_LIB=true ;;
  n|N) echo ; echo "Skipping generation" ;;
  *) exit -1 ;;
esac

if [[ $GENERATE_LIB ]]; then
  echo
  echo "Running Translator"
  echo
  sleep 0.5
  ${SK_ROOT}/tools/translator/translate --no-color --verbose -o ${SK_GENERATED} -i ${SK_ROOT} -g clib,cpp -w ${SK_GENERATED}/translator_cache.json -r ${SK_GENERATED}/translator_cache.json

  echo
  echo "Recreating Makefiles -- clib"
  echo
  sleep 0.5
  cd "${SK_CMAKE_CLIB}"
  cmake -G "Unix Makefiles" .

  echo
  echo "Recreating Makefiles -- cpp adapter"
  echo
  sleep 0.5
  cd "${SK_CMAKE_CPP}"
  cmake -G "Unix Makefiles" .
fi

echo
echo "Building -- clib"
echo
sleep 0.5
cd "${SK_CMAKE_CLIB}"
make
if [ $? != 0 ]; then echo "Error compiling"; exit 1; fi

make install
if [ $? != 0 ]; then echo "Error installing clib"; exit 1; fi


echo
echo "Building -- cpp adapter"
echo
sleep 0.5
cd "${SK_CMAKE_CPP}"
make
if [ $? != 0 ]; then echo "Error compiling"; exit 1; fi

make install
if [ $? != 0 ]; then echo "Error installing clib"; exit 1; fi


cd "${APP_PATH}"
