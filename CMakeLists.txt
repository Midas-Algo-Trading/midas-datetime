cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_executable(datetime main.cpp util/string_util.h DatetimeComponent.cpp DatetimeComponent.h Horologe.cpp Horologe.h time/TimeComponent.h time/TimeComponent.cpp time/Time.h time/components/Hour.h time/components/Microsecond.h time/components/Minute.h time/components/Second.cpp time/Time.cpp time/components/Hour.cpp time/components/Microsecond.cpp time/components/Minute.cpp time/components/Nanosecond.cpp)
