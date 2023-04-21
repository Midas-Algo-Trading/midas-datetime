#include "Time.h"
#include "../util/string_util.h"
#include <chrono>
#include <iostream>

 Timezone Time::default_timezone = UTC;

Time Time::now(Timezone timezone)
{
        // Get the current time point
        auto now = std::chrono::system_clock::now();
        // Convert the time point to a time_t object
        std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
        // Convert the time_t object to a tm struct
        std::tm now_tm = *std::localtime(&now_time_t);

        int hour = now_tm.tm_hour;
        int minute = now_tm.tm_min;
        int second = now_tm.tm_sec;

        // Set hour from system timezone to timezone
        hour += get_local_timezone().get_utc_offset_diff(timezone);

        std::tm tm_start_of_day = now_tm;
        tm_start_of_day.tm_hour = 0;
        tm_start_of_day.tm_min = 0;
        tm_start_of_day.tm_sec = 0;
        std::time_t time_t_start_of_day = std::mktime(&tm_start_of_day);
        auto start_of_day = std::chrono::system_clock::from_time_t(time_t_start_of_day);
        auto duration = now - start_of_day;

        int microsecond = static_cast<int>(std::chrono::duration_cast<std::chrono::microseconds>(duration).count() % MICROSECONDS_PER_SECOND);
        // TODO: I think this is incorrect
        int nanosecond = static_cast<int>(duration.count() % NANOSECONDS_PER_SECOND);

        return Time(hour, minute, second, microsecond, nanosecond,
                    get_local_timezone());
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
const int Time::MICROSECONDS_PER_SECOND = 1'000'000;
const uint64_t Time::MICROSECONDS_PER_HOUR = SECONDS_PER_HOUR * MICROSECONDS_PER_SECOND;
const uint64_t Time::MICROSECONDS_PER_MINUTE = SECONDS_PER_MINUTE * MICROSECONDS_PER_SECOND;
const int Time::NANOSECONDS_PER_MICROSECOND = 1'000;
const uint64_t Time::NANOSECONDS_PER_HOUR = MICROSECONDS_PER_HOUR * NANOSECONDS_PER_MICROSECOND;
const uint64_t Time::NANOSECONDS_PER_MINUTE = MICROSECONDS_PER_MINUTE * NANOSECONDS_PER_MICROSECOND;
const uint64_t Time::NANOSECONDS_PER_SECOND = MICROSECONDS_PER_SECOND * NANOSECONDS_PER_MICROSECOND;

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
        int new_total_second =   hour * SECONDS_PER_HOUR
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

void Time::add_microseconds(uint64_t microseconds_to_add)
{
        uint64_t new_total_microsecond =   hour * MICROSECONDS_PER_HOUR
                                         + minute * MICROSECONDS_PER_MINUTE
                                         + second * MICROSECONDS_PER_SECOND
                                         + microsecond
                                         + microseconds_to_add;
        int new_second = static_cast<int>(new_total_microsecond / MICROSECONDS_PER_SECOND);
        if (new_second != second)
        {
                int second_change = new_second - second;
                add_seconds(second_change);
        }
        microsecond = static_cast<int>(new_total_microsecond % MICROSECONDS_PER_SECOND);
}

void Time::add_nanoseconds(uint64_t nanoseconds_to_add)
{
        uint64_t new_total_nanoseconds =   hour * NANOSECONDS_PER_HOUR
                                         + minute * NANOSECONDS_PER_MINUTE
                                         + second * NANOSECONDS_PER_SECOND
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
        // Adjust other's hour to match this timezone
        int other_hour = other.hour;
        if (timezone != other.timezone)
                other_hour += (other_hour + other.timezone.get_utc_offset_diff(timezone)) % HOURS_PER_DAY;

        return hour > other_hour
            || minute > other.minute
            || second > other.second
            || microsecond > other.microsecond
            || nanosecond > other.nanosecond;
}

bool Time::operator>=(const Time& other) const
{
        // Adjust other's hour to match this timezone
        int other_hour = other.hour;
        if (timezone != other.timezone)
                other_hour += (other_hour + other.timezone.get_utc_offset_diff(timezone)) % HOURS_PER_DAY;

        return hour >= other_hour
            || minute >= other.minute
            || second >= other.second
            || microsecond >= other.microsecond
            || nanosecond >= other.nanosecond;
}

bool Time::operator<(const Time& other) const
{
        // Adjust other's hour to match this timezone
        int other_hour = other.hour;
        if (timezone != other.timezone)
                other_hour += (other_hour + other.timezone.get_utc_offset_diff(timezone)) % HOURS_PER_DAY;

        return hour < other_hour
            || minute < other.minute
            || second < other.second
            || microsecond < other.microsecond
            || nanosecond < other.nanosecond;
}

bool Time::operator<=(const Time& other) const
{
        // Adjust other's hour to match this timezone
        int other_hour = other.hour;
        if (timezone != other.timezone)
                other_hour += (other_hour + other.timezone.get_utc_offset_diff(timezone)) % HOURS_PER_DAY;

        return hour <= other_hour
            || minute <= other.minute
            || second <= other.second
            || microsecond <= other.microsecond
            || nanosecond <= other.nanosecond;
}

bool Time::operator==(const Time& other) const
{
        // Adjust other's hour to match this timezone
        int other_hour = other.hour;
        if (timezone != other.timezone)
                other_hour += (other_hour + other.timezone.get_utc_offset_diff(timezone)) % HOURS_PER_DAY;

        return hour == other_hour
            && minute == other.minute
            && second == other.second
            && microsecond == other.microsecond
            && nanosecond == other.nanosecond;
}

bool Time::operator!=(const Time& other) const
{
        // Adjust other's hour to match this timezone
        int other_hour = other.hour;
        if (timezone != other.timezone)
                other_hour += (other_hour + other.timezone.get_utc_offset_diff(timezone)) % HOURS_PER_DAY;

        return hour == other_hour
            && minute == other.minute
            && second == other.second
            && microsecond == other.microsecond
            && nanosecond == other.nanosecond;
}

