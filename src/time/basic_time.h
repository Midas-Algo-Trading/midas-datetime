#ifndef DATETIME_BASICTIME_H
#define DATETIME_BASICTIME_H

#include <utility>
#include <string>
#include <datetime/time/time_component.h>
#include <cstdlib>

/**
 * Basic time representation.
 *
 * @note 'Time' is split up into 'Time' and 'BasicTime' so 'TimeDelta' can inherit Time methods,
 * so code is not repeated.
 */
class BasicTime
{
public:

    /**
      * Hours of a day.
      */
    uint8_t hour = 0;

    /**
     * Minutes of a day.
     */
    uint8_t minute = 0;

    /**
     * Seconds of a day.
     */
    uint8_t second = 0;

    /**
     * Milliseconds of a day.
     */
    uint16_t millisecond = 0;

    /**
     * Microseconds of a day.
     */
    uint16_t microsecond = 0;

    /**
     * Nanoseconds of a day.
     */
    uint16_t nanosecond = 0;

    /**
    * Creates a 'Time' whose components match the values of 'hour', 'minute',
    * 'second', 'millisecond', 'microsecond', 'nanosecond', and 'timezone'.
    *
    * @param hour hour the 'Time' will be set to. (default 0)
    * @param minute minute the 'Time' will be set to. (default 0)
    * @param second second the 'Time' will be set to. (default 0)
    * @param millisecond millisecond the 'Time' will be set to. (default 0)
    * @param microsecond microsecond the 'Time' will be set to. (default 0)
    * @param nanosecond nanosecond the 'Time' will be set to. (default 0)
    * @param timezone timezone the 'Time' will be set to. (default default_timezone)
    */
    BasicTime(uint8_t hour = 0, uint8_t minute = 0, uint8_t second = 0, uint16_t millisecond = 0,
        uint16_t microsecond = 0, uint16_t nanosecond = 0) :
        hour(hour), minute(minute), second(second), millisecond(millisecond), microsecond
        (microsecond), nanosecond(nanosecond) {}

    /**
    * Checks if 'this' is greater than 'other'.
    *
    * @param other 'Time' to compare to.
    *
    * @return 'true' if 'this' is greater than 'other', 'false' otherwise.
    */
    bool operator>(BasicTime other) const;

    /**
     * Checks if 'this' is greater than or equal to 'other'.
     *
     * @param other 'Time' to compare to.
     *
     * @return 'true' if 'this' is greater than or equal to 'other', 'false' otherwise.
     */
    bool operator>=(BasicTime other) const;

    /**
     * Checks if 'this' is less than 'other'.
     *
     * @param other 'Time' to compare to.
     *
     * @return 'true' if 'this' is less than 'other', 'false' otherwise.
     */
    bool operator<(BasicTime other) const;

    /**
     * Checks if 'this' is less than or equal to 'other'.
     *
     * @param other 'Time' to compare to.
     *
     * @return 'true' if 'this' is less than or equal to 'other', 'false' otherwise.
     */
    bool operator<=(BasicTime other) const;

    /**
     * Checks if 'this' is equal to 'other'.
     *
     * @param other 'Time' to compare to.
     *
     * @return 'true' if 'this' is equal to 'other', 'false' otherwise.
     */
    bool operator==(BasicTime other) const;

    /**
     * Checks if 'this' is not equal to 'other'.
     *
     * @param other 'Time' to compare to.
     *
     * @return 'true' if 'this' is not equal to 'other', 'false' otherwise.
     */
    bool operator!=(BasicTime other) const;

    /**
     * Gets the total minutes of the day.
     *
     * @return total minutes of the day.
     */
    virtual int total_minutes() const;

    /**
     * Gets the total seconds of the day.
     *
     * @return total seconds of the day.
     */
    virtual int total_seconds() const;

    /**
     * Gets the total milliseconds of the day.
     *
     * @return total milliseconds of the day.
     */
    virtual int64_t total_milliseconds() const;

    /**
     * Gets the total microseconds of the day.
     *
     * @return total microseconds of the day.
     */
    virtual int64_t total_microseconds() const;

    /**
     * Gets the total nanoseconds of the day.
     *
     * @return total nanoseconds of the day.
     */
    virtual int64_t total_nanoseconds() const;

    /**
     * Hours in a day.
     */
    static const int HOURS_PER_DAY;

protected:

    /**
     * Represents this 'Time' as a std::string.
     *
     * Represents this 'Time' as a std::string with format %-H:%M:%S.%ms.%f.%ns
     *
     * @param include_to Include the time components up until 'include_to' in the resulting
     * string (inclusive).
     * @param delim_h_m_s 'char' separating hours, minutes, and seconds.
     * @param delim_ms_us_ns 'char' separating milliseconds, microseconds, and nanoseconds.
     *
     * @example
     * Time time = Datetime(1, 2, 3, 4, 5, 6);
     * std::string time_string = date.to_string();
     * std::cout << time_string;
     *
     * // output: 1:02:04.4.5.6
     *
     * @return resulting std::string.
     */
    virtual std::string to_string(TimeComponent include_to = TimeComponent::NANOSECOND,
                                  char delim_h_m_s = ':',
                                  char delim_ms_us_ns = '.') const;

    /**
     * Minutes in a hour.
     */
    static const size_t MINUTES_PER_HOUR;

    /**
     * Seconds in a minute.
     */
    static const size_t SECONDS_PER_MINUTE;

    /**
     * Seconds in a hour.
     */
    static const size_t SECONDS_PER_HOUR;

    /**
     * Milliseconds in a second.
     */
    static const size_t MILLISECONDS_PER_SECOND;

    /**
     * Milliseconds in a minute.
     */
    static const size_t MILLISECONDS_PER_MINUTE;

    /**
     * Milliseconds in a minute.
     */
    static const size_t MILLISECONDS_PER_HOUR;

    /**
     * Microseconds in a millisecond.
     */
    static const size_t MICROSECONDS_PER_MILLISECOND;

    /**
     * Microseconds in a hour.
     */
    static const size_t MICROSECONDS_PER_HOUR;

    /**
     * Microseconds in a minute.
     */
    static const size_t MICROSECONDS_PER_MINUTE;

    /**
     * Microseconds in a second.
     */
    static const size_t MICROSECONDS_PER_SECOND;

    /**
     * Nanoseconds in a microsecond.
     */
    static const size_t NANOSECONDS_PER_MICROSECOND;

    /**
     * Nanoseconds in a hour.
     */
    static const size_t NANOSECONDS_PER_HOUR;

    /**
     * Nanoseconds in a minute.
     */
    static const size_t NANOSECONDS_PER_MINUTE;

    /**
     * Nanoseconds in a second.
     */
    static const size_t NANOSECONDS_PER_SECOND;

    /**
     * Nanoseconds in a millisecond.
     */
    static const size_t NANOSECONDS_PER_MILLISECOND;
};


#endif //DATETIME_BASICTIME_H
