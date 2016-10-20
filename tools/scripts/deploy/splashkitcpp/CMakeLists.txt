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
                   -lcurl \
                   -lncurses")
# WINDOWS PROJECT FLAGS
elseif(MSYS)
    add_definitions(-DWINDOWS)
    set(LIB_FLAGS "-L${SK_LIB}/win64 \
                   -L/mingw64/lib \
                   -L/usr/lib \
                   -lSDL2main")
# LINUX PROJECT FLAGS
else()
    set(LIB_FLAGS "-lcurl \
                   -lncurses")
endif()

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# SOURCE FILES
file(GLOB SOURCE_FILES
    "${SK_GENERATED}/coresdk/*.cpp"
    "${SK_SRC}/backend/*.cpp"
    "${SK_EXT}/civetweb/src/civetweb.cpp"
    "${SK_EXT}/sqlite/sqlite3.c"
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
    include_directories("${SK_EXT}/sqlite")
endif()

# MACRO DEFINITIONS #
add_definitions(-DELPP_THREAD_SAFE)

#### END SETUP ####
#### SplashKitBackend STATIC LIBRARY ####
add_library(SplashKitBackend STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

target_link_libraries(SplashKitBackend ${LIB_FLAGS})

if (MSYS)
    link_directories("${SK_LIB}/win64")
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

if (MSYS)
    add_custom_command(TARGET sktest
        PRE_BUILD COMMAND
        ${CMAKE_COMMAND} -E copy "${SK_LIB}/win64/*.dll" $<TARGET_FILE_DIR:sktest>)
endif()

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
