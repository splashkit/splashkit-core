cmake_minimum_required(VERSION 3.2)
project(splashkit)

cmake_policy(SET CMP0083 NEW)
include(CheckPIESupported)
check_pie_supported()

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

if(EMSCRIPTEN)
  SET(MSYS "false")
endif()

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
                   -lncurses \
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

    set(LIB_FLAGS  "-L${SK_LIB}/${OS_PATH_SUFFIX} \
                    -L/${MINGW_PATH_PART}/lib \
                    -L/usr/lib \
                    -lSDL2main")
# EMSCRIPTEN PROJECT FLAGS
elseif(EMSCRIPTEN)
    message("Using emscripten")
    set(LIB_FLAGS "-lpthread \
                   -ldl \
                   -s LINKABLE=1 \
                   -s EXPORT_ALL=1 \
                   -sUSE_SDL=2 \
                   -sUSE_SDL_TTF=2 \
                   -sUSE_SDL_GFX=2 \
                   -sUSE_SDL_NET=2 \
                   -sUSE_SDL_MIXER=2 \
                   -sUSE_SDL_IMAGE=2 \
                   -sSDL2_IMAGE_FORMATS='[\"bmp\",\"png\",\"xpm\"]'")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++17 -sUSE_SDL=2")

    file(GLOB BUILD_AS_WINDOWS_FILES
        "${SK_EXT}/civetweb/src/civetweb.c"
        "${SK_EXT}/sqlite/sqlite3.c"
        "${SK_EXT}/hash-library/*.cpp"
        "${SK_SRC}/coresdk/terminal.cpp"
    )
    file(GLOB BUILD_AS_LINUX_FILES
        "${SK_EXT}/easyloggingpp/*.cc"
    )

    set_source_files_properties(${BUILD_AS_WINDOWS_FILES} PROPERTIES COMPILE_DEFINITIONS "WINDOWS")
    set_source_files_properties(${BUILD_AS_LINUX_FILES} PROPERTIES COMPILE_DEFINITIONS "__linux")
    set(CMAKE_EXECUTABLE_SUFFIX ".html")

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

if (EMSCRIPTEN)
  file(GLOB WASM_SOURCE_FILES
    "${SK_LIB}/wasm/*.cpp"
  )
  set(SOURCE_FILES ${SOURCE_FILES} ${WASM_SOURCE_FILES})
endif()

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
if (APPLE OR MSYS OR EMSCRIPTEN)
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
if (MSYS OR EMSCRIPTEN)
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

if (EMSCRIPTEN)
    # Ensure the 'generated' folder exists
    add_custom_target(WASMBindingsDirectory ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory "${SK_SRC}/emscripten_javascript/generated/")

    # Auto generate C++ Javascript Glue code from IDL bindings (the next dependency)
    add_custom_target( WASMBindings ALL DEPENDS "${SK_SRC}/emscripten_javascript/SplashKitWasm.idl" "${SK_SRC}/emscripten_javascript/generated/SplashKitWasmGlue.cpp")

    add_custom_command(
        DEPENDS "${SK_SRC}/emscripten_javascript/SplashKitWasm.idl"
        OUTPUT "${SK_SRC}/emscripten_javascript/generated/SplashKitWasmGlue.cpp" "${SK_SRC}/emscripten_javascript/generated/SplashKitWasmGlue.js"
        COMMENT "Generating Bindings..."
        COMMAND
        python "$ENV{EMSCRIPTEN}/tools/webidl_binder.py" "${SK_SRC}/emscripten_javascript/SplashKitWasm.idl" "${SK_SRC}/emscripten_javascript/generated/SplashKitWasmGlue")

    add_dependencies(WASMBindings WASMBindingsDirectory)
    add_dependencies(SplashKitBackend WASMBindings)

    # Auto generate IDL bindings first
    add_custom_target( WebIDLBindings ALL DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../../generated/docs/api.json")

    add_custom_command(
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/../../generated/docs/api.json" "${CMAKE_CURRENT_SOURCE_DIR}/../../tools/scripts/generateWebIDLBindings.py"
        OUTPUT "${SK_SRC}/emscripten_javascript/SplashKitWasmGlueWrapper.cpp" "${SK_SRC}/emscripten_javascript/SplashKitWasm.idl" "${SK_OUT}/lib/SplashKitGlobalAPI.js"
        COMMENT "Generating Web IDL Bindings..."
        COMMAND
        python "${CMAKE_CURRENT_SOURCE_DIR}/../../tools/scripts/generateWebIDLBindings.py" "${CMAKE_CURRENT_SOURCE_DIR}/../../generated/docs/api.json" "${SK_SRC}/emscripten_javascript/SplashKitWasmGlueWrapper.cpp" "${SK_SRC}/emscripten_javascript/SplashKitWasm.idl" "${SK_OUT}/lib/SplashKitGlobalAPI.js")

    add_dependencies(WASMBindings WebIDLBindings)

    list(FILTER SOURCE_FILES EXCLUDE REGEX ".*SplashKitWasmGlue\\.cpp$")
endif()

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
#### SplashKitBackend WASM LIBRARY ####
if (EMSCRIPTEN)
    add_executable(SplashKitBackendWASM "${SK_SRC}/emscripten_javascript/SplashKitWasmGlueWrapper.cpp")
    set_target_properties(SplashKitBackendWASM PROPERTIES LINK_FLAGS "--post-js ${SK_SRC}/emscripten_javascript/generated/SplashKitWasmGlue.js")
    target_link_libraries(SplashKitBackendWASM SplashKitBackend)
    set_target_properties(SplashKitBackendWASM
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY "${SK_OUT}/lib"
    )
    add_dependencies(SplashKitBackendWASM WASMBindings)
    #set_target_properties(SplashKitBackendWASM PROPERTIES SUFFIX ".js")
endif()
#### END SplashKitBackend WASM LIBRARY ####
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


if (EMSCRIPTEN)
    set_target_properties(sktest PROPERTIES LINK_FLAGS "--preload-file ${SK_SRC}/test/Resources@Resources")
endif()

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
target_link_libraries(skunit_tests SplashKitBackend)
target_link_libraries(skunit_tests ${LIB_FLAGS})

if (EMSCRIPTEN)
    set_target_properties(skunit_tests PROPERTIES LINK_FLAGS "--preload-file ${SK_SRC}/test/Resources@Resources")
endif()

set_target_properties(skunit_tests
        PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY ${SK_BIN}
        )
#### END sktest EXECUTABLE ####

install(TARGETS SplashKitBackend DESTINATION lib)
install(FILES ${INCLUDE_FILES} DESTINATION include/SplashKitBackend)
