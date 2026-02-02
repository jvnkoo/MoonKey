cmake_minimum_required(VERSION 3.20)
project(MoonKey LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find packages installed via vcpkg
find_package(lua REQUIRED)
find_package(sol2 REQUIRED)

add_executable(MoonKey src/main.cpp)

# Link everything together
target_link_libraries(MoonKey PRIVATE sol2::sol2 ${LUA_LIBRARIES})

target_include_directories(MoonKey PRIVATE ${LUA_INCLUDE_DIR})

if(MINGW OR WIN32)
    target_link_options(MoonKey PRIVATE "-static-libgcc" "-static-libstdc++" "-static")
endif()

# Copy scripts folder to build directory so they are easy to load
# file(COPY "${CMAKE_CURRENT_SOURCE_DIR}/scripts" DESTINATION "${CMAKE_CURRENT_BINARY_DIR}")