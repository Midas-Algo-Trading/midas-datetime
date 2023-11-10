#include "datetime/timedelta/TimeDelta.h"



Time TimeDelta::time() const
{
    return Time(hour, minute, second, millisecond, microsecond, nanosecond, timezone);
}

std::ostream &operator<<(std::ostream& os, const TimeDelta& time_delta)
{
    return os << fmt::format("{} days, {}", time_delta.days, time_delta.time().to_string());
}

bool TimeDelta::operator>(TimeDelta other) const
{
    return days > other.days
           || days == other.days && time() > other.time();
}

bool TimeDelta::operator>=(TimeDelta other) const
{
    return days >= other.days
           || days == other.days && time() >= other.time();
}

bool TimeDelta::operator==(TimeDelta other) const
{
    return days == other.days && time() == other.time();
}

bool TimeDelta::operator!=(TimeDelta other) const
{
    return days != other.days || time() != other.time();
}

bool TimeDelta::operator<=(TimeDelta other) const
{
    return days <= other.days
           || days == other.days && time() <= other.time();
}

bool TimeDelta::operator<(TimeDelta other) const
{
    return days < other.days
           || days == other.days && time() < other.time();
}