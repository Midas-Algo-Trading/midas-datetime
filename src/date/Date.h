#ifndef DATETIME_DATE_H
#define DATETIME_DATE_H


#include "components/Day.h"
#include "../time/Time.h"

class Date
{
public:
        friend std::ostream &operator<<(std::ostream &os, const Date &time);

        int year;
        int month;
        int day;

        explicit Date(int year=1900, int month=1, int day=1) :
                year(year),
                month(month),
                day(day) {}

        enum DayOfWeek { MONDAY, TUESDAY, WEDNESDAY, THURSDAY, FRIDAY, SATURDAY, SUNDAY };

        static Date today(Timezone timezone=TZ::LOCAL);

        Date& operator+=(const Day& days);
        Date& operator-=(const Day& days);
        Date& operator++(int);
        Date& operator--(int);
        bool operator>(const Date& other) const;
        bool operator>=(const Date& other) const;
        bool operator<(const Date& other) const;
        bool operator<=(const Date& other) const;
        bool operator==(const Date& other) const;
        bool operator!=(const Date& other) const;

        bool is_leap_year() const;

        int max_days_in_month() const;

        DayOfWeek day_of_week() const;

        bool is_weekday() const;

        bool is_weekend() const;

protected:
        void add_days(int days_to_add);
        void subtract_days(int days_to_subtract);

private:
        static const int MONTHS_PER_YEAR;
};


#endif //DATETIME_DATE_H
