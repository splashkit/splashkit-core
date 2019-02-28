#
# CMake file for generating the splashkit CPP library
#
cmake_minimum_required(VERSION 3.2)
project(splashkit)

# Detect Windows and flag MSYS
if (WIN32 OR MSYS OR MINGW)
  SET(MSYS "true")

  string(COMPARE EQUAL "MINGW32" "$ENV{MSYSTEM}" MINGW32)
  string(COMPARE EQUAL "MINGW64" "$ENV{MSYSTEM}" MINGW64)

  if (${MINGW32})
    message("Using mingw32")
    set(WIN_PATH_SUFFIX "win32")
    set(MINGW_PATH_PART "mingw32")
  elseif (${MINGW64})
    message("Using mingw64")
    set(WIN_PATH_SUFFIX "win64")
    set(MINGW_PATH_PART "mingw64")
  else ( )
    message(SEND_ERROR "Failed to detect windows architecture")
    return ()
  endif()

  set(WIN_NAME_SUFFIX "-${WIN_PATH_SUFFIX}")
endif()

# SK Directories relative to cmake project
set(SK_ROOT "../../../..")
set(SK_SRC "${SK_ROOT}/coresdk/src")
set(SK_EXT "${SK_ROOT}/coresdk/external")
set(SK_LIB "${SK_ROOT}/coresdk/lib")

set(SK_GENERATED "${SK_ROOT}/generated")
set(SK_BIN "${SK_ROOT}/bin")
set(SK_OUT "${SK_ROOT}/out")

set(SK_OUT "${SK_ROOT}/out")

set(SK_DEPLOY_ROOT "${SK_OUT}/skm/fpc")

#### END SETUP ####

# PASCAL FILES
file(GLOB SK_ADAPTER_SOURCE_FILES
    "${SK_GENERATED}/pascal/*.pas"
)

get_filename_component(SK_DEPLOY_ROOT ${SK_DEPLOY_ROOT} ABSOLUTE)

install(FILES ${SK_ADAPTER_SOURCE_FILES} DESTINATION ${SK_DEPLOY_ROOT})
