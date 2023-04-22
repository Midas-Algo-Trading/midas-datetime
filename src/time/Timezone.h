#ifndef DATETIME_TIMEZONE_H
#define DATETIME_TIMEZONE_H

#include <iostream>
#include <chrono>

struct Timezone
{
public:
        int utc_offset;

        explicit Timezone(int utc_offset) : utc_offset(utc_offset) {}

        int get_utc_offset_diff(Timezone other) const
        {
                return utc_offset - other.utc_offset;
        }

        bool operator==(const Timezone& other) const
        {
                return utc_offset == other.utc_offset;
        }

        bool operator!=(const Timezone& other) const
        {
                return utc_offset != other.utc_offset;
        }
};

namespace TZ
{

        const Timezone UTC = Timezone(0);
        const Timezone PST = Timezone(8);
        const Timezone CST = Timezone(6);
        const Timezone EST = Timezone(5);

        static Timezone get_from_str(std::string_view timezone_string)
        {
                if (timezone_string == "Coordinated Universal Time")
                        return UTC;
                else if (timezone_string == "Pacific Standard Time")
                        return TZ::PST;
                else if (timezone_string == "Central Daylight Time")
                        return TZ::CST;
                else if (timezone_string == "Eastern Standard Time")
                        return TZ::EST;
                throw std::invalid_argument(std::string(timezone_string) + " is not a valid timezone string");
        }

        static Timezone get_local_tz()
        {
                // Get the current system time
                std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
                // Convert the system time to a std::time_t object
                std::time_t now_time_t = std::chrono::system_clock::to_time_t(now);
                // Convert the std::time_t object to a std::tm object
                std::tm* now_tm = std::localtime(&now_time_t);
                // Get the name of the local timezone
                char timezone_name[128];
                std::strftime(timezone_name, sizeof(timezone_name), "%Z", now_tm);

                return get_from_str(timezone_name);
        }

        const Timezone LOCAL = get_local_tz();
}

#endif //DATETIME_TIMEZONE_H
