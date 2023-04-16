cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_executable(datetime main.cpp util/string_util.h time/Time.h time/Time.cpp time/components/Hour.h time/components/TimeComponent.h Duration.h time/components/Minute.h time/components/Second.h time/components/Microsecond.h time/components/Nanosecond.h)
