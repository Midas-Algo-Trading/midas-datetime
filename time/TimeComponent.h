#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H


#include "../DatetimeComponent.h"

class Time;

class TimeComponent : public DatetimeComponent
{
private:
        long long nanoseconds_per;

public:
        TimeComponent(int time, int component_idx, Horologe* owner, long long nanoseconds_per) :
                DatetimeComponent(time, component_idx, owner), nanoseconds_per(nanoseconds_per) {}

        TimeComponent(long long nanoseconds, int component_idx, Horologe* owner, long long nanoseconds_per);

        TimeComponent() = default;

        int min_value() override;

protected:
        long long to_nanoseconds() const;
};


#endif //DATETIME_TIMECOMPONENT_H
