cmake_minimum_required(VERSION 3.20)
project(MoonKey LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(lua REQUIRED)
find_package(sol2 REQUIRED)

file(GLOB_RECURSE SOURCES "src/*.cpp")
file(GLOB_RECURSE HEADERS "src/*.hpp")

add_executable(MoonKey ${SOURCES} ${HEADERS})

target_include_directories(MoonKey PRIVATE 
    src
    ${LUA_INCLUDE_DIR}
)

target_link_libraries(MoonKey PRIVATE sol2::sol2 ${LUA_LIBRARIES})

if(MINGW OR WIN32)
    target_link_options(MoonKey PRIVATE "-static-libgcc" "-static-libstdc++" "-static")
endif()

# Copy scripts folder to build directory so they are easy to load
# file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/scripts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")