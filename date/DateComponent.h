#ifndef DATETIME_DATECOMPONENT_H
#define DATETIME_DATECOMPONENT_H

#include "../DatetimeComponent.h"

class DateComponent : public DatetimeComponent
{
public:
        DateComponent(int date, int component_idx, Horologe* owner) :
                DatetimeComponent(date, component_idx, owner) {}

        DateComponent() = default;
};


#endif //DATETIME_DATECOMPONENT_H
