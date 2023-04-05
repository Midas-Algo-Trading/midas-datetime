#include <iostream>
#include "time/Time.h"

int main()
{
//    Date today = Date(2022, 1, 1);
//    today++;
//    std::cout << today << std::endl;

        Time now = Time();
        for (int i = 999; i < 10000; i++) {
                now.nanoseconds++;
                std::cout << i << std::endl;
        }
        std::cout << now << std::endl;
}
