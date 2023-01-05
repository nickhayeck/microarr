# Version Requirement for CMake
cmake_minimum_required(VERSION 3.23)
# Project Name
project(micro-array)
# Set C++ Standard to C++11
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Ensure all warnings are on
add_compile_options(-Wall -Wextra -pedantic -Werror)
# Add the include dir
include_directories(include)
## Main Library compilation
# The source files for the project
set(SRC_FILES lib/microarr.cpp)
# Add the main executable to the build script
add_library(microarr ${SRC_FILES})

## Test compilation
# target the test suite executable
add_executable(test_ops test/test_ops.cpp)
target_link_libraries(test_ops microarr)
add_executable(test_ind test/test_ind.cpp)
target_link_libraries(test_ind microarr)
# enable testing
enable_testing()
# define the test runners
add_test(
    NAME test_ops
    COMMAND $<TARGET_FILE:test_ops>
)
add_test(
    NAME test_ind
    COMMAND $<TARGET_FILE:test_ind>
)