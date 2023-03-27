#ifndef DATETIME_MICROSECOND_H
#define DATETIME_MICROSECOND_H


#include "../TimeComponent.h"

class Microsecond : public TimeComponent
{
public:
        friend class Time;

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Microsecond(int hours, Time* owner) : TimeComponent(hours, 1, owner) {}

        Microsecond() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};



#endif //DATETIME_MICROSECOND_H
