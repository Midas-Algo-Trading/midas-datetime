#include "Time.h"
#include "../util/string_util.h"
#include <chrono>
#include <iostream>

Timezone Time::default_timezone = get_local_timezone();

Time Time::now(Timezone timezone)
{
        // Get the current local time
        std::time_t now = std::time(nullptr);
        std::tm local_tm = *std::localtime(&now);

        // Extract the different time components
        int hour = local_tm.tm_hour;
        int minute = local_tm.tm_min;
        int second = local_tm.tm_sec;

        // Set hour from system timezone to timezone
        hour += get_local_timezone().get_utc_offset_diff(timezone);

        // Get the current system clock time
        auto system_time = std::chrono::system_clock::now();

        // Calculate the time difference between the system clock time and the local time
        auto system_time_today = system_time
                               - std::chrono::system_clock::from_time_t(std::mktime(&local_tm));

        // Extract the values of the different components
        auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(system_time_today);
        auto ns = std::chrono::duration_cast<std::chrono::nanoseconds>(system_time_today);
        auto us = std::chrono::duration_cast<std::chrono::microseconds>(system_time_today);

        // Extract the values of the millisecond, microsecond, and nanosecond

        int millisecond = static_cast<int>(ms.count());

        int microsecond = static_cast<int>(
                us.count()
              - (millisecond * MICROSECONDS_PER_MILLISECOND)
        );

        int nanosecond = static_cast<int>(
                ns.count()
              - (millisecond * NANOSECONDS_PER_MILLISECOND)
              - (microsecond * NANOSECONDS_PER_MICROSECOND)
        );

        return Time(hour, minute, second, millisecond, microsecond, nanosecond);

}

//////////////////////////////////////////////////
// Public Friend Methods
//////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Time &time)
{
        return os
        << time.hour
        << ':'
        << lpad(std::to_string(time.minute), 2, '0')
        << ':'
        << lpad(std::to_string(time.second), 2, '0')
        << '.'
        << time.millisecond
        << '.'
        << time.microsecond
        << '.'
        << time.nanosecond;
}

Time &Time::operator+=(const Hour& hours)
{
        add_hours(hours);
        return *this;
}

Time &Time::operator-=(const Hour& hours)
{
        add_hours(-hours);
        return *this;
}

Time &Time::operator+=(const Minute& minutes)
{
        add_minutes(minutes);
        return *this;
}

Time &Time::operator-=(const Minute& minutes)
{
        add_minutes(-minutes);
        return *this;
}

Time &Time::operator+=(const Second& seconds)
{
        add_seconds(seconds);
        return *this;
}

Time &Time::operator-=(const Second& seconds)
{
        add_seconds(-seconds);
        return *this;
}

Time &Time::operator+=(const Millisecond& milliseconds)
{
        add_milliseconds(milliseconds);
        return *this;
}

Time &Time::operator-=(const Millisecond& milliseconds)
{
        add_milliseconds(-milliseconds);
        return *this;
}

Time &Time::operator+=(const Microsecond& microseconds)
{
        add_microseconds(microseconds);
        return *this;
}

Time &Time::operator-=(const Microsecond& microseconds)
{
        add_microseconds(-microseconds);
        return *this;
}

Time &Time::operator+=(const Nanosecond& nanoseconds)
{
        add_nanoseconds(nanoseconds);
        return *this;
}

Time &Time::operator-=(const Nanosecond& nanoseconds)
{
        add_nanoseconds(-nanoseconds);
        return *this;
}

const int Time::MINUTES_PER_HOUR = 60;
const int Time::SECONDS_PER_MINUTE = 60;
const int Time::SECONDS_PER_HOUR = MINUTES_PER_HOUR * SECONDS_PER_MINUTE;
const int Time::MILLISECONDS_PER_SECOND = 1'000;
const uint64_t Time::MILLISECONDS_PER_HOUR = SECONDS_PER_HOUR * MILLISECONDS_PER_SECOND;
const uint64_t Time::MILLISECONDS_PER_MINUTE = SECONDS_PER_MINUTE * MILLISECONDS_PER_SECOND;
const int Time::MICROSECONDS_PER_MILLISECOND = 1'000;
const uint64_t Time::MICROSECONDS_PER_HOUR = MILLISECONDS_PER_HOUR * MICROSECONDS_PER_MILLISECOND;
const uint64_t Time::MICROSECONDS_PER_MINUTE = MILLISECONDS_PER_MINUTE * MICROSECONDS_PER_MILLISECOND;
const uint64_t Time::MICROSECONDS_PER_SECOND = MILLISECONDS_PER_SECOND * MICROSECONDS_PER_MILLISECOND;
const int Time::NANOSECONDS_PER_MICROSECOND = 1'000;
const uint64_t Time::NANOSECONDS_PER_HOUR = MICROSECONDS_PER_HOUR * NANOSECONDS_PER_MICROSECOND;
const uint64_t Time::NANOSECONDS_PER_MINUTE = MICROSECONDS_PER_MINUTE * NANOSECONDS_PER_MICROSECOND;
const uint64_t Time::NANOSECONDS_PER_SECOND = MICROSECONDS_PER_SECOND * NANOSECONDS_PER_MICROSECOND;
const uint64_t Time::NANOSECONDS_PER_MILLISECOND = MICROSECONDS_PER_MILLISECOND * NANOSECONDS_PER_MICROSECOND;

const int Time::HOURS_PER_DAY = 24;

void Time::add_hours(int hours_to_add)
{
        hour += hours_to_add;
}

