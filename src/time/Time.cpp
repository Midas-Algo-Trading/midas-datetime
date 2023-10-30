#include "datetime/time/Time.h"
#include "fmt/format.h"
#include <chrono>
#include <iostream>

Timezone Time::default_timezone = TZ::EST;

Time Time::now(uint8_t hour_offset, uint8_t minute_offset, uint8_t second_offset,
               uint16_t millisecond_offset, uint16_t microsecond_offset,
               uint16_t nanosecond_offset, Timezone timezone)
{
    // Get the current local time
    std::time_t now = std::time(nullptr);
    std::tm local_tm = *std::localtime(&now);

    // Extract the different time components
    int hour = local_tm.tm_hour;
    int minute = local_tm.tm_min;
    int second = local_tm.tm_sec;

    auto currentTimePoint = std::chrono::high_resolution_clock::now() + std::chrono::hours(hour);

    // Convert the time point to nanoseconds
    auto nanoseconds = std::chrono::time_point_cast<std::chrono::nanoseconds>(currentTimePoint);

    // Extract the nanoseconds count
    auto nanosecondsCount = nanoseconds.time_since_epoch().count();

    // Calculate milliseconds, microseconds, and remaining nanoseconds
    int millisecond = static_cast<int>(nanosecondsCount / 1'000'000 % 1'000);
    int microsecond = static_cast<int>(nanosecondsCount / 1'000 % 1'000);
    int nanosecond = static_cast<int>(nanosecondsCount % 1'000);

    Time time = Time(hour + hour_offset,
                     minute + minute_offset,
                     second + second_offset,
                     millisecond + millisecond_offset,
                     microsecond + microsecond_offset,
                     nanosecond + nanosecond_offset,
                     TZ::LOCAL); // Gets the time in local time, so Timezone must be TZ::LOCAL

    ASSERT(time.is_valid_time(),
           std::invalid_argument(fmt::format("Time '{}' is invalid", time.to_string())));

    time.set_timezone(timezone); // Set the local time to 'timezone'.


    return time;
}

std::ostream& operator<<(std::ostream& os, const Time& time)
{
    return os << time.to_string();
}

Time& Time::operator+=(const Hour& hours)
{
    add_hours(hours.value);
    return *this;
}

Time& Time::operator-=(const Hour& hours)
{
    add_hours(-hours.value);
    return *this;
}

Time& Time::operator+=(const Minute& minutes)
{
    add_minutes(minutes.value);
    return *this;
}

Time& Time::operator-=(const Minute& minutes)
{
    add_minutes(-minutes.value);
    return *this;
}

Time& Time::operator+=(const Second& seconds)
{
    add_seconds(seconds.value);
    return *this;
}

Time& Time::operator-=(const Second& seconds)
{
    add_seconds(-seconds.value);
    return *this;
}

Time& Time::operator+=(const Millisecond& milliseconds)
{
    add_milliseconds(milliseconds.value);
    return *this;
}

Time& Time::operator-=(const Millisecond& milliseconds)
{
    add_milliseconds(-milliseconds.value);
    return *this;
}

Time& Time::operator+=(const Microsecond& microseconds)
{
    add_microseconds(microseconds.value);
    return *this;
}

Time& Time::operator-=(const Microsecond& microseconds)
{
    add_microseconds(-microseconds.value);
    return *this;
}

Time& Time::operator+=(const Nanosecond& nanoseconds)
{
    add_nanoseconds(nanoseconds.value);
    return *this;
}

Time& Time::operator-=(const Nanosecond& nanoseconds)
{
    add_nanoseconds(-nanoseconds.value);
    return *this;
}

const size_t Time::MINUTES_PER_HOUR = 60;
const size_t Time::SECONDS_PER_MINUTE = 60;
const size_t Time::SECONDS_PER_HOUR = MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
const size_t Time::MILLISECONDS_PER_SECOND = 1'000;
const size_t Time::MILLISECONDS_PER_HOUR = SECONDS_PER_HOUR * MILLISECONDS_PER_SECOND;
const size_t Time::MILLISECONDS_PER_MINUTE = SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND;
const size_t Time::MICROSECONDS_PER_MILLISECOND = 1'000;
const size_t Time::MICROSECONDS_PER_HOUR = MILLISECONDS_PER_HOUR * MICROSECONDS_PER_MILLISECOND;
const size_t Time::MICROSECONDS_PER_MINUTE = MILLISECONDS_PER_MINUTE
                                             * MICROSECONDS_PER_MILLISECOND;
const size_t Time::MICROSECONDS_PER_SECOND = MILLISECONDS_PER_SECOND
                                             * MICROSECONDS_PER_MILLISECOND;
const size_t Time::NANOSECONDS_PER_MICROSECOND = 1'000;
const size_t Time::NANOSECONDS_PER_HOUR = MICROSECONDS_PER_HOUR * NANOSECONDS_PER_MICROSECOND;
const size_t Time::NANOSECONDS_PER_MINUTE = MICROSECONDS_PER_MINUTE * NANOSECONDS_PER_MICROSECOND;
const size_t Time::NANOSECONDS_PER_SECOND = MICROSECONDS_PER_SECOND * NANOSECONDS_PER_MICROSECOND;
const size_t Time::NANOSECONDS_PER_MILLISECOND = MICROSECONDS_PER_MILLISECOND
                                                 * NANOSECONDS_PER_MICROSECOND;

const int Time::HOURS_PER_DAY = 24;

void Time::add_hours(int64_t hours_to_add)
{
    int new_hour = static_cast<int>((static_cast<int64_t>(hour) + hours_to_add) % HOURS_PER_DAY);

    if (new_hour < 0)
        throw std::out_of_range("Time cannot be negative");

    hour = static_cast<uint8_t>(new_hour);
}

void Time::add_minutes(int64_t minutes_to_add)
{
    int64_t new_total_minutes = total_minutes() + minutes_to_add;
    int64_t new_total_hours = static_cast<int>(new_total_minutes / static_cast<int64_t>(MINUTES_PER_HOUR));
    int64_t hour_change = new_total_hours - hour;
    int new_minute = static_cast<int>(new_total_minutes % static_cast<int64_t>(MINUTES_PER_HOUR));
    if (new_minute < 0)
    {
        new_minute += MINUTES_PER_HOUR;
        hour_change--;
    }
    minute = new_minute;
    add_hours(hour_change);
}

void Time::add_seconds(int64_t seconds_to_add)
{
    int64_t new_total_seconds = total_seconds() + seconds_to_add;
    int64_t new_total_minutes = static_cast<int>(new_total_seconds / static_cast<int64_t>(SECONDS_PER_MINUTE));
    int64_t minute_change = new_total_minutes - total_minutes();
    int new_second = static_cast<int>(new_total_seconds % static_cast<int64_t>(SECONDS_PER_MINUTE));
    if (new_second < 0)
    {
        new_second += SECONDS_PER_MINUTE;
        minute_change--;
    }
    second = new_second;
    add_minutes(minute_change);
}

void Time::add_milliseconds(int64_t milliseconds_to_add)
{
    int64_t new_total_milliseconds = total_milliseconds() + milliseconds_to_add;
    int new_total_seconds = static_cast<int>(new_total_milliseconds / static_cast<int64_t>
    (MILLISECONDS_PER_SECOND));
    int second_change = new_total_seconds - total_seconds();
    int new_millisecond = static_cast<int>(new_total_milliseconds % static_cast<int64_t>
    (MILLISECONDS_PER_SECOND));
    if (new_millisecond < 0)
    {
        new_millisecond += MILLISECONDS_PER_SECOND;
        second_change--;
    }
    millisecond = new_millisecond;
    add_seconds(static_cast<int>(second_change));
}

void Time::add_microseconds(int64_t microseconds_to_add)
{
    int64_t new_total_microseconds = total_microseconds() + microseconds_to_add;
    int64_t new_total_milliseconds = new_total_microseconds / static_cast<int64_t>(MICROSECONDS_PER_MILLISECOND);
    int64_t millisecond_change = new_total_milliseconds - total_milliseconds();
    int new_microsecond = static_cast<int>(new_total_microseconds % static_cast<int64_t>
    (MICROSECONDS_PER_MILLISECOND));
    if (new_microsecond < 0)
    {
        new_microsecond += MICROSECONDS_PER_MILLISECOND;
        millisecond_change--;
    }
    microsecond = new_microsecond;
    add_milliseconds(static_cast<int>(millisecond_change));
}

void Time::add_nanoseconds(int64_t nanoseconds_to_add)
{
    int64_t new_total_nanoseconds = total_nanoseconds() + nanoseconds_to_add;
    int64_t new_total_microseconds = new_total_nanoseconds / static_cast<int64_t>(NANOSECONDS_PER_MICROSECOND);
    int64_t microsecond_change = new_total_microseconds - total_microseconds();
    int new_nanosecond = static_cast<int>(new_total_nanoseconds % static_cast<int64_t>
    (NANOSECONDS_PER_MICROSECOND));
    if (new_nanosecond < 0)
    {
        new_nanosecond += NANOSECONDS_PER_MICROSECOND;
        microsecond_change--;
    }
    nanosecond = new_nanosecond;
    add_microseconds(static_cast<int>(microsecond_change));
}

void Time::set_default_timezone(Timezone timezone)
{
    default_timezone = timezone;
}

void Time::set_timezone(Timezone new_timezone)
{
    (*this) += Hour(timezone.get_utc_offset_diff(new_timezone));
    timezone = new_timezone;
}

bool Time::operator>(Time other) const
{
    other.set_timezone(timezone);

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

bool Time::operator>=(Time other) const
{
    other.set_timezone(timezone);

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

bool Time::operator<(Time other) const
{
    other.set_timezone(timezone);

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

bool Time::operator<=(Time other) const
{
    other.set_timezone(timezone);

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

bool Time::operator==(Time other) const
{
    other.set_timezone(timezone);

    return    hour == other.hour
              && minute == other.minute
              && second == other.second
              && millisecond == other.millisecond
              && microsecond == other.microsecond
              && nanosecond == other.nanosecond;
}

bool Time::operator!=(Time other) const
{
    other.set_timezone(timezone);
    
    return    hour != other.hour
              || minute != other.minute
              || second != other.second
              || millisecond != other.millisecond
              || microsecond != other.microsecond
              || nanosecond != other.nanosecond;
}

Time::Time(uint8_t hour, uint8_t minute, uint8_t second, uint16_t millisecond, uint16_t microsecond,
           uint16_t nanosecond, Timezone timezone) :
        hour(hour),
        minute(minute),
        second(second),
        millisecond(millisecond),
        microsecond(microsecond),
        nanosecond(nanosecond),
        timezone(timezone)
{
    ASSERT(is_valid_time(),
           std::invalid_argument(fmt::format("Time '{}' is invalid", Time::to_string())));
}

Time& Time::round(Component to)
{
    if (to == NANOSECOND)
        return *this;

    if (nanosecond >= NANOSECONDS_PER_MICROSECOND / 2)
        add_microseconds(1);
    nanosecond = 0;

    if (to == MICROSECOND)
        return *this;

    if (microsecond >= MICROSECONDS_PER_MILLISECOND / 2)
        add_milliseconds(1);
    microsecond = 0;

    if (to == MILLISECOND)
        return *this;

    if (millisecond >= MILLISECONDS_PER_SECOND / 2)
        add_seconds(1);
    millisecond = 0;

    if (to == SECOND)
        return *this;

    if (second >= SECONDS_PER_MINUTE / 2)
        add_minutes(1);
    second = 0;

    if (to == MINUTE)
        return *this;

    if (minute >= MINUTES_PER_HOUR / 2)
        add_hours(1);
    minute = 0;

    return *this;
}

Time& Time::ceil(Time::Component to)
{
    if (to == NANOSECOND)
        return *this;

    if (nanosecond > 0)
        add_microseconds(1);
    nanosecond = 0;

    if (to == MICROSECOND)
        return *this;

    if (microsecond > 0)
        add_milliseconds(1);
    microsecond = 0;

    if (to == MILLISECOND)
        return *this;

    if (millisecond > 0)
        add_seconds(1);
    millisecond = 0;

    if (to == SECOND)
        return *this;

    if (second > 0)
        add_minutes(1);
    second = 0;

    if (to == MINUTE)
        return *this;

    if (minute > 0)
        add_hours(1);
    minute = 0;

    return *this;
}

Time& Time::floor(Time::Component to)
{
    if (to == NANOSECOND)
        return *this;
    nanosecond = 0;
    if (to == MICROSECOND)
        return *this;
    microsecond = 0;
    if (to == MILLISECOND)
        return *this;
    millisecond = 0;
    if (to == SECOND)
        return *this;
    second = 0;
    if (to == MINUTE)
        return *this;
    minute = 0;
    return *this;
}

int Time::total_minutes() const
{
    return static_cast<int>(
            hour * MINUTES_PER_HOUR
            + minute
    );
}

int Time::total_seconds() const
{
    return static_cast<int>(
            hour * SECONDS_PER_HOUR
            + minute * SECONDS_PER_MINUTE
            + second
    );
}

int64_t Time::total_milliseconds() const
{
    return static_cast<int64_t>(
            hour * MILLISECONDS_PER_HOUR
            + minute * MILLISECONDS_PER_MINUTE
            + second * MILLISECONDS_PER_SECOND
            + millisecond
    );
}

int64_t Time::total_microseconds() const
{
    return static_cast<int64_t>(
            hour * MICROSECONDS_PER_HOUR
            + minute * MICROSECONDS_PER_MINUTE
            + second * MICROSECONDS_PER_SECOND
            + millisecond * MICROSECONDS_PER_MILLISECOND
            + microsecond
    );
}

int64_t Time::total_nanoseconds() const
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

std::string Time::to_string() const
{
    return std::to_string(hour)
           + ':' + strh::align(std::to_string(minute), strh::Alignment::LEFT, 2, '0')
           + ':' + strh::align(std::to_string(second), strh::Alignment::LEFT, 2, '0')
           + '.' + std::to_string(millisecond)
           + '.' + std::to_string(microsecond)
           + '.' + std::to_string(nanosecond);
}

bool Time::is_valid_time() const
{
    return is_valid_hour() && is_valid_minute() && is_valid_second() && is_valid_millisecond()
           && is_valid_microsecond() && is_valid_nanosecond();
}

bool Time::is_valid_hour() const
{
    return hour < HOURS_PER_DAY && hour >= 0;
}

bool Time::is_valid_minute() const
{
    return minute < MINUTES_PER_HOUR && minute >= 0;
}

bool Time::is_valid_second() const
{
    return second < SECONDS_PER_MINUTE && second >= 0;
}

bool Time::is_valid_millisecond() const
{
    return millisecond < MILLISECONDS_PER_SECOND && millisecond >= 0;
}

bool Time::is_valid_microsecond() const
{
    return microsecond < MICROSECONDS_PER_MILLISECOND && microsecond >= 0;
}

bool Time::is_valid_nanosecond() const
{
    return nanosecond < NANOSECONDS_PER_MICROSECOND && nanosecond >= 0;
}

Time operator+(Time time, Time other)
{
    other.set_timezone(time.timezone);

    time += Nanosecond(other.nanosecond);
    time += Microsecond(other.microsecond);
    time += Millisecond(other.millisecond);
    time += Second(other.second);
    time += Minute(other.minute);
    time += Hour(other.hour);
    return time;
}

Time operator-(Time time, Time other)
{
    other.set_timezone(time.timezone);

    time -= Hour(other.hour);
    time -= Minute(other.minute);
    time -= Second(other.second);
    time -= Millisecond(other.millisecond);
    time -= Microsecond(other.microsecond);
    time -= Nanosecond(other.nanosecond);
    return time;
}

Time& Time::operator+=(Time other)
{
    other.set_timezone(timezone);

    (*this) += Nanosecond(other.nanosecond);
    (*this) += Microsecond(other.microsecond);
    (*this) += Millisecond(other.millisecond);
    (*this) += Second(other.second);
    (*this) += Minute(other.minute);
    (*this) += Hour(other.hour);
    return (*this);
}

Time &Time::operator-=(Time other)
{
    other.set_timezone(timezone);

    (*this) -= Hour(other.hour);
    (*this) -= Minute(other.minute);
    (*this) -= Second(other.second);
    (*this) -= Millisecond(other.millisecond);
    (*this) -= Microsecond(other.microsecond);
    (*this) -= Nanosecond(other.nanosecond);
    return (*this);
}

Time operator+(Time time, const Hour& hours)
{
    time += hours;
    return time;
}

Time operator-(Time time, const Hour& hours)
{
    time -= hours;
    return time;
}

Time operator+(Time time, const Minute& minutes)
{
    time += minutes;
    return time;
}

Time operator-(Time time, const Minute& minutes)
{
    time -= minutes;
    return time;
}

Time operator+(Time time, const Second& seconds)
{
    time += seconds;
    return time;
}

Time operator-(Time time, const Second& seconds)
{
    time -= seconds;
    return time;
}

Time operator+(Time time, const Millisecond& milliseconds)
{
    time += milliseconds;
    return time;
}

Time operator-(Time time, const Millisecond& milliseconds)
{
    time -= milliseconds;
    return time;
}

Time operator+(Time time, const Microsecond& microseconds)
{
    time += microseconds;
    return time;
}

Time operator-(Time time, const Microsecond& microseconds)
{
    time -= microseconds;
    return time;
}

Time operator+(Time time, const Nanosecond& nanoseconds)
{
    time += nanoseconds;
    return time;
}

Time operator-(Time time, const Nanosecond& nanoseconds)
{
    time -= nanoseconds;
    return time;
}
