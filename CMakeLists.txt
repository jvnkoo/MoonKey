cmake_minimum_required(VERSION 3.20)
project(MoonKey)

set(CMAKE_CXX_STANDARD 17)

file(DOWNLOAD 
    https://github.com/cpm-cmake/CPM.cmake/releases/download/v0.38.2/CPM.cmake 
    ${CMAKE_BINARY_DIR}/cmake/CPM.cmake)
include(${CMAKE_BINARY_DIR}/cmake/CPM.cmake)

CPMAddPackage(
    NAME Lua
    GITHUB_REPOSITORY lua/lua
    GIT_TAG v5.4.6
)

CPMAddPackage(
    NAME sol2
    GITHUB_REPOSITORY ThePhD/sol2
    GIT_TAG v3.3.0
)
# ------------------------------

add_executable(MoonKey src/main.cpp)

target_link_libraries(MoonKey PRIVATE sol2::sol2 lua)