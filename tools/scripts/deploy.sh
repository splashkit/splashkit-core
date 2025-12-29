#!/bin/bash

APP_PATH=`echo $0 | awk '{split($0,patharr,"/"); idx=1; while(patharr[idx+1] != "") { if (patharr[idx] != "/") {printf("%s/", patharr[idx]); idx++ }} }'`
APP_PATH=`cd "$APP_PATH"; pwd`
cd "$APP_PATH"

SK_ROOT="../../"
SK_ROOT=`cd "$SK_ROOT"; pwd`
SK_SRC="${SK_ROOT}/coresdk/src"
SK_EXT="${SK_ROOT}/coresdk/external"
SK_LIB="${SK_ROOT}/coresdk/lib"

LLAMA_SRC_DIR="${SK_EXT}/llama.cpp"
LLAMA_OUT_DIR="${APP_PATH}/llama.cpp"

SK_GENERATED="${SK_ROOT}/generated"
SK_BIN="${SK_ROOT}/bin"
SK_OUT="${SK_ROOT}/out"
SK_TOOLS="${SK_ROOT}/tools"

SK_CMAKE_CLIB="${SK_TOOLS}/scripts/cmake/libsplashkit"
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

  read -p "Build dotnet lib? [y,n] " doit
  case $doit in
    y|Y) BUILD_DOT_NET=true ;;
    n|N) echo ; echo "Skipping dotnet build" ;;
    *) exit -1 ;;
  esac

  if [[ $BUILD_DOT_NET ]]; then
    cd "$APP_PATH/nuget-pkg"

    echo
    echo "What version for nuget?"
    read nugetver

    dotnet build --configuration Release /p:version=$nugetver

    echo "Check you are happy to publish this, then publish using:"

    source $SK_ROOT/.env
    
    echo "dotnet nuget push ./bin/Release/*.nupkg  --api-key $API_KEY --source https://api.nuget.org/v3/index.json --skip-duplicate"
    
    cd "$APP_PATH"
  fi

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

read -p "Build llama lib? (needed on Mac) [y,n] " doit
case $doit in
  y|Y) BUILD_LLAMA=true ;;
  n|N) echo ; echo "Skipping llama build" ;;
  *) exit -1 ;;
esac

if [[ $BUILD_LLAMA ]]; then
  mkdir -p "${LLAMA_OUT_DIR}"
  cd "${LLAMA_OUT_DIR}"

  MACOS_MIN_OS_VERSION=13.3
  COMMON_C_FLAGS="-Wno-macro-redefined -Wno-shorten-64-to-32 -Wno-unused-command-line-argument -mmacosx-version-min=${MACOS_MIN_OS_VERSION}"
  COMMON_CXX_FLAGS="-Wno-macro-redefined -Wno-shorten-64-to-32 -Wno-unused-command-line-argument -mmacosx-version-min=${MACOS_MIN_OS_VERSION}"

  cmake \
    -DCMAKE_C_FLAGS="${COMMON_C_FLAGS}" \
    -DCMAKE_CXX_FLAGS="${COMMON_CXX_FLAGS}" \
    -DLLAMA_BUILD_TESTS=OFF -DLLAMA_BUILD_TOOLS=OFF -DLLAMA_BUILD_EXAMPLES=OFF -DLLAMA_BUILD_SERVER=OFF -DGGML_BLAS=OFF -DGGML_METAL=OFF -DGGML_VULKAN=OFF -DBUILD_SHARED_LIBS=OFF -DLLAMA_BUILD_COMMON=OFF -DLLAMA_TOOLS_INSTALL=OFF -DCMAKE_BUILD_TYPE=Release -DGGML_STATIC=ON -DGGML_OPENMP=OFF \
    -DCMAKE_OSX_ARCHITECTURES="arm64;x86_64" \
    -DCMAKE_OSX_DEPLOYMENT_TARGET=${MACOS_MIN_OS_VERSION} \
    -DCMAKE_OSX_SYSROOT="/Library/Developer/CommandLineTools/SDKs/MacOSX26.sdk" \
    -DCMAKE_INSTALL_PREFIX=./out \
    -S ${LLAMA_SRC_DIR}
  
  make
  make install
fi

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
  rm ${SK_OUT}/skm/lib/win64/*.a
fi

if [[ `uname` == Darwin ]]; then
  strip -x ${SK_OUT}/skm/lib/macos/libSplashKit.dylib
fi
