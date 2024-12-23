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

#### END SETUP ####

# C# FILES
file(GLOB SK_ADAPTER_SOURCE_FILES
    "${SK_GENERATED}/csharp/*.cs"
)

get_filename_component(SK_DEPLOY_ROOT ${SK_DEPLOY_ROOT} ABSOLUTE)

install(FILES ${SK_ADAPTER_SOURCE_FILES} DESTINATION ${SK_DEPLOY_ROOT}/dotnet)

# if (APPLE)
#     INSTALL(CODE "execute_process( \
#       COMMAND ${CMAKE_COMMAND} -E create_symlink \
#       libSplashKit.dylib \
#       ${SK_OUT}/splashkit-macos/lib/splashkit.dll   \
#       )"
#     )
# endif()
