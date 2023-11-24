#include "gtest/gtest.h"

#include "datetime/date/Date.h"
#include "datetime/date/components/Day.h"
#include "datetime/timedelta/TimeDelta.h"
#include "datetime/date/DateRange.h"

TEST(Date, ostream)
{
        Date date = Date(2000, 2, 3);
        std::stringstream actual;
        actual << date;
        ASSERT_EQ(actual.str(), "2000-02-03");
}

TEST(Day_test, constrctor_int_int_int_set_variable)
{
        Day day = Day(1);
        ASSERT_EQ(day.value, 1);
}

TEST(Date, constructor_int_int_int_sets_variables)
{
        Date date = Date(2000, 2, 3);
        EXPECT_EQ(date.year, 2000);
        EXPECT_EQ(date.month, 2);
        EXPECT_EQ(date.day, 3);
}

TEST(Date, constuctor_int_int_int_throws_invalid_argument)
{
    EXPECT_THROW(Date(2200, 1, 1), std::invalid_argument);
}

TEST(Date, today_sets_local_date)
{
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        // Convert the system time to a std::tm struct
        std::tm *now_tm = std::localtime(&t);

        int today_year = now_tm->tm_year + 1900;
        int today_month = now_tm->tm_mon + 1;
        int today_day = now_tm->tm_mday;

        Date today = Date::today();
        EXPECT_EQ(today.year, today_year);
        EXPECT_EQ(today.month, today_month);
        EXPECT_EQ(today.day, today_day);
}

TEST(Date, operator_plusequal_adds_day_basic)
{
        Date date = Date(1970, 1, 1);
        date += Day(1);
        int new_day = date.day;
        EXPECT_EQ(new_day, 2);
}

TEST(Date, operator_plusequal_adds_day_new_month)
{
        Date date = Date(1970, 1, 31);
        date += Day(1);
        EXPECT_EQ(date.month, 2);
        EXPECT_EQ(date.day, 1);
}

TEST(Date, operator_plusequal_adds_2_new_months)
{
        Date date = Date(1970, 3, 31);
        date += Day(31);
        EXPECT_EQ(date.month, 5);
        EXPECT_EQ(date.day, 1);
}

TEST(Date, operator_plusequal_adds_new_year)
{
        Date date = Date(1970, 1, 1);
        date += Day(365);
        EXPECT_EQ(date.year, 1971);
        EXPECT_EQ(date.month, 1);
        EXPECT_EQ(date.day, 1);
}

TEST(Date, operator_minusequal_subtracts_day_basic)
{
        Date date = Date(1970, 1, 2);
        date -= Day(1);
        EXPECT_EQ(date.day, 1);
}

TEST(Date, operator_minusequal_subtracts_month)
{
        Date date = Date(1970, 2, 1);
        date -= Day(1);
        EXPECT_EQ(date.month, 1);
        EXPECT_EQ(date.day, 31);
}

TEST(Date, operator_minusequal_subtracts_2_months)
{
        Date date = Date(1970, 5, 1);
        date -= Day(31);
        EXPECT_EQ(date.month, 3);
        EXPECT_EQ(date.day, 31);
}

TEST(Date, operator_minusqual_subtracts_year)
{
        Date date = Date(1970, 1, 1);
        date -= Day(365);
        EXPECT_EQ(date.year, 1969);
        EXPECT_EQ(date.month, 1);
        EXPECT_EQ(date.day, 1);
}

TEST(Date, operator_increment)
{
        Date date = Date(1970, 1, 1);
        ++date;
        ASSERT_EQ(date.day, 2);
}

TEST(Date, operator_decrement)
{
        Date date = Date(1970, 1, 2);
        --date;
        ASSERT_EQ(date.day, 1);
}

TEST(Date, operator_greater_than)
{
        Date date_greater = Date(1971, 1, 1);
        Date date_lesser = Date(1970, 1, 1);
        EXPECT_GT(date_greater, date_lesser);

        date_greater = Date(1970, 2, 1);
        date_lesser = Date(1970, 1, 1);
        EXPECT_GT(date_greater, date_lesser);

        date_greater = Date(1970, 1, 2);
        date_lesser = Date(1970, 1, 1);
        EXPECT_GT(date_greater, date_lesser);
}

