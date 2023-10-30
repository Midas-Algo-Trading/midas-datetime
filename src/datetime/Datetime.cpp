#include "datetime/datetime/Datetime.h"

Datetime Datetime::now(uint8_t  day_offset, uint8_t hour_offset, uint8_t minute_offset,
                       uint8_t second_offset, uint16_t millisecond_offset,
                       uint16_t microsecond_offset, uint16_t nanosecond_offset, Timezone timezone)
{
    return Datetime(Date::today(day_offset, timezone),
                    Time::now(hour_offset, minute_offset, second_offset, millisecond_offset,
                              microsecond_offset, nanosecond_offset, timezone));
}

void Datetime::add_hours(int64_t hours_to_add)
{
    int64_t hours = static_cast<int64_t>(hour) + hours_to_add;
    int64_t day_change = static_cast<int64_t>(hours) / HOURS_PER_DAY;
    int new_hour = static_cast<int>(hours % HOURS_PER_DAY);
    if (new_hour < 0)
    {
        new_hour += HOURS_PER_DAY;
        day_change--;
    }
    hour = new_hour;

    if (day_change > 0)
        add_days(day_change);
    if (day_change < 0)
        subtract_days(-day_change);
}

Date Datetime::date() const
{
    return Date(year, month, day);
}

Time Datetime::time() const
{
    return Time(hour, minute, second, millisecond, microsecond, nanosecond, timezone);
}


bool Datetime::operator>(Datetime other) const
{
    other.set_timezone(timezone);

    return Date::operator>(other.date())
        || Date::operator==(other.date()) && Time::operator>(other.time());
}

bool Datetime::operator>=(Datetime other) const
{
    other.set_timezone(timezone);

    return Date::operator>(other.date())
        || Date::operator==(other.date()) && Time::operator>=(other.time());
}

bool Datetime::operator<(Datetime other) const
{
    other.set_timezone(timezone);

    return Date::operator<(other.date())
        || Date::operator==(other.date()) && Time::operator<(other.time());
}

bool Datetime::operator<=(Datetime other) const
{
    other.set_timezone(timezone);

    return Date::operator<(other.date())
        || Date::operator==(other.date()) && Time::operator<=(other.time());
}

bool Datetime::operator==(Datetime other) const
{
    other.set_timezone(timezone);

    return Date::operator==(other.date()) && Time::operator==(other.time());
}

