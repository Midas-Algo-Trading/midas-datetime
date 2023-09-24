#ifndef DATETIME_DATETIME_H
#define DATETIME_DATETIME_H

#include "datetime/date/Date.h"
#include "datetime/time/Time.h"

/**
 * 'Date' and a 'Time' with components: 'year', 'month', 'day', 'hour', 'minute',
 * 'second', 'millisecond', 'microsecond', and 'nanosecond'.
 */
class Datetime : public Date, public Time
{
public:
    /**
     * Creates a 'Datetime' whose date values match 'date'.
     * 'time' will be set to the default 'Time'.
     *
     * @param date 'Date' to set the date values of 'Datetime' to.
     */
    explicit Datetime(const Date& date) :
        Date(date.year, date.month, date.day),
        Time() {}

    /**
     * Creates a 'Datetime' whose date values match 'date' and whose time values match 'time'.
     *
     * @param date 'Date' to set the date values of 'Datetime' to.
     * @param time 'Time' to set the time values of 'Datetime' to.
     */
    explicit Datetime(const Date& date, const Time& time) :
        Date(date.year, date.month, date.day),
        Time(time.hour, time.minute, time.second, time.millisecond, time.microsecond,
             time.nanosecond, time.timezone) {}

    /**
     * Creates a 'Datetime' based on the given arguments.
     *
     * @param year year value that 'Datetime' will be set to.
     * @param month month value that 'Datetime' will be set to.
     * @param day day value that 'Datetime' will be set to.
     * @param hour hour value that 'Datetime' will be set to.
     * @param minute minute value that 'Datetime' will be set to.
     * @param second second value that 'Datetime' will be set to.
     * @param millisecond millisecond value that 'Datetime' will be set to.
     * @param microsecond microsecond value that 'Datetime' will be set to.
     * @param nanosecond nanosecond value that 'Datetime' will be set to.
     * @param timezone timezone that 'Datetime' will be set to.
     */
    explicit Datetime(uint16_t year = 1900, uint8_t month = 1, uint8_t day = 1, uint8_t hour = 0, uint8_t minute = 0,
                      uint8_t second = 0, uint16_t millisecond = 0, uint16_t microsecond = 0,
                      uint16_t nanosecond = 0,
                      Timezone timezone = Time::default_timezone)
        :
        Date(year, month, day),
        Time(hour, minute, second, millisecond, microsecond, nanosecond, timezone) {}

    /**
     * Creates a 'Datetime' whose components' values match the current date and time.
     *
     * @param timezone 'Timezone' to set the current date and time to.
     *
     * @return created 'Datetime'.
     */
    static Datetime now(uint8_t day_offset = 0, uint8_t hour_offset = 0, uint8_t minute_offset =0,
                        uint8_t second_offset = 0, uint16_t millisecond_offset = 0,
                        uint16_t microsecond_offset = 0, uint16_t nanosecond_offset = 0,
                        Timezone timezone = default_timezone);

    /**
     * Constructs a datetime object from a millisecond unix timestamp.
     *
     * @param timestamp millisecond unix timestamp.
     * @param timezone timezone that 'Datetime' will be set to.
     *
     * @return the datetime object converted from the 'timestamp'.
     */
    static Datetime from_ms(size_t timestamp, Timezone timezone = Time::default_timezone);

    /**
     * Creates a 'Datetime' from a std::string.
     *
     * @tparam DateComponent1 should be of type 'Date::Component'.
     * @tparam DateComponent2 should be of type 'Date::Component'.
     * @tparam DateComponent3 should be of type 'Date::Component'.
     * @tparam TimeComponents should be of type 'Time::Component'.
     *
     * @param string string representation of the date and time.
     * @param date_component1 'Date' component that the first number in 'string' represents.
     * @param date_component2 'Date' component that the second number in 'string'
     * represents.
     * @param date_component3 'Date' component that the third number in 'string' represents.
     * @param time_components 'Time' components that correspond to each number in 'string'.
     */
    template<typename DateComponent1, typename DateComponent2, typename DateComponent3,
        typename... TimeComponents>
    explicit Datetime(std::string_view string, DateComponent1 date_component1,
                      DateComponent2 date_component2, DateComponent3 date_component3,
                      TimeComponents... time_components) :
    // First 10 characters in 'string' will be for the date, remaining will be for
    // the time.
        Date(string.substr(0, 10), date_component1, date_component2, date_component3),
        Time(string.substr(10, string.length()),
             std::forward<TimeComponents>(time_components)...) {}

    /**
     * Creates a new 'Date' whose components' values match the date values of this
     * 'Datetime'.
     *
     * @return newly created 'Date'.
     */
    Date date() const;

    /**
     * Creates a new 'Time' whose components' values match the time values of this
     * 'Datetime'.
     *
     * @return newly created 'Time'.
     */
    Time time() const;

    /**
     * Represents this 'Datetime' as a std::string.
     *
     * Represents this 'Datetime' as a std::string with format
     * %Y-%m-%d %-H:%M:%S.%ms.%f.%ns
     *
     * @example
     * Datetime datetime = Datetime(2000, 1, 2, 3, 4, 5, 6, 7, 8);
     * std::string datetime_string = date.to_string();
     * std::cout << datetime_string;
     *
     * // output: 2000-01-02 3:04:05.6.7.8
     *
     * @return resulting std::string.
     */
    std::string to_string() const override;

