cmake_minimum_required(VERSION 3.5)
project(splashkit)

cmake_policy(SET CMP0083 NEW)
include(CheckPIESupported)
check_pie_supported()

# SK Directories relative to cmake project
set(SKCORE_ROOT "${CMAKE_CURRENT_SOURCE_DIR}/../../../../../../../")
get_filename_component(SKCORE_ROOT "${SKCORE_ROOT}" ABSOLUTE)
set(SK_SRC "${SKCORE_ROOT}/coresdk/src")
set(SK_EXT "${SKCORE_ROOT}/coresdk/external")
set(SK_LIB "${SKCORE_ROOT}/coresdk/lib")
set(SK_OUT "${SKCORE_ROOT}/out")
set(SK_BIN "${SKCORE_ROOT}/bin")
set(SK_CLIB "${SKCORE_ROOT}/generated/clib")
set(SK_GEN_CPP "${SKCORE_ROOT}/generated/cpp")
set(BASE_OUTPUT_DIR "${CMAKE_CURRENT_SOURCE_DIR}/lib")

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

if (BCM_HOST_INCLUDE_DIR)
    message("Raspberry Pi detected")

    find_path(pigpio_INCLUDE_DIR NAMES pigpio.h pigpiod_if.h pigpiod_if2.h HINTS /usr/include)

    # Find the pigpio libraries.
    find_library(pigpio_LIBRARY NAMES libpigpio.so HINTS /usr/lib)

    find_library(pigpiod_if_LIBRARY NAMES libpigpiod_if.so HINTS /usr/lib)
    find_library(pigpiod_if2_LIBRARY NAMES libpigpiod_if2.so HINTS /usr/lib)
    if(pigpiod_if2_LIBRARY)
        set(pigpiod_if_LIBRARY ${pigpiod_if2_LIBRARY})
        # target_link_libraries(SplashKitBackend ${LIB_FLAGS} pigpiod_if2)
    endif()
    
    
     
    # Add necessary directories for Raspberry Pi
    include_directories(/usr/include)
    # target_link_libraries(/usr/lib)
    # target_link_libraries(SplashKitBackend ${LIB_FLAGS} pigpio)
    link_directories(/user/lib)
    # include_directories("/opt/vc/include")
    
    # link_directories("/opt/vc/lib")
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
                   -lstdc++fs\
                   -lpigpiod_if2")
# Add -Wall and -pthread options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
    # Define RASPBERRY_PI
    add_definitions(-DRASPBERRY_PI)
else()
    message("Raspberry Pi not detected")
endif()


# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# SOURCE FILES (excluding test files)
file(GLOB SOURCE_FILES
    "${SK_SRC}/coresdk/*.cpp"
    "${SK_SRC}/backend/*.cpp"
    "${SK_EXT}/civetweb/src/civetweb.c"
    "${SK_EXT}/sqlite/sqlite3.c"
    "${SK_EXT}/hash-library/*.cpp"
    "${SK_EXT}/easyloggingpp/*.cc"
    "${SK_EXT}/microui/src/*.c"
    "${SK_CLIB}/*.cpp"
    
)

# SKSDK FILE INCLUDES
file(GLOB SPLASHKITCPP_SOURCE_FILES
    "${SK_GEN_CPP}/*.cpp"
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
include_directories("${SK_CLIB}")
include_directories("${SK_GEN_CPP}")

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
#### SplashKitBackend SHARED LIBRARY ####
add_library(SplashKitBackend SHARED ${SOURCE_FILES} ${SPLASHKITCPP_SOURCE_FILES})
target_link_libraries(SplashKitBackend ${LIB_FLAGS})

# Set output directory based on the operating system
if (APPLE)
    set_target_properties(SplashKitBackend
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIR}/macos"
    )
elseif (WIN32)
    set_target_properties(SplashKitBackend
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIR}/windows"
    )
else()
    set_target_properties(SplashKitBackend
        PROPERTIES
        LIBRARY_OUTPUT_DIRECTORY "${BASE_OUTPUT_DIR}/linux"
    )
endif()
