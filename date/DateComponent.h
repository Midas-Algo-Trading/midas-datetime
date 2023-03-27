#ifndef DATETIME_DATECOMPONENT_H
#define DATETIME_DATECOMPONENT_H


#include "../DatetimeComponent.h"

class DateComponent : protected DatetimeComponent
{
public:
        friend class Date;

private:
        Date* owner{};

public:
        DateComponent(int value, int component_idx, Date* owner) :
                DatetimeComponent(value, component_idx), owner(owner) {}

        DateComponent() = default;

        int min_value() override;
};


#endif //DATETIME_DATECOMPONENT_H
