cmake_minimum_required(VERSION 3.2)
project(splashkit)

if (APPLE)
    include(CheckCXXCompilerFlag)
    check_cxx_compiler_flag("-arch arm64" armSupported)

    # Temporarily force x86_64 via Rosetta on M1 macs until
    # precompiled external libraries have symbols added for arm64.
    if (armSupported)
        set(CMAKE_OSX_ARCHITECTURES "x86_64")
    endif()
endif()

# SK Directories relative to cmake project
set(SK_SRC "${CMAKE_CURRENT_SOURCE_DIR}/../../coresdk/src")
set(SK_EXT "${CMAKE_CURRENT_SOURCE_DIR}/../../coresdk/external")
set(SK_LIB "${CMAKE_CURRENT_SOURCE_DIR}/../../coresdk/lib")
set(SK_OUT "${CMAKE_CURRENT_SOURCE_DIR}/../../out")
set(SK_BIN "${CMAKE_CURRENT_SOURCE_DIR}/../../bin")

if (WIN32 OR MSYS OR MINGW)
  SET(MSYS "true")
  add_definitions(-DWINDOWS)
endif()

#### SETUP ####
if (APPLE)
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

    set(LIB_FLAGS  "-L${SK_LIB}/${OS_PATH_SUFFIX} \
                    -L/${MINGW_PATH_PART}/lib \
                    -L/usr/lib \
                    -lSDL2main")
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
                   -lmikmod \
                   -logg \
                   -lwebp \
                   -lfreetype \
                   -lcurl \
                   -lncurses \
                   -ldl \
                   -lstdc++fs")
endif()

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17")

# SOURCE FILES
file(GLOB SOURCE_FILES
    "${SK_SRC}/coresdk/*.cpp"
    "${SK_SRC}/backend/*.cpp"
    "${SK_EXT}/civetweb/src/civetweb.c"
    "${SK_EXT}/sqlite/sqlite3.c"
    "${SK_EXT}/hash-library/*.cpp"
    "${SK_EXT}/easyloggingpp/*.cc"
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
    include_directories(/${MINGW_PATH_PART}/include)
    include_directories(/${MINGW_PATH_PART}/include/libpng16)
    include_directories("${SK_LIB}/win_inc")
    include_directories("${SK_EXT}/sqlite")
endif()

# MACRO DEFINITIONS #
add_definitions(-DELPP_THREAD_SAFE)

#### END SETUP ####
#### SplashKitBackend STATIC LIBRARY ####
add_library(SplashKitBackend STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

target_link_libraries(SplashKitBackend ${LIB_FLAGS})

if (MSYS)
    add_definitions(-DWINDOWS)
    link_directories("${SK_LIB}/${OS_PATH_SUFFIX}")
    target_link_libraries(SplashKitBackend SDL2_mixer
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
elseif(APPLE)
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

target_link_libraries(sktest SplashKitBackend)
target_link_libraries(sktest ${LIB_FLAGS})

set_target_properties(sktest
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SK_BIN}
)

# Copy resources folder in
add_custom_command(TARGET sktest
    PRE_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${SK_SRC}/test/Resources" $<TARGET_FILE_DIR:sktest>/Resources)

# if (MSYS)
#     add_custom_command(TARGET sktest
#         PRE_BUILD COMMAND
#         cmake -E copy ../../coresdk/lib/win64/*.dll ../../bin
#         )
# endif()

#### END sktest EXECUTABLE ####

#### skunit_tests EXECUTABLE ####
add_executable(skunit_tests ${UNIT_TEST_SOURCE_FILES})

target_link_libraries(skunit_tests SplashKitBackend)
target_link_libraries(skunit_tests ${LIB_FLAGS})

set_target_properties(skunit_tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${SK_BIN}
        )
#### END sktest EXECUTABLE ####

install(TARGETS SplashKitBackend DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include/SplashKitBackend)
