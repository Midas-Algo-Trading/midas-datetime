#ifndef DATETIME_TIME_H
#define DATETIME_TIME_H

#include <stdexcept>
#include "components/Hour.h"
#include "components/Minute.h"
#include "components/Second.h"
#include "components/Microsecond.h"
#include "components/Nanosecond.h"
#include "../Horologe.h"

class Time : public Horologe
{
public:
        Hour hours{};
        Minute minutes{};
        Second seconds{};
        Microsecond microseconds{};
        Nanosecond nanoseconds{};

public:
        //////////////////////////////////////////////////
        // Constructors
        //////////////////////////////////////////////////

        explicit Time(int hour=0, int minute=0, int second=0, int microsecond=0, int nanosecond=0) :
                hours(Hour(hour, this)),
                minutes(Minute(minute, this)),
                seconds(Second(second, this)),
                microseconds(Microsecond(microsecond, this)),
                nanoseconds(Nanosecond(nanosecond, this)) {}

        static Time now();
};


#endif //DATETIME_TIME_H
