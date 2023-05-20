#include "Datetime.h"

Datetime Datetime::now(Timezone timezone)
{
        return Datetime(Date::today(), Time::now(timezone));
}

void Datetime::add_hours(int hours_to_add)
{
        int new_hour = hour + hours_to_add;
        int day_change = new_hour / HOURS_PER_DAY;
        hour = new_hour % HOURS_PER_DAY;

        if (hour < 0)
        {
                hour += HOURS_PER_DAY;
                day_change--;
        }

        if (day_change > 0)
                add_days(day_change);
        if (day_change < 0)
                subtract_days(day_change*-1);
}

Date Datetime::date() const
{
        return Date(year, month, day);
}

Time Datetime::time() const
{
        return Time(hour, minute, second, millisecond, microsecond, nanosecond, timezone);
}


bool Datetime::operator>(const Datetime &other) const
{
        return date() > other.date() || time() > other.time();
}

bool Datetime::operator>=(const Datetime &other) const
{
        return   date() > other.date()
              || date() == other.date() && time() >= other.time();
}

bool Datetime::operator<(const Datetime &other) const
{
        return date() < other.date() || time() < other.time();
}

bool Datetime::operator<=(const Datetime &other) const
{
        return   date() < other.date()
              || date() == other.date() && time() <= other.time();
}

bool Datetime::operator==(const Datetime &other) const
{
        return date() == other.date() && time() == other.time();
}

bool Datetime::operator!=(const Datetime &other) const
{
        return date() != other.date() || time() != other.time();
}

Datetime &Datetime::operator+=(const Day &days)
{
        Date::operator+=(days);
        return *this;
}

Datetime &Datetime::operator-=(const Day &days)
{
        Date::operator-=(days);
        return *this;
}

Datetime &Datetime::operator+=(const Hour &hours)
{
        Time::operator+=(hours);
        return *this;
}

Datetime &Datetime::operator-=(const Hour &hours)
{
        Time::operator-=(hours);
        return *this;
}

Datetime &Datetime::operator+=(const Minute &minutes)
{
        Time::operator+=(minutes);
        return *this;
}

Datetime &Datetime::operator-=(const Minute &minutes)
{
        Time::operator-=(minutes);
        return *this;
}

Datetime &Datetime::operator+=(const Second &seconds)
{
        Time::operator+=(seconds);
        return *this;
}

Datetime &Datetime::operator-=(const Second &seconds)
{
        Time::operator-=(seconds);
        return *this;
}

Datetime &Datetime::operator+=(const Millisecond &milliseconds)
{
        Time::operator+=(milliseconds);
        return *this;
}

Datetime &Datetime::operator-=(const Millisecond &milliseconds)
{
        Time::operator-=(milliseconds);
        return *this;
}

Datetime &Datetime::operator+=(const Microsecond &microseconds)
{
        Time::operator+=(microseconds);
        return *this;
}

Datetime &Datetime::operator-=(const Microsecond &microseconds)
{
        Time::operator-=(microseconds);
        return *this;
}

Datetime &Datetime::operator+=(const Nanosecond &nanoseconds)
{
        Time::operator+=(nanoseconds);
        return *this;
}

Datetime &Datetime::operator-=(const Nanosecond &nanoseconds)
{
        Time::operator-=(nanoseconds);
        return *this;
}

Datetime &Datetime::operator++(int)
{
        Date::operator++(1);
        return *this;
}

Datetime &Datetime::operator--(int)
{
        Date::operator--(1);
        return *this;
}

std::string Datetime::to_string() const
{
    return Date::to_string() + ' ' + Time::to_string();
}
