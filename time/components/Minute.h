#ifndef DATETIME_MINUTE_H
#define DATETIME_MINUTE_H


#include "../TimeComponent.h"

class Minute : public TimeComponent
{
public:
        friend class Time;

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Minute(int hours, Horologe* owner) : TimeComponent(hours, 1, owner) {}

        Minute() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;
};

#endif //DATETIME_MINUTE_H
