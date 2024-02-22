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

include_directories(include)

set(INCLUDE
        include/Stack.h
        include/ProcessorEmulator.h
        include/CommandParser.h
)

add_library(${PROJECT_NAME} INTERFACE ${INCLUDE})

add_executable(${PROJECT_NAME}_tests tests/tests.cpp)
target_link_libraries(${PROJECT_NAME}_tests PRIVATE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME}_tests PRIVATE gtest_main)

include(GoogleTest)
gtest_discover_tests(${PROJECT_NAME}_tests)