#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H


#include "../DatetimeComponent.h"

class TimeComponent : protected DatetimeComponent
{
public:
        friend class Time;

private:
        Time* owner{};

public:
        TimeComponent(int value, int component_idx, Time* owner) :
                DatetimeComponent(value, component_idx), owner(owner) {}

        TimeComponent() = default;

        int min_value() override;

private:
        void inc(int inc_amount) override;

        void dec(int dec_amount) override;
};


#endif //DATETIME_TIMECOMPONENT_H
