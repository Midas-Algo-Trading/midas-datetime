#include "gtest/gtest.h"

#include "datetime/time/Time.h"
#include "datetime/time/TimeRange.h"
#include "datetime/timedelta/TimeDelta.h"

TEST(Time, constructor_sets_members)
{
        Time time = Time(1, 2, 3, 4, 5, 6, TZ::CST);
        EXPECT_EQ(time.hour, 1);
        EXPECT_EQ(time.minute, 2);
        EXPECT_EQ(time.second, 3);
        EXPECT_EQ(time.millisecond, 4);
        EXPECT_EQ(time.microsecond, 5);
        EXPECT_EQ(time.nanosecond, 6);
        EXPECT_EQ(time.timezone, TZ::CST);
}

TEST(Time, constructor_throws_invalid_argument)
{
        EXPECT_THROW(Time(24), std::invalid_argument);
        EXPECT_THROW(Time(1, 61), std::invalid_argument);
        EXPECT_THROW(Time(1, 1, 60), std::invalid_argument);
        EXPECT_THROW(Time(1, 1, 1, 1001), std::invalid_argument);
        EXPECT_THROW(Time(1, 1, 1, 1, 1000), std::invalid_argument);
        EXPECT_THROW(Time(1, 1, 1, 1, 1, 1001), std::invalid_argument);
}

TEST(Time, now_sets_timezone)
{
        Time time = Time::now(0, 0, 0, 0, 0, 0, TZ::EST);
        EXPECT_EQ(time.timezone, TZ::EST);
        int old_hour = time.hour;
        time.set_timezone(TZ::CST);
        EXPECT_EQ(time.hour - old_hour, -1);
}

TEST(Time, operator_plusequal_hour_basic)
{
        Time time = Time(1);
        time += Hours(1);
        EXPECT_EQ(time.hour, 2);
}

TEST(Time, operator_plusequal_hour_wraps)
{
        Time time = Time(22);
        time += Hours(4);
        EXPECT_EQ(time.hour, 2);
}

TEST(Time, operator_minusequal_hour_basic)
{
        Time time = Time(3);
        time -= Hours(1);
        EXPECT_EQ(time.hour, 2);
}

TEST(Time, operator_plusequal_minute_basic)
{
        Time time = Time(1, 1);
        time += Minutes(1);
        EXPECT_EQ(time.minute, 2);
}

TEST(Time, operator_plusequal_minute_adds_hour)
{
        Time time = Time(1, 58);
        time += Minutes(4);
        EXPECT_EQ(time.hour, 2);
        EXPECT_EQ(time.minute, 2);
}

TEST(Time, operator_minusequal_minute_basic)
{
        Time time = Time(1, 3);
        time -= Minutes(1);
        EXPECT_EQ(time.minute, 2);
}

TEST(Time, operator_minusequal_minute_subtracts_hour)
{
        Time time = Time(1, 1);
        time -= Minutes(2);
        EXPECT_EQ(time.hour, 0);
        EXPECT_EQ(time.minute, 59);
}

TEST(Time, operator_plusequal_second_basic)
{
        Time time = Time(1, 1, 1);
        time += Seconds(1);
        EXPECT_EQ(time.second, 2);
}

TEST(Time, operator_plusequal_second_adds_minute)
{
        Time time = Time(1, 1, 58);
        time += Seconds(4);
        EXPECT_EQ(time.minute, 2);
        EXPECT_EQ(time.second, 2);
}

TEST(Time, operator_minusequal_second_basic)
{
        Time time = Time(1, 1, 3);
        time -= Seconds(1);
        EXPECT_EQ(time.second, 2);
}

TEST(Time, operator_minusequal_second_subtracts_minute)
{
        Time time = Time(1, 1, 1);
        time -= Seconds(2);
        EXPECT_EQ(time.minute, 0);
        EXPECT_EQ(time.second, 59);
}

