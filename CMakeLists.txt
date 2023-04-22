cmake_minimum_required(VERSION 3.24)
project(datetime)

set(CMAKE_CXX_STANDARD 23)

add_executable(datetime src/main.cpp util/string_util.h src/time/Time.h src/time/Time.cpp src/time/components/Hour.h src/Component.h src/time/components/Minute.h src/time/components/Second.h src/time/components/Microsecond.h src/time/components/Nanosecond.h src/date/Date.cpp src/date/Date.h src/date/components/Day.h src/time/Timezone.h src/time/components/Millisecond.h src/time/TimeRange.h src/Range.h util/exceptions/NotImplementedError.h src/date/DateRange.h src/datetime/Datetime.cpp src/datetime/Datetime.h src/datetime/DatetimeRange.h)

add_subdirectory(test)