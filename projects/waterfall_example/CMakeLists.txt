cmake_minimum_required(VERSION 3.16)
# Include this before everything else to ensure we can override things,
# like the project name
include(${CMAKE_SOURCE_DIR}/../cmake/CMakeLists.txt)
set(CMAKE_BUILD_TYPE Debug)
project(Waterfall)

set(SOURCE_CXX 
    ${CMAKE_SOURCE_DIR}/../../generated/clib/sk_clib.cpp
    ${CMAKE_SOURCE_DIR}/../../generated/clib/lib_type_mapper.cpp
    ${CMAKE_SOURCE_DIR}/../../generated/cpp/adapter_type_mapper.cpp
    ${CMAKE_SOURCE_DIR}/../../generated/cpp/splashkit.cpp
    # box2d_spike.cpp
    waterfall_demonstration.cpp

)

add_executable(${PROJECT_NAME} ${SOURCE_CXX})
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../../generated/cpp/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../../generated/clib/)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/../../src/coresdk)
target_link_libraries(${PROJECT_NAME} SplashKitBackend)
target_link_libraries(${PROJECT_NAME} Box2D)