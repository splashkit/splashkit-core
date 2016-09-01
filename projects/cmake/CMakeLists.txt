cmake_minimum_required(VERSION 3.2)
project(splashkit)

# SK Directories relative to cmake project
set(SK_SRC "../../coresdk/src")
set(SK_EXT "../../coresdk/external")
set(SK_LIB "../../coresdk/lib")
set(SK_OUT "../../out")
set(SK_BIN "../../bin")

#### SETUP ####
if (APPLE)
    # MAC OS PROJECT FLAGS
    set(LIB_FLAGS "-L../../coresdk/lib/mac \
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
                   -lsqlite3 \
                   -ldl")
# WINDOWS PROJECT FLAGS
elseif(MSYS)
    set(LIB_FLAGS "-L../../coresdk/lib/win64 \
                   -L/mingw64/lib \
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
                   -lsmpeg2 \
                   -lfreetype \
                   -lcurl \
                   -lsqlite3 \
                   -ldl")
endif()

# FLAGS
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

# SOURCE FILES
file(GLOB SOURCE_FILES
    "${SK_SRC}/coresdk/*.cpp"
    "${SK_SRC}/backend/*.cpp"
    "${SK_EXT}/civetweb/src/civetweb.cpp"
)

# TEST FILE INCLUDES
file(GLOB TEST_SOURCE_FILES
    "${SK_SRC}/test/*.cpp"
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

#### END SETUP ####
#### SplashKit STATIC LIBRARY ####
add_library(SplashKit STATIC ${SOURCE_FILES} ${INCLUDE_FILES})

target_link_libraries(SplashKit ${LIB_FLAGS})

if (MSYS)
    target_link_libraries(SplashKit SDL2_mixer.dll
                                    SDL2_image.dll
                                    SDL2_net.dll
                                    libcivetweb.dll
                                    SDL2.dll
                                    SDL2_ttf.dll
                                    SDL2_ttf.dll
                                    libcurl.dll
                                    libSDL2_gfx-1-0-0.dll
                                    libpng16-16.dll
                                    libsqlite.dll)
endif()

# SET OUTPUT TO /path/to/splashkit/out/lib
set_target_properties(SplashKit
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${SK_OUT}/lib"
)

#### END SplashKit STATIC LIBRARY ####
#### sktest EXECUTABLE ####
add_executable(sktest ${TEST_SOURCE_FILES})

target_link_libraries(sktest SplashKit)
target_link_libraries(sktest ${LIB_FLAGS})

set_target_properties(sktest
    PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${SK_BIN}
)

# Copy resources folder in
add_custom_command(TARGET sktest
    PRE_BUILD COMMAND
    ${CMAKE_COMMAND} -E copy_directory "${SK_SRC}/test/Resources" $<TARGET_FILE_DIR:sktest>/Resources)

#### END sktest EXECUTABLE ####

install(TARGETS SplashKit DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include/SplashKit)