TEST(Time, operator_plusequal_millisecond_basic)
{
        Time time = Time(1, 1, 1, 1);
        time += Milliseconds(1);
        EXPECT_EQ(time.millisecond, 2);
}

TEST(Time, operator_plusequal_millisecond_adds_minute)
{
        Time time = Time(1, 1, 1, 999);
        time += Milliseconds(3);
        EXPECT_EQ(time.second, 2);
        EXPECT_EQ(time.millisecond, 2);
}

TEST(Time, operator_minusequal_millisecond_basic)
{
        Time time = Time(1, 1, 1, 3);
        time -= Milliseconds(1);
        EXPECT_EQ(time.millisecond, 2);
}

TEST(Time, operator_minusequal_millisecond_subtracts_second)
{
        Time time = Time(1, 1, 1, 1);
        time -= Milliseconds(2);
        EXPECT_EQ(time.second, 0);
        EXPECT_EQ(time.millisecond, 999);
}

TEST(Time, operator_plusequal_microsecond_basic)
{
        Time time = Time(1, 1, 1, 1, 1);
        time += Microseconds(1);
        EXPECT_EQ(time.microsecond, 2);
}

TEST(Time, operator_plusequal_microsecond_adds_millisecond)
{
        Time time = Time(1, 1, 1, 1, 999);
        time += Microseconds(3);
        EXPECT_EQ(time.millisecond, 2);
        EXPECT_EQ(time.microsecond, 2);
}

TEST(Time, operator_minusequal_microsecond_basic)
{
        Time time = Time(1, 1, 1, 1, 3);
        time -= Microseconds(1);
        EXPECT_EQ(time.microsecond, 2);
}

TEST(Time, operator_minusequal_microsecond_subtracts_millisecond)
{
        Time time = Time(1, 1, 1, 1, 1);
        time -= Microseconds(2);
        EXPECT_EQ(time.millisecond, 0);
        EXPECT_EQ(time.microsecond, 999);
}

TEST(Time, operator_plusequal_nanosecond_basic)
{
        Time time = Time(1, 1, 1, 1, 1, 1);
        time += Nanoseconds(1);
        EXPECT_EQ(time.nanosecond, 2);
}

TEST(Time, operator_plusequal_nanoecond_adds_minute)
{
        Time time = Time(1, 1, 1, 1, 1, 999);
        time += Nanoseconds(3);
        EXPECT_EQ(time.microsecond, 2);
        EXPECT_EQ(time.nanosecond, 2);
}

TEST(Time, operator_minusequal_nanosecond_basic)
{
        Time time = Time(1, 1, 1, 1, 1, 3);
        time -= Nanoseconds(1);
        EXPECT_EQ(time.nanosecond, 2);
}

TEST(Time, operator_minusequal_nanosecond_subtracts_microsecond)
{
        Time time = Time(1, 1, 1, 1, 1, 1);
        time -= Nanoseconds(2);
        EXPECT_EQ(time.microsecond, 0);
        EXPECT_EQ(time.nanosecond, 999);
}

TEST(Time, set_timezone_basic)
{
        Time time = Time(1 ,0 ,0, 0, 0, 0, TZ::CST);
        time.set_timezone(TZ::EST);
        EXPECT_EQ(time.hour, 2);
}

TEST(Time, set_timezone_wraps)
{
        Time time = Time(23 ,0 ,0, 0, 0, 0, TZ::CST);
        time.set_timezone(TZ::EST);
        EXPECT_EQ(time.hour, 0);
}

TEST(Time, set_default_timezone)
{
        Timezone original_default_timezone = Time::default_timezone;
        Time::set_default_timezone(TZ::UTC);
        EXPECT_EQ(Time::default_timezone, TZ::UTC);
        Time::default_timezone = original_default_timezone;
}

TEST(Time, ostream)
{
        Time time = Time(1, 2, 3, 4, 5, 6);
        std::stringstream actual;
        actual << time;
        EXPECT_EQ(actual.str(), "1:02:03.4.5.6");
}

