cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_subdirectory(libs/stringhelpers)

find_package(fmt CONFIG REQUIRED)

    add_library(${PROJECT_NAME}
        include/datetime/time/Time.h
        include/datetime/time/components/Hours.h
        include/datetime/time/components/Minutes.h
        include/datetime/time/components/Seconds.h
        include/datetime/time/components/Microseconds.h
        include/datetime/time/components/Nanoseconds.h
        include/datetime/date/Date.h
        include/datetime/date/components/Days.h
        include/datetime/time/Timezone.h
        include/datetime/time/components/Milliseconds.h
        include/datetime/time/TimeRange.h
        src/util/exceptions/not_implemented_error.h
        include/datetime/date/DateRange.h
        include/datetime/datetime/Datetime.h
        include/datetime/datetime/DatetimeRange.h
        include/datetime/timedelta/TimeDelta.h
        include/datetime/time/TimeComponent.h
        include/datetime/date/DateComponent.h

        src/Component.h
        src/Range.h
        src/time/BasicTime.h
        src/time/Time.cpp
        src/date/Date.cpp
        src/datetime/Datetime.cpp
        src/timedelta/TimeDelta.cpp
        src/time/BasicTime.cpp)

target_include_directories(${PROJECT_NAME} PUBLIC
        libs/stringhelpers/include)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

target_link_libraries(${PROJECT_NAME} PUBLIC stringhelpers fmt::fmt)

option(DATETIME_BUILD_TESTS "Build the test directory for datetime" OFF)
if (DATETIME_BUILD_TESTS)
    add_subdirectory(tests)
endif()