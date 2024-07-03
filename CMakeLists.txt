cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs/stringhelpers)

find_package(fmt CONFIG REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "include/*.h" "src/*.h" "src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC stringhelpers fmt::fmt)

option(DATETIME_BUILD_TESTS "Build the test directory for datetime" OFF)
if (DATETIME_BUILD_TESTS)
    add_subdirectory(tests)
endif()
