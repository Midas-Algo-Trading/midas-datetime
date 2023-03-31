#ifndef DATETIME_SECOND_H
#define DATETIME_SECOND_H


#include "../TimeComponent.h"

class Second : public TimeComponent
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

        Second(int hours, Horologe* owner) : TimeComponent(hours, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Second(long long nanoseconds, Horologe* owner) : TimeComponent(nanoseconds, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Second() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};


#endif //DATETIME_SECOND_H
