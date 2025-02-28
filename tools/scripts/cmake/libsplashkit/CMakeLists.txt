#
# CMake file for generating the splashkit core library
#

cmake_minimum_required(VERSION 3.10)
project(splashkit)

# SK Directories relative to cmake project
set(SK_ROOT "../../../..")
set(SK_SRC "${SK_ROOT}/coresdk/src")
set(SK_EXT "${SK_ROOT}/coresdk/external")
set(SK_LIB "${SK_ROOT}/coresdk/lib")

set(SK_GENERATED "${SK_ROOT}/generated")
set(SK_BIN "${SK_ROOT}/bin")
set(SK_OUT "${SK_ROOT}/out")

set(SK_DEPLOY_ROOT "${SK_OUT}/skm")

# Detect Windows and flag MSYS
if (WIN32 OR MSYS OR MINGW)
    SET(MSYS "true")

    string(COMPARE EQUAL "MINGW32" "$ENV{MSYSTEM}" MINGW32)
    string(COMPARE EQUAL "MINGW64" "$ENV{MSYSTEM}" MINGW64)

    if (${MINGW32})
        message("Using mingw32")
        set(OS_PATH_SUFFIX "win32")
        set(MINGW_PATH_PART "mingw32")
        message(SEND_ERROR "32bit version no longer supported!")
        return()
    elseif (${MINGW64})
        message("Using mingw64")
        set(OS_PATH_SUFFIX "win64")
        set(MINGW_PATH_PART "mingw64")
    else ( )
        message(SEND_ERROR "Failed to detect windows architecture")
        return ()
    endif()

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2 sdl2_ttf sdl2_image sdl2_net sdl2_mixer sdl2_gfx libpng libcurl)

#    target_link_libraries(testapp ${SDL2_LIBRARIES})
#    target_include_directories(testapp PUBLIC ${SDL2_INCLUDE_DIRS})
#    target_compile_options(testapp PUBLIC ${SDL2_CFLAGS_OTHER})

    add_definitions(-DWINDOWS)
    set(LIB_FLAGS  "-L${SK_LIB}/${OS_PATH_SUFFIX} \
                    -L/${MINGW_PATH_PART}/lib \
                    -L/usr/lib \
                    ${SDL2_LDFLAGS} \
                    -Wl,-Bdynamic \
                    -lcivetweb"
                    )

    file(GLOB SK_LIB_DLL_FILES
        "${SK_LIB}/${OS_PATH_SUFFIX}/*.dll"
    )
elseif (APPLE)
    set(CMAKE_OSX_SYSROOT "/Library/Developer/CommandLineTools/SDKs/MacOSX.sdk")
    set(CMAKE_OSX_DEPLOYMENT_TARGET "12.3") # CACHE STRING "Minimum OS X deployment version")
    message(CMAKE_OSX_DEPLOYMENT_TARGET="${CMAKE_OSX_DEPLOYMENT_TARGET}")
    message(CMAKE_OSX_SYSROOT="${CMAKE_OSX_SYSROOT}")

    set(OS_PATH_SUFFIX "macos")
    # MAC OS PROJECT FLAGS
    set(LIB_FLAGS "-L${SK_LIB}/mac \
                   -framework IOKit \
                   -framework ForceFeedback \
                   -framework CoreFoundation \
                   -framework Cocoa \
                   -framework Carbon \
                   -framework Metal \
                   -framework AudioUnit \
                   -framework AudioToolbox \
                   -framework CoreAudio \
                   -framework CoreVideo \
                   -lSDL2 \
                   -lSDL2_mixer \
                   -lSDL2_ttf \
                   -lSDL2_gfx \
                   -lSDL2_image \
                   -lSDL2_net \
                   -lpthread \
                   -lpng16 \
                   -lz \
                   -lcurl \
                   -liconv \
                   -ldl")

         # SOURCE FILES
         file(GLOB OS_SOURCE_FILES
             "${SK_EXT}/civetweb/src/civetweb.c"
         )
# LINUX PROJECT FLAGS
else()
    set(OS_PATH_SUFFIX "linux")
    find_package(PNG REQUIRED)
    include_directories(${PNG_INCLUDE_DIR})
    SET(LINUX "true")
    set(LIB_FLAGS "-lSDL2 \
                   -lSDL2_mixer \
                   -lSDL2_ttf \
                   -lSDL2_gfx \
                   -lSDL2_image \
                   -lSDL2_net \
                   -lpthread \
                   -lbz2 \
                   -lFLAC \
                   -lvorbis \
                   -lz \
                   -lvorbisfile \
                   -lmikmod \
                   -logg \
                   -lwebp \
                   -lfreetype \
                   -lcurl \
                   -ldl")
    # SOURCE FILES
    file(GLOB OS_SOURCE_FILES
       "${SK_EXT}/civetweb/src/civetweb.c"
    )
endif()

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# SOURCE FILES
file(GLOB SOURCE_FILES
    "${SK_SRC}/coresdk/*.cpp"
    "${SK_SRC}/backend/*.cpp"
    "${SK_GENERATED}/clib/*.cpp"
    "${SK_EXT}/civetweb/src/md5.inl"
    "${SK_EXT}/easyloggingpp/easylogging++.cc"
    "${SK_EXT}/microui/src/*.c"
)

