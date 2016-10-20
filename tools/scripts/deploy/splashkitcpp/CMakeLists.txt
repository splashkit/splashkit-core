#
# CMake file for generating the splashkit CPP library
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
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-macos/compilers/clang++")
    # MAC OS PROJECT FLAGS
    set(LIB_FLAGS "-L${SK_OUT}/splashkit-macos/lib \
                   -llibSplashKit \
                   -framework IOKit \
                   -framework ForceFeedback \
                   -framework CoreFoundation \
                   -framework Cocoa \
                   -framework Carbon \
                   -framework AudioUnit \
                   -framework AudioToolbox \
                   -framework CoreAudio \
                   -framework CoreVideo \
                   -lcurl \
                   -lncurses")
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
    "${SK_GENERATED}/cpp/*.cpp"
)

# SKSDK FILE INCLUDES
file(GLOB SK_ADAPTER_INCLUDE_FILE
    "${SK_GENERATED}/cpp/*.h"
)

include_directories(${SK_GENERATED}/cpp, ${SK_GENERATED}/clib)

#### END SETUP ####

#### SplashKitBackend STATIC LIBRARY ####

add_custom_target (
  SplashKitCPPCode
  COMMAND ${SK_ROOT}/tools/translator/translate --no-color --verbose -o ${SK_GENERATED} -i ${SK_ROOT} -g cpp -w ${SK_GENERATED}/translator_cache.json -r ${SK_GENERATED}/translator_cache.json
  )

add_library(SplashKitCPP STATIC ${SOURCE_FILES})
target_link_libraries(SplashKitCPP ${LIB_FLAGS})
add_dependencies(SplashKitCPP SplashKitCPPCode)

set_target_properties(
    SplashKitCPP PROPERTIES LINKER_LANGUAGE CXX
)

get_filename_component(SK_DEPLOY_ROOT ${SK_DEPLOY_ROOT} ABSOLUTE)

install(TARGETS SplashKitCPP DESTINATION ${SK_DEPLOY_ROOT}/lib)
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/include)
