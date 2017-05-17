#
# CMake file for generating the splashkit CPP library
#
cmake_minimum_required(VERSION 3.2)
project(splashkit)

# Detect Windows and flag MSYS
if (WIN32 OR MSYS OR MINGW)
  SET(MSYS "true")
endif()

# SK Directories relative to cmake project
set(SK_ROOT "../../../..")

set(SK_GENERATED "${SK_ROOT}/generated")
set(SK_OUT "${SK_ROOT}/out")

# Setup OS specific flags
if (APPLE)
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-macos/commands/python3")
elseif(MSYS)
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-windows/commands/python3")
else()
    set(SK_DEPLOY_ROOT "${SK_OUT}/splashkit-linux/commands/python3")
endif()

#### END SETUP ####

# PASCAL FILES
file(GLOB SK_ADAPTER_SOURCE_FILES
    "${SK_GENERATED}/python/*.py"
)

get_filename_component(SK_DEPLOY_ROOT ${SK_DEPLOY_ROOT} ABSOLUTE)

install(FILES ${SK_ADAPTER_SOURCE_FILES} DESTINATION ${SK_DEPLOY_ROOT})