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
