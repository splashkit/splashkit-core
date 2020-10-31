#
# CMake file for generating the splashkit CPP library
#
cmake_minimum_required(VERSION 3.2)
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
    elseif (${MINGW64})
        message("Using mingw64")
        set(OS_PATH_SUFFIX "win64")
        set(MINGW_PATH_PART "mingw64")
    else ( )
        message(SEND_ERROR "Failed to detect windows architecture")
        return ()
    endif()

    add_definitions(-DWINDOWS)
    set(LIB_FLAGS "-L${SK_LIB}/${OS_PATH_SUFFIX} \
                   -L/${MINGW_PATH_PART}/lib \
                   -L/usr/lib \
                 -lSplashKit")
elseif (APPLE)
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.5" CACHE STRING "Minimum OS X deployment version")
    set(OS_PATH_SUFFIX "macos")
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
else()
    # LINUX PROJECT FLAGS
    set(OS_PATH_SUFFIX "linux")

    set(LIB_FLAGS "-llibSplashKit")

    # SOURCE FILES
    file(GLOB OS_SOURCE_FILES
       "${SK_EXT}/sqlite/sqlite3.c"
       "${SK_EXT}/civetweb/src/civetweb.c"
    )
endif()

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

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

install(TARGETS SplashKitCPP DESTINATION ${SK_DEPLOY_ROOT}/clang++/lib/${OS_PATH_SUFFIX})
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/clang++/include)
install(FILES ${SOURCE_FILES} DESTINATION ${SK_DEPLOY_ROOT}/clang++/src)

install(TARGETS SplashKitCPP DESTINATION ${SK_DEPLOY_ROOT}/g++/lib/${OS_PATH_SUFFIX})
install(FILES ${SK_ADAPTER_INCLUDE_FILE} DESTINATION ${SK_DEPLOY_ROOT}/g++/include)
install(FILES ${SOURCE_FILES} DESTINATION ${SK_DEPLOY_ROOT}/g++/src)
