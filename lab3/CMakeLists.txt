cmake_minimum_required(VERSION 3.20)
project(lab_03 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Раскладка проекта:
#   include/student.hpp, include/student_set.hpp
#   src/student.cpp, src/student_set.cpp, src/main.cpp
#   tests/test_student_set.cpp
add_library(student_lib
    src/student.cpp
    src/student_set.cpp
)
target_include_directories(student_lib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_compile_options(student_lib PUBLIC -Wall -Wextra -Wpedantic)

add_executable(lab_03 src/main.cpp)
target_link_libraries(lab_03 PRIVATE student_lib)

# Google Test
include(FetchContent)
FetchContent_Declare(
    googletest
    URL https://github.com/google/googletest/archive/refs/tags/v1.14.0.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_executable(lab_03_tests tests/test_student_set.cpp)
target_link_libraries(lab_03_tests PRIVATE student_lib GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(lab_03_tests)
