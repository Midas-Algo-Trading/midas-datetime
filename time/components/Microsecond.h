#ifndef DATETIME_MICROSECOND_H
#define DATETIME_MICROSECOND_H


#include "../TimeComponent.h"

class Microsecond : public TimeComponent
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

        Microsecond(int hours, Horologe* owner) : TimeComponent(hours, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Microsecond(long long nanoseconds, Horologe* owner) : TimeComponent(nanoseconds, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Microsecond() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};



#endif //DATETIME_MICROSECOND_H
