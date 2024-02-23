cmake_minimum_required(VERSION 3.11)  # Specify the minimum version of CMake

project(mll VERSION 1.0
            DESCRIPTION "Machine Learning Library"
            LANGUAGES CXX
)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

enable_testing()

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/extern/pybind11/include)

# Find Python
find_package(Python COMPONENTS Interpreter Development REQUIRED)
include_directories(${Python_INCLUDE_DIRS})

set(PYTHON_EXECUTABLE ${Python_EXECUTABLE})
add_subdirectory(extern/pybind11)
find_package(pybind11 REQUIRED)
pybind11_add_module(mll src/pydef.cpp)

target_link_libraries(
  mll
  PRIVATE
  "C:/Python310/libs/python310.lib"  # Manually specify the Python library
)

# Link Python libraries
target_link_libraries(mll PRIVATE ${Python_LIBRARIES})

add_subdirectory(tests)
