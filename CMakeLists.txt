cmake_minimum_required(VERSION 3.27)
project(ProcessorEmulator)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(
        googletest
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

include_directories(src)

set(SRC
        src/Stack.h
        src/ProcessorEmulator.h
        src/ProcessorEmulator.cpp
        src/CommandParser.h
        src/Commands.h
        src/CommandParser.cpp
        src/Commands.cpp
)

add_library(${PROJECT_NAME} ${SRC})
target_include_directories(${PROJECT_NAME} PRIVATE src)

add_executable(${PROJECT_NAME}_stack_tests tests/stack_tests.cpp)
target_link_libraries(${PROJECT_NAME}_stack_tests PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_stack_tests PRIVATE gtest_main)

add_executable(${PROJECT_NAME}_parser_tests tests/emulTests.cpp)
target_link_libraries(${PROJECT_NAME}_parser_tests PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_parser_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_stack_tests)
gtest_discover_tests(${PROJECT_NAME}_parser_tests)