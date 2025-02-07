cmake_minimum_required(VERSION 3.30)
project(exercise_1)

set(CMAKE_CXX_STANDARD 23)
add_compile_options(/fsanitize=address)
add_link_options(/fsanitize=address)
add_executable(exercise_1 main.cpp)
