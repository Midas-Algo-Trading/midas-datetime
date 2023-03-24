#include "date/date.h"
#include <iostream>

int main()
{
    Date today = Date(2022, 1, 1);
    today++;
    std::cout << today << std::endl;
}
