#
# CMake file for generating the splashkit core library
#
cmake_minimum_required(VERSION 3.2)
project(splashkit)

# Detect Windows and flag MSYS
if (WIN32 OR MSYS OR MINGW)
  SET(MSYS "true")
endif()

# SK Directories relative to cmake project
set(SK_ROOT "../../../..")
set(SK_SRC "${SK_ROOT}/coresdk/src")
set(SK_EXT "${SK_ROOT}/coresdk/external")
set(SK_LIB "${SK_ROOT}/coresdk/lib")

set(SK_GENERATED "${SK_ROOT}/generated")
set(SK_BIN "${SK_ROOT}/bin")
set(SK_OUT "${SK_ROOT}/out")

# Setup OS specific flags
if (APPLE)
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-macos")
    # MAC OS PROJECT FLAGS
    set(LIB_FLAGS "-L${SK_LIB}/mac \
                   -framework IOKit \
                   -framework ForceFeedback \
                   -framework CoreFoundation \
                   -framework Cocoa \
                   -framework Carbon \
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
                   -lbz2 \
                   -lFLAC \
                   -lvorbis \
                   -lz \
                   -lpng16 \
                   -lvorbisfile \
                   -lmikmod \
                   -logg \
                   -lwebp \
                   -lsmpeg2 \
                   -lfreetype \
                   -lcurl \
                   -lncurses \
                   -ldl")

         # SOURCE FILES
         file(GLOB OS_SOURCE_FILES
             "${SK_EXT}/sqlite/sqlite3.c"
             "${SK_EXT}/civetweb/src/civetweb.c"
         )
# WINDOWS PROJECT FLAGS
elseif(MSYS)
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-windows")
    add_definitions(-DWINDOWS)
    set(LIB_FLAGS " \
      -L${SK_LIB}/win64 \
      -static-libstdc++ -static-libgcc \
      ")
# LINUX PROJECT FLAGS
else()
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-ubuntu")
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
                   -lpng12 \
                   -lvorbisfile \
                   -lmikmod \
                   -logg \
                   -lwebp \
                   -lfreetype \
                   -lcurl \
                   -lncurses \
                   -ldl")
    # SOURCE FILES
    file(GLOB OS_SOURCE_FILES
       "${SK_EXT}/sqlite/sqlite3.c"
       "${SK_EXT}/civetweb/src/civetweb.c"
    )
endif()

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# SOURCE FILES
file(GLOB SOURCE_FILES
    "${SK_SRC}/coresdk/*.cpp"
    "${SK_SRC}/backend/*.cpp"
    "${SK_GENERATED}/clib/*.cpp"
)

# SKSDK FILE INCLUDES
file(GLOB INCLUDE_FILES
    "${SK_SRC}/coresdk/*.h"
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
include_directories("${SK_EXT}/sqlite")
include_directories("${SK_EXT}/catch")

# MAC OS AND WINDOWS DIRECTORY INCLUDES
if (APPLE OR MSYS)
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
endif()

# WINDOWS ONLY DIRECTORY INCLUDES
if (MSYS)
    include_directories(/mingw64/include)
    include_directories(/mingw64/include/libpng16)
    include_directories("${SK_LIB}/win_inc")
endif()

# MACRO DEFINITIONS #
add_definitions(-DELPP_THREAD_SAFE)

#### END SETUP ####

#### SplashKitBackend STATIC LIBRARY ####

add_custom_target (
  SplashKitCode
  COMMAND ${SK_ROOT}/tools/translator/translate --no-color --verbose -o ${SK_GENERATED} -i ${SK_ROOT} -g clib -w ${SK_GENERATED}/translator_cache.json -r ${SK_GENERATED}/translator_cache.json
  )

add_library(SplashKit SHARED ${SOURCE_FILES} ${OS_SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(SplashKit ${LIB_FLAGS})
add_dependencies(SplashKit SplashKitCode)

if (MSYS)
    link_directories("${SK_LIB}/win64")

    add_library(pthread STATIC IMPORTED)
    add_library(stdc++ STATIC IMPORTED)

    target_link_libraries(SplashKit
        SDL2_mixer
        SDL2_image
        SDL2_net
        libcivetweb
        SDL2
        SDL2_ttf
        libcurl
        libSDL2_gfx-1-0-0
        libpng16-16
        libsqlite
        pthread
        stdc++
        ws2_32
        libncursesw
      )
# elseif(APPLE)
#     # To make a universal single static library from dependent
#     # static libraries, run libtool on SplashKitBackend
#     file(GLOB APPLE_STATIC_LIBS
#         "${SK_LIB}/mac/*.a"
#     )
#     add_custom_command(TARGET SplashKitBackend POST_BUILD
#       COMMAND /usr/bin/libtool -static -o $<TARGET_FILE:SplashKitBackend>
#       $<TARGET_FILE:SplashKitBackend> ${APPLE_STATIC_LIBS}
#     )
endif()

get_filename_component(SK_DEPLOY_ROOT ${SK_DEPLOY_ROOT} ABSOLUTE)

install(TARGETS SplashKit DESTINATION ${SK_DEPLOY_ROOT}/lib)
install(FILES ${SK_LIB_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/include)
