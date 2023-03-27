#include "DatetimeComponent.h"

//////////////////////////////////////////////////
// Public Operators
//////////////////////////////////////////////////

DatetimeComponent DatetimeComponent::operator++(int)
{
        change_value(1);
        return *this;
}

DatetimeComponent DatetimeComponent::operator--(int)
{
        change_value(-1);
        return *this;
}

DatetimeComponent DatetimeComponent::operator+=(int change_amount)
{
        change_value(change_amount);
        return *this;
}

DatetimeComponent DatetimeComponent::operator-=(int change_amount)
{
        change_value(change_amount);
        return *this;
}

DatetimeComponent::operator int() const
{
        return value;
}

//////////////////////////////////////////////////
// Private Methods
//////////////////////////////////////////////////

void DatetimeComponent::change_value(int change_by)
{
        if (change_by >= 0)
        {
                inc(change_by);
        }
        else
        {
                dec(change_by);
        }
}
