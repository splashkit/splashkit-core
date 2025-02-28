#!/bin/bash

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

function update_distro {
  if [ ! -d $1 ]; then
    cd "$SK_OUT"
    git clone "https://github.com/splashkit/$1.git"
    cd "$SK_OUT/$1"
  else
    cd "$SK_OUT/$1"
  fi
  git checkout develop
  git pull
}

update_distro "skm"

cd "$APP_PATH"

read -p "New C++ code? - Regenerate SplashKit core library? [y,n] " doit
case $doit in
  y|Y) GENERATE_LIB=true ;;
  n|N) echo ; echo "Skipping generation" ;;
  *) exit -1 ;;
esac

read -p "Delete cmake cache? [y,n] " doit
case $doit in
  y|Y) DELETE_CMAKE_CACHE=true ;;
  n|N) echo ; echo "Keeping cache" ;;
  *) exit -1 ;;
esac

if [[ $GENERATE_LIB ]]; then
  echo
  echo "Running Translator - this is a long process...."
  echo
  sleep 0.5
  cd "${SK_ROOT}/tools/translator/"
  
  # docker compose build
  docker compose run --rm  headerdoc clib,cpp,pascal,python,csharp,docs

  cd "$APP_PATH/nuget-pkg"

  echo
  echo "What version for nuget?"
  read nugetver

  dotnet build --configuration Release /p:version=$nugetver

  echo "Check you are happy to publish this, then publish using:"

  echo "dotnet nuget push ./bin/Release/*.nupkg  --api-key $API_KEY --source https://api.nuget.org/v3/index.json --skip-duplicate"
  
  cd "$APP_PATH"
  read -p "Rebuild website? [y,n]" doit
  case $doit in
    y|Y) bash deploy-website.sh ;;
    n|N) echo ; echo "Skipping Website re-build" ;;
  *) exit -1 ;;
  esac

fi

function do_make {
  sleep 0.5
  if [[ ${DELETE_CMAKE_CACHE} ]]; then
    ./clean.sh
  fi
  cmake -G "Unix Makefiles" .
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
echo "Building -- pascal adapter"
echo
cd "${SK_CMAKE_FPC}"
do_make

echo
echo "Building -- C# adapter"
echo
cd "${SK_CMAKE_CSHARP}"
do_make

echo
echo "Building -- Python adapter"
echo
cd "${SK_CMAKE_PYTHON}"
do_make



cd "${APP_PATH}"

if [[ `uname` == MINGW* ]]; then
  rm ${SK_OUT}/skm/lib/win32/*.a
  rm ${SK_OUT}/skm/lib/win64/*.a
fi

if [[ `uname` == Darwin ]]; then
  strip -x ${SK_OUT}/skm/lib/macos/libSplashKit.dylib
fi
