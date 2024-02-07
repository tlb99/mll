cmake_minimum_required(VERSION 3.10)  # Specify the minimum version of CMake

project(MLL VERSION 1.0
            DESCRIPTION "Machine Learning Library"
            LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Add library
add_library(lib SHARED src/lib.cpp)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
