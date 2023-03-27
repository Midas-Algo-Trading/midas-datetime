cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_executable(datetime main.cpp date/date.h date/date.cpp util/string_util.h time/Time.cpp time/Time.h DatetimeComponent.cpp DatetimeComponent.h time/components/Nanosecond.cpp time/components/Nanosecond.h time/components/Microsecond.cpp time/components/Microsecond.h time/TimeComponent.cpp time/TimeComponent.h time/components/Second.cpp time/components/Second.h time/components/Minute.cpp time/components/Minute.h time/components/Hour.cpp time/components/Hour.h date/DateComponent.cpp date/DateComponent.h)
