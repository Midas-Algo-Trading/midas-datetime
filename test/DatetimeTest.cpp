#include "gtest/gtest.h"

#define private public
#include "../src/datetime/Datetime.cpp"
#include "../src/datetime/DatetimeRange.h"


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
        Datetime datetime = Datetime(1, 2, 3, 4, 5, 6, 7, 8, 9);
        EXPECT_EQ(datetime.year, 1);
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

TEST(Datetime, add_hours_pos_basic)
{
        Datetime datetime = Datetime(1900, 1, 1, 1);
        datetime.add_hours(1);
        ASSERT_EQ(datetime.hour, 2);
}

TEST(Datetime, add_hours_pos_adds_day)
{
        Datetime datetime = Datetime(1900, 1, 1, 23);
        datetime.add_hours(4);
        ASSERT_EQ(datetime.day, 2);
        ASSERT_EQ(datetime.hour, 3);
}

TEST(Datetime, add_hours_neg_basic)
{
        Datetime datetime = Datetime(1900, 1, 1, 3);
        datetime.add_hours(-1);
        ASSERT_EQ(datetime.hour, 2);
}

TEST(Datetime, add_hours_neg_subtracts_day)
{
        Datetime datetime = Datetime(1900, 1, 1, 1);
        datetime.add_hours(-4);
        ASSERT_EQ(datetime.year, 1899);
        ASSERT_EQ(datetime.month, 12);
        ASSERT_EQ(datetime.day, 31);
        ASSERT_EQ(datetime.hour, 21);
}

TEST(Datetime, date)
{
        Datetime datetime = Datetime(1900, 2, 3);
        Date date = datetime.date();
        ASSERT_EQ(date.year, 1900);
        ASSERT_EQ(date.month, 2);
        ASSERT_EQ(date.day, 3);
}

TEST(Datetime, time)
{
        Datetime datetime = Datetime(2000, 1, 1, 1, 2, 3, 4, 5, 6);
        Time time = datetime.time();
        ASSERT_EQ(time.hour, 1);
        ASSERT_EQ(time.minute, 2);
        ASSERT_EQ(time.second, 3);
        ASSERT_EQ(time.millisecond, 4);
        ASSERT_EQ(time.microsecond, 5);
        ASSERT_EQ(time.nanosecond, 6);
}

TEST(Datetime, test)
{
        Datetime datetime = Datetime(2000, 1, 1, 0, 0, 0, 0, 0, 0);
        datetime -= Nanosecond(3);
        ASSERT_EQ(datetime, Datetime(1999, 12, 31, 23, 59, 59, 999, 999, 997));
}

TEST(Datetime, operator_greater_than)
{
       Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
       Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
       ASSERT_GT(datetime_greater, datetime_lesser);
}

TEST(Datetime, operator_greater_than_or_equal_to)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        ASSERT_GE(datetime_greater, datetime_lesser);

        Datetime datetime_equal = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        ASSERT_GE(datetime_greater, datetime_equal);
}

TEST(Datetime, operator_less_than)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        ASSERT_LT(datetime_lesser, datetime_greater);
}

TEST(Datetime, operator_less_than_or_equal_to)
{
        Datetime datetime_lesser = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime_greater = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        ASSERT_LE(datetime_lesser, datetime_greater);

        Datetime datetime_equal = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        ASSERT_LE(datetime_lesser, datetime_equal);
}

TEST(Datetime, operator_equal_to)
{
        Datetime datetime1 = Datetime();
        Datetime datetime2 = Datetime();
        ASSERT_EQ(datetime1, datetime2);
}

TEST(Datetime, operator_not_equal_to)
{
        Datetime datetime1 = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 1);
        Datetime datetime2 = Datetime(2000, 1, 1, 1, 1, 1, 1, 1, 2);
        ASSERT_NE(datetime1, datetime2);
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