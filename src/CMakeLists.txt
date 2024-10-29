add_library(parser SHARED parser.cpp)
add_library(robot SHARED robot.cpp)

add_executable(robot_simulator main.cpp parser.cpp robot.cpp)

include_directories(${PROJECT_SOURCE_DIR}/include)