TEST(TimeRange, constructor_sets_variables)
{
        Time start = Time(1);
        Time end = Time(2);
        TimeRange time_range = TimeRange(start, end);
        EXPECT_EQ(time_range.start, start);
        EXPECT_EQ(time_range.end, end);
}

TEST(TimeRange, constructor_start_greater_than_end_throws_illegal_argument)
{
        Time start = Time(1);
        Time end = Time(0);
        EXPECT_THROW(TimeRange(start, end), std::invalid_argument);
}

TEST(TimeRange, in_range)
{
        Time start = Time(1);
        Time end = Time(3);
        TimeRange date_range = TimeRange(start, end);

        Time date = Time(2);
        EXPECT_TRUE(date_range.in_range(date));

        date = Time(1);
        EXPECT_TRUE(date_range.in_range(date));

        date = Time(3);
        EXPECT_TRUE(date_range.in_range(date));

        date = Time();
        EXPECT_FALSE(date_range.in_range(date));

        date = Time(4);
        EXPECT_FALSE(date_range.in_range(date));
}

TEST(Time, operator_greater_than)
{
        Time time_greater = Time(2);
        Time time_lesser = Time(1);
        EXPECT_GT(time_greater, time_lesser);

        time_greater = Time(1, 2);
        time_lesser = Time(1, 1);
        EXPECT_GT(time_greater, time_lesser);

        time_greater = Time(1, 0, 2);
        time_lesser = Time(1, 0, 1);
        EXPECT_GT(time_greater, time_lesser);

        time_greater = Time(1, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 1);
        EXPECT_GT(time_greater, time_lesser);

        time_greater = Time(1, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 1);
        EXPECT_GT(time_greater, time_lesser);

        time_greater = Time(1, 0, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 0, 1);
        EXPECT_GT(time_greater, time_lesser);
}

TEST(Time, operator_greater_than_or_equal_to)
{
        Time time_greater = Time(2);
        Time time_lesser = Time(1);
        EXPECT_GE(time_greater, time_lesser);

        time_greater = Time(1, 2);
        time_lesser = Time(1, 1);
        EXPECT_GE(time_greater, time_lesser);

        time_greater = Time(1, 0, 2);
        time_lesser = Time(1, 0, 1);
        EXPECT_GE(time_greater, time_lesser);

        time_greater = Time(1, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 1);
        EXPECT_GE(time_greater, time_lesser);

        time_greater = Time(1, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 1);
        EXPECT_GE(time_greater, time_lesser);

        time_greater = Time(1, 0, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 0, 1);
        EXPECT_GE(time_greater, time_lesser);

        time_lesser = Time(1, 0, 0, 0, 0, 2);
        EXPECT_GE(time_greater, time_lesser);
}

TEST(Time, operator_less_than)
{
        Time time_greater = Time(2);
        Time time_lesser = Time(1);
        EXPECT_LT(time_lesser, time_greater);

        time_greater = Time(1, 2);
        time_lesser = Time(1, 1);
        EXPECT_LT(time_lesser, time_greater);

        time_greater = Time(1, 0, 2);
        time_lesser = Time(1, 0, 1);
        EXPECT_LT(time_lesser, time_greater);

        time_greater = Time(1, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 1);
        EXPECT_LT(time_lesser, time_greater);

        time_greater = Time(1, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 1);
        EXPECT_LT(time_lesser, time_greater);

        time_greater = Time(1, 0, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 0, 1);
        EXPECT_LT(time_lesser, time_greater);
}