    /**
     * Checks if 'other' is greater than this 'Datetime'.
     *
     * @param other 'Datetime' to check if greater than this 'Datetime'.
     *
     * @return 'true' if 'other' is greater than this 'Datetime', 'false' otherwise.
     */
    bool operator>(const Datetime& other) const;

    /**
     * Checks if 'other' is greater than or equal to this 'Datetime'.
     *
     * @param other 'Datetime' to check if greater than or equal to this 'Datetime'.
     *
     * @return 'true' if 'other' is greater than or equal to this 'Datetime', 'false' otherwise.
     */
    bool operator>=(const Datetime& other) const;

    /**
     * Checks if 'other' is less than this 'Datetime'.
     *
     * @param other 'Datetime' to check if less than this 'Datetime'.
     *
     * @return 'true' if 'other' is less than this 'Datetime', 'false' otherwise.
     */
    bool operator<(const Datetime& other) const;

    /**
     * Checks if 'other' is less than or equal to this 'Datetime'.
     *
     * @param other Datetime' to check if less than or equal to this 'Datetime'.
     *
     * @return 'true' if 'other' is less than or equal to this 'Datetime', 'false' otherwise.
     */
    bool operator<=(const Datetime& other) const;

    /**
     * Checks if 'other' is equal to this 'Datetime'.
     *
     * @param other 'Datetime' to check if equal to this 'Datetime'.
     *
     * @return 'true' if 'other' is equal to this 'Datetime', 'false' otherwise.
     */
    bool operator==(const Datetime& other) const;

    /**
     * Checks if 'other' is not equal to this 'Datetime'.
     *
     * @param other 'Datetime' to check if not equal to this 'Datetime'.
     *
     * @return 'true' if 'other' is not equal to this 'Datetime', 'false' otherwise.
     */
    bool operator!=(const Datetime& other) const;

    /**
     * Adds a day to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator++() override;

    /**
     * Subtracts a day from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator--() override;

    /**
     * Adds 'time' to this 'Datetime'.
     *
     * @param time the other 'Time' added to this 'Datetime'.
     *
     * @return reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Time& time) override;

    /**
     * Subtracts 'time' to this 'Datetime'.
     *
     * @param time the other 'Time' subtracted from this 'Datetime'.
     *
     * @return reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Time& time) override;

    /**
     * Adds 'days' to this 'Datetime'.
     *
     * @param days number of days to add to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Day& days) override;

    /**
     * Subtracts 'days' from this 'Datetime'.
     *
     * @param days number of days to subtract from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Day& days) override;

    /**
     * Adds 'hours' to this 'Datetime'.
     *
     * @param days number of days to add to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Hour& hours) override;

    /**
     * Subtracts 'hours' from this 'Datetime'.
     *
     * @param days number of days to subtract from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Hour& hours) override;

    /**
     * Adds 'minutes' to this 'Datetime'.
     *
     * @param days number of days to add to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Minute& minutes) override;

    /**
     * Subtracts 'minutes' from this 'Datetime'.
     *
     * @param days number of days to subtract from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Minute& minutes) override;

    /**
     * Adds 'seconds' to this 'Datetime'.
     *
     * @param days number of days to add to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Second& seconds) override;

    /**
     * Subtracts 'seconds' from this 'Datetime'.
     *
     * @param days number of days to subtract from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Second& seconds) override;

    /**
     * Adds 'milliseconds' to this 'Datetime'.
     *
     * @param days number of days to add to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Millisecond& milliseconds) override;

    /**
     * Subtracts 'milliseconds' from this 'Datetime'.
     *
     * @param days number of days to subtract from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Millisecond& milliseconds) override;

    /**
     * Adds 'microseconds' to this 'Datetime'.
     *
     * @param days number of days to add to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Microsecond& microseconds) override;

    /**
     * Subtracts 'microseconds' from this 'Datetime'.
     *
     * @param days number of days to subtract from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Microsecond& microseconds) override;

    /**
     * Adds 'nanoseconds' to this 'Datetime'.
     *
     * @param days number of days to add to this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator+=(const Nanosecond& nanoseconds) override;

    /**
     * Subtracts 'nanoseconds' from this 'Datetime'.
     *
     * @param days number of days to subtract from this 'Datetime'.
     *
     * @return A reference to this modified 'Datetime'.
     */
    Datetime& operator-=(const Nanosecond& nanoseconds) override;

    /**
     * Adds 'hours' to 'datetime'.
     *
     * @param datetime the base 'Datetime' to add 'hours' to.
     * @param hours the number of hours to add.
     *
     * @return a new 'Datetime' with 'hours' added.
     */
    friend Datetime operator+(Datetime datetime, const Hour& hours);

