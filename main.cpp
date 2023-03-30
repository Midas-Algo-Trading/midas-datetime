#include <iostream>
#include "time/Time.h"

int main()
{
//    Date today = Date(2022, 1, 1);
//    today++;
//    std::cout << today << std::endl;

        Time now = Time::now();
        now.nanoseconds++;
        std::cout << now.nanoseconds << std::endl;
}
