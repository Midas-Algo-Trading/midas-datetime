#include "gtest/gtest.h"

#include <datetime/datetime/Datetime.h>
#include "datetime/datetime/DatetimeRange.h"
#include "datetime/timedelta/TimeDelta.h"


TEST(Datetime, constructor_date_sets_members)
{
        Datetime datetime = Datetime(Date(2000, 2, 3));
        EXPECT_EQ(datetime.year, 2000);
        EXPECT_EQ(datetime.month, 2);
        EXPECT_EQ(datetime.day, 3);

        Time default_time = Time();
        EXPECT_EQ(datetime.hour, default_time.hour);
        EXPECT_EQ(datetime.minute, default_time.minute);
        EXPECT_EQ(datetime.second, default_time.second);
        EXPECT_EQ(datetime.millisecond, default_time.millisecond);
        EXPECT_EQ(datetime.microsecond, default_time.microsecond);
        EXPECT_EQ(datetime.nanosecond, default_time.nanosecond);
}

TEST(Datetime, constructor_date_time_sets_members)
{
        Date date = Date(2000, 2, 3);
        Time time = Time(1, 2, 3, 4, 5, 6);
        Datetime datetime = Datetime(date, time);

        EXPECT_EQ(datetime.year, 2000);
        EXPECT_EQ(datetime.month, 2);
        EXPECT_EQ(datetime.day, 3);

        EXPECT_EQ(datetime.hour, 1);
        EXPECT_EQ(datetime.minute, 2);
        EXPECT_EQ(datetime.second, 3);
        EXPECT_EQ(datetime.millisecond, 4);
        EXPECT_EQ(datetime.microsecond, 5);
        EXPECT_EQ(datetime.nanosecond, 6);
}

TEST(Datetime, contructor_int_int_int_int_int_int_int_int_int_sets_members)
{
        Datetime datetime = Datetime(2000, 2, 3, 4, 5, 6, 7, 8, 9);
        EXPECT_EQ(datetime.year, 2000);
        EXPECT_EQ(datetime.month, 2);
        EXPECT_EQ(datetime.day, 3);
        EXPECT_EQ(datetime.hour, 4);
        EXPECT_EQ(datetime.minute, 5);
        EXPECT_EQ(datetime.second, 6);
        EXPECT_EQ(datetime.millisecond, 7);
        EXPECT_EQ(datetime.microsecond, 8);
        EXPECT_EQ(datetime.nanosecond, 9);
}

TEST(Datetime, date)
{
        Datetime datetime = Datetime(1970, 2, 3);
        Date date = datetime.date();
        EXPECT_EQ(date.year, 1970);
        EXPECT_EQ(date.month, 2);
        EXPECT_EQ(date.day, 3);
}

TEST(Datetime, time)
{
        Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
        Time time = datetime.time();
        EXPECT_EQ(time.hour, 1);
        EXPECT_EQ(time.minute, 2);
        EXPECT_EQ(time.second, 3);
        EXPECT_EQ(time.millisecond, 4);
        EXPECT_EQ(time.microsecond, 5);
        EXPECT_EQ(time.nanosecond, 6);
}

TEST(Datetime, operator_greater_than)
{
       Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
       Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
       EXPECT_GT(datetime_greater, datetime_lesser);
}

TEST(Datetime, operator_greater_than_timezone)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_GT(datetime_greater, datetime_lesser);
}

TEST(Datetime, operator_greater_than_timezone_day_wrap)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_GT(datetime_greater, datetime_lesser);
}

TEST(Datetime, operator_greater_than_or_equal_to)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_GE(datetime_greater, datetime_lesser);

        Datetime datetime_equal = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_GE(datetime_greater, datetime_equal);
}

TEST(Datetime, operator_greater_than_or_equal_to_timezone)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_GE(datetime_greater, datetime_lesser);

    Datetime datetime_equal = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_GE(datetime_greater, datetime_equal);
}

TEST(Datetime, operator_greater_than_or_equal_to_timezone_day_wrap)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_GT(datetime_greater, datetime_lesser);

    Datetime datetime_equal = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_GE(datetime_greater, datetime_equal);
}

TEST(Datetime, operator_less_than)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_LT(datetime_lesser, datetime_greater);
}

TEST(Datetime, operator_less_than_timezone)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_LT(datetime_lesser, datetime_greater);
}

TEST(Datetime, operator_less_than_timezone_day_wrap)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_LT(datetime_lesser, datetime_greater);
}

