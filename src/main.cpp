#include <iostream>
#include "time/Time.h"
#include "date/Date.h"

int main()
{
        Time::set_default_timezone(TZ::CST);
        Time now = Time::now();
//        for (int i = 0; i < 1000; i++) {
//                now += Nanosecond(1);
//        }
        std::cout << now << std::endl;
        now.set_timezone(TZ::UTC);
        std::cout << now << std::endl;

        Time one = Time(1, 5, 0, 0, 0, 0, TZ::CST);
        Time two = Time(2, 5, 0, 0, 0, 0, TZ::EST);
        std::cout << (one == two) << std::endl;

        Date today = Date::today();
        std::cout << today << std::endl;
}
