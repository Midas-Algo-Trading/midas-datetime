#ifndef DATETIME_BASICTIME_H
#define DATETIME_BASICTIME_H

#include <utility>
#include <string>

/**
 * Basic time representation.
 *
 * @note 'Time' is split up into 'Time' and 'BasicTime' so 'TimeDelta' can inherit Time methods,
 * so code is not repeated.
 */
struct BasicTime
{
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
     * Represents this 'Time' as a std::string.
     *
     * Represents this 'Time' as a std::string with format %-H:%M:%S.%ms.%f.%ns
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
    virtual std::string to_string(char separate_time = ':', char separate_seconds = '.') const;
};


#endif //DATETIME_BASICTIME_H
