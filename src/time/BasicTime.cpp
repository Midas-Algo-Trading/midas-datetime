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

int BasicTime::total_minutes() const
{
    return static_cast<int>(
        hour * MINUTES_PER_HOUR
        + minute
    );
}

int BasicTime::total_seconds() const
{
    return static_cast<int>(
        hour * SECONDS_PER_HOUR
        + minute * SECONDS_PER_MINUTE
        + second
    );
}

int64_t BasicTime::total_milliseconds() const
{
    return static_cast<int64_t>(
        hour * MILLISECONDS_PER_HOUR
        + minute * MILLISECONDS_PER_MINUTE
        + second * MILLISECONDS_PER_SECOND
        + millisecond
    );
}

int64_t BasicTime::total_microseconds() const
{
    return static_cast<int64_t>(
        hour * MICROSECONDS_PER_HOUR
        + minute * MICROSECONDS_PER_MINUTE
        + second * MICROSECONDS_PER_SECOND
        + millisecond * MICROSECONDS_PER_MILLISECOND
        + microsecond
    );
}

int64_t BasicTime::total_nanoseconds() const
{
    return static_cast<int64_t>(
        hour * NANOSECONDS_PER_HOUR
        + minute * NANOSECONDS_PER_MINUTE
        + second * NANOSECONDS_PER_SECOND
        + millisecond * NANOSECONDS_PER_MILLISECOND
        + microsecond * NANOSECONDS_PER_MICROSECOND
        + nanosecond
    );
}

std::string BasicTime::to_string(TimeComponent include_to,
                                 char delim_h_m_s,
                                 char delim_ms_us_na) const
{
    std::stringstream ss;

    ss << static_cast<int>(hour);

    if (include_to == TimeComponent::HOUR) return ss.str();

    ss << delim_h_m_s << strh::align(std::to_string(minute), strh::Alignment::LEFT, 2, '0');

    if (include_to == TimeComponent::MINUTE) return ss.str();

    ss << delim_h_m_s << strh::align(std::to_string(second), strh::Alignment::LEFT, 2, '0');

    if (include_to == TimeComponent::SECOND) return ss.str();

    ss << delim_ms_us_na << static_cast<int>(millisecond);

    if (include_to == TimeComponent::MILLISECOND) return ss.str();

    ss << delim_ms_us_na << static_cast<int>(microsecond);

    if (include_to == TimeComponent::MICROSECOND) return ss.str();

    ss << delim_ms_us_na << static_cast<int>(nanosecond);

    return ss.str();
}

const int BasicTime::HOURS_PER_DAY = 24;

const size_t BasicTime::MINUTES_PER_HOUR = 60;
const size_t BasicTime::SECONDS_PER_MINUTE = 60;
const size_t BasicTime::SECONDS_PER_HOUR = MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
const size_t BasicTime::MILLISECONDS_PER_SECOND = 1'000;
const size_t BasicTime::MILLISECONDS_PER_HOUR = SECONDS_PER_HOUR * MILLISECONDS_PER_SECOND;
const size_t BasicTime::MILLISECONDS_PER_MINUTE = SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND;
const size_t BasicTime::MICROSECONDS_PER_MILLISECOND = 1'000;
const size_t BasicTime::MICROSECONDS_PER_HOUR = MILLISECONDS_PER_HOUR * MICROSECONDS_PER_MILLISECOND;
const size_t BasicTime::MICROSECONDS_PER_MINUTE = MILLISECONDS_PER_MINUTE
                                             * MICROSECONDS_PER_MILLISECOND;
const size_t BasicTime::MICROSECONDS_PER_SECOND = MILLISECONDS_PER_SECOND
                                             * MICROSECONDS_PER_MILLISECOND;
const size_t BasicTime::NANOSECONDS_PER_MICROSECOND = 1'000;
const size_t BasicTime::NANOSECONDS_PER_HOUR = MICROSECONDS_PER_HOUR * NANOSECONDS_PER_MICROSECOND;
const size_t BasicTime::NANOSECONDS_PER_MINUTE = MICROSECONDS_PER_MINUTE * NANOSECONDS_PER_MICROSECOND;
const size_t BasicTime::NANOSECONDS_PER_SECOND = MICROSECONDS_PER_SECOND * NANOSECONDS_PER_MICROSECOND;
const size_t BasicTime::NANOSECONDS_PER_MILLISECOND = MICROSECONDS_PER_MILLISECOND
                                                 * NANOSECONDS_PER_MICROSECOND;