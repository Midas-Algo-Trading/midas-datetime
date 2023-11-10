#include "BasicTime.h"
#include <stringhelpers/stringhelpers.h>

bool BasicTime::operator>(BasicTime other) const
{
    return    hour > other.hour
              || hour == other.hour && minute > other.minute
              || hour == other.hour && minute == other.minute && second > other.second
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond > other.millisecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond > other.microsecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond == other.microsecond
                 && nanosecond > other.nanosecond;
}

bool BasicTime::operator>=(BasicTime other) const
{
    return    hour > other.hour
              || hour == other.hour && minute > other.minute
              || hour == other.hour && minute == other.minute && second > other.second
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond > other.millisecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond > other.microsecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond == other.microsecond
                 && nanosecond >= other.nanosecond;
}

bool BasicTime::operator<(BasicTime other) const
{
    return    hour < other.hour
              || hour == other.hour && minute < other.minute
              || hour == other.hour && minute == other.minute && second < other.second
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond < other.millisecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond < other.microsecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond == other.microsecond
                 && nanosecond < other.nanosecond;
}

bool BasicTime::operator<=(BasicTime other) const
{
    return    hour < other.hour
              || hour == other.hour && minute < other.minute
              || hour == other.hour && minute == other.minute && second < other.second
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond < other.millisecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond < other.microsecond
              || hour == other.hour && minute == other.minute && second == other.second
                 && millisecond == other.millisecond && microsecond == other.microsecond
                 && nanosecond <= other.nanosecond;
}

bool BasicTime::operator==(BasicTime other) const
{
    return    hour == other.hour
              && minute == other.minute
              && second == other.second
              && millisecond == other.millisecond
              && microsecond == other.microsecond
              && nanosecond == other.nanosecond;
}

bool BasicTime::operator!=(BasicTime other) const
{
    return    hour != other.hour
              || minute != other.minute
              || second != other.second
              || millisecond != other.millisecond
              || microsecond != other.microsecond
              || nanosecond != other.nanosecond;
}

std::string BasicTime::to_string(char separate_time, char separate_seconds) const
{
    return std::to_string(hour)
           + separate_time + strh::align(std::to_string(minute), strh::Alignment::LEFT, 2, '0')
           + separate_time + strh::align(std::to_string(second), strh::Alignment::LEFT, 2, '0')
           + separate_seconds + std::to_string(millisecond)
           + separate_seconds + std::to_string(microsecond)
           + separate_seconds + std::to_string(nanosecond);
}