TEST(Datetime, operator_less_than_or_equal_to)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_LE(datetime_lesser, datetime_greater);

        Datetime datetime_equal = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_LE(datetime_lesser, datetime_equal);
}

TEST(Datetime, operator_less_than_or_equal_to_timezone)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_LE(datetime_lesser, datetime_greater);

    Datetime datetime_equal = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_LE(datetime_greater, datetime_equal);
}

TEST(Datetime, operator_less_than_or_equal_to_timezone_day_wrap)
{
    Datetime datetime_lesser = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime_greater = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_LE(datetime_lesser, datetime_greater);

    Datetime datetime_equal = Datetime(2000, 1, 1, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_LE(datetime_greater, datetime_equal);
}

TEST(Datetime, operator_equal_to)
{
        Datetime datetime1 = Datetime();
        Datetime datetime2 = Datetime();
        EXPECT_EQ(datetime1, datetime2);
}

TEST(Datetime, operator_equal_to_timezone)
{
    Datetime datetime1 = Datetime(2000, 1, 2, 3, 0, 0, 0, 0, 0, TZ::EST);
    Datetime datetime2 = Datetime(2000, 1, 2, 8, 0, 0, 0, 0, 0, TZ::UTC);
    EXPECT_EQ(datetime1, datetime2);
}

TEST(Datetime, operator_equal_to_timezone_day_wrap)
{
    Datetime datetime1 = Datetime(2000, 1, 3, 1, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime2 = Datetime(2000, 1, 2, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_EQ(datetime1, datetime2);
}

TEST(Datetime, operator_not_equal_to)
{
        Datetime datetime1 = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime2 = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_NE(datetime1, datetime2);
}

TEST(Datetime, operator_not_equal_to_timezone)
{
    Datetime datetime1 = Datetime(2000, 1, 2, 3, 0, 0, 0, 0, 0, TZ::EST);
    Datetime datetime2 = Datetime(2000, 1, 2, 3, 0, 0, 0, 0, 0, TZ::UTC);
    EXPECT_NE(datetime1, datetime2);
}

TEST(Datetime, operator_not_equal_to_timezone_day_wrap)
{
    Datetime datetime1 = Datetime(2000, 1, 2, 20, 0, 0, 0, 0, 0, TZ::UTC);
    Datetime datetime2 = Datetime(2000, 1, 2, 20, 0, 0, 0, 0, 0, TZ::EST);
    EXPECT_NE(datetime1, datetime2);
}

TEST(DatetimeRange, constructor_sets_variables)
{
        Datetime start = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 1);
        Datetime end = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 2);
        DatetimeRange datetime_range = DatetimeRange(start, end);
        EXPECT_EQ(datetime_range.start, start);
        EXPECT_EQ(datetime_range.end, end);
}

TEST(DatetimeRange, constructor_start_greater_than_end_throws_illegal_argument)
{
        Datetime start = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 0);
        Datetime end = Datetime(1999, 1, 1, 0, 0, 0, 0, 0, 0);
        EXPECT_THROW(DatetimeRange(start, end), std::invalid_argument);
}

TEST(DatetimeRange, in_range)
{
        Datetime start = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0);
        Datetime end = Datetime(2000, 1, 1, 3, 0, 0, 0, 0, 0);
        DatetimeRange datetime_range = DatetimeRange(start, end);

        Datetime datetime = Datetime(2000, 1, 1, 2, 0, 0, 0, 0, 0);
        EXPECT_TRUE(datetime_range.in_range(datetime));

        datetime = Datetime(2000, 1, 1, 1, 0, 0, 0, 0, 0);
        EXPECT_TRUE(datetime_range.in_range(datetime));

        datetime = Datetime(2000, 1, 1, 3, 0, 0, 0, 0, 0);
        EXPECT_TRUE(datetime_range.in_range(datetime));

        datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 0);
        EXPECT_FALSE(datetime_range.in_range(datetime));

        datetime = Datetime(2000, 1, 1, 4, 0, 0, 0, 0, 0);
        EXPECT_FALSE(datetime_range.in_range(datetime));
}

TEST(Datetime, operator_plusequal_adds_day_basic)
{
        Datetime datetime = Datetime(1970, 1, 1);
        datetime += Days(1);
        int new_day = datetime.day;
        EXPECT_EQ(new_day, 2);
}

