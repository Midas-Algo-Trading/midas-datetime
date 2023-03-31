#ifndef DATETIME_NANOSECOND_H
#define DATETIME_NANOSECOND_H


#include "../TimeComponent.h"

class Time;

class Nanosecond : public TimeComponent
{
private:
        static long long NANOSECONDS_PER;
        static int COMPONENT_IDX;

public:
        Nanosecond(int hours, Horologe* owner) : TimeComponent(hours, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Nanosecond(long long nanoseconds, Horologe* owner) : TimeComponent(nanoseconds, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Nanosecond() = default;

        int max_value() override;
};

#endif //DATETIME_NANOSECOND_H
