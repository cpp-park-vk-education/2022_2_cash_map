cmake_minimum_required(VERSION 3.18)

include("cmake/HunterGate.cmake")
HunterGate(
        URL "https://github.com/cpp-pm/hunter/archive/v0.23.314.tar.gz"
        SHA1 "95c47c92f68edb091b5d6d18924baabe02a6962a"
)

project(watch_up_project)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)
option(BUILD_DOCS "Build documentation" OFF)
option(BUILD_COVERAGE "Build code coverage" OFF)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wpedantic -Werror -Wall -Wextra")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-command-line-argument")
SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wshadow -Wnon-virtual-dtor")

find_package(GTest CONFIG)
if (NOT GTest_FOUND)
    hunter_add_package(GTest)
endif()
find_package(GTest CONFIG REQUIRED)

if (BUILD_TESTS)
    include(GoogleTest)
    enable_testing()
endif()

if (BUILD_COVERAGE)
    set(ENABLE_COVERAGE ON CACHE BOOL "Enable coverage build." FORCE)
    list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/externals/CMake-codecov/cmake")
    find_package(codecov)
    string(APPEND CMAKE_CXX_FLAGS " --coverage")
endif()

add_subdirectory(server)
add_subdirectory(client)

if (BUILD_COVERAGE)
    coverage_evaluate()
endif()
