# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(PhysEngLib)

# Add source files for the PhysEngLib library
add_library(PhysEngLib
    physics/rigidbody/SphericRigidbody.cpp
    renderer/OpenGLRenderer.cpp
    # Add other source files here
)

find_package(Boost REQUIRED)

# Include directories for the library
target_include_directories(PhysEngLib PUBLIC
    ${CMAKE_SOURCE_DIR}/include
)
# Find OpenGL, GLFW, and GLEW
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Add the main executable
add_executable(PhysEngMain sandbox.cpp renderer/OpenGLRenderer.cpp)

# Link the executable with OpenGL, GLFW, and GLEW
target_link_libraries(PhysEngMain PhysEngLib OpenGL::GL GLEW::GLEW glfw)
