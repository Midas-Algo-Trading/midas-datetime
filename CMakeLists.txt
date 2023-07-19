cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs/fmt)

add_library(${PROJECT_NAME}
        include/datetime/time/Time.h
        include/datetime/time/components/Hour.h
        include/datetime/Component.h
        include/datetime/time/components/Minute.h
        include/datetime/time/components/Second.h
        include/datetime/time/components/Microsecond.h
        include/datetime/time/components/Nanosecond.h
        include/datetime/date/Date.h
        include/datetime/date/components/Day.h
        include/datetime/time/Timezone.h
        include/datetime/time/components/Millisecond.h
        include/datetime/time/TimeRange.h
        include/datetime/Range.h
        ../util/exceptions/not_implemented_error.h
        include/datetime/date/DateRange.h
        include/datetime/datetime/Datetime.h
        include/datetime/datetime/DatetimeRange.h
        include/datetime/time/components/TimeComponent.h)

target_sources(${PROJECT_NAME} PRIVATE
        src/date/Date.cpp
        src/datetime/Datetime.cpp
        src/time/Time.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        libs/stringhelpers/include)

include_directories(include)

target_link_libraries(${PROJECT_NAME} fmt::fmt)

option(DATETIME_BUILD_TESTS "Build the test directory for datetime" OFF)

if (DATETIME_BUILD_TESTS)
    add_subdirectory(tests)
endif()