TEST(Datetime, operator_plusequal_adds_day_new_month)
{
        Datetime datetime = Datetime(1970, 1, 31);
        datetime += Days(1);
        EXPECT_EQ(datetime.month, 2);
        EXPECT_EQ(datetime.day, 1);
}

TEST(Datetime, operator_minusequal_subtracts_day_basic)
{
        Datetime datetime = Datetime(1970, 1, 2);
        datetime -= Days(1);
        EXPECT_EQ(datetime.day, 1);
}

TEST(Datetime, operator_minusequal_subtracts_month)
{
        Datetime datetime = Datetime(1970, 2, 1);
        datetime -= Days(1);
        EXPECT_EQ(datetime.month, 1);
        EXPECT_EQ(datetime.day, 31);
}

TEST(Datetime, operator_plusequal_hour_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 1);
        datetime += Hours(1);
        EXPECT_EQ(datetime.hour, 2);
}

TEST(Datetime, operator_plusequal_hour_adds_day)
{
        Datetime datetime = Datetime(2000, 1, 2, 22);
        datetime += Hours(4);
        EXPECT_EQ(datetime.day, 3);
        EXPECT_EQ(datetime.hour, 2);
}

TEST(Datetime, operator_minusequal_hour_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 3);
        datetime -= Hours(1);
        EXPECT_EQ(datetime.hour, 2);
}

TEST(Datetime, operator_minusequal_hour_subtracts_day)
{
        Datetime datetime = Datetime(2000, 1, 1, 0);
        datetime -= Hours(1);
        EXPECT_EQ(datetime.year, 1999);
        EXPECT_EQ(datetime.month, 12);
        EXPECT_EQ(datetime.day, 31);
        EXPECT_EQ(datetime.hour, 23);
}

TEST(Datetime, operator_plusequal_minute_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 1);
        datetime += Minutes(1);
        EXPECT_EQ(datetime.minute, 2);
}

TEST(Datetime, operator_plusequal_minute_adds_hour)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 58);
        datetime += Minutes(4);
        EXPECT_EQ(datetime.hour, 1);
        EXPECT_EQ(datetime.minute, 2);
}

TEST(Datetime, operator_minusequal_minute_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 3);
        datetime -= Minutes(1);
        EXPECT_EQ(datetime.minute, 2);
}

TEST(Datetime, operator_minusequal_minute_subtracts_hour)
{
        Datetime datetime = Datetime(2000, 1, 1, 1, 1);
        datetime -= Minutes(2);
        EXPECT_EQ(datetime.hour, 0);
        EXPECT_EQ(datetime.minute, 59);
}

TEST(Datetime, operator_plusequal_second_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 1);
        datetime += Seconds(1);
        EXPECT_EQ(datetime.second, 2);
}

TEST(Datetime, operator_plusequal_second_adds_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 58);
        datetime += Seconds(4);
        EXPECT_EQ(datetime.minute, 1);
        EXPECT_EQ(datetime.second, 2);
}

TEST(Datetime, operator_minusequal_second_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 3);
        datetime -= Seconds(1);
        EXPECT_EQ(datetime.second, 2);
}

TEST(Datetime, operator_minusequal_second_subtracts_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 1, 1);
        datetime -= Seconds(2);
        EXPECT_EQ(datetime.minute, 0);
        EXPECT_EQ(datetime.second, 59);
}

TEST(Datetime, operator_plusequal_millisecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 1);
        datetime += Milliseconds(1);
        EXPECT_EQ(datetime.millisecond, 2);
}

TEST(Datetime, operator_plusequal_millisecond_adds_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 999);
        datetime += Milliseconds(3);
        EXPECT_EQ(datetime.second, 1);
        EXPECT_EQ(datetime.millisecond, 2);
}

TEST(Datetime, operator_minusequal_millisecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 3);
        datetime -= Milliseconds(1);
        EXPECT_EQ(datetime.millisecond, 2);
}

TEST(Datetime, operator_minusequal_millisecond_subtracts_second)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 1, 1);
        datetime -= Milliseconds(2);
        EXPECT_EQ(datetime.second, 0);
        EXPECT_EQ(datetime.millisecond, 999);
}

TEST(Datetime, operator_plusequal_microsecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 1);
        datetime += Microseconds(1);
        EXPECT_EQ(datetime.microsecond, 2);
}