TEST(Time, operator_less_than_or_equal_to)
{
        Time time_greater = Time(2, 0, 0, 0, 0, 0);
        Time time_lesser = Time(1, 0, 0, 0, 0, 0);
        EXPECT_LE(time_lesser, time_greater);

        time_greater = Time(1, 2);
        time_lesser = Time(1, 1);
        EXPECT_LE(time_lesser, time_greater);

        time_greater = Time(1, 0, 2);
        time_lesser = Time(1, 0, 1);
        EXPECT_LE(time_lesser, time_greater);

        time_greater = Time(1, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 1);
        EXPECT_LE(time_lesser, time_greater);

        time_greater = Time(1, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 1);
        EXPECT_LE(time_lesser, time_greater);

        time_greater = Time(1, 0, 0, 0, 0, 2);
        time_lesser = Time(1, 0, 0, 0, 0, 1);
        EXPECT_LE(time_lesser, time_greater);

        time_lesser = Time(1, 0, 0, 0, 0, 2);
        EXPECT_LE(time_lesser, time_greater);
}

TEST(Time, operator_equal_to)
{
        Time time1 = Time();
        Time time2 = Time();
        EXPECT_EQ(time1, time2);

        time2 = Time(1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 0, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 0, 0, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 0, 0, 0, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 0, 0, 0, 0, 1);
        EXPECT_NE(time1, time2);
}

TEST(Time, operator_not_equal_to)
{
        Time time1 = Time();
        Time time2 = Time(1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 2, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 0, 0, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 0, 0, 0, 1);
        EXPECT_NE(time1, time2);

        time2 = Time(1, 0, 0, 0, 0, 1);
        EXPECT_NE(time1, time2);

        time2 = Time();
        EXPECT_EQ(time1, time2);
}

TEST(Timezone, get_from_str)
{
        EXPECT_EQ(TZ::helpers::get_from_str("Coordinated Universal Time"), TZ::UTC);
        EXPECT_EQ(TZ::helpers::get_from_str("Pacific Standard Time"), TZ::PST);
        EXPECT_EQ(TZ::helpers::get_from_str("Central Standard Time"), TZ::CST);
        EXPECT_EQ(TZ::helpers::get_from_str("Central Daylight Time"), TZ::CDT);
        EXPECT_EQ(TZ::helpers::get_from_str("Eastern Standard Time"), TZ::EST);
        EXPECT_EQ(TZ::helpers::get_from_str("Eastern Daylight Time"), TZ::EDT);
        EXPECT_EQ(TZ::helpers::get_from_str("Pacific Daylight Time"), TZ::PDT);
}

TEST(Timezone, get_from_str_throws_if_not_timezone_str)
{
        EXPECT_THROW(TZ::helpers::get_from_str("Invalid timezone str"), std::invalid_argument);
}


TEST(Time, round_up)
{
        Time time = Time(11, 29, 30, 1, 1, 1);
        time.round(Time::Component::HOUR);
        EXPECT_EQ(time, Time(12, 0, 0, 0, 0, 0));

        time = Time(1, 29, 29, 500, 1, 1);
        time.round(Time::Component::MINUTE);
        EXPECT_EQ(time, Time(1, 30, 0, 0, 0, 0));

        time = Time(1, 0, 29, 499, 500, 1);
        time.round(Time::Component::SECOND);
        EXPECT_EQ(time, Time(1, 0, 30, 0, 0, 0));

        time = Time(1, 0, 0, 499, 499, 500);
        time.round(Time::Component::MILLISECOND);
        EXPECT_EQ(time, Time(1, 0, 0, 500, 0, 0));

        time = Time(1, 0, 0, 0, 499, 500);
        time.round(Time::Component::MICROSECOND);
        EXPECT_EQ(time, Time(1, 0, 0, 0, 500, 0));
}

TEST(Time, round_down)
{
        Time time = Time(11, 29, 1, 1, 1, 1);
        time.round(Time::Component::HOUR);
        EXPECT_EQ(time, Time(11, 0, 0, 0, 0, 0));

        time = Time(1, 29, 29, 1, 1, 1);
        time.round(Time::Component::MINUTE);
        EXPECT_EQ(time, Time(1, 29, 0, 0, 0, 0));

        time = Time(1, 1, 29, 499, 1, 1);
        time.round(Time::Component::SECOND);
        EXPECT_EQ(time, Time(1, 1, 29, 0, 0, 0));

        time = Time(1, 1, 1, 499, 499, 1);
        time.round(Time::Component::MILLISECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 499, 0, 0));

        time = Time(1, 1, 1, 1, 499, 499);
        time.round(Time::Component::MICROSECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 1, 499, 0));

        time = Time(1, 1, 1, 1, 1, 499);
        time.round(Time::Component::NANOSECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 1, 1, 499));
}

