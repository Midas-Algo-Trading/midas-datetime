#include "date.h"
#include "../util/string_util.h"

//////////////////////////////////////////////////
// Public Constructors
//////////////////////////////////////////////////

Date::Date()
{
        // Get the current Time
        auto now = std::chrono::system_clock::now();
        std::time_t t = std::chrono::system_clock::to_time_t(now);

        // Convert the system Time to a std::tm struct
        std::tm *now_tm = std::localtime(&t);

        // Set the year, month, and day member variables
        year = Year(now_tm->tm_year + 1900);
        month = Month(now_tm->tm_mon + 1, this);
        day = Day(now_tm->tm_mday, this);
}

Date::Date(int year, int month, int day) : year(Year(year)), month(Month(month, this)), day(Day(day, this)) {}

//////////////////////////////////////////////////
// Public Operators
//////////////////////////////////////////////////

Date Date::operator++(int)
{
        day++;
        return *this;
}

Date Date::operator--(int)
{
        day--;
        return *this;
}

Date Date::operator+=(int change_amount)
{
        day += change_amount;
        return *this;
}

Date Date::operator-=(int change_amount)
{
        day -= change_amount;
        return *this;

}

//////////////////////////////////////////////////
// Public Friend Methods
//////////////////////////////////////////////////

std::ostream &operator<<(std::ostream &os, const Date &date)
{
    return os << date.year << '-' << lpad(std::to_string(date.month), 2, '0') << '-' << lpad(std::to_string(date.day), 2, '0');
}
