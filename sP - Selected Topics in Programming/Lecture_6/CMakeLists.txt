cmake_minimum_required(VERSION 3.30)
project(Exercise6)

set(CMAKE_CXX_STANDARD 23)

include(doctest.cmake)

enable_testing()

add_executable(main main.cpp)
target_link_libraries(main PRIVATE doctest_with_main)
add_test(NAME main COMMAND main)
