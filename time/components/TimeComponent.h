#ifndef DATETIME_TIMECOMPONENT_H
#define DATETIME_TIMECOMPONENT_H


#include "../../Duration.h"

class TimeComponent : public Duration
{
private:
        int value;

public:
        TimeComponent(int value, uint64_t n_nanoseconds) :
                value(value), Duration(value * n_nanoseconds) {}

        operator int() const override
        {
                return value;
        }

        TimeComponent& operator+=(int inc_by)
        {
                value += inc_by;
        }

        TimeComponent& operator-=(int dec_by)
        {
                value -= dec_by;
        }
};



#endif //DATETIME_TIMECOMPONENT_H