TEST(Date, operator_greater_than_or_equal_to)
{
        Date date_greater = Date(1971, 1, 1);
        Date date_lesser = Date(1970, 1, 1);
        EXPECT_GE(date_greater, date_lesser);

        date_greater = Date(1970, 2, 1);
        date_lesser = Date(1970, 1, 1);
        EXPECT_GE(date_greater, date_lesser);

        date_greater = Date(1970, 1, 2);
        date_lesser = Date(1970, 1, 1);
        EXPECT_GE(date_greater, date_lesser);

        date_lesser = Date(1970, 1, 2);
        EXPECT_GE(date_greater, date_lesser);
}

TEST(Date, operator_lessr_than)
{
        Date date_greater = Date(1971, 1, 1);
        Date date_lesser = Date(1970, 1, 1);
        EXPECT_LT(date_lesser, date_greater);

        date_greater = Date(1970, 2, 1);
        date_lesser = Date(1970, 1, 1);
        EXPECT_LT(date_lesser, date_greater);

        date_greater = Date(1970, 1, 2);
        date_lesser = Date(1970, 1, 1);
        EXPECT_LT(date_lesser, date_greater);
}

TEST(Date, operator_less_than_or_equal_to)
{
        Date date_greater = Date(1971, 1, 1);
        Date date_lesser = Date(1970, 1, 1);
        EXPECT_LE(date_lesser, date_greater);

        date_greater = Date(1970, 2, 1);
        date_lesser = Date(1970, 1, 1);
        EXPECT_LE(date_lesser, date_greater);

        date_greater = Date(1970, 1, 2);
        date_lesser = Date(1970, 1, 1);
        EXPECT_LE(date_lesser, date_greater);

        date_lesser = Date(1970, 1, 2);
        EXPECT_LE(date_lesser, date_greater);
}

TEST(Date, operator_equal_to)
{
        Date date1 = Date(1970, 1, 1);
        Date date2 = Date(1970, 1, 1);
        EXPECT_EQ(date1, date2);
}

TEST(Date, operator_not_equal_to)
{
        Date date1 = Date(1970, 1, 1);
        Date date2 = Date(1971, 1, 1);
        EXPECT_NE(date1, date2);

        date2 = Date(1970, 2, 1);
        EXPECT_NE(date1, date2);

        date2 = Date(1970, 1, 2);
        EXPECT_NE(date1, date2);
}

TEST(Date, is_leap_year)
{
        Date date = Date(2004, 1, 1);
        EXPECT_TRUE(Date::is_leap_year(date.year));
        date = Date(1970, 1, 1);
        EXPECT_FALSE(Date::is_leap_year(date.year));
        date = Date(2000, 1, 1);
        EXPECT_TRUE(Date::is_leap_year(date.year));
        date = Date(1999, 1, 1);
        EXPECT_FALSE(Date::is_leap_year(date.year));
}

TEST(Date, max_days_in_month)
{
        EXPECT_EQ(Date::max_days_in_month(1), 31);
        EXPECT_EQ(Date::max_days_in_month(2), 28);
        EXPECT_EQ(Date::max_days_in_month(3), 31);
        EXPECT_EQ(Date::max_days_in_month(4), 30);
        EXPECT_EQ(Date::max_days_in_month(5), 31);
        EXPECT_EQ(Date::max_days_in_month(6), 30);
        EXPECT_EQ(Date::max_days_in_month(7), 31);
        EXPECT_EQ(Date::max_days_in_month(8), 31);
        EXPECT_EQ(Date::max_days_in_month(9), 30);
        EXPECT_EQ(Date::max_days_in_month(10), 31);
        EXPECT_EQ(Date::max_days_in_month(11), 30);
        EXPECT_EQ(Date::max_days_in_month(12), 31);
}
TEST(DateRange, constructor_sets_variables)
{
        Date start = Date(1970, 1, 1);
        Date end = Date(2000, 1, 1);
        DateRange date_range = DateRange(start, end);
        EXPECT_EQ(date_range.start, start);
        EXPECT_EQ(date_range.end, end);
}

