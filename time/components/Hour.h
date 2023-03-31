#ifndef DATETIME_HOUR_H
#define DATETIME_HOUR_H

#include "../TimeComponent.h"

class Hour : public TimeComponent
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

        Hour(int hours, Horologe* owner) : TimeComponent(hours, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

        Hour(long long nanoseconds, Horologe* owner) : TimeComponent(nanoseconds, COMPONENT_IDX, owner, NANOSECONDS_PER) {}

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