TEST(Time, ceil_up)
{
        Time time = Time(11, 1, 0, 0, 0, 0);
        time.ceil(Time::Component::HOUR);
        EXPECT_EQ(time, Time(12, 0, 0, 0, 0, 0));

        time = Time(1, 29, 29, 1, 1, 1);
        time.ceil(Time::Component::MINUTE);
        EXPECT_EQ(time, Time(1, 30, 0, 0, 0, 0));

        time = Time(1, 1, 29, 1, 1, 1);
        time.ceil(Time::Component::SECOND);
        EXPECT_EQ(time, Time(1, 1, 30, 0, 0, 0));

        time = Time(1, 1, 1, 499, 1, 1);
        time.ceil(Time::Component::MILLISECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 500, 0, 0));

        time = Time(1, 1, 1, 1, 499, 1);
        time.ceil(Time::Component::MICROSECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 1, 500, 0));

        time = Time(1, 1, 1, 1, 1, 499);
        time.ceil(Time::Component::NANOSECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 1, 1, 499));
}

TEST(Time, ceil_no_up)
{
        Time time = Time(1);
        time.ceil(Time::Component::HOUR);
        EXPECT_EQ(time, Time(1));

        time = Time(1, 1);
        time.ceil(Time::Component::MINUTE);
        EXPECT_EQ(time, Time(1, 1));

        time = Time(1, 0, 1);
        time.ceil(Time::Component::SECOND);
        EXPECT_EQ(time, Time(1, 0, 1));

        time = Time(1, 0, 0, 1);
        time.ceil(Time::Component::MILLISECOND);
        EXPECT_EQ(time, Time(1, 0, 0, 1));

        time = Time(1, 0, 0, 0, 1);
        time.ceil(Time::Component::MICROSECOND);
        EXPECT_EQ(time, Time(1, 0, 0, 0, 1));

        time = Time(1, 1, 1, 1, 1, 499);
        time.ceil(Time::Component::NANOSECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 1, 1, 499));
}

TEST(Time, floor)
{
        Time time = Time(1, 59);
        time.floor(Time::Component::HOUR);
        EXPECT_EQ(time, Time(1));

        time = Time(1, 1, 59);
        time.floor(Time::Component::MINUTE);
        EXPECT_EQ(time, Time(1, 1));

        time = Time(1, 0, 1, 999);
        time.floor(Time::Component::SECOND);
        EXPECT_EQ(time, Time(1, 0, 1));

        time = Time(1, 0, 0, 1, 999);
        time.floor(Time::Component::MILLISECOND);
        EXPECT_EQ(time, Time(1, 0, 0, 1));

        time = Time(1, 0, 0, 0, 1, 999);
        time.floor(Time::Component::MICROSECOND);
        EXPECT_EQ(time, Time(1, 0, 0, 0, 1  ));

        time = Time(1, 1, 1, 1, 1, 499);
        time.floor(Time::Component::NANOSECOND);
        EXPECT_EQ(time, Time(1, 1, 1, 1, 1, 499));
}

TEST(Time, to_string)
{
    Time time = Time(1, 2, 30, 4, 5, 6);
    EXPECT_EQ(time.to_string(), "1:02:30.4.5.6");
}