TEST(Date, day_of_week)
{
        Date date = Date(1970, 1, 5);
        EXPECT_EQ(date.day_of_week(), Date::DayOfWeek::MONDAY);

        date = Date(1975, 3, 4);
        EXPECT_EQ(date.day_of_week(), Date::DayOfWeek::TUESDAY);

        date = Date(1980, 4, 2);
        EXPECT_EQ(date.day_of_week(), Date::DayOfWeek::WEDNESDAY);

        date = Date(1985, 5, 2);
        EXPECT_EQ(date.day_of_week(), Date::DayOfWeek::THURSDAY);

        date = Date(1990, 7, 6);
        EXPECT_EQ(date.day_of_week(), Date::DayOfWeek::FRIDAY);

        date = Date(1995, 8, 5);
        EXPECT_EQ(date.day_of_week(), Date::DayOfWeek::SATURDAY);

        date = Date(2000, 10, 1);
        EXPECT_EQ(date.day_of_week(), Date::DayOfWeek::SUNDAY);
}

TEST(Date, is_weekday)
{
        Date date = Date(1970, 1, 5);
        EXPECT_TRUE(date.is_weekday());

        date = Date(1980, 3, 4);
        EXPECT_TRUE(date.is_weekday());

        date = Date(1990, 4, 4);
        EXPECT_TRUE(date.is_weekday());

        date = Date(2000, 7, 6);
        EXPECT_TRUE(date.is_weekday());

        date = Date(2010, 9, 3);
        EXPECT_TRUE(date.is_weekday());
}

TEST(Date, is_weekend)
{
        Date date = Date(2000, 1, 1);
        EXPECT_TRUE(date.is_weekend());

        date = Date(2010, 12, 5);
        EXPECT_TRUE(date.is_weekend());
}

TEST(DateRange, constructor_start_greater_than_end_throws_illegal_argument)
{
        Date start = Date(2000, 1, 1);
        Date end = Date(1970, 1, 1);
        EXPECT_THROW(DateRange(start, end), std::invalid_argument);
}

TEST(DateRange, in_range)
{
        Date start = Date(1975, 1, 1);
        Date end = Date(2000, 1, 1);
        DateRange date_range = DateRange(start, end);

        Date date = Date(1990, 1, 1);
        EXPECT_TRUE(date_range.in_range(date));

        date = Date(1975, 1, 1);
        EXPECT_TRUE(date_range.in_range(date));

        date = Date(2000, 1, 1);
        EXPECT_TRUE(date_range.in_range(date));

        date = Date(1970, 1, 1);
        EXPECT_FALSE(date_range.in_range(date));

        date = Date(2100, 1, 1);
        EXPECT_FALSE(date_range.in_range(date));
}

TEST(Date, to_string)
{
    Date date = Date(2000, 1, 10);
    EXPECT_EQ(date.to_string(), "2000-01-10");
}

TEST(Date, constructor_string_DateComponents_basic)
{
    Date date = Date("2000-01-20",
                     Date::Component::YEAR, Date::Component::MONTH, Date::Component::DAY);
    EXPECT_EQ(date.year, 2000);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 20);

    date = Date("2000-20-01",
                Date::Component::YEAR, Date::Component::DAY, Date::Component::MONTH);
    EXPECT_EQ(date.year, 2000);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 20);
}

TEST(Date, constructor_string_DateComponents_throws_invalid_argument_on_wrong_date_components)
{
        EXPECT_THROW(Date("2000", Date::Component::YEAR, Date::Component::MONTH),
                     std::invalid_argument);
}

TEST(Date, constructor_string_DateComponents_throws_invalid_argument_on_out_of_range_components)
{
    EXPECT_THROW(Date("1800-01-01", Date::Component::YEAR, Date::Component::MONTH,
                      Date::Component::DAY),
                 std::invalid_argument);
}

TEST(Date, constructor_string_basic)
{
    Date date = Date("2000-01-20");
    EXPECT_EQ(date.year, 2000);
    EXPECT_EQ(date.month, 1);
    EXPECT_EQ(date.day, 20);
}

TEST(Date, constructor_string_throws_invalid_argument)
{
    EXPECT_THROW(Date("1800-01-01"), std::invalid_argument);
}

TEST(Date, operator_plus)
{
    Date date = Date(2000, 1, 1);
    Date new_date = date + Day(1);
    EXPECT_EQ(new_date, Date(2000, 1, 2));
}

TEST(Date, operator_minus)
{
    Date date = Date(2000, 1, 2);
    Date new_date = date - Day(1);
    EXPECT_EQ(new_date, Date(2000, 1, 1));
}

TEST(Date, tomorrow)
{
    Date today = Date::today();
    Date tomorrow = Date::tomorrow();
    EXPECT_EQ(tomorrow - Day(1), today);
}

TEST(Date, hash)
{
    size_t hashed = std::hash<Date>{}(Date());
}