cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs/stringhelpers)

find_package(fmt CONFIG REQUIRED)
find_package(Boost REQUIRED)

file(GLOB_RECURSE SOURCE_FILES "${CMAKE_SOURCE_DIR}/src/*.h" "${CMAKE_SOURCE_DIR}/src/*.cpp")

add_library(${PROJECT_NAME} ${SOURCE_FILES})

target_include_directories(${PROJECT_NAME} PUBLIC include)

target_link_libraries(${PROJECT_NAME} PUBLIC stringhelpers fmt::fmt ${Boost_LIBRARIES})

option(DATETIME_BUILD_TESTS "Build the test directory for datetime" OFF)
if (DATETIME_BUILD_TESTS)
    add_subdirectory(tests)
endif()