TEST(Time, string_TimeComponents_basic)
{
    Time time = Time("1:02:30.4.5.6",
                     Time::Component::HOUR, Time::Component::MINUTE, Time::Component::SECOND,
                     Time::Component::MILLISECOND, Time::Component::MICROSECOND,
                     Time::Component::NANOSECOND);
    EXPECT_EQ(time.hour, 1);
    EXPECT_EQ(time.minute, 2);
    EXPECT_EQ(time.second, 30);
    EXPECT_EQ(time.millisecond, 4);
    EXPECT_EQ(time.microsecond, 5);
    EXPECT_EQ(time.nanosecond, 6);
}

TEST(Time, string_TimeComponents_skip)
{
    Time time = Time("1.2", Time::Component::HOUR, Time::Component::NANOSECOND);
    EXPECT_EQ(time.hour, 1);
    EXPECT_EQ(time.nanosecond, 2);
}

TEST(Time, constructor_int_int_int_int_int_int_throws_invalid_argument)
{
    EXPECT_THROW(Time(100), std::invalid_argument);
}

TEST(Time, constructor_string_TimeComponents_throws_invalid_argument_on_wrong_time_components)
{
    EXPECT_THROW(Time("1:2:3", Time::Component::HOUR, Time::Component::MINUTE),
                 std::invalid_argument);
}

TEST(Time, constructor_string_TimeComponents_throws_invalid_argument_on_out_of_range_components)
{
    EXPECT_THROW(Time("25", Time::Component::HOUR), std::invalid_argument);
}

TEST(Time, operator_plus_time)
{
    TimeDelta time_delta = Time(1, 2, 3, 4, 5, 6) + Time(2, 3, 4, 5, 6, 7);
    EXPECT_EQ(time_delta, TimeDelta(0, 3, 5, 7, 9, 11, 13));
}

TEST(Time, operator_plus_time_day_wrap)
{
    TimeDelta time_delta = Time(23) + Time(1);
    EXPECT_EQ(time_delta, TimeDelta(1));
}

TEST(Time, operator_minus_time)
{
    TimeDelta time_delta = Time(3, 5, 7, 9, 11, 13) - Time(2, 3, 4, 5, 6, 7);
    EXPECT_EQ(time_delta, TimeDelta(0, 1, 2, 3, 4, 5, 6));
}

TEST(Time, operator_minus_time_day_wrap)
{
    TimeDelta time_delta = Time() - Time(1);
    EXPECT_EQ(time_delta, TimeDelta(-1, 23));
}

TEST(Time, operator_plus_hour)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time + Hours(1);
    EXPECT_EQ(new_time, Time(2, 2, 3, 4, 5, 6));
}

TEST(Time, operator_plus_minute)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time + Minutes(1);
    EXPECT_EQ(new_time, Time(1, 3, 3, 4, 5, 6));
}

TEST(Time, operator_plus_second)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time + Seconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 4, 4, 5, 6));
}

TEST(Time, operator_plus_millisecond)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time + Milliseconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 3, 5, 5, 6));
}

TEST(Time, operator_plus_microsecond)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time + Microseconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 3, 4, 6, 6));
}

TEST(Time, operator_plus_nanosecond)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time + Nanoseconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 3, 4, 5, 7));
}

TEST(Time, operator_minus_hour)
{
    Time time = Time(2, 2, 3, 4, 5, 6);
    Time new_time = time - Hours(1);
    EXPECT_EQ(new_time, Time(1, 2, 3, 4, 5, 6));
}

TEST(Time, operator_minus_minute)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time - Minutes(1);
    EXPECT_EQ(new_time, Time(1, 1, 3, 4, 5, 6));
}

TEST(Time, operator_minus_second)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time - Seconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 2, 4, 5, 6));
}

TEST(Time, operator_minus_millisecond)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time - Milliseconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 3, 3, 5, 6));
}

TEST(Time, operator_minus_microsecond)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time - Microseconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 3, 4, 4, 6));
}

TEST(Time, operator_minus_nanosecond)
{
    Time time = Time(1, 2, 3, 4, 5, 6);
    Time new_time = time - Nanoseconds(1);
    EXPECT_EQ(new_time, Time(1, 2, 3, 4, 5, 5));
}