#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "../TimeComponent.h"

class Hour : TimeComponent
{
public:
        friend class Time;

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Hour(int hours, Time* owner) : TimeComponent(hours, 1, owner) {}

        Hour() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;

private:
        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        void inc(int inc_amount) override;

        void dec(int dec_amount) override;
};


#endif //DATETIME_HOUR_H
