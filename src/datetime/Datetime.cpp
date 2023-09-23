#include "datetime/datetime/Datetime.h"

Datetime Datetime::now(uint8_t  day_offset, uint8_t hour_offset, uint8_t minute_offset,
                       uint8_t second_offset, uint16_t millisecond_offset,
                       uint16_t microsecond_offset, uint16_t nanosecond_offset, Timezone timezone)
{
    return Datetime(Date::today(day_offset, timezone),
                    Time::now(hour_offset, minute_offset, second_offset, millisecond_offset,
                              microsecond_offset, nanosecond_offset, timezone));
}

void Datetime::add_hours(int hours_to_add)
{
    int new_hour = hour + hours_to_add;
    int day_change = new_hour / HOURS_PER_DAY;
    new_hour %= HOURS_PER_DAY;
    if (new_hour < 0)
    {
        new_hour += HOURS_PER_DAY;
        day_change--;
    }
    hour = new_hour;

    if (day_change > 0)
        add_days(day_change);
    if (day_change < 0)
        subtract_days(day_change * -1);
}

Date Datetime::date() const
{
    return Date(year, month, day);
}

Time Datetime::time() const
{
    return Time(hour, minute, second, millisecond, microsecond, nanosecond, timezone);
}


bool Datetime::operator>(const Datetime& other) const
{
    return Date::operator>(other.date())
        || Date::operator==(other.date()) && Time::operator>(other.time());
}

bool Datetime::operator>=(const Datetime& other) const
{
    return Date::operator>(other.date())
        || Date::operator==(other.date()) && Time::operator>=(other.time());
}

bool Datetime::operator<(const Datetime& other) const
{
    return Date::operator<(other.date())
        || Date::operator==(other.date()) && Time::operator<(other.time());
}

bool Datetime::operator<=(const Datetime& other) const
{
    return Date::operator<(other.date())
        || Date::operator==(other.date()) && Time::operator<=(other.time());
}

bool Datetime::operator==(const Datetime& other) const
{
    return Date::operator==(other.date()) && Time::operator==(other.time());
}

bool Datetime::operator!=(const Datetime& other) const
{
    return Date::operator!=(other.date()) || Time::operator!=(other.time());
}

Datetime &Datetime::operator+=(const Day& days)
{
    Date::operator+=(days);
    return *this;
}

Datetime &Datetime::operator-=(const Day& days)
{
    Date::operator-=(days);
    return *this;
}

Datetime &Datetime::operator+=(const Hour& hours)
{
    Time::operator+=(hours);
    return *this;
}

Datetime &Datetime::operator-=(const Hour& hours)
{
    Time::operator-=(hours);
    return *this;
}

Datetime &Datetime::operator+=(const Minute& minutes)
{
    Time::operator+=(minutes);
    return *this;
}

Datetime &Datetime::operator-=(const Minute& minutes)
{
    Time::operator-=(minutes);
    return *this;
}

Datetime &Datetime::operator+=(const Second& seconds)
{
    Time::operator+=(seconds);
    return *this;
}

Datetime &Datetime::operator-=(const Second& seconds)
{
    Time::operator-=(seconds);
    return *this;
}

Datetime &Datetime::operator+=(const Millisecond& milliseconds)
{
    Time::operator+=(milliseconds);
    return *this;
}

Datetime &Datetime::operator-=(const Millisecond& milliseconds)
{
    Time::operator-=(milliseconds);
    return *this;
}

Datetime &Datetime::operator+=(const Microsecond& microseconds)
{
    Time::operator+=(microseconds);
    return *this;
}

Datetime &Datetime::operator-=(const Microsecond& microseconds)
{
    Time::operator-=(microseconds);
    return *this;
}

Datetime &Datetime::operator+=(const Nanosecond& nanoseconds)
{
    Time::operator+=(nanoseconds);
    return *this;
}

Datetime &Datetime::operator-=(const Nanosecond& nanoseconds)
{
    Time::operator-=(nanoseconds);
    return *this;
}

Datetime &Datetime::operator++()
{
    Date::operator++();
    return *this;
}

Datetime &Datetime::operator--()
{
    Date::operator--();
    return *this;
}

std::string Datetime::to_string() const
{
    return Date::to_string() + ' ' + Time::to_string();
}

std::ostream& operator<<(std::ostream& os, const Datetime& datetime)
{
    return os << datetime.to_string();
}

Datetime Datetime::from_ms(size_t timestamp, Timezone timezone)
{
    // The timezone offset in milliseconds,
    size_t timezone_offset_ms = 5 * 60 * 60 * 1000;

    // Convert milliseconds to seconds and milliseconds
    size_t timestamp_sec = (timestamp - timezone_offset_ms) / 1000;
    uint16_t millisecond = timestamp % 1000;

    auto is_leap_year = [](size_t year) {
        return (year % 4 == 0 && (year % 100 != 0 || year % 400 == 0));
    };

    // Calculate year.
    uint16_t year = 1970;  // Unix epoch year.
    while (timestamp_sec >= 31536000)  // Number of seconds in a non-leap year.
    {
        size_t seconds_in_year = is_leap_year(year) ? 31622400 : 31536000;
        timestamp_sec -= seconds_in_year;
        year++;
    }

    // Number of days in each month for a non-leap year,
    size_t days_in_month[] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

    // Adjust February for leap years.
    if (is_leap_year(year))
        days_in_month[2] = 29;

    // Calculate month and day.
    uint8_t month = 1;
    size_t seconds_per_day = 86400;
    while (timestamp_sec >= days_in_month[month] * seconds_per_day)
    {
        timestamp_sec -= days_in_month[month] * seconds_per_day;
        month++;
    }
    uint8_t day = (timestamp_sec / seconds_per_day) + 1;

    uint8_t hour = (timestamp_sec % 86400LL) / 3600;
    uint8_t minute = (timestamp_sec % 3600) / 60;
    uint8_t second = timestamp_sec % 60;

    return Datetime(year, month, day, hour, minute, second, millisecond, 0, 0, timezone);
}
