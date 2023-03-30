#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H


#include "../DatetimeComponent.h"

class Time;

class TimeComponent : public DatetimeComponent
{
public:
        TimeComponent(int time, int component_idx, Horologe* owner) :
                DatetimeComponent(time, component_idx, owner) {}

        TimeComponent() = default;

        int min_value() override;
};


#endif //DATETIME_TIMECOMPONENT_H
