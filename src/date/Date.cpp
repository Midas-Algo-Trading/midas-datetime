#include "datetime/date/Date.h"
#include "../../util/exceptions/not_implemented_error.h"
#include <chrono>
#include <iostream>

Date Date::today(uint8_t day_offset, Timezone timezone)
{
    // Get the current time
    auto now = std::chrono::system_clock::now();
    std::time_t t = std::chrono::system_clock::to_time_t(now);

    // Convert the system time to a std::tm struct
    std::tm *now_tm = std::localtime(&t);

    int year = now_tm->tm_year + 1900;
    int month = now_tm->tm_mon + 1;
    int day = now_tm->tm_mday;

    // Adjust date for non-local timezone
    if (timezone != TZ::LOCAL)
    {
        Date today = Date(year, month, day);
        int hour = Time::now().hour + TZ::LOCAL.get_utc_offset_diff(timezone);
        if (hour > Time::HOURS_PER_DAY)
            today.add_days(1);
        else if (hour < 0)
            today.subtract_days(1);
        return today;
    }

    // Create date
    Date date = Date(year, month, day);
    date += Day(day_offset);

    // Check if date is valid
    ASSERT(date.is_valid_date(),
           std::invalid_argument(fmt::format("{} is an invalid date", date.to_string())));

    return date;
}

Date& Date::operator+=(const Day& days)
{
    add_days(days.value);
    return *this;
}

Date& Date::operator-=(const Day& days)
{
    subtract_days(days.value);
    return *this;
}

Date& Date::operator++()
{
    add_days(1);
    return *this;
}

Date& Date::operator--()
{
    subtract_days(1);
    return *this;
}

bool Date::operator>(const Date& other) const
{
    return year > other.year
        || year == other.year && month > other.month
        || year == other.year && month == other.month && day > other.day;
}

bool Date::operator>=(const Date& other) const
{
    return year > other.year
        || year == other.year && month > other.month
        || year == other.year && month == other.month && day >= other.day;
}

bool Date::operator<(const Date& other) const
{
    return year < other.year
        || year == other.year && month < other.month
        || year == other.year && month == other.month && day < other.day;
}

bool Date::operator<=(const Date& other) const
{
    return year < other.year
        || year == other.year && month < other.month
        || year == other.year && month == other.month && day <= other.day;
}

bool Date::operator==(const Date& other) const
{
    return year == other.year
        && month == other.month
        && day == other.day;
}

bool Date::operator!=(const Date& other) const
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

size_t Date::max_days_in_month() const
{
    ASSERT(month >= 1 && month <= 12,
           std::runtime_error(fmt::format("'{}' is not a valid month", month)));

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

void Date::add_days(size_t days_to_add)
{
    while (days_to_add > 0)
    {
        size_t days_till_next_month = (max_days_in_month() - day) + 1;
        if (days_to_add < days_till_next_month)
        {
            day += static_cast<int>(days_to_add);
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

    ASSERT(is_valid_date(),
           std::runtime_error(fmt::format("'{}' is not a valid date", this->to_string())));
}

void Date::subtract_days(size_t days_to_subtract)
{
    while (days_to_subtract > 0)
    {
        size_t days_till_prev_month = day;
        if (days_to_subtract < days_till_prev_month)
        {
            day -= static_cast<int>(days_to_subtract);
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
            day = static_cast<int>(max_days_in_month());
            days_to_subtract -= days_till_prev_month;
        }
    }

    ASSERT(is_valid_date(),
           std::runtime_error(fmt::format("'{}' is not a valid date", this->to_string())));
}

const int Date::MONTHS_PER_YEAR = 12;

std::ostream& operator<<(std::ostream& os, const Date& date)
{
    return os
        << date.year
        << '-'
        << strh::align(std::to_string(date.month), strh::Alignment::LEFT, 2, '0')
        << '-'
        << strh::align(std::to_string(date.day), strh::Alignment::LEFT, 2, '0');
}

Date::DayOfWeek Date::day_of_week() const
{
    // Checks
    if (year < 1901)
        throw not_implemented_error("Year must greater than 1901");

    int _year = year;
    int _month = month;

    // Adjust month and year for Zeller's congruence formula
    if (_month < 3)
    {
        _month += 12;
        _year -= 1;
    }

    // Calculate anchor day (January 1st, 1900 was a Monday)
    int anchor_day = 1 + (365 + 365 + 365 + 366) % 7; // January 1st, 1900 was a Monday

    // Calculate day of the week using Zeller's congruence formula
    int h = (
                day + (13 * (_month + 1) / 5)
                + _year + (_year / 4)
                - (_year / 100)
                + (_year / 400)
                + anchor_day
            ) % 7;

    // Convert Sunday-Saturday numbering to Monday-Sunday numbering
    size_t day_of_week = (h + 6) % 7;

    switch (day_of_week) {
    case 0:
        return MONDAY;
    case 1:
        return TUESDAY;
    case 2:
        return WEDNESDAY;
    case 3:
        return THURSDAY;
    case 4:
        return FRIDAY;
    case 5:
        return SATURDAY;
    case 6:
        return SUNDAY;
    default:
        throw std::runtime_error(
            fmt::format("day_of_week '{}' is invalid. Must be between 0 and 6", day_of_week));
    }
}

bool Date::is_weekday() const
{
    return !is_weekend();
}

bool Date::is_weekend() const
{
    switch (day_of_week()) {
    case SATURDAY:
    case SUNDAY:
        return true;
    default:
        return false;
    }
}

std::string Date::to_string(char separate_year, char separate_day) const
{
    return std::to_string(year)
           + separate_year + strh::align(std::to_string(month), strh::Alignment::LEFT, 2, '0')
           + separate_day + strh::align(std::to_string(day), strh::Alignment::LEFT, 2, '0');
}

bool Date::is_valid_date() const
{
    return is_valid_year() && is_valid_month() && is_valid_day();
}

Date::Date(uint16_t year, uint8_t month, uint8_t day) :
    year(year),
    month(month),
    day(day)
{
    ASSERT(is_valid_date(),
           std::invalid_argument(fmt::format("'{}' is an invalid date", Date::to_string())));
}

bool Date::is_valid_year() const
{
    // Even though year would technically be valid, we don't expect to have a date passed
    // these values.
    return year <= 2100 && year >= 1900;
}

bool Date::is_valid_month() const
{
    return month <= 12 && month >= 1;
}

bool Date::is_valid_day() const
{
    return day <= max_days_in_month() && day >= 1;
}

Date Date::operator+(const Day& days)
{
    Date date = (*this);
    date += days;
    return date;
}

Date Date::operator-(const Day &days)
{
    Date date = (*this);
    date -= days;
    return date;
}

Date Date::tomorrow(Timezone timezone)
{
    return Date::today(1, timezone);
}
