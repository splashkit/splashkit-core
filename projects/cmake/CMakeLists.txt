cmake_minimum_required(VERSION 3.2)
project(splashkit)

if (APPLE)
    set(LIB_FLAGS "-L../../coresdk/lib/mac -framework IOKit -framework ForceFeedback -framework CoreFoundation -framework Cocoa -framework Carbon -framework AudioUnit -framework AudioToolbox -framework CoreAudio -framework CoreVideo -lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2_net -lpthread -lbz2 -lFLAC -lvorbis -lz -lpng16 -lvorbisfile -lmikmod -logg -lwebp -lsmpeg2 -lfreetype -lcurl -lsqlite3 -ldl")
else()
    set(LIB_FLAGS "-lSDL2 -lSDL2_mixer -lSDL2_ttf -lSDL2_gfx -lSDL2_image -lSDL2_net -lpthread -lbz2 -lFLAC -lvorbis -lz -lpng16 -lvorbisfile -lmikmod -logg -lwebp -lsmpeg2 -lfreetype -lcurl -lsqlite3 -ldl")
endif()

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

file(GLOB SOURCE_FILES
        ../../coresdk/src/coresdk/*.cpp
        ../../coresdk/src/backend/*.cpp
        ../../coresdk/src/backend/*.h
        ../../coresdk/external/civetweb/src/civetweb.cpp)

file(GLOB TEST_SOURCE_FILES
        ../../coresdk/src/test/*.cpp
        ../../coresdk/src/test/*.h
)

file(GLOB INCLUDE_FILES
        ../../coresdk/src/coresdk/*.h
)

include_directories(../../coresdk/src)
include_directories(../../coresdk/src/coresdk)
include_directories(../../coresdk/src/backend)
include_directories(../../coresdk/src/test)
include_directories(../../coresdk/external/civetweb/include)

if (APPLE)
    include_directories(../../coresdk/external/SDL/include)
    include_directories(../../coresdk/external/SDL_gfx)
    include_directories(../../coresdk/external/SDL_image/external/libpng-1.6.2)
    include_directories(../../coresdk/external/SDL_image)
    include_directories(../../coresdk/external/SDL_mixer)
    include_directories(../../coresdk/external/SDL_net)
    include_directories(../../coresdk/external/SDL_ttf)
endif()

add_library(splashkit SHARED ${SOURCE_FILES} ${INCLUDE_FILES})
target_link_libraries(splashkit ${LIB_FLAGS})

add_executable(splashkit_test ${TEST_SOURCE_FILES})
target_link_libraries(splashkit_test splashkit)
target_link_libraries(splashkit_test ${LIB_FLAGS})

add_custom_command(TARGET splashkit_test PRE_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory
        ../../coresdk/src/test/Resources $<TARGET_FILE_DIR:splashkit_test>/Resources)

install(TARGETS splashkit DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include/splashkit)
