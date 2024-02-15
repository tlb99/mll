cmake_minimum_required(VERSION 3.28.2)  # Specify the minimum version of CMake

project(MLL VERSION 1.0
            DESCRIPTION "Machine Learning Library"
            LANGUAGES CXX CUDA
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set CUDA standard
set(CMAKE_CUDA_STANDARD 17)
set(CMAKE_CUDA_STANDARD_REQUIRED True)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)

add_subdirectory(tests)
