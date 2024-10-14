# Specify the minimum version for CMake
cmake_minimum_required(VERSION 3.10)

# Set the project name
project(UnitTests)

# Find GTest package
find_package(GTest REQUIRED)

# Add the test executable
add_executable(test_Rigidbody test_Rigidbody.cpp)

# Link the test executable with GTest and the PhysEngLib library
target_link_libraries(test_Rigidbody GTest::GTest GTest::Main PhysEngLib)

#TODO change it to auto
# Register the test manually
add_test(NAME RigidbodyTest COMMAND test_Rigidbody --gtest_filter=RigidbodyTest.*)

# Include directories for the test
target_include_directories(test_Rigidbody PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# Register the test with CTest
include(GoogleTest)
gtest_discover_tests(test_Rigidbody)

enable_testing()

