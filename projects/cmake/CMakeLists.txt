cmake_minimum_required(VERSION 3.10)
project(splashkit)

set(CMAKE_BUILD_TYPE Debug)

cmake_policy(SET CMP0083 NEW)
include(CheckPIESupported)
check_pie_supported()

# SK Directories relative to cmake project
set(SK_SRC "${CMAKE_CURRENT_SOURCE_DIR}/../../coresdk/src")
set(SK_EXT "${CMAKE_CURRENT_SOURCE_DIR}/../../coresdk/external")
set(SK_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../../coresdk/lib")
set(SK_OUT "${CMAKE_CURRENT_SOURCE_DIR}/../../out")
set(SK_BIN "${CMAKE_CURRENT_SOURCE_DIR}/../../bin")

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++20")

# Includes for CTest/Catch2 integration
include(CTest)
include("${CMAKE_CURRENT_SOURCE_DIR}/catch/Catch.cmake")

if (WIN32 OR MSYS OR MINGW)
  SET(MSYS "true")
  add_definitions(-DWINDOWS)
endif()

# Check for Raspberry Pi
include(CheckIncludeFile)
find_path(BCM_HOST_INCLUDE_DIR bcm_host.h PATHS "/opt/vc/include")
#### SETUP ####
if (APPLE)
    # MAC OS PROJECT FLAGS
    add_link_options("-Wl-U,___darwin_check_fd_set_overflow")
    set(LIB_FLAGS "-L${SK_LIB}/mac \
                   -framework IOKit \
                   -framework ForceFeedback \
                   -framework CoreFoundation \
                   -framework Metal \
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
                   -logg \
                   -lwebp \
                   -lcurl \
                   -liconv \
                   -ldl")
# WINDOWS PROJECT FLAGS
elseif(MSYS)
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

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2 sdl2_ttf sdl2_image sdl2_net sdl2_mixer sdl2_gfx libpng libcurl)

    set(LIB_FLAGS  "-L${SK_LIB}/${OS_PATH_SUFFIX} \
                    -L/${MINGW_PATH_PART}/lib \
                    -L/usr/lib \
                    ${SDL2_LDFLAGS} \
                    -lSDL2main \
                    -Wl,-Bdynamic \
                    -lws2_32 \
                    -lcivetweb")
                    
# LINUX PROJECT FLAGS
else()
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
                   -lpng16 \
                   -lvorbisfile \
                   -logg \
                   -lwebp \
                   -lfreetype \
                   -lcurl \
                   -ldl \
                   -lstdc++fs")
endif()

# --- New Raspberry Pi detection method (active on Linux only) ---
# We now detect Raspberry Pi by checking for specific device model and CPU info.
if (NOT APPLE AND NOT MSYS)
    set(RASPBERRY_PI FALSE)
    # Method 1: Check for Raspberry Pi specific file
    if(EXISTS "/proc/device-tree/model")
        file(READ "/proc/device-tree/model" DEVICE_MODEL)
        if(DEVICE_MODEL MATCHES "Raspberry Pi")
            set(RASPBERRY_PI TRUE)
        endif()
    endif()

    # Method 2: Check for ARM architecture and Broadcom chip
    if(CMAKE_SYSTEM_PROCESSOR MATCHES "^(arm|aarch64)")
        if(EXISTS "/proc/cpuinfo")
            file(READ "/proc/cpuinfo" CPU_INFO)
            if(CPU_INFO MATCHES "BCM[0-9]+")
                set(RASPBERRY_PI TRUE)
            endif()
        endif()
    endif()

    if(RASPBERRY_PI)
        message("-- Raspberry Pi Detected")
        # Locate Pigpio libraries
        find_path(PIGPIOD_INCLUDE_DIR NAMES pigpiod_if2.h PATHS "/usr/include")
        find_library(PIGPIOD_IF2_LIB NAMES pigpiod_if2 HINTS "/usr/lib")
        find_library(PIGPIO_LIB NAMES pigpio HINTS "/usr/lib")
        include(FindPackageHandleStandardArgs)
        find_package_handle_standard_args(PIGPIO DEFAULT_MSG PIGPIOD_INCLUDE_DIR PIGPIOD_IF2_LIB PIGPIO_LIB)
        if(PIGPIO_FOUND)
            message("-- Pigpio libraries found")
            include_directories(${PIGPIOD_INCLUDE_DIR})
            add_definitions(-DRASPBERRY_PI)
            add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)
            # Override LIB_FLAGS for Raspberry Pi to include pigpiod_if2
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
                           -lpng16 \
                           -lvorbisfile \
                           -logg \
                           -lwebp \
                           -lfreetype \
                           -lcurl \
                           -ldl \
                           -lstdc++fs \
                           -lpigpiod_if2")
            set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
        else()
            message(WARNING "-- Pigpio libraries NOT found. Some features may be unavailable.")
        endif()
    else()
        message("Raspberry Pi not detected")
    endif()
endif()
# --- End Raspberry Pi detection ---

# SOURCE FILES
file(GLOB SOURCE_FILES
    "${SK_SRC}/coresdk/*.cpp"
    "${SK_SRC}/backend/*.cpp"
    "${SK_EXT}/civetweb/src/civetweb.c"
    "${SK_EXT}/sqlite/sqlite3.c"
    "${SK_EXT}/hash-library/*.cpp"
    "${SK_EXT}/easyloggingpp/*.cc"
    "${SK_EXT}/microui/src/*.c"
)

