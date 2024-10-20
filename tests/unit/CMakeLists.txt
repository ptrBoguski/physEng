# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UnitTests)

# Set the module path to include the cmake directory
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake")

# Manually specify the GTest library using a custom path
add_library(GTest::GTest UNKNOWN IMPORTED)
set_target_properties(GTest::GTest PROPERTIES
  IMPORTED_LOCATION "/home/dns/Dev/googletest/build/lib/libgtest.a"
)

# Manually specify the GMock library using a custom path
add_library(GMock::GMock UNKNOWN IMPORTED)
set_target_properties(GMock::GMock PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../googletest/build/lib/libgmock.a"
)

# Manually specify the GTest Main library using a custom path
add_library(GTest::Main UNKNOWN IMPORTED)
set_target_properties(GTest::Main PROPERTIES
  IMPORTED_LOCATION "${CMAKE_SOURCE_DIR}/../googletest/build/lib/libgtest_main.a"
)

# Find Boost
find_package(Boost REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS})

# Add the Rigidbody test executable
add_executable(test_Rigidbody test_Rigidbody.cpp)
add_executable(test_SphericRigidbody test_SphericRigidbody.cpp)
add_executable(test_SphereCollisionDetection test_SphereCollisionDetection.cpp)

# Link GTest, GMock, and GTest Main to the Rigidbody test
target_link_libraries(test_Rigidbody PRIVATE PhysEngLib GTest::GTest GMock::GMock GTest::Main)
target_link_libraries(test_SphericRigidbody PRIVATE PhysEngLib GTest::GTest GMock::GMock GTest::Main)
target_link_libraries(test_SphereCollisionDetection PRIVATE PhysEngLib GTest::GTest GMock::GMock GTest::Main)

# Find OpenGL, GLEW, and GLFW
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(glfw3 REQUIRED)

# Find GLM
find_path(GLM_INCLUDE_DIR glm/glm.hpp)

# Add the OpenGLRenderer test executable
add_executable(test_OpenGLRenderer test_OpenGLRenderer.cpp)

# Include directories for OpenGLRenderer test
target_include_directories(test_OpenGLRenderer PRIVATE 
    ${OPENGL_INCLUDE_DIRS} 
    ${GLM_INCLUDE_DIR} 
    ${GLEW_INCLUDE_DIRS} 
    ${GLFW_INCLUDE_DIRS}
)

# Link libraries for OpenGLRenderer test
target_link_libraries(test_OpenGLRenderer PRIVATE 
    PhysEngLib 
    ${OPENGL_LIBRARIES} 
    GLEW::GLEW 
    glfw
    GTest::GTest
    GMock::GMock
    GTest::Main
)

# Enable testing
enable_testing()

# Add tests
add_test(NAME TestRigidbody COMMAND test_Rigidbody)
add_test(NAME TestSphericRigidbody COMMAND test_SphericRigidbody)
add_test(NAME TestOpenGLRenderer COMMAND test_OpenGLRenderer)
add_test(NAME TestSphereCollisionDetection COMMAND test_SphereCollisionDetection)
