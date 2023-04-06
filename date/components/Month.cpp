#include "Month.h"

int Month::COMPONENT_IDX = 1;

int Month::max_value()
{
        return DatetimeComponent::max_value();
}

int Month::max_days() const
{
        switch (value)
        {
                case 2:
                        return 1;
//                        return owner->year.is_leap_year() ? 29 : 28;
                case 4:
                case 6:
                case 9:
                case 11:
                        return 30;
                default:
                        return 31;
        }
}
