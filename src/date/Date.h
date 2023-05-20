#ifndef DATETIME_DATE_H
#define DATETIME_DATE_H


#include "components/Day.h"
#include "../time/Time.h"

/**
 * Represents a date.
 */
class Date
{
public:
        /**
         * The year of the date.
         */
        int year;
        /**
         * The month of the date.
         */
        int month;
        /**
         * The day of the date.
         */
        int day;

        /**
         * Represents the components of a date.
         *
         * @see Date
         */
        enum Component { YEAR, MONTH, DAY };

        /**
         * Represents the different days in a week.
         *
         * @see day_of_week
         */
        enum DayOfWeek { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

        /**
         * Creates a 'Date' based off the given 'year', 'month', and 'day'.
         *
         * @param year the year the 'Date' will be set to.
         * @param month the month the 'Date' will be set to.
         * @param day the day the 'Date' will be set to.
         */
        explicit Date(int year=1900, int month=1, int day=1);

        /**
         * Creates a 'Date' from a string.
         *
         * @tparam DateComponent Should be 'Component'.
         *
         * @param string The string representation of the date.
         * @param date_components The 'Components' that correspond to each number in 'string'.
         *
         * @throws std::out_of_range if the number of 'date_components' does not match the
         * number of numbers given in 'string'.
         *
         * @see Component
         */
        template<typename... DateComponent>
        explicit Date(std::string_view string, DateComponent... date_components);

        static Date today(Timezone timezone=TZ::LOCAL);

        DayOfWeek day_of_week() const;

        bool is_weekday() const;

        bool is_weekend() const;

        std::string to_string() const;

        bool is_leap_year() const;

        int max_days_in_month() const;

        bool is_valid_date() const;

        virtual Date& operator+=(const Day& days);
        virtual Date& operator-=(const Day& days);
        virtual Date& operator++(int);
        virtual Date& operator--(int);
        bool operator>(const Date& other) const;
        bool operator>=(const Date& other) const;
        bool operator<(const Date& other) const;
        bool operator<=(const Date& other) const;
        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;

        friend std::ostream &operator<<(std::ostream &os, const Date &time);

protected:
        void add_days(int days_to_add);
        void subtract_days(int days_to_subtract);

private:
        static const int MONTHS_PER_YEAR;

        bool is_valid_year() const;
        bool is_valid_month() const;
        bool is_valid_day() const;
};

#endif //DATETIME_DATE_H
