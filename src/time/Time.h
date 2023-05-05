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
        explicit Time(int hour=0, int minute=0, int second=0, int millisecond=0,
                      int microsecond=0, int nanosecond=0,
                      Timezone timezone=default_timezone);

        static Time now(Timezone timezone=default_timezone);

        enum Component { HOUR, MINUTE, SECOND, MILLISECOND, MICROSECOND, NANOSECOND };

        virtual Time& operator+=(const Hour& hours);
        virtual Time& operator-=(const Hour& hours);
        virtual Time& operator+=(const Minute& minutes);
        virtual Time& operator-=(const Minute& minutes);
        virtual Time& operator+=(const Second& seconds);
        virtual Time& operator-=(const Second& seconds);
        virtual Time& operator+=(const Millisecond& milliseconds);
        virtual Time& operator-=(const Millisecond& milliseconds);
        virtual Time& operator+=(const Microsecond& microseconds);
        virtual Time& operator-=(const Microsecond& microseconds);
        virtual Time& operator+=(const Nanosecond& nanoseconds);
        virtual Time& operator-=(const Nanosecond& nanoseconds);
        bool operator>(const Time& other) const;
        bool operator>=(const Time& other) const;
        bool operator<(const Time& other) const;
        bool operator<=(const Time& other) const;
        bool operator==(const Time& other) const;
        bool operator!=(const Time& other) const;

        void set_timezone(Timezone new_timezone);

        static void set_default_timezone(Timezone timezone);

        int get_hour_at_timezone(Timezone timezone) const;

        void round(Component to);

        void ceil(Component to);

        void floor(Component to);

        static const int HOURS_PER_DAY;

protected:
        virtual void add_hours(int hours_to_add);
        virtual void add_minutes(int minutes_to_add);
        virtual void add_seconds(int seconds_to_add);
        virtual void add_milliseconds(int64_t milliseconds_to_add);
        virtual void add_microseconds(int64_t microseconds_to_add);
        virtual void add_nanoseconds(int64_t nanoseconds_to_add);

        int total_minutes() const;
        int total_seconds() const;
        int64_t total_milliseconds() const;
        int64_t total_microseconds() const;
        int64_t total_nanoseconds() const;

private:
        static const int MINUTES_PER_HOUR;
        static const int SECONDS_PER_MINUTE;
        static const int SECONDS_PER_HOUR;
        static const int MILLISECONDS_PER_SECOND;
        static const uint64_t MILLISECONDS_PER_MINUTE;
        static const uint64_t MILLISECONDS_PER_HOUR;
        static const int MICROSECONDS_PER_MILLISECOND;
        static const uint64_t MICROSECONDS_PER_HOUR;
        static const uint64_t MICROSECONDS_PER_MINUTE;
        static const uint64_t MICROSECONDS_PER_SECOND;
        static const int NANOSECONDS_PER_MICROSECOND;
        static const uint64_t NANOSECONDS_PER_HOUR;
        static const uint64_t NANOSECONDS_PER_MINUTE;
        static const uint64_t NANOSECONDS_PER_SECOND;
        static const uint64_t NANOSECONDS_PER_MILLISECOND;
};


#endif //DATETIME_TIME_H
