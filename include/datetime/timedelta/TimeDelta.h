#ifndef DATETIME_TIMEDELTA_H
#define DATETIME_TIMEDELTA_H

#include <utility>
#include <ostream>
#include "../../../src/time/BasicTime.h"

/**
 * Stores addition/subtraction operations result between 2 date/time/datetime objects.
 */
class TimeDelta : public BasicTime
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
              uint16_t millisecond = 0, uint16_t microsecond = 0, uint16_t nanosecond = 0) :
        days(days), BasicTime(hour, minute, second, millisecond, microsecond, nanosecond) {}

    /**
     * Sets 'days' to the absolute value of 'days'.
     *
     * @return 'this' with 'days' equal to the absolute value of 'days'.
     */
    TimeDelta& abs();

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

    /**
     * Gets the total hours.
     *
     * @return total hours.
     */
    int total_hours() const;

    /**
     * Gets the total minutes.
     *
     * @return total minutes.
     */
    int total_minutes() const override;

    /**
     * Gets the total seconds.
     *
     * @return total seconds.
     */
    int total_seconds() const override;

    /**
     * Gets the total milliseconds.
     *
     * @return total milliseconds.
     */
    int64_t total_milliseconds() const override;

    /**
     * Gets the total microseconds.
     *
     * @return total microseconds.
     */
    int64_t total_microseconds() const override;

    /**
     * Gets the total nanoseconds.
     *
     * @return total nanoseconds.
     */
    int64_t total_nanoseconds() const override;
};


#endif //DATETIME_TIMEDELTA_H
