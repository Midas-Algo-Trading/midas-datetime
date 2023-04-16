#include <iostream>
#include "time/Time.h"

int main()
{
        Time now = Time();
        for (int i = 0; i < 1000; i++) {
                now += Nanosecond(1);
        }
        std::cout << now << std::endl;
}
