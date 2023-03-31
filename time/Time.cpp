#include "Time.h"
#include "../util/string_util.h"
#include <chrono>
#include <iostream>

//////////////////////////////////////////////////
// Public Constructors
//////////////////////////////////////////////////

Time::Time(long long nanoseconds_)
{
        long long used_nanoseconds = 0;

        hours = Hour(nanoseconds_, this);
        used_nanoseconds += hours.to_nanoseconds();

        minutes = Minute(nanoseconds_ - used_nanoseconds, this);
        used_nanoseconds += minutes.to_nanoseconds();

        seconds = Second(nanoseconds_ - used_nanoseconds, this);
        used_nanoseconds += seconds.to_nanoseconds();

        microseconds = Microsecond(nanoseconds_ - used_nanoseconds, this);
        used_nanoseconds += microseconds.to_nanoseconds();

        nanoseconds -= Nanosecond(nanoseconds_ - used_nanoseconds, this);

        component_hierarchy = {&nanoseconds, &microseconds, &seconds, &minutes, &hours};
}

//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

Time Time::now()
{
        auto now = std::chrono::system_clock::now();
        auto now_ns = std::chrono::time_point_cast<std::chrono::nanoseconds>(now);
        auto epoch = now_ns.time_since_epoch();
        auto today_nanoseconds = (std::chrono::duration_cast<std::chrono::nanoseconds>(epoch) % std::chrono::seconds(1)).count();
        return Time(today_nanoseconds);
}

//////////////////////////////////////////////////
// Public Friend Methods
//////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Time &time)
{
        return os
        << time.hours
        << ':'
        << lpad(std::to_string(time.minutes), 2, '0')
        << ':'
        << lpad(std::to_string(time.seconds), 2, '0')
        << '.'
        << time.microseconds
        << '.'
        << time.nanoseconds;
}