    /**
     * Subtracts 'hours' from 'datetime'.
     *
     * @param datetime the base 'Datetime' to subtract 'hours' from.
     * @param hours the number of hours to subtract.
     *
     * @return a new 'Datetime' with 'hours' subtracted.
     */
    friend Datetime operator-(Datetime datetime, const Hour& hours);

    /**
     * Adds 'minutes' to 'datetime'.
     *
     * @param datetime the base 'Datetime' to add 'minutes' to.
     * @param minutes the number of minutes to add.
     *
     * @return a new 'Datetime' with 'minutes' added.
     */
    friend Datetime operator+(Datetime datetime, const Minute& minutes);

    /**
     * Subtracts 'minutes' from 'datetime'.
     *
     * @param datetime the base 'Datetime' to subtract 'minutes' from.
     * @param minutes the number of minutes to subtract.
     *
     * @return a new 'Datetime' with 'minutes' subtracted.
     */
    friend Datetime operator-(Datetime datetime, const Minute& minutes);

    /**
     * Adds 'seconds' to 'datetime'.
     *
     * @param datetime the base 'Datetime' to add 'seconds' to.
     * @param seconds the number of seconds to add.
     *
     * @return a new 'Datetime' with 'seconds' added.
     */
    friend Datetime operator+(Datetime datetime, const Second& seconds);

    /**
     * Subtracts 'seconds' from 'datetime'.
     *
     * @param datetime the base 'Datetime' to subtract 'seconds' from.
     * @param seconds the number of seconds to subtract.
     *
     * @return a new 'Datetime' with 'seconds' subtracted.
     */
    friend Datetime operator-(Datetime datetime, const Second& seconds);

    /**
      * Adds 'milliseconds' to 'datetime'.
      *
      * @param datetime the base 'Datetime' to add 'milliseconds' to.
      * @param milliseconds the number of milliseconds to add.
      *
      * @return a new 'Datetime' with 'milliseconds' added.
      */
    friend Datetime operator+(Datetime datetime, const Millisecond& milliseconds);

    /**
     * Subtracts 'milliseconds' from 'datetime'.
     *
     * @param datetime the base 'Datetime' to subtract 'milliseconds' from.
     * @param milliseconds the number of milliseconds to subtract.
     *
     * @return a new 'Datetime' with 'milliseconds' subtracted.
     */
    friend Datetime operator-(Datetime datetime, const Millisecond& milliseconds);

    /**
    * Adds 'microseconds' to 'datetime'.
    *
    * @param datetime the base 'Datetime' to add 'microseconds' to.
    * @param microseconds the number of microseconds to add.
    *
    * @return a new 'Datetime' with 'microseconds' added.
    */
    friend Datetime operator+(Datetime datetime, const Microsecond& microseconds);

    /**
     * Subtracts 'microseconds' from 'datetime'.
     *
     * @param datetime the base 'Datetime' to subtract 'microseconds' from.
     * @param microseconds the number of microseconds to subtract.
     *
     * @return a new 'Datetime' with 'microseconds' subtracted.
     */
    friend Datetime operator-(Datetime datetime, const Microsecond& microseconds);

    /**
     * Adds 'nanoseconds' to 'datetime'.
     *
     * @param datetime the base 'Datetime' to add 'nanoseconds' to.
     * @param nanoseconds the number of nanoseconds to add.
     *
     * @return a new 'Datetime' with 'nanoseconds' added.
     */
    friend Datetime operator+(Datetime datetime, const Nanosecond& nanoseconds);

    /**
    * Subtracts 'nanoseconds' from 'datetime'.
    *
    * @param datetime the base 'Datetime' to subtract 'nanoseconds' from.
    * @param nanoseconds the number of nanoseconds to subtract.
    *
    * @return a new 'Datetime' with 'nanoseconds' subtracted.
    */
    friend Datetime operator-(Datetime datetime, const Nanosecond& nanoseconds);

    /**
     * Adds this 'Datetime' and 'other' 'Datetime'.
     *
     * @param datetime the base 'Datetime' to add 'other' to.
     * @param other the other 'Datetime' added to this 'Datetime'.
     *
     * @return new 'Datetime' object of this 'Datetime' added with 'other' 'Datetime'.
     */
    friend Datetime operator+(Datetime datetime, const Time& other);

    /**
     * Subtracts this 'Datetime' and 'other' 'Datetime'.
     *
     * @param datetime the base 'Datetime' to subtract 'other' from.
     * @param other the other 'Datetime' subtracted to this 'Datetime'.
     *
     * @return new 'Datetime' object of this 'Datetime' subtracted with 'other' 'Datetime'.
     */
    friend Datetime operator-(Datetime datetime, const Time& other);

    /**
     * Outputs 'datetime' into 'os'.
     *
     * @param os std::ostream' to insert 'datetime' into.
     * @param datetime 'Datetime' to insert into 'os'.
     *
     * @return reference to 'os' after inserting 'date' into 'os'.
     */
    friend std::ostream& operator<<(std::ostream& os, const Datetime& datetime);

private:

    /**
     * Adds hours to this 'Datetime'.
     *
     * @param hours_to_add number of hours to add.
     */
    void add_hours(int hours_to_add) override;
};

#endif //DATETIME_DATETIME_H
