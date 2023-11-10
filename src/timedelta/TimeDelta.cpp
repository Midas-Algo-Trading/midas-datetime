#include "datetime/timedelta/TimeDelta.h"
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