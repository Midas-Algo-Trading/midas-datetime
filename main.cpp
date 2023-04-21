#include <iostream>
#include "time/Time.h"

int main()
{
        Time::set_default_timezone(CST);
        Time now = Time::now();
//        for (int i = 0; i < 1000; i++) {
//                now += Nanosecond(1);
//        }
        std::cout << now << std::endl;
        now.set_timezone(UTC);
        std::cout << now << std::endl;
}
