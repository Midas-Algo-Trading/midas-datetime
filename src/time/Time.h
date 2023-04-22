#ifndef DATETIME_TIME_H
#define DATETIME_TIME_H

#include <iostream>
#include "components/Hour.h"
#include "components/Minute.h"
#include "components/Second.h"
#include "components/Microsecond.h"
#include "components/Nanosecond.h"
#include "Timezone.h"
#include "components/Millisecond.h"


class Time
{
public:
        friend std::ostream &operator<<(std::ostream &os, const Time &time);

        int hour;
        int minute;
        int second;
        int millisecond;
        int microsecond;
        int nanosecond;

        Timezone timezone;

        static Timezone default_timezone;

public:
        explicit Time(int hour=1, int minute=0, int second=0, int millisecond=0,
                      int microsecond=0, int nanosecond=0,
                      Timezone timezone=default_timezone) :
                hour(hour),
                minute(minute),
                second(second),
                millisecond(millisecond),
                microsecond(microsecond),
                nanosecond(nanosecond),
                timezone(timezone) {}

        static Time now(Timezone timezone=default_timezone);

        Time& operator+=(const Hour& hours);
        Time& operator-=(const Hour& hours);
        Time& operator+=(const Minute& minutes);
        Time& operator-=(const Minute& minutes);
        Time& operator+=(const Second& seconds);
        Time& operator-=(const Second& seconds);
        Time& operator+=(const Millisecond& milliseconds);
        Time& operator-=(const Millisecond& milliseconds);
        Time& operator+=(const Microsecond& microseconds);
        Time& operator-=(const Microsecond& microseconds);
        Time& operator+=(const Nanosecond& nanoseconds);
        Time& operator-=(const Nanosecond& nanoseconds);
        bool operator>(const Time& other) const;
        bool operator>=(const Time& other) const;
        bool operator<(const Time& other) const;
        bool operator<=(const Time& other) const;
        bool operator==(const Time& other) const;
        bool operator!=(const Time& other) const;

        void set_timezone(Timezone new_timezone);

        static void set_default_timezone(Timezone timezone);

        int get_hour_at_timezone(Timezone timezone) const;

        static const int HOURS_PER_DAY;

protected:
        virtual void add_hours(int hours_to_add);
        void add_minutes(int minutes_to_add);
        void add_seconds(int seconds_to_add);
        void add_milliseconds(uint64_t milliseconds_to_add);
        void add_microseconds(uint64_t microseconds_to_add);
        void add_nanoseconds(uint64_t nanoseconds_to_add);

private:
        static const int MINUTES_PER_HOUR;
        static const int SECONDS_PER_MINUTE;
        static const int SECONDS_PER_HOUR;
        static const int MILLISECONDS_PER_SECOND;
        static const uint64_t MILLISECONDS_PER_HOUR;
        static const uint64_t MILLISECONDS_PER_MINUTE;
        static const int MICROSECONDS_PER_MILLISECOND;
        static const uint64_t MICROSECONDS_PER_SECOND;
        static const uint64_t MICROSECONDS_PER_HOUR;
        static const uint64_t MICROSECONDS_PER_MINUTE;
        static const int NANOSECONDS_PER_MICROSECOND;
        static const uint64_t NANOSECONDS_PER_HOUR;
        static const uint64_t NANOSECONDS_PER_MINUTE;
        static const uint64_t NANOSECONDS_PER_SECOND;
        static const uint64_t NANOSECONDS_PER_MILLISECOND;
};


#endif //DATETIME_TIME_H
