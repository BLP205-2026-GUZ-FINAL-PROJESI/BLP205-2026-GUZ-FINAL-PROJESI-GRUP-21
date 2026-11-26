cmake_minimum_required(VERSION 3.15)
project(MyWorkspace)

set(CMAKE_CXX_STANDARD 17)

file(GLOB_RECURSE SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/*.cpp")

list(FILTER SOURCES EXCLUDE REGEX "${CMAKE_CURRENT_SOURCE_DIR}/build/.*")

add_executable(my_app ${SOURCES})

target_include_directories(my_app PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}")