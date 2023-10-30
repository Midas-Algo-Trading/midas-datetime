#ifndef DATETIME_DATE_H
#define DATETIME_DATE_H


#include "datetime/date/components/Day.h"
#include "datetime/time/Time.h"
#include "fmt/format.h"
#include "../../../util/macros.h"
#include "stringhelpers/stringhelpers.h"

/**
 * Date with components: 'year', 'month', and 'day'.
 */
class Date
{
public:
    /**
     * Year of the date.
     */
    uint16_t year = 1900;
    /**
     * Month of the date.
     */
    uint8_t month = 1;
    /**
     * Day of the date.
     */
    uint8_t day = 1;

    /**
     * Components of a date.
     *
     * @see Date
     */
    enum Component { YEAR, MONTH, DAY };

    /**
     * Different days in a week.
     *
     * @see day_of_week
     */
    enum DayOfWeek { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

    /**
     * Creates a 'Date' whose components match the values of 'year', 'month', and 'day'.
     *
     * @param year Year the 'Date' will be set to.
     * @param month Month the 'Date' will be set to.
     * @param day Day the 'Date' will be set to.
     */
    explicit Date(uint16_t year= 1900, uint8_t month = 1, uint8_t day = 1);

    /**
     * Creates a 'Date' from a std::string.
     *
     * @tparam DateComponents Should be of type 'Component'.
     *
     * @param string String representation of the date.
     * @param date_components 'Components' that correspond to each number in 'string'.
     *
     * @throws std::out_of_range if the number of 'date_components' does not match the
     * number of numbers given in 'string'.
     *
     * @see Component
     */
    template<typename... DateComponents>
    explicit Date(std::string_view string, DateComponents... date_components);

    /**
     * Creates a 'Date' from a std::string.
     *
     * @param string string representation of the date.
     * Should be in the format %Y-%m-%d.
     *
     * @note calls Date(std::string, DateComponents...) with DateComponents: Year, Month, Day.
     */
    explicit Date(std::string_view string) :
        Date(string, Component::YEAR, Component::MONTH, Component::DAY) {}

    /**
     * Creates a 'Date' that matches today's date.
     *
     * @param timezone timezone to get the current date of.
     *
     * @return a 'Date' that matches today's date.
     */
    static Date today(uint8_t day_offset = 0, Timezone timezone = TZ::LOCAL);

    /**
     * Creates a 'Date' that matches tomorrow's date.
     *
     * @param timezone timezone to get tomorrow's date of.
     *
     * @return a 'Date' that matches tomorrow's date.
     */
    static Date tomorrow(Timezone timezone = TZ::LOCAL);

    /**
     * Gets the 'DayOfWeek' of this 'Date'.
     *
     * @return 'DayOfWeek' of 'Date'.
     */
    DayOfWeek day_of_week() const;

    /**
     * Returns whether this 'Date' is a weekday.
     *
     * Will return true if the day of the week is a Monday, Tuesday, Wednesday, Thursday, or
     * Friday.
     *
     * @return 'true' if this 'Date' is a weekday, 'false' otherwise.
     */
    bool is_weekday() const;

    /**
     * Returns whether this 'Date' is a weekend.
     *
     * Will return true if the day of the week is a Saturday or Sunday.
     *
     * @return True if this 'Date' is a weekend, 'false' otherwise.
     */
    bool is_weekend() const;

    /**
     * Represents this 'Date' as a std::string.
     *
     * Represents this 'Date' as a std::string with format %Y-%m-%d.
     *
     * @return resulting std::string.
     *
     * @example
     * Date date = Date(2000, 1, 30);
     * std::string date_string = date.to_string();
     * std::cout << date_string;
     *
     * // output: 2000-01-30
     */
    virtual std::string to_string() const;

    /**
     * Returns whether 'year' is a leap year.
     *
     * @return 'true' if 'year' is a leap year.
     */
    static bool is_leap_year(uint16_t year);

    /**
     * Gets the maximum number of days in the month that corresponds to 'month_idx'.
     *
     * @return maximum number of days in the month that corresponds to 'month_idx'.
     *
     * @example
     * Date date = Date(2000, 1, 2);
     * size_t max_days_in_january = Date::max_days_in_month(date.month);
     * std::cout << max_days_in_january;
     *
     * // output: 31
     */
    static size_t max_days_in_month(uint8_t month_idx, std::optional<uint16_t> year = {});

    /**
     * Adds 'days' to this 'Date'.
     *
     * @param days number of days to add to this 'Date'.
     *
     * @return A reference to this modified 'Date'.
     */
    virtual Date& operator+=(const Day& days);

    /**
     * Subtracts 'days' from this 'Date'.
     *
     * @param days number of days to subtract from this 'Date'.
     *
     * @return A reference to this modified 'Date'.
     */
    virtual Date& operator-=(const Day& days);

    /**
     * Adds 'days' to 'this'.
     *
     * @param days the number of days to add.
     *
     * @return a new 'Date' with 'days' added.
     */
    Date operator+(const Day& days);

    /**
     * Subtracts 'days' to 'this'.
     *
     * @param days the number of days to subtract.
     *
     * @return a new 'Date' with 'days' subtracted.
     */
    Date operator-(const Day& days);

    /**
     * Adds a day to this 'Date'.
     *
     * @return A reference to this modified 'Date'.
     */
    virtual Date& operator++();

