find_package(Catch2 REQUIRED)

enable_testing()

add_executable(tests robotTest.cpp parserTest.cpp)
include_directories(${PROJECT_SOURCE_DIR}/include)
target_link_libraries(tests PUBLIC Catch2::Catch2WithMain robot parser)

include(CTest)
include(Catch)
catch_discover_tests(tests)
