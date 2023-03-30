#include "Time.h"
#include <chrono>


//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

Time Time::now()
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

        // Create Time object
        return Time(hours_value, minutes_value, seconds_value, microseconds_value, nanoseconds_value);
}