    /**
     * Subtracts a day from this 'Date'.
     *
     * @return A reference to this modified 'Date'.
     */
    virtual Date& operator--();

    /**
     * Checks if 'other' is greater than this 'Date'.
     *
     * @param other 'Date' to check if greater than this 'Date'.
     *
     * @return 'true' if 'other' is greater than this 'Date', 'false' otherwise.
     */
    bool operator>(const Date& other) const;

    /**
     * Checks if 'other' is greater than or equal to this 'Date'.
     *
     * @param other 'Date' to check if greater than or equal to this 'Date'.
     *
     * @return 'true' if 'other' is greater than or equal to this 'Date', 'false' otherwise.
     */
    bool operator>=(const Date& other) const;

    /**
     * Checks if 'other' is less than this 'Date'.
     *
     * @param other 'Date' to check if less than this 'Date'.
     *
     * @return 'true' if 'other' is less than this 'Date', 'false' otherwise.
     */
    bool operator<(const Date& other) const;

    /**
     * Checks if 'other' is less than or equal to this 'Date'.
     *
     * @param other 'Date' to check if less than or equal to this 'Date'.
     *
     * @return 'true' if 'other' is less than or equal to this 'Date', 'false' otherwise.
     */
    bool operator<=(const Date& other) const;

    /**
     * Checks if 'other' is equal to this 'Date'.
     *
     * @param other 'Date' to check if equal to this 'Date'.
     *
     * @return 'true' if 'other' is equal to this 'Date', 'false' otherwise.
     */
    bool operator==(const Date& other) const;

    /**
     * Checks if 'other' is not equal to this 'Date'.
     *
     * @param other 'Date' to check if not equal to this 'Date'.
     *
     * @return 'true' if 'other' is not equal to this 'Date', 'false' otherwise.
     */
    bool operator!=(const Date& other) const;

    /**
     * Outputs 'date' into 'os'.
     *
     * @param os 'std::ostream' to insert 'date' into.
     * @param date 'Date' to insert into 'os'.
     *
     * @return a reference to 'os' after inserting 'date' into 'os'.
     */
    friend std::ostream& operator<<(std::ostream& os, const Date& date);

protected:
    /**
     * Adds days to this 'Date'.
     *
     * @param days_to_add number of days to add to this 'Date'.
     */
    void add_days(size_t days_to_add);

    /**
     * Subtracts days from this 'Date'.
     *
     * @param days_to_subtract number of days to subtract from this 'Date'.
     */
    void subtract_days(size_t days_to_subtract);

private:
    /**
     * Number of months in a year.
     */
    static const int MONTHS_PER_YEAR;

    /**
     * Checks if this 'Date' is valid.
     *
     * Checks if 'is_valid_year', 'is_valid_month', and 'is_valid_day' all return 'true'.
     *
     * @return 'true' if this 'Date' is valid, 'false' otherwise.
     */
    bool is_valid_date() const;

    /**
     * Checks if 'year' is valid.
     *
     * Checks if 'year' is less than or equal to 2100 and greater than or equal to 1900.
     *
     * @return 'true' if 'year' is valid, 'false' otherwise.
     */
    bool is_valid_year() const;

    /**
     * Checks if 'month' is valid.
     *
     * Checks if 'month' is less than or equal to 12 and greater than or equal to 1.
     *
     * @return 'true' is 'month' is valid, 'false' otherwise.
     */
    bool is_valid_month() const;

    /**
     * Checks if 'day' is valid.
     *
     * Checks if 'day' is less than or equal to the return value of 'max_days_in_month' and
     * is greater than or equal to 1.
     *
     * @return 'true' if 'day' is valid, 'false' otherwise.
     */
    bool is_valid_day() const;
};

template<typename... DateComponents>
Date::Date(std::string_view string, DateComponents... date_components)
{
    std::vector<std::string> date_components_strs = strh::split_alphabetical(string);

    ASSERT(date_components_strs.size() == sizeof...(date_components),
           std::invalid_argument(fmt::format("components: '{}' with size '{}' does not match date "
                                             "strings: '{}' with size '{}'",
                                             strh::from_parameter_pack(date_components...),
                                             sizeof...(date_components),
                                             fmt::join(date_components_strs, ", "),
                                             date_components_strs.size())));

    size_t idx = 0;

    // Lambda to get each date component value from each corresponding date component string
    auto set_date_components_from_str = [&](const auto& date_component, size_t idx) {
        switch (date_component) {
        case Date::Component::YEAR:
            year = std::stoi(date_components_strs[idx]);
            break;
        case Date::Component::MONTH:
            if (date_components_strs[idx][0] == '0')
                month = date_components_strs[idx][1] - '0'; // char to int
            else
                month = std::stoi(date_components_strs[idx]);
            break;
        case Date::Component::DAY:
            if (date_components_strs[idx][0] == '0')
                day = date_components_strs[idx][1] - '0'; // char to int
            else
                day = std::stoi(date_components_strs[idx]);
            break;
        }
    };

    // Call the lambda function on each date component
    (set_date_components_from_str(date_components, idx++), ...);

    ASSERT(is_valid_date(),
           std::invalid_argument(fmt::format("'{}' is an invalid date", Date::to_string())));
}

#endif //DATETIME_DATE_H
