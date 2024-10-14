# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PhysEngLib)

# Add source files for the PhysEngLib library
add_library(PhysEngLib
    physics/rigidbody/Rigidbody.cpp
    # Add other source files here
)

# Include directories for the library
target_include_directories(PhysEngLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
