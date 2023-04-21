#include "Datetime.h"

Datetime Datetime::now(Timezone timezone)
{
        return Datetime(Date::today(), Time::now(timezone));
}

void Datetime::add_hours(int hours_to_add)
{
        int new_total_hours = day * HOURS_PER_DAY
                            + hours_to_add;
        int new_day = new_total_hours / HOURS_PER_DAY;
        if (new_day != day)
        {
                int day_change = new_day - day;
                add_days(day_change);
        }
        hour = new_total_hours % HOURS_PER_DAY;
}
