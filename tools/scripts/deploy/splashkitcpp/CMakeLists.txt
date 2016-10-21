#
# CMake file for generating the splashkit CPP library
#
cmake_minimum_required(VERSION 3.2)
project(splashkit)

# Detect Windows and flag MSYS
if (WIN32 OR MSYS OR MINGW)
  SET(MSYS "true")

  if (MINGW32)
    set(WIN_PATH_SUFFIX, "win32")
    set(MINGW_PATH_PART, "mingw32")
  elseif (MINGW64)
    set(WIN_PATH_SUFFIX, "win64")
    set(MINGW_PATH_PART, "mingw64")
  else ( )
    message(SEND_ERROR "Failed to detect windows architecture")
    return ()
  endif()
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
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-macos/compilers/clang++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")

    add_definitions(-DWINDOWS)
    set(LIB_FLAGS "-L${SK_LIB}/${WIN_PATH_SUFFIX} \
                   -L/${MINGW_PATH_PART}/lib \
                   -L/usr/lib \
                   -llibSplashKit \
                   -static-libstdc++ -static-libgcc -Wl,-Bstatic -lstdc++ -lpthread -Wl,-Bdynamic")
# LINUX PROJECT FLAGS
else()
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-ubuntu")
    set(LIB_FLAGS "-llibSplashKit")
    # SOURCE FILES
    file(GLOB OS_SOURCE_FILES
       "${SK_EXT}/sqlite/sqlite3.c"
       "${SK_EXT}/civetweb/src/civetweb.c"
    )
endif()

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

#### END SETUP ####

#### SplashKitBackend STATIC LIBRARY ####

# SOURCE FILES
file(GLOB SOURCE_FILES
    "${SK_GENERATED}/cpp/*.cpp"
)

# SKSDK FILE INCLUDES
file(GLOB SK_ADAPTER_INCLUDE_FILE
    "${SK_GENERATED}/cpp/*.h"
)

include_directories(${SK_GENERATED}/cpp, ${SK_GENERATED}/clib)

add_library(SplashKitCPP STATIC ${SOURCE_FILES})
target_link_libraries(SplashKitCPP ${LIB_FLAGS})


set_target_properties(
    SplashKitCPP PROPERTIES LINKER_LANGUAGE CXX
)

get_filename_component(SK_DEPLOY_ROOT ${SK_DEPLOY_ROOT} ABSOLUTE)

install(TARGETS SplashKitCPP DESTINATION ${SK_DEPLOY_ROOT}/lib)
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/include)
