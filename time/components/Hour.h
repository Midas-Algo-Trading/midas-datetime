#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "../TimeComponent.h"

class Hour : public TimeComponent
{
public:
        friend class Time;

        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        Hour(int hours, Horologe* owner) : TimeComponent(hours, 1, owner) {}

        Hour() = default;

        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        int max_value() override;

protected:
        //////////////////////////////////////////////////
        // Methods
        //////////////////////////////////////////////////

        void inc(int inc_amount) override;

        void dec(int dec_amount) override;
};


#endif //DATETIME_HOUR_H
