#ifndef DATETIME_DATETIME_H
#define DATETIME_DATETIME_H


#include "../time/Time.h"
#include "../date/Date.h"

class Datetime : public Date, public Time
{
public:
        explicit Datetime(const Date& date) :
                Date(date.year, date.month, date.day),
                Time() {}

        explicit Datetime(const Date& date, const Time& time) :
                Date(date.year, date.month, date.day),
                Time(time.hour, time.minute, time.second, time.millisecond, time.microsecond,
                     time.nanosecond, time.timezone) {}

        explicit Datetime(int year=1900, int month=1, int day=1, int hour=0, int minute=0,
                          int second=0, int millisecond=0, int microsecond=0, int nanosecond=0) :
                 Date(year, month, day),
                 Time(hour, minute, second, millisecond, microsecond, nanosecond) { }

        static Datetime now(Timezone timezone=default_timezone);

        template<typename DateComponent1, typename DateComponent2, typename DateComponent3,
                 typename... TimeComponent>
        explicit Datetime(std::string string, DateComponent1 date_component1,
                          DateComponent2 date_component2, DateComponent3 date_component3,
                          TimeComponent... time_components) :
                // First 10 characters in 'string' will be for the date, remaining will be for
                // the time.
                Date(string.substr(0, 10), date_component1, date_component2, date_component3),
                Time(string.substr(10, string.length()),
                     std::forward<TimeComponent>(time_components)...) {}

        void add_hours(int hours_to_add) override;

        Date date() const;

        Time time() const;

        std::string to_string() const override;

        bool operator>(const Datetime& other) const;
        bool operator>=(const Datetime& other) const;
        bool operator<(const Datetime& other) const;
        bool operator<=(const Datetime& other) const;
        bool operator==(const Datetime& other) const;
        bool operator!=(const Datetime& other) const;

        Datetime& operator++(int) override;
        Datetime& operator--(int) override;
        Datetime& operator+=(const Day& days) override;
        Datetime& operator-=(const Day& days) override;
        Datetime& operator+=(const Hour& hours) override;
        Datetime& operator-=(const Hour& hours) override;
        Datetime& operator+=(const Minute& minutes) override;
        Datetime& operator-=(const Minute& minutes) override;
        Datetime& operator+=(const Second& seconds) override;
        Datetime& operator-=(const Second& seconds) override;
        Datetime& operator+=(const Millisecond& milliseconds) override;
        Datetime& operator-=(const Millisecond& milliseconds) override;
        Datetime& operator+=(const Microsecond& microseconds) override;
        Datetime& operator-=(const Microsecond& microseconds) override;
        Datetime& operator+=(const Nanosecond& nanoseconds) override;
        Datetime& operator-=(const Nanosecond& nanoseconds) override;
};

#endif //DATETIME_DATETIME_H
