#include "Time.h"
#include <chrono>

//////////////////////////////////////////////////
// Public Constructors
//////////////////////////////////////////////////

Time::Time()
{
        // Get the current time
        auto now = std::chrono::system_clock::now();

        // Extract the current time in nanoseconds
        auto nanoseconds_since_epoch = std::chrono::duration_cast<std::chrono::nanoseconds>(now.time_since_epoch()).count();

        // Calculate the number of nanoseconds since midnight
        auto nanos_since_midnight = nanoseconds_since_epoch % (24 * 60LL * 60 * 1000000000);

        // Calculate component values
        int hours_value = (nanos_since_midnight / (60LL * 60 * 1000000000));
        int minutes_value = (hours_value * 60) - (nanos_since_midnight % (60LL * 60 * 1000000000) / (60LL * 1000000000));
        int seconds_value = (minutes_value * 60) - (nanos_since_midnight % (60LL * 1000000000)) / 1000000000;
        int microseconds_value = (seconds_value * 1000000) - (nanos_since_midnight % 1000000000) / 1000;
        int nanoseconds_value = (microseconds_value * 10000) - nanos_since_midnight;

        // Create components
        hours = Hour(hours_value, this);
        minutes = Minute(minutes_value, this);
        seconds = Second(seconds_value, this);
        microseconds = Microsecond(microseconds_value, this);
        nanoseconds = Nanosecond(nanoseconds_value, this);
}

//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

TimeComponent Time::get_component_by_idx(int idx)
{
        // Check if idx is in range of Time's components
        if (idx < 0 || idx > 4)
        {
                throw std::invalid_argument("idx must be between 0 and 4");
        }

        return component_hierarchy[idx];
}
