#include <utility>

#include "datetime/datetime/Datetime.h"
#include "datetime/timedelta/TimeDelta.h"

Datetime Datetime::now(uint8_t  day_offset, uint8_t hour_offset, uint8_t minute_offset,
                       uint8_t second_offset, uint16_t millisecond_offset,
                       uint16_t microsecond_offset, uint16_t nanosecond_offset, Timezone timezone)
{
    return Datetime(Date::today(day_offset, timezone),
                    Time::now(hour_offset, minute_offset, second_offset, millisecond_offset,
                              microsecond_offset, nanosecond_offset, timezone));
}

int64_t Datetime::add_hours(int64_t hours_to_add)
{
    int64_t day_change = Time::add_hours(hours_to_add);

    if (day_change > 0)
        add_days(day_change);
    if (day_change < 0)
        subtract_days(-day_change);

    return day_change;
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

Datetime &Datetime::operator+=(const Hours& hours)
{
    Time::operator+=(hours);
    return *this;
}

Datetime &Datetime::operator-=(const Hours& hours)
{
    Time::operator-=(hours);
    return *this;
}

Datetime &Datetime::operator+=(const Minutes& minutes)
{
    Time::operator+=(minutes);
    return *this;
}

Datetime &Datetime::operator-=(const Minutes& minutes)
{
    Time::operator-=(minutes);
    return *this;
}

Datetime &Datetime::operator+=(const Seconds& seconds)
{
    Time::operator+=(seconds);
    return *this;
}

Datetime &Datetime::operator-=(const Seconds& seconds)
{
    Time::operator-=(seconds);
    return *this;
}

Datetime &Datetime::operator+=(const Milliseconds& milliseconds)
{
    Time::operator+=(milliseconds);
    return *this;
}

Datetime &Datetime::operator-=(const Milliseconds& milliseconds)
{
    Time::operator-=(milliseconds);
    return *this;
}

Datetime &Datetime::operator+=(const Microseconds& microseconds)
{
    Time::operator+=(microseconds);
    return *this;
}

Datetime &Datetime::operator-=(const Microseconds& microseconds)
{
    Time::operator-=(microseconds);
    return *this;
}

Datetime &Datetime::operator+=(const Nanoseconds& nanoseconds)
{
    Time::operator+=(nanoseconds);
    return *this;
}

Datetime &Datetime::operator-=(const Nanoseconds& nanoseconds)
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

    // Hours.
    uint8_t hour = timestamp / MILLISECONDS_PER_HOUR;
    timestamp %= MILLISECONDS_PER_HOUR;

    // Minutes.
    uint8_t minute = timestamp / MILLISECONDS_PER_MINUTE;
    timestamp %= MILLISECONDS_PER_MINUTE;

    // Seconds.
    uint8_t second = timestamp / MILLISECONDS_PER_SECOND;
    timestamp %= MILLISECONDS_PER_SECOND;

    // Milliseconds.
    uint16_t millisecond = timestamp;


    Datetime ret =
        Datetime(year, month, day+1, hour, minute, second, millisecond, 0, 0, from_timezone);

    ret.set_timezone(to_timezone);

    return ret;
}

Datetime operator+(Datetime datetime, const Hours& hours)
{
    datetime += hours;
    return datetime;
}

Datetime operator-(Datetime datetime, const Hours& hours)
{
    datetime -= hours;
    return datetime;
}

Datetime operator+(Datetime datetime, const Minutes& minutes)
{
    datetime += minutes;
    return datetime;
}

Datetime operator-(Datetime datetime, const Minutes& minutes)
{
    datetime -= minutes;
    return datetime;
}

Datetime operator+(Datetime datetime, const Seconds& seconds)
{
    datetime += seconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Seconds& seconds)
{
    datetime -= seconds;
    return datetime;
}

Datetime operator+(Datetime datetime, const Milliseconds& milliseconds)
{
    datetime += milliseconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Milliseconds& milliseconds)
{
    datetime -= milliseconds;
    return datetime;
}

Datetime operator+(Datetime datetime, const Microseconds& microseconds)
{
    datetime += microseconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Microseconds& microseconds)
{
    datetime -= microseconds;
    return datetime;
}

Datetime operator+(Datetime datetime, const Nanoseconds& nanoseconds)
{
    datetime += nanoseconds;
    return datetime;
}

Datetime operator-(Datetime datetime, const Nanoseconds& nanoseconds)
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
    TimeDelta time_delta = this->time() + std::move(time);
    nanosecond = time_delta.nanosecond;
    microsecond = time_delta.microsecond;
    millisecond = time_delta.millisecond;
    second = time_delta.second;
    minute = time_delta.minute;
    hour = time_delta.hour;
    (*this) += Day(time_delta.days);
    return *this;
}

Datetime& Datetime::operator-=(Time time)
{
    TimeDelta time_delta = this->time() - std::move(time);
    nanosecond = time_delta.nanosecond;
    microsecond = time_delta.microsecond;
    millisecond = time_delta.millisecond;
    second = time_delta.second;
    minute = time_delta.minute;
    hour = time_delta.hour;
    (*this) -= Day(-time_delta.days);
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

    // Hours.
    ret += datetime.hour * MILLISECONDS_PER_HOUR;

    // Minutes.
    ret += datetime.minute * MILLISECONDS_PER_MINUTE;

    // Seconds.
    ret += datetime.second * MILLISECONDS_PER_SECOND;

    // Milliseconds.
    ret += datetime.millisecond;

    return ret;
}

const size_t Datetime::MILLISECONDS_PER_DAY = MILLISECONDS_PER_HOUR * 24;
const size_t Datetime::MILLISECONDS_PER_NON_LEAP_YEAR = MILLISECONDS_PER_DAY * 365;
const size_t Datetime::MILLISECONDS_PER_LEAP_YEAR = MILLISECONDS_PER_NON_LEAP_YEAR + MILLISECONDS_PER_DAY;

Datetime& Datetime::operator+=(TimeDelta time_delta)
{
    (*this) += Day(time_delta.days);
    (*this) += Time(time_delta, timezone);
    return *this;
}

Datetime& Datetime::operator-=(TimeDelta time_delta)
{
    (*this) -= Day(time_delta.days);
    (*this) -= Time(time_delta, timezone);
    return *this;
}

Datetime operator+(Datetime datetime, TimeDelta time_delta)
{
    datetime += std::move(time_delta);
    return datetime;
}

Datetime operator-(Datetime datetime, TimeDelta time_delta)
{
    datetime -= std::move(time_delta);
    return datetime;
}

TimeDelta operator-(Datetime datetime, Datetime other)
{
    TimeDelta date_delta = datetime.date() - other.date();
    TimeDelta time_delta = datetime.time() - other.time();
    return TimeDelta(date_delta.days, time_delta.hour, time_delta.minute, time_delta.second,
                     time_delta.millisecond, time_delta.microsecond, time_delta.nanosecond);
}

