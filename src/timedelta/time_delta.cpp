#include "datetime/timedelta/timedelta.h"
#include <fmt/format.h>

std::ostream& operator<<(std::ostream& os, const TimeDelta& time_delta)
{
    return os << fmt::format("{} days, {}", time_delta.days, time_delta.to_string());
}

bool TimeDelta::operator>(TimeDelta other) const
{
    return days > other.days
           || days == other.days && BasicTime::operator>(other);
}

bool TimeDelta::operator>=(TimeDelta other) const
{
    return days >= other.days
           || days == other.days && BasicTime::operator>=(other);
}

bool TimeDelta::operator==(TimeDelta other) const
{
    return days == other.days && BasicTime::operator==(other);
}

bool TimeDelta::operator!=(TimeDelta other) const
{
    return days != other.days || BasicTime::operator!=(other);
}

bool TimeDelta::operator<=(TimeDelta other) const
{
    return days <= other.days
           || days == other.days && BasicTime::operator<=(other);
}

bool TimeDelta::operator<(TimeDelta other) const
{
    return days < other.days
           || days == other.days && BasicTime::operator<(other);
}

int TimeDelta::total_hours() const
{
    return hour + days * HOURS_PER_DAY;
}

int TimeDelta::total_minutes() const
{
    return BasicTime::total_minutes() + days * HOURS_PER_DAY * MINUTES_PER_HOUR;
}

int TimeDelta::total_seconds() const
{
    return BasicTime::total_seconds() + days * HOURS_PER_DAY * SECONDS_PER_HOUR;
}

int64_t TimeDelta::total_milliseconds() const
{
    return BasicTime::total_milliseconds() + days * HOURS_PER_DAY * MILLISECONDS_PER_HOUR;
}

int64_t TimeDelta::total_microseconds() const
{
    return BasicTime::total_microseconds() + days * HOURS_PER_DAY * MICROSECONDS_PER_HOUR;
}

int64_t TimeDelta::total_nanoseconds() const
{
    return BasicTime::total_nanoseconds() + days * HOURS_PER_DAY * NANOSECONDS_PER_HOUR;
}

TimeDelta &TimeDelta::abs()
{
    days = std::abs(days);
    return *this;
}
