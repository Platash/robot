cmake_minimum_required(VERSION 3.7.2)
project(robot_simulator LANGUAGES CXX VERSION 1.0.0 DESCRIPTION "Robot simulator")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/build)

add_subdirectory(src)
add_subdirectory(test)


