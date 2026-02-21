cmake_minimum_required(VERSION 3.20)
project(MoonKey LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)

find_package(lua REQUIRED)
find_package(sol2 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
add_executable(MoonKey ${SOURCES})

target_link_libraries(MoonKey PRIVATE sol2::sol2 lua)

if(MSVC)
    set_property(TARGET MoonKey PROPERTY MSVC_RUNTIME_LIBRARY "MultiThreaded$<$<CONFIG:Debug>:Debug>")
endif()