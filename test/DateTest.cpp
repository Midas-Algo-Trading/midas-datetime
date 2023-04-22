#include "gtest/gtest.h"

//#define private public
//#include "../src/date/components/Day.h"
#include "../src/date/Date.h"
#include "../src/date/Date.cpp"

//TEST(Date_test, constrctor_set_variable)
//{
//        int day_value = 1;
//        Day day = Day(day_value);
//        ASSERT_EQ(day.value, day_value);
//}

TEST(Date_test, constructor_sets_variables)
{
        int year_value = 2000;
        int month_value = 2;
        int day_value = 3;
        Date date = Date(year_value, month_value, day_value);
        EXPECT_EQ(date.year, year_value);
        EXPECT_EQ(date.month, month_value);
        EXPECT_EQ(date.day, day_value);
}

TEST(Date_test, today_sets_local_date)
{
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        // Convert the system time to a std::tm struct
        std::tm *now_tm = std::localtime(&t);

        int today_year = now_tm->tm_year + 1900;
        int today_month = now_tm->tm_mon + 1;
        int toda_day = now_tm->tm_mday;

        Date today = Date::today();
        EXPECT_EQ(today.year, today_year);
        EXPECT_EQ(today.month, today_month);
        EXPECT_EQ(today.day, toda_day);
}

//TEST(Date_test, today_sets_timezone_date)
//{
//
//}

//TEST(Date_test, operator_plusequal_adds_day)
//{
//        Date date = Date();
//        int old_day = date.day;
//        int day_inc = 1;
//        date += Day(day_inc);
//        int new_day = date.day;
//        ASSERT_EQ(new_day, old_day+day_inc);
//}

int main(int argc, char **argv)
{
        testing::InitGoogleTest(&argc, argv);
        return RUN_ALL_TESTS();
}