void Time::add_minutes(int minutes_to_add)
{
        int new_total_minutes = (hour * MINUTES_PER_HOUR) + minutes_to_add;
        int new_hour = new_total_minutes / MINUTES_PER_HOUR;
        if (new_hour != hour)
        {
                int hour_change = new_hour - hour;
                add_hours(hour_change);
        }
        minute = new_total_minutes % MINUTES_PER_HOUR;
}

void Time::add_seconds(int seconds_to_add)
{
        int new_total_second = hour * SECONDS_PER_HOUR
                             + minute * SECONDS_PER_MINUTE
                             + second
                             + seconds_to_add;
        int new_minute = static_cast<int>(new_total_second / SECONDS_PER_MINUTE);
        if (new_minute != minute)
        {
                int minute_change = new_minute - minute;
                add_minutes(minute_change);
        }
        second = static_cast<int>(new_total_second % SECONDS_PER_MINUTE);
}

void Time::add_milliseconds(uint64_t milliseconds_to_add)
{
        uint64_t new_total_millisecond = hour * MILLISECONDS_PER_HOUR
                                       + minute * MILLISECONDS_PER_MINUTE
                                       + second * MILLISECONDS_PER_SECOND
                                       + millisecond
                                       + milliseconds_to_add;
        int new_second = static_cast<int>(new_total_millisecond / MILLISECONDS_PER_SECOND);
        if (new_second != second)
        {
                int second_change = new_second - second;
                add_seconds(second_change);
        }
        second = static_cast<int>(new_total_millisecond % MILLISECONDS_PER_SECOND);
}

void Time::add_microseconds(uint64_t microseconds_to_add)
{
        uint64_t new_total_microsecond =   hour * MICROSECONDS_PER_HOUR
                                         + minute * MICROSECONDS_PER_MINUTE
                                         + second * MICROSECONDS_PER_SECOND
                                         + millisecond * MICROSECONDS_PER_MILLISECOND
                                         + microsecond
                                         + microseconds_to_add;
        uint64_t new_millisecond = new_total_microsecond / MICROSECONDS_PER_MILLISECOND;
        if (new_millisecond != microsecond)
        {
                uint64_t millisecond_change = new_millisecond - microsecond;
                add_milliseconds(millisecond_change);
        }
        microsecond = static_cast<int>(new_total_microsecond % MICROSECONDS_PER_MILLISECOND);
}

void Time::add_nanoseconds(uint64_t nanoseconds_to_add)
{
        uint64_t new_total_nanoseconds =   hour * NANOSECONDS_PER_HOUR
                                         + minute * NANOSECONDS_PER_MINUTE
                                         + second * NANOSECONDS_PER_SECOND
                                         + microsecond * NANOSECONDS_PER_MILLISECOND
                                         + microsecond * NANOSECONDS_PER_MICROSECOND
                                         + nanosecond
                                         + nanoseconds_to_add;
        uint64_t new_microsecond = new_total_nanoseconds / NANOSECONDS_PER_MICROSECOND;
        if (new_microsecond != microsecond)
        {
                uint64_t microsecond_change = new_microsecond - microsecond;
                add_microseconds(microsecond_change);
        }
        nanosecond = static_cast<int>(new_total_nanoseconds % NANOSECONDS_PER_MICROSECOND);
}

void Time::set_default_timezone(Timezone timezone)
{
        default_timezone = timezone;
}

void Time::set_timezone(Timezone new_timezone)
{
        hour += timezone.get_utc_offset_diff(new_timezone);
        hour %= HOURS_PER_DAY;
        timezone = new_timezone;
}

bool Time::operator>(const Time& other) const
{
        return hour > other.get_hour_at_timezone(timezone)
            || minute > other.minute
            || second > other.second
            || millisecond > other.millisecond
            || microsecond > other.microsecond
            || nanosecond > other.nanosecond;
}

bool Time::operator>=(const Time& other) const
{
        return hour >= other.get_hour_at_timezone(timezone)
            || minute >= other.minute
            || second >= other.second
            || millisecond >= other.millisecond
            || microsecond >= other.microsecond
            || nanosecond >= other.nanosecond;
}

bool Time::operator<(const Time& other) const
{
        return hour < other.get_hour_at_timezone(timezone)
            || minute < other.minute
            || second < other.second
            || millisecond < other.millisecond
            || microsecond < other.microsecond
            || nanosecond < other.nanosecond;
}

bool Time::operator<=(const Time& other) const
{
        return hour <= other.get_hour_at_timezone(timezone)
            || minute <= other.minute
            || second <= other.second
            || millisecond <= other.millisecond
            || microsecond <= other.microsecond
            || nanosecond <= other.nanosecond;
}

bool Time::operator==(const Time& other) const
{

        return hour == other.get_hour_at_timezone(timezone)
            && minute == other.minute
            && second == other.second
            && millisecond == other.millisecond
            && microsecond == other.microsecond
            && nanosecond == other.nanosecond;
}

bool Time::operator!=(const Time& other) const
{
        return hour != other.get_hour_at_timezone(timezone)
            || minute != other.minute
            || second != other.second
            || millisecond != other.millisecond
            || microsecond != other.microsecond
            || nanosecond != other.nanosecond;
}

int Time::get_hour_at_timezone(Timezone timezone) const
{
        if (this->timezone == timezone)
                return hour;

        return (hour + this->timezone.get_utc_offset_diff(timezone))
               % HOURS_PER_DAY;
}

