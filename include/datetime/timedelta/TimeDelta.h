#ifndef DATETIME_TIMEDELTA_H
#define DATETIME_TIMEDELTA_H


#include <utility>

#include "datetime/time/Time.h"

/**
 * Stores addition/subtraction operations result between 2 date/time/datetime objects.
 */
class TimeDelta : public Time
{
public:

    /**
     * The number of days changed from the operation.
     */
    int64_t days;

    /**
     * Creates a 'TimeDelta' object.
     *
     * @param days days of the delta.
     * @param hour hour of the delta. (default 0)
     * @param minute minute of the delta. (default 0)
     * @param second second of the delta. (default 0)
     * @param millisecond millisecond of the delta. (default 0)
     * @param microsecond microsecond of the delta. (default 0)
     * @param nanosecond nanosecond of the delta. (default 0)
     * @param timezone timezone the of the delta. (default default_timezone)
     */
    TimeDelta(int64_t days = 0, uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0,
              uint16_t millisecond = 0, uint16_t microsecond = 0, uint16_t nanosecond = 0,
              Timezone timezone = default_timezone) :
        days(days), Time(hour, minute, second, millisecond, microsecond, nanosecond, timezone) {}

    /**
     * Creates a 'TimeDelta' object.
     *
     * @param days days of the delta.
     * @param time time components of the delta will be set to the components of this.
     */
    TimeDelta(int64_t days, Time time) :
        days(days), Time(std::move(time)) {}

    /**
     * Creates a 'Time' object using the time components of 'this'.
     *
     * @return 'Time' object with components matching 'this'.
     */
    Time time() const;

    /**
     * Outputs 'time_delta' into 'os'.
     *
     * @param os 'std::ostream' to insert 'time_delta' into.
     * @param time_delta 'time_delta' to insert into 'os'.
     *
     * @return a reference to 'os' after inserting 'time_delta' into 'os'.
     */
    friend std::ostream& operator<<(std::ostream& os, const TimeDelta& time_delta);

    /**
     * Checks if 'this' is greater than 'other'.
     *
     * @param other 'TimeDelta' to compare to.
     *
     * @return 'true' if 'this' is greater than 'other', 'false' otherwise.
     */
    bool operator>(TimeDelta other) const;

    /**
     * Checks if 'this' is greater than or equal to 'other'.
     *
     * @param other 'TimeDelta' to compare to.
     *
     * @return 'true' if 'this' is greater than or equal to 'other', 'false' otherwise.
     */
    bool operator>=(TimeDelta other) const;

    /**
     * Checks if 'this' is equal to 'other'.
     *
     * @param other 'TimeDelta' to compare to.
     *
     * @return 'true' if 'this' is equal to 'other', 'false' otherwise.
     */
    bool operator==(TimeDelta other) const;

    /**
     * Checks if 'this' is not equal to 'other'.
     *
     * @param other 'TimeDelta' to compare to.
     *
     * @return 'true' if 'this' is not equal to 'other', 'false' otherwise.
     */
    bool operator!=(TimeDelta other) const;

    /**
     * Checks if 'this' is less than or equal to 'other'.
     *
     * @param other 'TimeDelta' to compare to.
     *
     * @return 'true' if 'this' is less than or equal to 'other', 'false' otherwise.
     */
    bool operator<=(TimeDelta other) const;

    /**
     * Checks if 'this' is less than 'other'.
     *
     * @param other 'TimeDelta' to compare to.
     *
     * @return 'true' if 'this' is less than 'other', 'false' otherwise.
     */
    bool operator<(TimeDelta other) const;
};


#endif //DATETIME_TIMEDELTA_H
