include(FetchContent)
FetchContent_Declare(
        googletest
        # Specify the commit you depend on and update it regularly.
        URL https://github.com/google/googletest/archive/5376968f6948923e2411081fd9372e71a59d8e77.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

add_library(DatetimeLib
        ../src/time/Time.h
        ../src/time/Time.cpp
        ../src/time/components/Hour.h
        ../src/Component.h
        ../src/time/components/Minute.h
        ../src/time/components/Second.h
        ../src/time/components/Microsecond.h
        ../src/time/components/Nanosecond.h
        ../src/date/Date.cpp
        ../src/date/Date.h
        ../src/date/components/Day.h
        ../src/time/Timezone.h
        ../src/time/components/Millisecond.h
        ../src/time/TimeRange.h
        ../src/Range.h
        ../util/exceptions/not_implemented_error.h
        ../src/date/DateRange.h
        ../src/datetime/Datetime.cpp
        ../src/datetime/Datetime.h
        ../src/datetime/DatetimeRange.h
        ../src/time/components/TimeComponent.h)


# Now simply link against gtest or gtest_main as needed. Eg
add_executable(test DateTest.cpp TimeTest.cpp DatetimeTest.cpp Test.cpp)

target_link_libraries(test DatetimeLib StringHelpersLib gtest_main)
add_test(NAME example_test COMMAND example)