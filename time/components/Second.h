#ifndef DATETIME_SECOND_H
#define DATETIME_SECOND_H


#include "../TimeComponent.h"

class Second : public TimeComponent
{
public:
        friend class Time;

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Second(int hours, Time* owner) : TimeComponent(hours, 1, owner) {}

        Second() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};


#endif //DATETIME_SECOND_H