bool Datetime::operator!=(Datetime other) const
{
    other.set_timezone(timezone);

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

std::string Datetime::to_string(char separate_components, char separate_time) const
{
    return Date::to_string() + separate_components + Time::to_string(separate_time);
}

std::ostream& operator<<(std::ostream& os, const Datetime& datetime)
{
    return os << datetime.to_string();
}

Datetime Datetime::from_ms(size_t timestamp, Timezone to_timezone, Timezone from_timezone)
{
    // Year.
    uint16_t year = 1970;  // Unix epoch year.
    while (timestamp >= MILLISECONDS_PER_NON_LEAP_YEAR)
    {
        size_t ms_in_year = is_leap_year(year)
                                    ? MILLISECONDS_PER_LEAP_YEAR
                                    : MILLISECONDS_PER_NON_LEAP_YEAR;
        timestamp -= ms_in_year;
        year++;
    }

    // Month.
    uint8_t month = 1;
    while (timestamp >= max_days_in_month(month, year) * MILLISECONDS_PER_DAY)
    {
        timestamp -= max_days_in_month(month, year) * MILLISECONDS_PER_DAY;
        month++;
    }

    // Day.
    // We'll later add 1 to 'day' because we cannot have day = 0. Minimum day is 1.
    uint8_t day = timestamp / MILLISECONDS_PER_DAY;
    timestamp %= MILLISECONDS_PER_DAY;

    // Hour.
    uint8_t hour = timestamp / MILLISECONDS_PER_HOUR;
    timestamp %= MILLISECONDS_PER_HOUR;

    // Minute.
    uint8_t minute = timestamp / MILLISECONDS_PER_MINUTE;
    timestamp %= MILLISECONDS_PER_MINUTE;

    // Second.
    uint8_t second = timestamp / MILLISECONDS_PER_SECOND;
    timestamp %= MILLISECONDS_PER_SECOND;

    // Millisecond.
    uint16_t millisecond = timestamp;


    Datetime ret =
        Datetime(year, month, day+1, hour, minute, second, millisecond, 0, 0, from_timezone);

    ret.set_timezone(to_timezone);

    return ret;
}

Datetime operator+(Datetime datetime, const Hour& hours)
{
    datetime += hours;
    return datetime;
}

Datetime operator-(Datetime datetime, const Hour& hours)
{
    datetime -= hours;
    return datetime;
}

Datetime operator+(Datetime datetime, const Minute& minutes)
{
    datetime += minutes;
    return datetime;
}

Datetime operator-(Datetime datetime, const Minute& minutes)
{
    datetime -= minutes;
    return datetime;
}

Datetime operator+(Datetime datetime, const Second& seconds)
{
    datetime += seconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Second& seconds)
{
    datetime -= seconds;
    return datetime;
}

Datetime operator+(Datetime datetime, const Millisecond& milliseconds)
{
    datetime += milliseconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Millisecond& milliseconds)
{
    datetime -= milliseconds;
    return datetime;
}

Datetime operator+(Datetime datetime, const Microsecond& microseconds)
{
    datetime += microseconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Microsecond& microseconds)
{
    datetime -= microseconds;
    return datetime;
}

Datetime operator+(Datetime datetime, const Nanosecond& nanoseconds)
{
    datetime += nanoseconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Nanosecond& nanoseconds)
{
    datetime -= nanoseconds;
    return datetime;
}

Datetime operator+(Datetime datetime, Time other)
{
    other.set_timezone(datetime.timezone);
    datetime += other;
    return datetime;
}

Datetime operator-(Datetime datetime, Time other)
{
    other.set_timezone(datetime.timezone);
    datetime -= other;
    return datetime;
}

Datetime& Datetime::operator+=(Time time)
{
    Time::operator+=(std::move(time));
    return *this;
}

Datetime &Datetime::operator-=(Time time)
{
    Time::operator-=(std::move(time));
    return *this;
}

size_t Datetime::to_ms(std::optional<Timezone> timezone) const
{
    // Create datetime copy to convert incase we need to change timezone.
    Datetime datetime = Datetime(*this);
    if (timezone.has_value())
        datetime.set_timezone(timezone.value());

    size_t ret = 0;

    // Years.
    for (uint16_t y = 1970; y < datetime.year; ++y)
    {
        ret += (is_leap_year(y) ? MILLISECONDS_PER_LEAP_YEAR : MILLISECONDS_PER_NON_LEAP_YEAR);
    }

    // Months.
    for (uint8_t m = 1; m < datetime.month; ++m)
    {
        ret += max_days_in_month(m, year) * MILLISECONDS_PER_DAY;
    }

    // Days.
    ret += (day - 1) * MILLISECONDS_PER_DAY;

    // Hour.
    ret += datetime.hour * MILLISECONDS_PER_HOUR;

    // Minute.
    ret += datetime.minute * MILLISECONDS_PER_MINUTE;

    // Second.
    ret += datetime.second * MILLISECONDS_PER_SECOND;

    // Millisecond.
    ret += datetime.millisecond;

    return ret;
}

const size_t Datetime::MILLISECONDS_PER_DAY = MILLISECONDS_PER_HOUR * 24;
const size_t Datetime::MILLISECONDS_PER_NON_LEAP_YEAR = MILLISECONDS_PER_DAY * 365;
const size_t Datetime::MILLISECONDS_PER_LEAP_YEAR = MILLISECONDS_PER_NON_LEAP_YEAR + MILLISECONDS_PER_DAY;
