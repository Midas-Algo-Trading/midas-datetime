#include <ctime>
#include "Date.h"
#include "../util/string_util.h"

Date Date::today()
{
        // Get the current time
        std::time_t current_time = std::time(nullptr);
        // Convert the current time to a tm
        std::tm* now = std::localtime(&current_time);
        // Extract the year, month, day
        int year = now->tm_year + 1900;  // tm_year is years since 1900
        int month = now->tm_mon + 1;  // tm_mon is 0-indexed
        int day = now->tm_mday;
        return Date(year, month, day);
}

std::ostream &operator<<(std::ostream &os, const Date &date)
{
        return os;
//        << date.year
//        << "-"
//        << lpad(std::to_string(date.month), 2, '0')
//        << "-"
//        << lpad(std::to_string(date.day), 2, '0');

}