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

void DatetimeComponent::inc(int inc_amount)
{
        while (inc_amount > 0)
        {
                value++;

                // Update next component if need be
                if (value > max_value())
                {
                        // Increment the next component
                        DatetimeComponent* next_component = owner->get_component_by_idx(component_idx+1);
                        (*next_component)++;
                        value -= max_value();
                }

                inc_amount--;
        }
}

void DatetimeComponent::dec(int dec_amount)
{
        while (dec_amount < 0)
        {
                value--;

                // Update next component if need be
                if (value < min_value())
                {
                        // Decrement the previous component
                        DatetimeComponent* previous_component = owner->get_component_by_idx(component_idx-1);
                        (*previous_component)--;
                        value -= max_value();
                }

                dec_amount++;
        }
}
