#include "gtest/gtest.h"

#define private public
#include "datetime/time/Time.h"
#include "datetime/datetime/Datetime.h"
#include "datetime/datetime/DatetimeRange.h"


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

TEST(Datetime, now_sets_members)
{
        Datetime now_datetime = Datetime::now();
        Time now_time = Time::now();
        now_datetime.round(Time::MILLISECOND);
        now_time.round(Time::Component::MILLISECOND);
        EXPECT_EQ(now_datetime.time(), now_time);
}

TEST(Datetime, date)
{
        Datetime datetime = Datetime(1900, 2, 3);
        Date date = datetime.date();
        EXPECT_EQ(date.year, 1900);
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

TEST(Datetime, test)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 0);
        datetime -= Nanosecond(3);
        EXPECT_EQ(datetime, Datetime(1999, 12, 31, 23, 59, 59, 999, 999, 997));
}

TEST(Datetime, operator_greater_than)
{
       Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
       Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
       EXPECT_GT(datetime_greater, datetime_lesser);
}

TEST(Datetime, operator_greater_than_or_equal_to)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_GE(datetime_greater, datetime_lesser);

        Datetime datetime_equal = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        EXPECT_GE(datetime_greater, datetime_equal);
}

TEST(Datetime, operator_less_than)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_LT(datetime_lesser, datetime_greater);
}

TEST(Datetime, operator_less_than_or_equal_to)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        EXPECT_LE(datetime_lesser, datetime_greater);

        Datetime datetime_equal = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        EXPECT_LE(datetime_lesser, datetime_equal);
}

TEST(Datetime, operator_equal_to)
{
        Datetime datetime1 = Datetime();
        Datetime datetime2 = Datetime();
        EXPECT_EQ(datetime1, datetime2);
}

TEST(Datetime, operator_not_equal_to)
{
        Datetime datetime1 = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime2 = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
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
        Datetime datetime = Datetime(1900, 1, 1);
        datetime += Day(1);
        int new_day = datetime.day;
        EXPECT_EQ(new_day, 2);
}

TEST(Datetime, operator_plusequal_adds_day_new_month)
{
        Datetime datetime = Datetime(1900, 1, 31);
        datetime += Day(1);
        EXPECT_EQ(datetime.month, 2);
        EXPECT_EQ(datetime.day, 1);
}

TEST(Datetime, operator_minusequal_subtracts_day_basic)
{
        Datetime datetime = Datetime(1900, 1, 2);
        datetime -= Day(1);
        EXPECT_EQ(datetime.day, 1);
}

TEST(Datetime, operator_minusequal_subtracts_month)
{
        Datetime datetime = Datetime(1900, 2, 1);
        datetime -= Day(1);
        EXPECT_EQ(datetime.month, 1);
        EXPECT_EQ(datetime.day, 31);
}

TEST(Datetime, operator_plusequal_hour_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 1);
        datetime += Hour(1);
        EXPECT_EQ(datetime.hour, 2);
}

TEST(Datetime, operator_plusequal_hour_adds_day)
{
        Datetime datetime = Datetime(2000, 1, 2, 22);
        datetime += Hour(4);
        EXPECT_EQ(datetime.day, 3);
        EXPECT_EQ(datetime.hour, 2);
}

TEST(Datetime, operator_minusequal_hour_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 3);
        datetime -= Hour(1);
        EXPECT_EQ(datetime.hour, 2);
}

TEST(Datetime, operator_minusequal_hour_subtracts_day)
{
        Datetime datetime = Datetime(2000, 1, 1, 0);
        datetime -= Hour(1);
        EXPECT_EQ(datetime.year, 1999);
        EXPECT_EQ(datetime.month, 12);
        EXPECT_EQ(datetime.day, 31);
        EXPECT_EQ(datetime.hour, 23);
}

TEST(Datetime, operator_plusequal_minute_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 1);
        datetime += Minute(1);
        EXPECT_EQ(datetime.minute, 2);
}

