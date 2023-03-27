#ifndef DATETIME_NANOSECOND_H
#define DATETIME_NANOSECOND_H


#include "../TimeComponent.h"

class Time;

class Nanosecond : public TimeComponent
{
public:
//        friend class Time;

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Nanosecond(int hours, Time* owner) : TimeComponent(hours, 1, owner) {}

        Nanosecond() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};

#endif //DATETIME_NANOSECOND_H
