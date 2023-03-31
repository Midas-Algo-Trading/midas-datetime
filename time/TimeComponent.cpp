#include "TimeComponent.h"

//////////////////////////////////////////////////
// Public Constructors
//////////////////////////////////////////////////

TimeComponent::TimeComponent(long long nanoseconds, int component_idx, Horologe* owner, long long nanoseconds_per)
{
        value = (int) (nanoseconds % nanoseconds_per);
        component_idx = component_idx;
        owner = owner;
        this->nanoseconds_per = nanoseconds_per;
}

//////////////////////////////////////////////////
// Public Methods
//////////////////////////////////////////////////

int TimeComponent::min_value()
{
        return 1;
}

//////////////////////////////////////////////////
// Private Methods
//////////////////////////////////////////////////

long long TimeComponent::to_nanoseconds() const
{
        return value * nanoseconds_per;
}
