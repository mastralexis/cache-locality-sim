cmake_minimum_required(VERSION 3.15)
set(CMAKE_POLICY_VERSION_MINIMUM 3.5)

if(POLICY CMP0135)
    cmake_policy(SET CMP0135 NEW)
endif()

project(cache-locality-sim VERSION 1.0 DESCRIPTION "Cache Locality Simulation" LANGUAGES C)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_executable(${PROJECT_NAME} src/main.c)
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_SOURCE_DIR}/include)

find_package(raylib QUIET)

if (NOT raylib_FOUND)
    message(STATUS "Raylib not found natively. Fetching automatically from GitHub...")
    include(FetchContent)
    
    FetchContent_Declare(
        raylib
        URL https://github.com/raysan5/raylib/archive/refs/tags/5.0.tar.gz
    )
    
    set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
    set(BUILD_GAMES    OFF CACHE BOOL "" FORCE)
    
    FetchContent_MakeAvailable(raylib)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE raylib)

if (UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE m)
endif()
