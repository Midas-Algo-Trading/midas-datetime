cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_executable(datetime main.cpp date/date.h date/date.cpp util/string_util.h date/components/year.h date/components/year.cpp date/components/month.cpp date/components/month.h date/components/day.cpp date/components/day.h)