TEST(Datetime, operator_plusequal_microsecond_adds_millisecond)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 999);
        datetime += Microseconds(3);
        EXPECT_EQ(datetime.millisecond, 1);
        EXPECT_EQ(datetime.microsecond, 2);
}

TEST(Datetime, operator_minusequal_microsecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 3);
        datetime -= Microseconds(1);
        EXPECT_EQ(datetime.microsecond, 2);
}

TEST(Datetime, operator_minusequal_microsecond_subtracts_millisecond)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 1, 1);
        datetime -= Microseconds(2);
        EXPECT_EQ(datetime.millisecond, 0);
        EXPECT_EQ(datetime.microsecond, 999);
}

TEST(Datetime, operator_plusequal_nanosecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 1);
        datetime += Nanoseconds(1);
        EXPECT_EQ(datetime.nanosecond, 2);
}

TEST(Datetime, operator_plusequal_nanoecond_adds_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 999);
        datetime += Nanoseconds(3);
        EXPECT_EQ(datetime.microsecond, 1);
        EXPECT_EQ(datetime.nanosecond, 2);
}

TEST(Datetime, operator_minusequal_nanosecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 3);
        datetime -= Nanoseconds(1);
        EXPECT_EQ(datetime.nanosecond, 2);
}

TEST(Datetime, operator_minusequal_nanosecond_subtracts_microsecond)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 1, 1);
        datetime -= Nanoseconds(2);
        EXPECT_EQ(datetime.microsecond, 0);
        EXPECT_EQ(datetime.nanosecond, 999);
}

TEST(Datetime, operator_incremenet)
{
        Datetime datetime = Datetime(2000, 1, 1);
        ++datetime;
        EXPECT_EQ(datetime.day, 2);
}

TEST(Datetime, operator_decrement)
{
        Datetime datetime = Datetime(2000, 1, 2);
        --datetime;
        EXPECT_EQ(datetime.day, 1);
}

TEST(Datetime, constructor_string_DateComponent1_DateComponent2_DateComponent3_TimeComponents_basic)
{
    Datetime datetime = Datetime("2000-01-02 3:04:50.6.7.8",
                                 Date::Component::YEAR,
                                 Date::Component::MONTH,
                                 Date::Component::DAY,
                                 Time::Component::HOUR,
                                 Time::Component::MINUTE,
                                 Time::Component::SECOND,
                                 Time::Component::MILLISECOND,
                                 Time::Component::MICROSECOND,
                                 Time::Component::NANOSECOND);
    EXPECT_EQ(datetime.year, 2000);
    EXPECT_EQ(datetime.month, 1);
    EXPECT_EQ(datetime.day, 2);
    EXPECT_EQ(datetime.hour, 3);
    EXPECT_EQ(datetime.minute, 4);
    EXPECT_EQ(datetime.second, 50);
    EXPECT_EQ(datetime.millisecond, 6);
    EXPECT_EQ(datetime.microsecond, 7);
    EXPECT_EQ(datetime.nanosecond, 8);
}

TEST(Datetime, constructor_string_DateComponent1_DateComponent2_DateComponent3_TimeComponents_skip)
{
    Datetime datetime = Datetime("2000-01-02 3.4",
                                 Date::Component::YEAR,
                                 Date::Component::MONTH,
                                 Date::Component::DAY,
                                 Time::Component::HOUR,
                                 Time::Component::NANOSECOND);
    EXPECT_EQ(datetime.year, 2000);
    EXPECT_EQ(datetime.month, 1);
    EXPECT_EQ(datetime.day, 2);
    EXPECT_EQ(datetime.hour, 3);
    EXPECT_EQ(datetime.nanosecond, 4);
}

TEST(Datetime, to_string)
{
    Datetime datetime = Datetime(2000, 1, 2, 3, 4, 50, 6, 7, 8);
    EXPECT_EQ(datetime.to_string(), "2000-01-02 3:04:50.6.7.8");
}

TEST(Datetime, ostream)
{
        Datetime datetime = Datetime(2000, 1, 2, 3, 4, 5, 6, 7, 8);
        std::stringstream actual;
        actual << datetime;
        EXPECT_EQ(actual.str(), "2000-01-02 3:04:05.6.7.8");
}