# SKSDK FILE INCLUDES
file(GLOB INCLUDE_FILES
    "${SK_SRC}/coresdk/*.h"
)

# Adapter files

file(GLOB ADAPTER_INCLUDE_FILES
    "${SK_GENERATED}/cpp/*.h"
)

file(GLOB ADAPTER_CPP_FILES
    "${SK_GENERATED}/cpp/*.cpp"
)

file(GLOB SK_LIB_INCLUDE_FILE
    "${SK_GENERATED}/clib/*.h"
)

# DIRECTORY INCLUDES
include_directories("${SK_SRC}")
include_directories("${SK_SRC}/coresdk")
include_directories("${SK_SRC}/backend")
include_directories("${SK_EXT}/civetweb/include")
include_directories("${SK_EXT}/easyloggingpp")
include_directories("${SK_EXT}/json")
include_directories("${SK_EXT}/catch")
include_directories("${SK_EXT}/hash-library")
include_directories("${SK_EXT}/microui/src")
include_directories(${SK_GENERATED}/cpp, ${SK_GENERATED}/clib)

# MAC OS AND WINDOWS DIRECTORY INCLUDES
if (APPLE)
    include_directories("${SK_EXT}/SDL/include")
    include_directories("${SK_EXT}/SDL_gfx")
    include_directories("${SK_EXT}/SDL_image")
    include_directories("${SK_EXT}/SDL_mixer")
    include_directories("${SK_EXT}/SDL_net")
    include_directories("${SK_EXT}/SDL_ttf")
endif()

# MAC OS ONLY DIRECTORY INCLUDES
if (APPLE)
    include_directories("${SK_EXT}/SDL_image/external/libpng-1.6.2")
    set(CMAKE_OSX_ARCHITECTURES "arm64;x86_64")
endif()

# WINDOWS ONLY DIRECTORY INCLUDES
if (MSYS)
    include_directories(/${MINGW_PATH_PART}/include)
    include_directories(/${MINGW_PATH_PART}/include/libpng16)
    include_directories("${SK_LIB}/win_inc")
endif()

# MACRO DEFINITIONS #
add_definitions(-DELPP_THREAD_SAFE)

#### END SETUP ####

#### SplashKitBackend STATIC LIBRARY ####


add_library(SplashKit SHARED ${SOURCE_FILES} ${OS_SOURCE_FILES} ${INCLUDE_FILES} ${ADAPTER_INCLUDE_FILES} ${ADAPTER_CPP_FILES})
target_link_libraries(SplashKit ${LIB_FLAGS})

if (LINUX)
    target_link_libraries(SplashKit ${PNG_LIBRARY})
endif()

if ( MSYS )
  set_target_properties(SplashKit PROPERTIES PREFIX "")
  target_include_directories(SplashKit PUBLIC ${SDL2_INCLUDE_DIRS})
  target_compile_options(SplashKit PUBLIC ${SDL2_CFLAGS_OTHER})
endif()

get_filename_component(SK_DEPLOY_ROOT ${SK_DEPLOY_ROOT} ABSOLUTE)

install(TARGETS SplashKit DESTINATION ${SK_DEPLOY_ROOT}/lib/${OS_PATH_SUFFIX})
install(FILES ${SK_LIB_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/source/include)
install(FILES ${INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/source/include)
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/clang++/include)
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/g++/include)

if ( MSYS )
  install(FILES ${SK_LIB_DLL_FILES} DESTINATION ${SK_DEPLOY_ROOT}/lib/${OS_PATH_SUFFIX})
endif()

file(GLOB LINUX_INCLUDE_FILES
    "${SK_EXT}/civetweb/include/*.h"
    "${SK_EXT}/hash-library/*.h"
    "${SK_SRC}/backend/*.h"
    "${SK_EXT}/easyloggingpp/*.h"
    "${SK_EXT}/json/*.hpp"
    "${SK_EXT}/catch/*.h"
    "${SK_EXT}/microui/src/microui.h"
)

file(GLOB INL_FILES
    "${SK_EXT}/civetweb/src/*.inl"
)

# Adapter files
install(FILES ${ADAPTER_INCLUDE_FILES}  DESTINATION ${SK_DEPLOY_ROOT}/g++/include)
install(FILES ${ADAPTER_CPP_FILES}  DESTINATION ${SK_DEPLOY_ROOT}/g++/src)
install(FILES ${ADAPTER_INCLUDE_FILES}  DESTINATION ${SK_DEPLOY_ROOT}/clang++/include)
install(FILES ${ADAPTER_CPP_FILES}  DESTINATION ${SK_DEPLOY_ROOT}/clang++/src)

install(FILES ${LINUX_INCLUDE_FILES}  DESTINATION ${SK_DEPLOY_ROOT}/source/include)
install(FILES ${INCLUDE_FILES}  DESTINATION ${SK_DEPLOY_ROOT}/source/include)
install(FILES ${OS_SOURCE_FILES} DESTINATION ${SK_DEPLOY_ROOT}/source)
install(FILES ${SOURCE_FILES} DESTINATION ${SK_DEPLOY_ROOT}/source)
install(FILES ${INL_FILES} DESTINATION ${SK_DEPLOY_ROOT}/source)