# TEST FILE INCLUDES
file(GLOB TEST_SOURCE_FILES
    "${SK_SRC}/test/*.cpp"
)

file(GLOB UNIT_TEST_SOURCE_FILES
    "${SK_SRC}/test/unit_tests/*.cpp"
)

# SKSDK FILE INCLUDES
file(GLOB INCLUDE_FILES
    "${SK_SRC}/coresdk/*.h"
)

# DIRECTORY INCLUDES
include_directories("${SK_SRC}")
include_directories("${SK_SRC}/coresdk")
include_directories("${SK_SRC}/backend")
include_directories("${SK_SRC}/test")
include_directories("${SK_EXT}/civetweb/include")
include_directories("${SK_EXT}/easyloggingpp")
include_directories("${SK_EXT}/hash-library")
include_directories("${SK_EXT}/json")
include_directories("${SK_EXT}/catch")
include_directories("${SK_EXT}/microui/src")

# MAC OS DIRECTORY INCLUDES
if (APPLE)
    include_directories("${SK_EXT}/SDL/include")
    include_directories("${SK_EXT}/SDL_gfx")
    include_directories("${SK_EXT}/SDL_image")
    include_directories("${SK_EXT}/SDL_mixer")
    include_directories("${SK_EXT}/SDL_net")
    include_directories("${SK_EXT}/SDL_ttf")
    include_directories("${SK_EXT}/SDL_image/external/libpng-1.6.2")
endif()

# MACRO DEFINITIONS #
add_definitions(-DELPP_THREAD_SAFE)

#### END SETUP ####
#### SplashKitBackend STATIC LIBRARY ####
add_library(SplashKitBackend STATIC ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(SplashKitBackend ${LIB_FLAGS})

if (MSYS)
    set_target_properties(SplashKitBackend PROPERTIES PREFIX "")
    target_include_directories(SplashKitBackend PUBLIC ${SDL2_INCLUDE_DIRS})
    target_compile_options(SplashKitBackend PUBLIC ${SDL2_CFLAGS_OTHER})
elseif (APPLE)
    # To make a universal single static library from dependent
    # static libraries, run libtool on SplashKitBackend
    file(GLOB APPLE_STATIC_LIBS
        "${SK_LIB}/mac/*.a"
    )
    add_custom_command(TARGET SplashKitBackend POST_BUILD
      COMMAND /usr/bin/libtool -static -o $<TARGET_FILE:SplashKitBackend>
      $<TARGET_FILE:SplashKitBackend> ${APPLE_STATIC_LIBS}
    )
endif()

# SET OUTPUT TO /path/to/splashkit/out/lib
set_target_properties(SplashKitBackend
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${SK_OUT}/lib"
)

#### END SplashKitBackend STATIC LIBRARY ####
#### sktest EXECUTABLE ####
add_executable(sktest ${TEST_SOURCE_FILES})
set_property(TARGET sktest PROPERTY POSITION_INDEPENDENT_CODE FALSE)

target_link_libraries(sktest SplashKitBackend)
target_link_libraries(sktest ${LIB_FLAGS})

# target_link_options(sktest PUBLIC "LINKER:-U,___darwin_check_fd_set_overflow")

set_target_properties(sktest
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SK_BIN}
)

# Copy resources folder in
add_custom_command(TARGET sktest
    PRE_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${SK_SRC}/test/Resources" $<TARGET_FILE_DIR:sktest>/Resources)

# Test if windows build works with folders inside Resources
add_custom_command(TARGET sktest
    PRE_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${SK_SRC}/test/Resources/" $<TARGET_FILE_DIR:sktest>)

# if (MSYS)
#     add_custom_command(TARGET sktest
#         PRE_BUILD COMMAND
#         cmake -E copy ../../coresdk/lib/win64/*.dll ../../bin
#         )
# endif()

#### END sktest EXECUTABLE ####

#### skunit_tests EXECUTABLE ####
add_executable(skunit_tests ${UNIT_TEST_SOURCE_FILES})
set_property(TARGET skunit_tests PROPERTY POSITION_INDEPENDENT_CODE FALSE)

# target_link_options(skunit_tests PUBLIC "LINKER:-U,___darwin_check_fd_set_overflow")

# Disable logs in skunit_tests (but not in sktest)
# target_compile_options(skunit_tests PRIVATE -DELPP_DISABLE_LOGS)
# target_compile_options(SplashKitBackend PRIVATE -DELPP_DISABLE_LOGS)

target_link_libraries(skunit_tests SplashKitBackend)
target_link_libraries(skunit_tests ${LIB_FLAGS})

set_target_properties(skunit_tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${SK_BIN}
        )

# Copy resources folder into projects/cmake folder for CTest
add_custom_command(
    TARGET skunit_tests 
    PRE_BUILD 
    COMMAND ${CMAKE_COMMAND} -E copy_directory
    "${SK_SRC}/test/Resources" 
    "${CMAKE_CURRENT_SOURCE_DIR}/Resources"
)

# Discover and register Catch2 tests
catch_discover_tests(skunit_tests)
#### END sktest EXECUTABLE ####

install(TARGETS SplashKitBackend DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include/SplashKitBackend)