TEST(Datetime, from_ms_basic)
{
    Datetime datetime = Datetime::from_ms(946803845000, TZ::UTC);
    EXPECT_EQ(datetime.year, 2000);
    EXPECT_EQ(datetime.month, 1);
    EXPECT_EQ(datetime.day, 2);
    EXPECT_EQ(datetime.hour, 9);
    EXPECT_EQ(datetime.minute, 4);
    EXPECT_EQ(datetime.second, 5);
    EXPECT_EQ(datetime.millisecond, 0);
    EXPECT_EQ(datetime.microsecond, 0);
    EXPECT_EQ(datetime.nanosecond, 0);
}

TEST(Datetime, from_ms_complex)
{
    Datetime datetime = Datetime::from_ms(946803845999, TZ::EST);
    EXPECT_EQ(datetime.year, 2000);
    EXPECT_EQ(datetime.month, 1);
    EXPECT_EQ(datetime.day, 2);
    EXPECT_EQ(datetime.hour, 4);
    EXPECT_EQ(datetime.minute, 4);
    EXPECT_EQ(datetime.second, 5);
    EXPECT_EQ(datetime.millisecond, 999);
    EXPECT_EQ(datetime.microsecond, 0);
    EXPECT_EQ(datetime.nanosecond, 0);
}

TEST(Datetime, operator_plus_time)
{
    Datetime datetime = Datetime(2000, 1, 2, 3, 4, 5, 6, 7, 8) + Time(1, 2, 3, 4, 5, 6);
    EXPECT_EQ(datetime, Datetime(2000, 1, 2, 4, 6, 8, 10, 12, 14));
}

TEST(Datetime, operator_plus_time_day_wrap)
{
    Datetime datetime = Datetime(2000, 1, 2, 3) + Time(23);
    EXPECT_EQ(datetime, Datetime(2000, 1, 3, 2));
}

TEST(Datetime, operator_minus_time)
{
    Datetime datetime = Datetime(2000, 1, 2, 3, 4, 5, 6, 7, 8) - Time(1, 2, 3, 4, 5, 6);
    EXPECT_EQ(datetime, Datetime(2000, 1, 2, 2, 2, 2, 2, 2, 2));
}

TEST(Datetime, operator_minus_time_day_wrap)
{
    Datetime datetime = Datetime(2000, 1, 2, 3) - Time(4);
    EXPECT_EQ(datetime, Datetime(2000, 1, 1, 23));
}

TEST(Datetime, operator_plus_equal_time)
{
    Datetime datetime = Datetime(2000, 1, 2, 3, 4, 5, 6, 7, 8);
    datetime += Time(1, 2, 3, 4, 5, 6);
    EXPECT_EQ(datetime, Datetime(2000, 1, 2, 4, 6, 8, 10, 12, 14));
}

TEST(Datetime, operator_plus_equal_time_day_wrap)
{
    Datetime datetime = Datetime(2000, 1, 2, 3);
    datetime += Time(23);
    EXPECT_EQ(datetime, Datetime(2000, 1, 3, 2));
}

TEST(Datetime, operator_minus_equal_time)
{
    Datetime datetime = Datetime(2000, 1, 2, 3, 4, 5, 6, 7, 8);
    datetime -= Time(1, 2, 3, 4, 5, 6);
    EXPECT_EQ(datetime, Datetime(2000, 1, 2, 2, 2, 2, 2, 2, 2));
}

TEST(Datetime, operator_minus_equal_time_day_wrap)
{
    Datetime datetime = Datetime(2000, 1, 2, 3);
    datetime -= Time(4);
    EXPECT_EQ(datetime, Datetime(2000, 1, 1, 23));
}

TEST(Datetime, operator_plus_hour)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime + Hours(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 2, 2, 3, 4, 5, 6));
}

TEST(Datetime, operator_plus_minute)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime + Minutes(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 3, 3, 4, 5, 6));
}

TEST(Datetime, operator_plus_second)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime + Seconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 4, 4, 5, 6));
}

TEST(Datetime, operator_plus_millisecond)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime + Milliseconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 3, 5, 5, 6));
}

TEST(Datetime, operator_plus_microsecond)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime + Microseconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 3, 4, 6, 6));
}

TEST(Datetime, operator_plus_nanosecond)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime + Nanoseconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 7));
}

TEST(Datetime, operator_minus_hour)
{
    Datetime datetime = Datetime(2000, 1, 1, 2, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime - Hours(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6));
}

TEST(Datetime, operator_minus_minute)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime - Minutes(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 1, 3, 4, 5, 6));
}

TEST(Datetime, operator_minus_second)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime - Seconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 2, 4, 5, 6));
}

