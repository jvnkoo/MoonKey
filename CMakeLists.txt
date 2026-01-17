cmake_minimum_required(VERSION 3.20)
project(MoonKey)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

link_directories(${CMAKE_CURRENT_SOURCE_DIR}/lib)

add_executable(MoonKey src/main.cpp)

target_link_libraries(MoonKey lua54)