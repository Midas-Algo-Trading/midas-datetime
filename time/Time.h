#ifndef DATETIME_TIME_H
#define DATETIME_TIME_H

#include <iostream>
#include "components/Hour.h"
#include "components/Minute.h"
#include "components/Second.h"
#include "components/Microsecond.h"
#include "components/Nanosecond.h"

class Time
{
public:
        friend std::ostream &operator<<(std::ostream &os, const Time &time);

        int hour;
        int minute;
        int second;
        int microsecond;
        int nanosecond;

public:
        explicit Time(int hour=0, int minute=0, int second=0, int microsecond=0, int nanosecond=0) :
                hour(hour),
                minute(minute),
                second(second),
                microsecond(microsecond),
                nanosecond(nanosecond) {}

        static Time now();

        Time& operator+=(const Hour& hours);
        Time& operator-=(const Hour& hours);
        Time& operator+=(const Minute& minutes);
        Time& operator-=(const Minute& minutes);
        Time& operator+=(const Second& seconds);
        Time& operator-=(const Second& seconds);
        Time& operator+=(const Microsecond& microseconds);
        Time& operator-=(const Microsecond& microseconds);
        Time& operator+=(const Nanosecond& nanoseconds);
        Time& operator-=(const Nanosecond& nanoseconds);

protected:
        void add_hours(int hours_to_add);
        void add_minutes(int minutes_to_add);
        void add_seconds(int seconds_to_add);
        void add_microseconds(int microseconds_to_add);
        void add_nanoseconds(int nanoseconds_to_add);

private:
        static const int MINUTES_PER_HOUR;
        static const int SECONDS_PER_MINUTE;
        static const int SECONDS_PER_HOUR;
        static const int MICROSECONDS_PER_SECOND;
        static const uint64_t MICROSECONDS_PER_HOUR;
        static const uint64_t MICROSECONDS_PER_MINUTE;
        static const int NANOSECONDS_PER_MICROSECOND;
        static const uint64_t NANOSECONDS_PER_HOUR;
        static const uint64_t NANOSECONDS_PER_MINUTE;
        static const uint64_t NANOSECONDS_PER_SECOND;
};


#endif //DATETIME_TIME_H
