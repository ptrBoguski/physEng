cmake_minimum_required(VERSION 3.10)

# Project name
project(PhysEng)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set the module path to include the cmake directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Add subdirectories for source and tests
add_subdirectory(src)
add_subdirectory(tests/unit)

# Enable testing
enable_testing()
