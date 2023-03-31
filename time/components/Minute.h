#ifndef DATETIME_MINUTE_H
#define DATETIME_MINUTE_H


#include "../TimeComponent.h"

class Minute : public TimeComponent
{
public:
        friend class Time;

private:
        static long long NANOSECONDS_PER;
        static int COMPONENT_IDX;

public:

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Minute(int hours, Horologe* owner) : TimeComponent(hours, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Minute(long long nanoseconds, Horologe* owner) : TimeComponent(nanoseconds, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Minute() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};

#endif //DATETIME_MINUTE_H
