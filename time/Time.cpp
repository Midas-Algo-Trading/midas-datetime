#include "Time.h"
#include "../util/string_util.h"
#include <chrono>
#include <iostream>

//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

Time Time::now()
{
        auto now = std::chrono::system_clock::now();
        auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
        auto epoch = now_ns.time_since_epoch();
        uint64_t nanoseconds = (std::chrono::duration_cast<std::chrono::nanoseconds>(epoch) % std::chrono::seconds(1)).count();

        Hour hour = Hour(static_cast<int>(Hour::N_NANOSECONDS / nanoseconds));
        nanoseconds -= hour.duration;

        Minute minute = Minute(static_cast<int>(Minute::N_NANOSECONDS / nanoseconds));
        nanoseconds -= minute.duration;

        Second second = Second(static_cast<int>(Second::N_NANOSECONDS / nanoseconds));
        nanoseconds -= second.duration;

        Microsecond microsecond = Microsecond(static_cast<int>(Microsecond::N_NANOSECONDS / nanoseconds));
        nanoseconds -= microsecond.duration;

        Nanosecond nanosecond = Nanosecond(static_cast<int>(Nanosecond::N_NANOSECONDS / nanoseconds));

        return Time(hour, minute, second, microsecond, nanosecond);
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

void Time::add_microseconds(int microseconds_to_add)
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

void Time::add_nanoseconds(int nanoseconds_to_add)
{
        uint64_t new_total_nanoseconds =   hour * NANOSECONDS_PER_HOUR
                                         + minute * NANOSECONDS_PER_MINUTE
                                         + second * NANOSECONDS_PER_SECOND
                                         + microsecond * NANOSECONDS_PER_MICROSECOND
                                         + nanosecond
                                         + nanoseconds_to_add;
        int new_microsecond = static_cast<int>(new_total_nanoseconds / NANOSECONDS_PER_MICROSECOND);
        if (new_microsecond != microsecond)
        {
                int microsecond_change = new_microsecond - microsecond;
                add_microseconds(microsecond_change);
        }
        nanosecond = static_cast<int>(new_total_nanoseconds % NANOSECONDS_PER_MICROSECOND);
}