TEST(Datetime, operator_minus_millisecond)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime - Milliseconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 3, 3, 5, 6));
}

TEST(Datetime, operator_minus_microsecond)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime - Microseconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 3, 4, 4, 6));
}

TEST(Datetime, operator_minus_nanosecond)
{
    Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
    Datetime new_datetime = datetime - Nanoseconds(1);
    EXPECT_EQ(new_datetime, Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 5));
}

TEST(Datetime, to_ms_1)
{
    Datetime datetime = Datetime(2000, 1, 2, 3, 4, 5, 6, 0, 0);
    EXPECT_EQ(datetime.to_ms(), 946782245006);
}

TEST(Datetime, to_ms_2)
{
    Datetime datetime = Datetime("2023-10-30 3:25:09.0.0.0",
                                Date::Component::YEAR,
                                Date::Component::MONTH,
                                Date::Component::DAY,
                                Time::Component::HOUR,
                                Time::Component::MINUTE,
                                Time::Component::SECOND,
                                Time::Component::MILLISECOND,
                                Time::Component::MICROSECOND,
                                Time::Component::NANOSECOND);
    EXPECT_EQ(datetime.to_ms({}), 1698636309000);
}

TEST(Datetime, to_ms_3)
{
    Datetime datetime = Datetime("2023-10-30 3:25:09.0.0.0",
                                 Date::Component::YEAR,
                                 Date::Component::MONTH,
                                 Date::Component::DAY,
                                 Time::Component::HOUR,
                                 Time::Component::MINUTE,
                                 Time::Component::SECOND,
                                 Time::Component::MILLISECOND,
                                 Time::Component::MICROSECOND,
                                 Time::Component::NANOSECOND);
    EXPECT_EQ(datetime.to_ms(), 1698636309000);
}

TEST(Datetime, to_ms_timezone)
{
    Datetime datetime = Datetime(2000, 1, 1, 6, 0, 0, 0, 0, 0, TZ::UTC);
    EXPECT_EQ(datetime.to_ms(TZ::CST), 946684800000);
}

TEST(Datetime, operator_plus_datetime_time_delta_pos_day)
{
    Datetime datetime = Datetime(2000, 1, 1) + TimeDelta(1);
    EXPECT_EQ(datetime, Datetime(2000, 1, 2));
}

TEST(Datetime, operator_plus_datetime_time_delta_0_day)
{
        Datetime datetime = Datetime(2000, 1, 1) + TimeDelta(0);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}

TEST(Datetime, operator_plus_datetime_time_delta_neg_day)
{
        Datetime datetime = Datetime(2000, 1, 2) + TimeDelta(-1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}


TEST(Datetime, operator_plus_datetime_time_delta_with_time)
{
        Datetime datetime = Datetime(2000, 1, 1) + TimeDelta(1, 1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 2, 1));
}

TEST(Datetime, operator_minus_datetime_time_delta_pos_day)
{
        Datetime datetime = Datetime(2000, 1, 2) - TimeDelta(1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}

TEST(Datetime, operator_minus_datetime_time_delta_0_day)
{
        Datetime datetime = Datetime(2000, 1, 1) - TimeDelta(0);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}

TEST(Datetime, operator_minus_datetime_time_delta_neg_day)
{
        Datetime datetime = Datetime(2000, 1, 1) - TimeDelta(-1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 2));
}


TEST(Datetime, operator_minus_datetime_time_delta_with_time)
{
        Datetime datetime = Datetime(2000, 1, 2, 2) - TimeDelta(1, 1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1, 1));
}

TEST(Datetime, operator_plusequal_datetime_time_delta_pos_day)
{
        Datetime datetime = Datetime(2000, 1, 1) += TimeDelta(1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 2));
}

TEST(Datetime, operator_plusequal_datetime_time_delta_0_day)
{
        Datetime datetime = Datetime(2000, 1, 1) += TimeDelta(0);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}

TEST(Datetime, operator_plusequal_datetime_time_delta_neg_day)
{
        Datetime datetime = Datetime(2000, 1, 2) += TimeDelta(-1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}


TEST(Datetime, operator_plusequal_datetime_time_delta_with_time)
{
        Datetime datetime = Datetime(2000, 1, 1) += TimeDelta(1, 1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 2, 1));
}

