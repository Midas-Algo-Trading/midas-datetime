#include "Year.h"

int Year::COMPONENT_IDX = 2;


int Year::max_value()
{
        return DatetimeComponent::max_value();
}

bool Year::is_leap_year() const
{
        if (value % 4 != 0)
                return false;

        else if (value % 100 != 0)
                return true;

        else if (value % 400 != 0)
                return false;

        else
                return true;
}
