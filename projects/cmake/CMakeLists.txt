cmake_minimum_required(VERSION 3.2)
project(splashkit)

if (APPLE)
    set(LIB_FLAGS "-L../../coresdk/lib/mac -framework IOKit -framework ForceFeedback -framework CoreFoundation -framework Cocoa -framework Carbon -framework AudioUnit -framework AudioToolbox -framework CoreAudio -framework CoreVideo -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2_net -lpthread -lbz2 -lFLAC -lvorbis -lz -lpng16 -lvorbisfile -lmikmod -logg -lwebp -lsmpeg2 -lfreetype -lcurl -lsqlite3 -ldl")
elseif(MSYS)
    set(LIB_FLAGS "-L../../coresdk/lib/win64 -L/mingw64/lib -L/usr/lib -lSDL2main")
else()
    set(LIB_FLAGS "-lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2_net -lpthread -lbz2 -lFLAC -lvorbis -lz -lpng16 -lvorbisfile -lmikmod -logg -lwebp -lsmpeg2 -lfreetype -lcurl -lsqlite3 -ldl")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB SOURCE_FILES
        ../../coresdk/src/coresdk/*.cpp
        ../../coresdk/src/backend/*.cpp
        ../../coresdk/external/civetweb/src/civetweb.cpp)

file(GLOB TEST_SOURCE_FILES
        ../../coresdk/src/test/*.cpp
        )

file(GLOB INCLUDE_FILES
        ../../coresdk/src/coresdk/*.h
        )

include_directories(../../coresdk/src)
include_directories(../../coresdk/src/coresdk)
include_directories(../../coresdk/src/backend)
include_directories(../../coresdk/src/test)
include_directories(../../coresdk/external/civetweb/include)

if (APPLE OR MSYS)
    include_directories(../../coresdk/external/SDL/include)
    include_directories(../../coresdk/external/SDL_gfx)
    include_directories(../../coresdk/external/SDL_image)
    include_directories(../../coresdk/external/SDL_mixer)
    include_directories(../../coresdk/external/SDL_net)
    include_directories(../../coresdk/external/SDL_ttf)
endif()

if (APPLE)
    include_directories(../../coresdk/external/SDL_image/external/libpng-1.6.2)
endif()

if (MSYS)
    include_directories(/mingw64/include)
    include_directories(/mingw64/include/libpng16)
    include_directories(../../coresdk/lib/win_inc)
    include_directories(../../coresdk/external/sqlite)
endif()


add_library(splashkit SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
if (MSYS)
    target_link_libraries(splashkit SDL2_mixer.dll SDL2_image.dll SDL2_net.dll  libcivetweb.dll SDL2.dll SDL2_ttf.dll SDL2_ttf.dll libcurl.dll libSDL2_gfx-1-0-0.dll libpng16-16.dll libsqlite.dll)
endif()
target_link_libraries(splashkit ${LIB_FLAGS})

add_executable(splashkit_test ${TEST_SOURCE_FILES})
target_link_libraries(splashkit_test splashkit)
target_link_libraries(splashkit_test ${LIB_FLAGS})

add_custom_command(TARGET splashkit_test PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ../../coresdk/src/test/Resources $<TARGET_FILE_DIR:splashkit_test>/Resources)

install(TARGETS splashkit DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include/splashkit)