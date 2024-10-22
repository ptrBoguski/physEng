# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UnitTests)

# Include FetchContent module
include(FetchContent)

# Fetch GoogleTest
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/refs/tags/release-1.11.0.zip
)
FetchContent_MakeAvailable(googletest)

# Find Boost
find_package(Boost REQUIRED)

# Include directories
include_directories(${Boost_INCLUDE_DIRS})

# Add the Rigidbody test executable
add_executable(test_Rigidbody test_Rigidbody.cpp)
add_executable(test_SphericRigidbody test_SphericRigidbody.cpp)
add_executable(test_SphereCollisionDetection test_SphereCollisionDetection.cpp)

# Link GTest, GMock, and GTest Main to the Rigidbody test
target_link_libraries(test_Rigidbody PRIVATE PhysEngLib GTest::gtest GTest::gmock GTest::gtest_main)
target_link_libraries(test_SphericRigidbody PRIVATE PhysEngLib GTest::gtest GTest::gmock GTest::gtest_main)
target_link_libraries(test_SphereCollisionDetection PRIVATE PhysEngLib GTest::gtest GTest::gmock GTest::gtest_main)

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
    GTest::gtest
    GTest::gmock
    GTest::gtest_main
)

# Enable testing
enable_testing()

# Add tests
add_test(NAME TestRigidbody COMMAND test_Rigidbody)
add_test(NAME TestSphericRigidbody COMMAND test_SphericRigidbody)
add_test(NAME TestSphereCollisionDetection COMMAND test_SphereCollisionDetection)
add_test(NAME TestOpenGLRenderer COMMAND test_OpenGLRenderer)