TEST(Datetime, operator_minusequal_datetime_time_delta_pos_day)
{
        Datetime datetime = Datetime(2000, 1, 2) -= TimeDelta(1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}

TEST(Datetime, operator_minusequal_datetime_time_delta_0_day)
{
        Datetime datetime = Datetime(2000, 1, 1) -= TimeDelta(0);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}

TEST(Datetime, operator_minusequal_datetime_time_delta_neg_day)
{
        Datetime datetime = Datetime(2000, 1, 1) -= TimeDelta(-1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 2));
}


TEST(Datetime, operator_minusequal_datetime_time_delta_with_time)
{
        Datetime datetime = Datetime(2000, 1, 2, 1) -= TimeDelta(1, 1);
        EXPECT_EQ(datetime, Datetime(2000, 1, 1));
}

TEST(Datetime, operator_minus_datetime_datetime)
{
    TimeDelta time_delta = Datetime(2000, 1, 2) - Datetime(2000, 1, 1);
    EXPECT_EQ(time_delta, TimeDelta(1));
}

TEST(Datetime, operator_minus_datetime_datetime_month)
{
    TimeDelta time_delta = Datetime(2000, 2, 1) - Datetime(2000, 1, 1);
    EXPECT_EQ(time_delta, TimeDelta(31));
}

TEST(Datetime, operator_minus_datetime_datetime_year)
{
    TimeDelta time_delta = Datetime(2000, 1, 1) - Datetime(1999, 1, 1);
    EXPECT_EQ(time_delta, TimeDelta(365));
}

TEST(Datetime, hash)
{
    size_t hashed = std::hash<Date>{}(Date());
}

TEST(Datetime, increment_days)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 30),
                                                   Datetime(2023, 1, 1),
                                                   Days(1));
    std::vector<Datetime> expected = {Datetime(2022, 12, 30),
                                      Datetime(2022, 12, 31),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_2_days)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 30),
                                                   Datetime(2023, 1, 1),
                                                   Days(2));
    std::vector<Datetime> expected = {Datetime(2022, 12, 30),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_hours)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 22),
                                                   Datetime(2023, 1, 1, 0),
                                                   Hours(1));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 22),
                                      Datetime(2022, 12, 31, 23),
                                      Datetime(2023, 1, 1, 0)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_2_hours)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 22),
                                                   Datetime(2023, 1, 1, 1),
                                                   Hours(2));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 22), Datetime(2023, 1, 1, 0)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_minutes)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 58),
                                                   Datetime(2023, 1, 1),
                                                   Minutes(1));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 58),
                                      Datetime(2022, 12, 31, 23, 59),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_2_minutes)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 58),
                                                   Datetime(2023, 1, 1),
                                                   Minutes(2));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 58), Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_seconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 58),
                                                   Datetime(2023, 1, 1),
                                                   Seconds(1));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 58),
                                      Datetime(2022, 12, 31, 23, 59, 59),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_2_seconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 58),
                                                   Datetime(2023, 1, 1),
                                                   Seconds(2));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 58), Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_milliseconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 59, 998),
                                                   Datetime(2023, 1, 1),
                                                   Milliseconds(1));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 59, 998),
                                      Datetime(2022, 12, 31, 23, 59, 59, 999),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_2_milliseconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 59, 998),
                                                   Datetime(2023, 1, 1),
                                                   Milliseconds(2));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 59, 998),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_microseconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 59, 999, 998),
                                                   Datetime(2023, 1, 1),
                                                   Microseconds(1));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 59, 999, 998),
                                      Datetime(2022, 12, 31, 23, 59, 59, 999, 999),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_2_microseconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 59, 999, 998),
                                                   Datetime(2023, 1, 1),
                                                   Microseconds(2));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 59, 999, 998),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_nanoseconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 59, 999, 999,
                                                            998),
                                                   Datetime(2023, 1, 1),
                                                   Nanoseconds(1));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 59, 999, 999, 998),
                                      Datetime(2022, 12, 31, 23, 59, 59, 999, 999, 999),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}

TEST(Datetime, increment_2_nanoseconds)
{
    std::vector<Datetime> actual = Datetime::range(Datetime(2022, 12, 31, 23, 59, 59, 999, 999,
                                                            998),
                                                   Datetime(2023, 1, 1),
                                                   Nanoseconds(2));
    std::vector<Datetime> expected = {Datetime(2022, 12, 31, 23, 59, 59, 999, 999, 998),
                                      Datetime(2023, 1, 1)};
    EXPECT_EQ(actual, expected);
}