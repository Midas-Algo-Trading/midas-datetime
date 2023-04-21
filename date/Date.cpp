#include "Date.h"
#include <iostream>
#include <chrono>
#include <algorithm>

Date Date::today()
{
        // Get the current time
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        // Convert the system time to a std::tm struct
        std::tm *now_tm = std::localtime(&t);

        int year = now_tm->tm_year + 1900;
        int month = now_tm->tm_mon + 1;
        int day = now_tm->tm_mday;

        return Date(year, month, day);
}

Date &Date::operator+=(const Day& days)
{
        if (days > 0)
                add_days(days);
        else
                subtract_days(days);

        return *this;
}

Date &Date::operator-=(const Day& days)
{
        if (days > 0)
                subtract_days(days);
        else
                add_days(days);

        return *this;
}

Date& Date::operator++(int)
{
        add_days(1);
        return *this;
}

Date& Date::operator--(int)
{
        subtract_days(1);
        return *this;
}

bool Date::operator>(const Date &other) const
{
        return year > other.year
               || month > other.month
               || day > other.day;
}

bool Date::operator>=(const Date &other) const
{
        return year >= other.year
            || month >= other.month
            || day >= other.day;
}

bool Date::operator<(const Date &other) const
{
        return year < other.year
               || month < other.month
               || day < other.day;
}

bool Date::operator<=(const Date &other) const
{
        return year <= other.year
               || month <= other.month
               || day <= other.day;
}

bool Date::operator==(const Date &other) const
{
        return year == other.year
               && month == other.month
               && day == other.day;
}

bool Date::operator!=(const Date &other) const
{
        return year != other.year
               || month != other.month
               || day != other.day;
}

bool Date::is_leap_year() const
{
        if (year % 4 != 0)
                return false;
        else if (year % 100 != 0)
                return true;
        else if (year % 400 != 0)
                return false;
        return true;
}

int Date::max_days_in_month() const
{
        switch (month) {
        case 2:
                return is_leap_year() ? 29 : 28;
        case 4:
        case 6:
        case 9:
        case 11:
                return 30;
        default:
                return 31;
        }
}

void Date::add_days(int days_to_add)
{
        while (days_to_add > 0)
        {
                int days_till_next_month = (max_days_in_month() - day) + 1;
                if (days_to_add < days_till_next_month)
                {
                        day += days_to_add;
                        return;
                }
                else
                {
                        month++;
                        if (month > MONTHS_PER_YEAR)
                        {
                                year++;
                                month = 1;
                        }
                        day = 1;
                        days_to_add -= days_till_next_month;
                }
        }
}

void Date::subtract_days(int days_to_subtract)
{
        while (days_to_subtract > 0)
        {
                int days_till_prev_month = day;
                if (days_to_subtract < days_till_prev_month)
                {
                        day += days_till_prev_month;
                        return;
                }
                else
                {
                        month--;
                        if (month < 1)
                        {
                                year--;
                                month = 12;
                        }
                        day = max_days_in_month();
                        days_to_subtract -= days_till_prev_month;
                }
        }
}

const int Date::MONTHS_PER_YEAR = 12;
