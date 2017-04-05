#
# CMake file for generating the splashkit CPP library
#
cmake_minimum_required(VERSION 3.2)
project(splashkit)

# Detect Windows and flag MSYS
if (WIN32 OR MSYS OR MINGW)
  SET(MSYS "true")

  string(COMPARE EQUAL "MINGW32" "$ENV{MSYSTEM}" MINGW32)
  string(COMPARE EQUAL "MINGW64" "$ENV{MSYSTEM}" MINGW64)

  if (${MINGW32})
    message("Using mingw32")
    set(WIN_PATH_SUFFIX "win32")
    set(MINGW_PATH_PART "mingw32")
  elseif (${MINGW64})
    message("Using mingw64")
    set(WIN_PATH_SUFFIX "win64")
    set(MINGW_PATH_PART "mingw64")
  else ( )
    message(SEND_ERROR "Failed to detect windows architecture")
    return ()
  endif()

  set(WIN_NAME_SUFFIX "-${WIN_PATH_SUFFIX}")
endif()

# SK Directories relative to cmake project
set(SK_ROOT "../../../..")
set(SK_SRC "${SK_ROOT}/coresdk/src")
set(SK_EXT "${SK_ROOT}/coresdk/external")
set(SK_EXT "${SK_ROOT}/coresdk/external/hash-library")
set(SK_LIB "${SK_ROOT}/coresdk/lib")

set(SK_GENERATED "${SK_ROOT}/generated")
set(SK_BIN "${SK_ROOT}/bin")
set(SK_OUT "${SK_ROOT}/out")
set(SK_LANGUAGES "${SK_ROOT}/languages")

# Setup OS specific flags
if (APPLE)
    set(SK_OS_DEPLOY_PATH "${SK_OUT}/splashkit-macos")
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
    set(SK_OS_DEPLOY_PATH "${SK_OUT}/splashkit-windows")

    add_definitions(-DWINDOWS)
    set(LIB_FLAGS "-L${SK_LIB}/${WIN_PATH_SUFFIX} \
                   -L/${MINGW_PATH_PART}/lib \
                   -L/usr/lib \
                 -lSplashKit")
# LINUX PROJECT FLAGS
else()
    set(SK_OS_DEPLOY_PATH "${SK_OUT}/splashkit-linux")
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

file(GLOB STARTER_SOURCE_FILES
    "${SK_LANGUAGES}/cpp/splashkit_starter.cpp"
)

file(GLOB STARTER_HEADER_FILES
    "${SK_LANGUAGES}/cpp/splashkit_starter.h"
)

include_directories(${SK_GENERATED}/cpp, ${SK_GENERATED}/clib)

add_library(SplashKitCPP${WIN_NAME_SUFFIX} STATIC ${SOURCE_FILES})
add_library(SplashKitStarter STATIC ${STARTER_SOURCE_FILES})
target_link_libraries(SplashKitCPP${WIN_NAME_SUFFIX} ${LIB_FLAGS})


set_target_properties(
    SplashKitCPP${WIN_NAME_SUFFIX} PROPERTIES LINKER_LANGUAGE CXX
)

set(SK_DEPLOY_PATH "${SK_OS_DEPLOY_PATH}/commands/clang++")
get_filename_component(SK_DEPLOY_PATH ${SK_DEPLOY_PATH} ABSOLUTE)

install(TARGETS SplashKitCPP${WIN_NAME_SUFFIX} DESTINATION ${SK_DEPLOY_PATH}/lib)
install(TARGETS SplashKitStarter DESTINATION ${SK_DEPLOY_PATH}/lib)
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_PATH}/include)
install(FILES ${STARTER_HEADER_FILES} DESTINATION ${SK_DEPLOY_PATH}/include)
install(FILES ${SOURCE_FILES} DESTINATION ${SK_DEPLOY_PATH}/src)

set(SK_DEPLOY_PATH "${SK_OS_DEPLOY_PATH}/commands/g++")
get_filename_component(SK_DEPLOY_PATH ${SK_DEPLOY_PATH} ABSOLUTE)

install(TARGETS SplashKitCPP${WIN_NAME_SUFFIX} DESTINATION ${SK_DEPLOY_PATH}/lib)
install(TARGETS SplashKitStarter DESTINATION ${SK_DEPLOY_PATH}/lib)
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_PATH}/include)
install(FILES ${STARTER_HEADER_FILES} DESTINATION ${SK_DEPLOY_PATH}/include)
install(FILES ${SOURCE_FILES} DESTINATION ${SK_DEPLOY_PATH}/src)