TEST(Datetime, operator_plusequal_minute_adds_hour)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 58);
        datetime += Minute(4);
        EXPECT_EQ(datetime.hour, 1);
        EXPECT_EQ(datetime.minute, 2);
}

TEST(Datetime, operator_minusequal_minute_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 3);
        datetime -= Minute(1);
        EXPECT_EQ(datetime.minute, 2);
}

TEST(Datetime, operator_minusequal_minute_subtracts_hour)
{
        Datetime datetime = Datetime(2000, 1, 1, 1, 1);
        datetime -= Minute(2);
        EXPECT_EQ(datetime.hour, 0);
        EXPECT_EQ(datetime.minute, 59);
}

TEST(Datetime, operator_plusequal_second_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 1);
        datetime += Second(1);
        EXPECT_EQ(datetime.second, 2);
}

TEST(Datetime, operator_plusequal_second_adds_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 58);
        datetime += Second(4);
        EXPECT_EQ(datetime.minute, 1);
        EXPECT_EQ(datetime.second, 2);
}

TEST(Datetime, operator_minusequal_second_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 3);
        datetime -= Second(1);
        EXPECT_EQ(datetime.second, 2);
}

TEST(Datetime, operator_minusequal_second_subtracts_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 1, 1);
        datetime -= Second(2);
        EXPECT_EQ(datetime.minute, 0);
        EXPECT_EQ(datetime.second, 59);
}

TEST(Datetime, operator_plusequal_millisecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 1);
        datetime += Millisecond(1);
        EXPECT_EQ(datetime.millisecond, 2);
}

TEST(Datetime, operator_plusequal_millisecond_adds_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 999);
        datetime += Millisecond(3);
        EXPECT_EQ(datetime.second, 1);
        EXPECT_EQ(datetime.millisecond, 2);
}

TEST(Datetime, operator_minusequal_millisecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 3);
        datetime -= Millisecond(1);
        EXPECT_EQ(datetime.millisecond, 2);
}

TEST(Datetime, operator_minusequal_millisecond_subtracts_second)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 1, 1);
        datetime -= Millisecond(2);
        EXPECT_EQ(datetime.second, 0);
        EXPECT_EQ(datetime.millisecond, 999);
}

TEST(Datetime, operator_plusequal_microsecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 1);
        datetime += Microsecond(1);
        EXPECT_EQ(datetime.microsecond, 2);
}

TEST(Datetime, operator_plusequal_microsecond_adds_millisecond)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 999);
        datetime += Microsecond(3);
        EXPECT_EQ(datetime.millisecond, 1);
        EXPECT_EQ(datetime.microsecond, 2);
}

TEST(Datetime, operator_minusequal_microsecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 3);
        datetime -= Microsecond(1);
        EXPECT_EQ(datetime.microsecond, 2);
}

TEST(Datetime, operator_minusequal_microsecond_subtracts_millisecond)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 1, 1);
        datetime -= Microsecond(2);
        EXPECT_EQ(datetime.millisecond, 0);
        EXPECT_EQ(datetime.microsecond, 999);
}

TEST(Datetime, operator_plusequal_nanosecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 1);
        datetime += Nanosecond(1);
        EXPECT_EQ(datetime.nanosecond, 2);
}

TEST(Datetime, operator_plusequal_nanoecond_adds_minute)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 999);
        datetime += Nanosecond(3);
        EXPECT_EQ(datetime.microsecond, 1);
        EXPECT_EQ(datetime.nanosecond, 2);
}

TEST(Datetime, operator_minusequal_nanosecond_basic)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 3);
        datetime -= Nanosecond(1);
        EXPECT_EQ(datetime.nanosecond, 2);
}

TEST(Datetime, operator_minusequal_nanosecond_subtracts_microsecond)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 1, 1);
        datetime -= Nanosecond(2);
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