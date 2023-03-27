#include "TimeComponent.h"
#include "Time.h"

//////////////////////////////////////////////////
// Private Methods
//////////////////////////////////////////////////

void TimeComponent::inc(int inc_amount)
{
        for (int i = 0; i < inc_amount; i++)
        {
                value++;

                // Update next component if need be
                if (value >= max_value())
                {
                        // Increment the next component
                        TimeComponent next_component = owner->get_component_by_idx(component_idx+1);
                        next_component++;
                        value -= next_component.max_value();
                }
        }
}

void TimeComponent::dec(int dec_amount)
{
        for (int i = 0; i < dec_amount*-1; i++)
        {
                value--;

                // Update next component if need be
                if (value >= min_value())
                {
                        // Decrement the previous component
                        TimeComponent previous_component = owner->get_component_by_idx(component_idx-1);
                        previous_component--;
                        value += previous_component.max_value();
                }
        }
}

int TimeComponent::min_value()
{
        return 1;
}
